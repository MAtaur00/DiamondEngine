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
	if (ImGui::Begin("Shapes", &App->imgui->showShapes))
	{
		if (ImGui::Button("Sphere"))
		{
			par_shapes_mesh* shape = par_shapes_create_subdivided_sphere(3);
			Mesh* mesh = App->import->MeshParShape(shape, "Sphere");
			par_shapes_free_mesh(shape);
		}

		ImGui::Separator();

		if (ImGui::Button("Cube"))
		{
			par_shapes_mesh* shape = par_shapes_create_cube();
			Mesh* mesh = App->import->MeshParShape(shape, "Cube");
			par_shapes_free_mesh(shape);
		}

		ImGui::Separator();

		if (ImGui::Button("Cylinder"))
		{
			par_shapes_mesh* shape = par_shapes_create_cylinder(15, 15);
			Mesh* mesh = App->import->MeshParShape(shape, "Cylinder");
			par_shapes_free_mesh(shape);
		}

		ImGui::Separator();

		if (ImGui::Button("Cone"))
		{
			par_shapes_mesh* shape = par_shapes_create_cone(15, 15);
			Mesh* mesh = App->import->MeshParShape(shape, "Cone");
			par_shapes_free_mesh(shape);
		}

		ImGui::Separator();

		if (ImGui::Button("Knot"))
		{
			par_shapes_mesh* shape = par_shapes_create_trefoil_knot(15, 15, 2.0f);
			Mesh* mesh = App->import->MeshParShape(shape, "Knot");
			par_shapes_free_mesh(shape);
		}

		ImGui::Separator();

		if (ImGui::Button("Torus"))
		{
			par_shapes_mesh* shape = par_shapes_create_torus(15, 15, 0.3f);
			Mesh* mesh = App->import->MeshParShape(shape, "Torus");
			par_shapes_free_mesh(shape);
		}
	}
	ImGui::End();
}
