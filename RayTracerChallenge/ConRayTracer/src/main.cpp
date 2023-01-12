// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <memory>
#include "utils.h"
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "environment.h"
#include "projectile.h"
#include "canvas.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "ray.h"
#include "intersection.h"
#include "hit.h"
#include "object.h"
#include "sphere.h"
#include "point-light.h"
#include "world.h"
#include "engine.h"
#include "camera.h"
#include "plane.h"

int main() {

	int res_x = 1280;
	int res_y = 720;

	World world = World(WorldType::EMPTY);

	Plane floor("floor", Matrix4().scaling(10.0f, 0.01f, 10.0f));
	Material floor_mat;
	floor_mat.SetColor(Color(1.0f, 0.9f, 0.9f));
	floor_mat.SetSpecular(0.0f);
	floor.SetMaterial(floor_mat);

	Sphere middle("middle", Matrix4().translation(-0.5f, 1.0f, 0.5f));
	Material middle_mat;
	middle_mat.SetColor(Color(0.1f, 1.0f, 0.5f));
	middle_mat.SetDiffuse(0.7f);
	middle_mat.SetSpecular(0.3f);
	middle.SetMaterial(middle_mat);

	Sphere right("right", Matrix4().translation(1.5f, 0.5f, -0.5f) * Matrix4().scaling(0.5f, 0.5f, 0.5f));
	Material right_mat;
	right_mat.SetColor(Color(0.5f, 1.0f, 0.1f));
	right_mat.SetDiffuse(0.7f);
	right_mat.SetSpecular(0.3f);
	right.SetMaterial(right_mat);

	Sphere left("left", Matrix4().translation(-1.5f, 0.33f, -0.75f) * Matrix4().scaling(0.33f, 0.33f, 0.33f));
	Material left_mat;
	left_mat.SetColor(Color(1.0f, 0.8f, 0.1f));
	left_mat.SetDiffuse(0.7f);
	left_mat.SetSpecular(0.3f);
	left.SetMaterial(left_mat);
	
	PointLight light(Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));

	Camera camera(res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 1.5f, -5.0f),
																							 Point(0.0f, 1.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));

	world.AddObject(&floor);
	world.AddObject(&middle);
	world.AddObject(&right);
	world.AddObject(&left);
	world.AddObject(&light);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);
	
	utils::ExportFile("render_test.ppm", image.ToPPM());
	
	std::cout << "\n\nPress any key to exit...";
	std::cin.get();
	return 0;
}
