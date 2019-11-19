#include "ModuleImport.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include "ModuleResources.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment ( lib, "DevIL/libx86/ILU.lib" )
#pragma comment ( lib, "DevIL/libx86/ILUT.lib" )

#include <gl/GL.h>

ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleImport::~ModuleImport()
{
}


bool ModuleImport::Start()
{
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	GLubyte checkImage[500][500][4];
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &checkerImageID);
	glBindTexture(GL_TEXTURE_2D, checkerImageID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	ImportFBX("Assets\\Models\\Street environment_V01.FBX");
	/*ImportTexture("Assets\\Textures\\Baker_house.png");*/


	return ret;
}

void ModuleImport::ImportFBX(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* newGameObject = App->sceneIntro->current_object = LoadMeshNode(scene, scene->mRootNode, App->game_object->root, path);

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", path);
}

GameObject* ModuleImport::LoadMeshNode(const aiScene * scene, aiNode * node, GameObject * parent, const char* path)
{
	GameObject* go = new GameObject(parent, node->mName.C_Str());
	
	if (node->mNumMeshes > 0)
	{
		aiMesh* new_mesh = scene->mMeshes[node->mMeshes[0]];

		std::string _path = path;
		std::string _name = node->mName.C_Str();

		ResourceMesh* m = (ResourceMesh*)App->resources->GetResource(ResourceType::Mesh, (_path + _name).c_str());
		if (m == nullptr)
		{
			m = new ResourceMesh((_path + _name).c_str());
			m->vertex.size = new_mesh->mNumVertices * 3;
			m->vertex.data = new float[m->vertex.size];
			memset(m->vertex.data, 0, sizeof(float) * m->vertex.size);
			memcpy(m->vertex.data, new_mesh->mVertices, sizeof(float) * m->vertex.size);
			LOG("New mesh with %d vertices", m->vertex.size);

			//Load bounding box
			go->originalBoundingBox.Enclose((float3*)m->vertex.data, m->vertex.size/3);
			go->boundingBox = go->originalBoundingBox;

			if (new_mesh->HasFaces())
			{
				m->index.size = new_mesh->mNumFaces * 3;
				m->index.data = new uint[m->index.size];
				memset(m->index.data, 0, sizeof(float) * m->index.size);
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}

					else
					{
						memcpy(&m->index.data[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}
			}
			if (new_mesh->HasTextureCoords(m->uvs.id))
			{
				m->uvs.size = new_mesh->mNumVertices * 2;
				m->uvs.data = new float[m->uvs.size];

				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m->uvs.data[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m->uvs.data[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}

				glGenBuffers(1, (GLuint*)&(m->uvs.id));
				glBindBuffer(GL_ARRAY_BUFFER, m->uvs.id);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->uvs.size, m->uvs.data, GL_STATIC_DRAW);
			}

			if (new_mesh->HasNormals()) {
				m->hasNormals = true;
				m->normals.size = new_mesh->mNumVertices * 3;
				m->normals.data = new float[m->normals.size];
				memcpy(m->normals.data, new_mesh->mNormals, sizeof(float) * m->normals.size);
			}
			glGenBuffers(1, (GLuint*) & (m->vertex.id));
			glBindBuffer(GL_ARRAY_BUFFER, m->vertex.id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->vertex.size, m->vertex.data, GL_STATIC_DRAW);

			glGenBuffers(1, (GLuint*) & (m->index.id));
			glBindBuffer(GL_ARRAY_BUFFER, m->index.id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->index.size, m->index.data, GL_STATIC_DRAW);

			App->resources->AddResource(m);
		}
		else
		{
			App->resources->ResourceUsageIncreased(m);
		}

		if (scene->HasMaterials())
		{
			aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];

			if (material)
			{
				aiString textName;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &textName);

				std::string textPath(textName.data);

				textPath = textPath.substr(textPath.find_last_of("\\") + 1);

				textPath = "Assets\\Textures\\" + textPath;

				ImportTexture(textPath.c_str(), go);
			}
		}
		
		ComponentMesh* newMesh = new ComponentMesh(go);
		newMesh->mesh = m;
		
		SaveMeshImporter(m, newMesh->uuid);

		App->renderer3D->mesh_list.push_back(newMesh);
		LOG("Mesh loaded");
	}

	float4x4 transformMat(
		node->mTransformation.a1, node->mTransformation.a2, node->mTransformation.a3, node->mTransformation.a4,
		node->mTransformation.b1, node->mTransformation.b2, node->mTransformation.b3, node->mTransformation.b4,
		node->mTransformation.c1, node->mTransformation.c2, node->mTransformation.c3, node->mTransformation.c4,
		node->mTransformation.d1, node->mTransformation.d2, node->mTransformation.d3, node->mTransformation.d4);

	go->transform->SetTransform(transformMat);

	for (int child = 0; child < node->mNumChildren; ++child)
	{
		LoadMeshNode(scene, node->mChildren[child], go, path);
	}
	return go;
}

