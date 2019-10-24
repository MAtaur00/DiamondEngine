#include "Shapes.h"
#include "Application.h"
#include "ParShapes/par_shapes.h"

Shapes::Shapes()
{
}


Shapes::~Shapes()
{
}

void Shapes::Draw()
{
	if (ImGui::Begin("Inspector", &App->imgui->showShapes))
	{
		/*if (ImGui::Button("Sphere"))
		{
			par_shapes_mesh* shape = par_shapes_create_subdivided_sphere(3);
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Sphere");
		}

		ImGui::Separator();

		if (ImGui::Button("Cube"))
		{
			par_shapes_mesh* shape = par_shapes_create_cube();
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Cube");
		}

		ImGui::Separator();

		if (ImGui::Button("Cylinder"))
		{
			par_shapes_mesh* shape = par_shapes_create_cylinder(4, 4);
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Cylinder");
		}

		ImGui::Separator();

		if (ImGui::Button("Cone"))
		{
			par_shapes_mesh* shape = par_shapes_create_cone(4, 4);
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Cone");
		}

		ImGui::Separator();

		if (ImGui::Button("Knot"))
		{
			par_shapes_mesh* shape = par_shapes_create_trefoil_knot(4, 4, 2.0f);
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Knot");
		}

		ImGui::Separator();

		if (ImGui::Button("Torus"))
		{
			par_shapes_mesh* shape = par_shapes_create_torus(4, 4, 2.0f);
			Mesh* mesh = App->import->MeshParShape(shape);
			par_shapes_free_mesh(shape);

			GameObject* gameObject = new GameObject(NULL, "Torus");
		}*/
	}
	ImGui::End();
}
