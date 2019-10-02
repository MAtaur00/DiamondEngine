#include "ModuleGeometry.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#include <gl/GL.h>

ModuleGeometry::ModuleGeometry(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGeometry::~ModuleGeometry()
{
}


bool ModuleGeometry::Start() {

	return ret;
}

void ModuleGeometry::Draw(){
	glBegin(GL_TRIANGLES);



	

	//// Right face
	GLfloat vertex[] =

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


	glEnd();

	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
}

update_status ModuleGeometry::Update(float dt) {

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// … draw other buffers
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	return UPDATE_CONTINUE;
}