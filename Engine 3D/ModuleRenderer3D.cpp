#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Primitive.h"
#include "ModuleCamera3D.h"

#include <gl/GL.h>


#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		LOG("Glew Error: ", glewGetErrorString(err));
	}
	else
	{
		LOG("Using Glew %s", glewGetString(GLEW_VERSION));
		LOG("Vendor: %s", glGetString(GL_VENDOR));
		LOG("Renderer: %s", glGetString(GL_RENDERER));
		LOG("OpenGL version supported %s", glGetString(GL_VERSION));
		LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	}
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glLoadMatrixf(App->camera->compCamera->GetProjectionMatrix().ptr());



	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->compCamera->GetViewMatrix().ptr());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->compCamera->frustum.pos.x, App->camera->compCamera->frustum.pos.y, App->camera->compCamera->frustum.pos.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	//Geometry
	for (std::vector<ComponentMesh*>::iterator it = mesh_list.begin(); it != mesh_list.end(); ++it)
	{
		(*it)->Draw();
	}
	
	//Debug Draw
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		drawBoxes = !drawBoxes;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	if (drawBoxes)
	{
		for (auto gameobject : App->game_object->gameObjects)
		{
			float3 corners[8];
			gameobject->boundingBox.GetCornerPoints(corners);

			glLineWidth(2.0f);

			if (gameobject == App->sceneIntro->current_object)
				glColor3f(0.0f, 1.0f, 0.0f);

			else
				glColor3f(0.0f, 0.0f, 1.0f);

			glBegin(GL_QUADS);

			glVertex3fv((GLfloat*)&corners[1]);
			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[7]);
			glVertex3fv((GLfloat*)&corners[3]);
								
			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[2]);
			glVertex3fv((GLfloat*)&corners[6]);
								
			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[6]);
			glVertex3fv((GLfloat*)&corners[7]);
								
			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[1]);
			glVertex3fv((GLfloat*)&corners[3]);
			glVertex3fv((GLfloat*)&corners[2]);

			glVertex3fv((GLfloat*)&corners[3]);
			glVertex3fv((GLfloat*)&corners[7]);
			glVertex3fv((GLfloat*)&corners[6]);
			glVertex3fv((GLfloat*)&corners[2]);

			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[1]);

			glEnd();
		}
	}

	else
	{
		if (App->sceneIntro->current_object)
		{
			float3 corners[8];
			App->sceneIntro->current_object->boundingBox.GetCornerPoints(corners);

			glLineWidth(2.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);

			glVertex3fv((GLfloat*)&corners[1]);
			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[7]);
			glVertex3fv((GLfloat*)&corners[3]);

			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[2]);
			glVertex3fv((GLfloat*)&corners[6]);

			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[6]);
			glVertex3fv((GLfloat*)&corners[7]);

			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[1]);
			glVertex3fv((GLfloat*)&corners[3]);
			glVertex3fv((GLfloat*)&corners[2]);

			glVertex3fv((GLfloat*)&corners[3]);
			glVertex3fv((GLfloat*)&corners[7]);
			glVertex3fv((GLfloat*)&corners[6]);
			glVertex3fv((GLfloat*)&corners[2]);

			glVertex3fv((GLfloat*)&corners[0]);
			glVertex3fv((GLfloat*)&corners[4]);
			glVertex3fv((GLfloat*)&corners[5]);
			glVertex3fv((GLfloat*)&corners[1]);

			glEnd();
		}
	}

	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_CULL_FACE);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		for (auto gameobject : App->game_object->gameObjects)
		{
			if (gameobject->HasComponent(Object_Type::CompTexture))
			{
				ComponentTexture* tex = (ComponentTexture*)gameobject->GetComponent(Object_Type::CompTexture);
				if (paintTextures)
				{
					tex->print = false;
				}
				else if (!paintTextures)
				{
					tex->print = true;
				}
			}
		}
		paintTextures = !paintTextures;
	}

	//UI
	App->imgui->Draw();



	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	App->window->width = width;
	App->window->height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (App->camera->compCamera)
		App->camera->compCamera->frustum.horizontalFov = 2.f * atan(tan(App->camera->compCamera->frustum.verticalFov * 0.5f) * (float(App->window->width) / App->window->height));
}