void ModuleImport::SaveMeshImporter(ResourceMesh* m, const uint &uuid, char* path)
{
	uint ranges[4] = { m->index.size, m->vertex.size, m->normals.size, m->uvs.size };
	float size = 
		sizeof(ranges) +
		sizeof(uint) * m->index.size +
		sizeof(float) * m->vertex.size +
		sizeof(float) * m->normals.size +
		sizeof(float) * m->uvs.size;

	char* meshBuffer = new char[size];
	char* cursor = meshBuffer;

	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);

	cursor += bytes;
	bytes = sizeof(uint) * m->index.size;
	memcpy(cursor, m->index.data, bytes);

	cursor += bytes;
	bytes = sizeof(float) * m->vertex.size;
	memcpy(cursor, m->vertex.data, bytes);

	if (m->normals.data)
	{
		cursor += bytes;
		bytes = sizeof(float) * m->normals.size;
		memcpy(cursor, m->normals.data, bytes);
	}

	if (m->uvs.data)
	{
		cursor += bytes;
		bytes = sizeof(float) * m->uvs.size;
		memcpy(cursor, m->uvs.data, bytes);
	}

	App->resources->SaveFile(size, meshBuffer, ResourceType::Mesh, uuid, path);

	delete[] meshBuffer;
}

void ModuleImport::LoadMeshImporter(ResourceMesh* m, const uint &uuid, char* buff)
{
	uint ranges[4];

	char* cursor = buff;

	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	m->index.size = ranges[0];
	m->vertex.size = ranges[1];
	m->normals.size = ranges[2];
	m->uvs.size = ranges[3];

	cursor += bytes;
	bytes = sizeof(uint) * m->index.size;
	m->index.data = new uint[m->index.size];
	memcpy(m->index.data, cursor, bytes);

	glGenBuffers(1, (GLuint*) & (m->index.id));
	glBindBuffer(GL_ARRAY_BUFFER, m->index.id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->index.size, m->index.data, GL_STATIC_DRAW);

	cursor += bytes;
	bytes = sizeof(float) * m->vertex.size;
	m->vertex.data = new float[m->vertex.size];
	memcpy(m->vertex.data, cursor, bytes);

	glGenBuffers(1, (GLuint*) & (m->vertex.id));
	glBindBuffer(GL_ARRAY_BUFFER, m->vertex.id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->vertex.size, m->vertex.data, GL_STATIC_DRAW);

	cursor += bytes;
	bytes = sizeof(float) * m->normals.size;
	m->normals.data = new float[m->normals.size];
	memcpy(m->normals.data, cursor, bytes);

	cursor += bytes;
	bytes = sizeof(float) * m->uvs.size;
	m->uvs.data = new float[m->uvs.size];
	memcpy(m->uvs.data, cursor, bytes);

	glGenBuffers(1, (GLuint*)&(m->uvs.id));
	glBindBuffer(GL_ARRAY_BUFFER, m->uvs.id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->uvs.size, m->uvs.data, GL_STATIC_DRAW);
}

void ModuleImport::ImportTexture(const char* path)
{
	ResourceTexture* m = (ResourceTexture*)App->resources->GetResource(ResourceType::Texture, path);
	if (m == nullptr)
	{
		m = new ResourceTexture(path);
		uint texture_id = 0;

		RealLoadTexture(path, texture_id);
		m->id = texture_id;

		App->resources->AddResource(m);
	}
	else
	{
		App->resources->ResourceUsageIncreased(m);
	}

	if (App->sceneIntro->current_object->HasComponent(CompTexture))
	{
		ComponentTexture* texture = (ComponentTexture*)App->sceneIntro->current_object->GetComponent(CompTexture);
		App->resources->ResourceUsageDecreased(texture->RTexture);	
		std::string tex_path(path);
		texture->path = tex_path;
		texture->RTexture = m;
		LOG("Texture loaded");
	}
	else
	{
		ComponentTexture* texture = new ComponentTexture(App->sceneIntro->current_object);
		std::string tex_path(path);
		texture->path = tex_path;
		texture->RTexture = m;
		LOG("Texture loaded");
	}
}

