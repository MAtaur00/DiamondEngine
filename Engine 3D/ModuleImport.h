#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "GameObject.h"
#include "ParShapes/par_shapes.h"

class Mesh;

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

	GameObject* LoadMeshNode(const aiScene* scene, aiNode* node, GameObject* parent);

	void ImportTexture(const char* path);

	void ImportTexture(const char* path, GameObject* go);

	bool CleanUp();

	Mesh* MeshParShape(par_shapes_mesh* mesh, const char* name);

public:

	uint checkerImageID = 0u;
	
};

