#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "GameObject.h"
#include "ParShapes/par_shapes.h"

class ResourceMesh;
class ResourceTexture;

struct aiScene;
struct aiNode;

class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	~ModuleImport();

	bool Start();
	update_status Update(float dt);

	void ImportFBX(const char* path);

	GameObject* LoadMeshNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* path);

	void SaveMeshImporter(ResourceMesh* m, const uint &uuid, char* path = nullptr);

	void SaveTextureImporter(ResourceTexture* m, const uint &uuid, char* path = nullptr);

	void ImportTexture(const char* path);

	void ImportTexture(const char* path, GameObject* go);

	bool CleanUp();

	ResourceMesh* MeshParShape(par_shapes_mesh* mesh, const char* name);

public:

	uint checkerImageID = 0u;
};

