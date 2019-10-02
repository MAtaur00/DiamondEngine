#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"

#pragma comment(lib, "Glew/libx86/glew32.lib")

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	glBegin(GL_TRIANGLES);



	//// Front face
	//glTexCoord2f(0, 0); glVertex3f(-1, 1, 1); // v1
	//glTexCoord2f(0, 1); glVertex3f(-1, -1, 1); // v2
	//glTexCoord2f(1, 1); glVertex3f(1, -1, 1); // v3
	//glTexCoord2f(0, 0); glVertex3f(-1, 1, 1); // v1
	//glTexCoord2f(0, 1); glVertex3f(-1, -1, 1); // v2
	//glTexCoord2f(1, 1); glVertex3f(1, 1, 1); // v0
	//// Left face
	//glTexCoord2f(0, 0); glVertex3f(1, 1, 1); // v0
	//glTexCoord2f(0, 1); glVertex3f(1, -1, 1); // v3
	//glTexCoord2f(1, 1); glVertex3f(1, -1, -1); // v4
	//glTexCoord2f(0, 0); glVertex3f(1, 1, 1); // v0
	//glTexCoord2f(1, 1); glVertex3f(1, -1, -1); // v4
	//glTexCoord2f(1, 0); glVertex3f(1, 1, -1); // v5
	//// Back face

	//// Right face
	GLfloat vertices[] =

		//front
	{ 1.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f, 

		//front2

		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		//right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		//right2
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 0.0f,

		//back
		1.0f, 0.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,


		//back2
		1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, -1.0f,


	
		//top
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,

		//top2
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, -1.0f,

		//left
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, -1.0f,

		//left2
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		//bottom
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,

		//bottom2
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,

	};

	
	glEnd();

	
	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, vertices, GL_STATIC_DRAW);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	PrimitivePlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// � draw other buffers
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