void ModuleImport::RealLoadTexture(const char* path, uint &texture_id)
{
	ilInit();
	iluInit();
	ilutInit();
	if (ilLoadImage(path))
	{
		ilEnable(IL_FILE_OVERWRITE);

		ILuint size;
		ILubyte *data;

		ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
		size = ilSaveL(IL_DDS, NULL, 0);
		if (size > 0) {
			data = new ILubyte[size];
			if (ilSaveL(IL_DDS, data, size) > 0)
				App->resources->SaveFile(size, (char*)data, ResourceType::Texture, 0u, path);
		}

		uint id = 0;

		ilGenImages(1, &id);
		ilBindImage(id);
		ilLoadImage(path);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		texture_id = ilutGLBindTexImage();
		glBindTexture(GL_TEXTURE_2D, 0);
		ilDeleteImages(1, &id);
	}
	else
	{
		LOG("Couldn't load texture");
	}
}

void ModuleImport::ImportTexture(const char * path, GameObject * go)
{
	ResourceTexture* m = (ResourceTexture*)App->resources->GetResource(ResourceType::Texture, path);
	if (m == nullptr)
	{
		m = new ResourceTexture(path);

		ilInit();
		iluInit();
		ilutInit();
		if (ilLoadImage(path))
		{
			ilEnable(IL_FILE_OVERWRITE);

			ILuint size;
			ILubyte *data;

			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
			size = ilSaveL(IL_DDS, NULL, 0);
			if (size > 0) {
				data = new ILubyte[size];
				if (ilSaveL(IL_DDS, data, size) > 0)
					App->resources->SaveFile(size, (char*)data, ResourceType::Texture, 0u, path);
			}

			uint texture_id = 0;

			uint id = 0;

			ilGenImages(1, &id);
			ilBindImage(id);
			ilLoadImage(path);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			texture_id = ilutGLBindTexImage();
			glBindTexture(GL_TEXTURE_2D, 0);
			ilDeleteImages(1, &id);	

			m->id = texture_id;

			App->resources->AddResource(m);
		}
		else
		{
			LOG("Couldn't load texture: %s", path);
			return;
		}
	}
	else
	{
		App->resources->ResourceUsageIncreased(m);
	}

	if (go->HasComponent(CompTexture))
	{
		ComponentTexture* texture = (ComponentTexture*)go->GetComponent(CompTexture);
		App->resources->ResourceUsageDecreased(texture->RTexture);
		std::string tex_path(path);
		texture->path = tex_path;
		texture->RTexture = m;
		LOG("Texture loaded");
	}
	else
	{
		ComponentTexture* texture = new ComponentTexture(go);
		std::string tex_path(path);
		texture->path = tex_path;
		texture->RTexture = m;
		LOG("Texture loaded");
	}
}

update_status ModuleImport::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImport::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

ResourceMesh* ModuleImport::MeshParShape(par_shapes_mesh* mesh, const char* name)
{
	GameObject* go = new GameObject(App->game_object->root, name);

	ResourceMesh* m = (ResourceMesh*)App->resources->GetResource(ResourceType::Mesh, name);

	if (m == nullptr)
	{
		m = new ResourceMesh(name);

		m->vertex.size = mesh->npoints;
		m->vertex.data = new float[m->vertex.size * 3];
		memcpy(m->vertex.data, mesh->points, sizeof(float) * mesh->npoints * 3);

		m->index.size = mesh->ntriangles * 3;
		m->index.data = new uint[m->index.size];

		for (int i = 0; i < m->index.size; i++)
		{
			m->index.data[i] = (uint)mesh->triangles[i];
		}

		glGenBuffers(1, (GLuint*) &(m->vertex.id));
		glBindBuffer(GL_ARRAY_BUFFER, m->vertex.id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->vertex.size, m->vertex.data, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*) &(m->index.id));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->index.id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m->index.size, m->index.data, GL_STATIC_DRAW);

		App->resources->AddResource(m);
	}
	else
	{
		App->resources->ResourceUsageIncreased(m);
	}

	ComponentMesh* newMesh = new ComponentMesh(go);
	newMesh->mesh = m;

	App->renderer3D->mesh_list.push_back(newMesh);

	LOG("Par_Shapes Mesh loaded");

	return m;
}