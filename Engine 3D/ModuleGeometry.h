#include "Module.h"


class ModuleGeometry : public Module
{
public:
	ModuleGeometry(Application* app, bool start_enabled = true);
	~ModuleGeometry();

	bool Start();
	update_status Update(float dt);
	void Draw();
};

