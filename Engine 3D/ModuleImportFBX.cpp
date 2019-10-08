#include "ModuleImportFBX.h"
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


#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include <gl/GL.h>

ModuleImportFBX::ModuleImportFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleImportFBX::~ModuleImportFBX()
{
}


bool ModuleImportFBX::Start() 
{
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

Mesh* ModuleImportFBX::Import(const char* path)
{
	//"Assets/Models/Warrior.fbx"

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", path);

	Mesh* m = new Mesh();
	aiMesh* new_mesh = scene->mMeshes[0];

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

	glGenBuffers(1, (GLuint*) &(m->id));
	glBindBuffer(GL_ARRAY_BUFFER, m->id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->vertex.size, m->vertex.data, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*) &(m->id));
	glBindBuffer(GL_ARRAY_BUFFER, m->id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->index.size, m->index.data, GL_STATIC_DRAW);

	return m;
}

update_status ModuleImportFBX::Update(float dt) 
{
	return UPDATE_CONTINUE;
}

bool ModuleImportFBX::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}