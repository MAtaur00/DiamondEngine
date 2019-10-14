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

	m = new Mesh();

	return ret;
}

void ModuleImport::ImportFBX(const char* path)
{
	//"Assets/Models/Warrior.fbx"

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		//aiReleaseImport(scene);

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[i];

			m = new Mesh();
			// copy vertices

			m->vertex.size = new_mesh->mNumVertices;
			m->vertex.data = new float[m->vertex.size * 3];
			memcpy(m->vertex.data, new_mesh->mVertices, sizeof(float) * m->vertex.size * 3);
			LOG("New mesh with %d vertices", m->vertex.size);

			// copy faces
			if (new_mesh->HasFaces())
			{
				m->index.size = new_mesh->mNumFaces * 3;
				m->index.data = new uint[m->index.size]; // assume each face is a triangle
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
				m->uvs.size = new_mesh->mNumVertices;
				m->uvs.data = new float[m->uvs.size * 2];

				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m->uvs.data[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m->uvs.data[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}

				glGenBuffers(1, (GLuint*)&(m->uvs.id));
				glBindBuffer(GL_ARRAY_BUFFER, m->uvs.id);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m->uvs.size, m->uvs.data, GL_STATIC_DRAW);
			}
			if (new_mesh->HasNormals()) {
				m->normals.size = new_mesh->mNumVertices;
				m->normals.data = new float[m->normals.size * 3];
				memcpy(m->normals.data, new_mesh->mNormals, sizeof(float) * m->normals.size * 3);
			}
			glGenBuffers(1, (GLuint*) & (m->vertex.id));
			glBindBuffer(GL_ARRAY_BUFFER, m->vertex.id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->vertex.size, m->vertex.data, GL_STATIC_DRAW);

			glGenBuffers(1, (GLuint*) & (m->index.id));
			glBindBuffer(GL_ARRAY_BUFFER, m->index.id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->index.size, m->index.data, GL_STATIC_DRAW);

			App->renderer3D->mesh_list.push_back(m);
		}
	}
	else
		LOG("Error loading scene %s", path);
}

void ModuleImport::ImportTexture(const char* path)
{
	ilInit();
	iluInit();
	ilutInit();
	if (ilLoadImage(path))
	{
		uint id = 0;

		ilGenImages(1, &id);
		ilBindImage(id);
		ilLoadImage(path);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		tex_id = ilutGLBindTexImage();
		glBindTexture(GL_TEXTURE_2D, 0);
		ilDeleteImages(1, &id);
		LOG("Texture loaded");
	}
	else
	{
		LOG("Couldn't load texture");
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