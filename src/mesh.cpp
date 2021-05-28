#include "mesh.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <cmath>
#include <iostream>
#include <fstream>

#include <sstream>

using namespace std;
using namespace glm;
using namespace agl;

Mesh::Mesh()
{
	vertices = 0;
	faces = 0;
	min_bound = glm::vec3(0);
	max_bound = glm::vec3(0);
	pos_arr = NULL;
	norm_arr = NULL;
	ind_arr = NULL;
}

Mesh::~Mesh()
{
	delete[] pos_arr;
	delete[] norm_arr;
	delete[] ind_arr;
}
bool Mesh::loadPLY(const std::string& filename)
{
	delete[] pos_arr;
	delete[] norm_arr;
	delete[] ind_arr;

	ifstream file(filename);
	if (!file) {
		file.close();
		return false;
	}

	string next;

	while (next != "element") {
		file >> next;
	}
	file >> next; 
	file >> vertices;

	while (next != "element") {
		file >> next;
	}
	file >> next; 
	file >> faces;

	while (next != "end_header") {
		file >> next;
	}

	pos_arr = new float[3 * vertices];
	norm_arr = new float[3 * vertices];
	ind_arr = new unsigned int[3 * faces];

	string line;
	
	for (int i = 0; i < vertices; i++) {

		file >> pos_arr[3 * i];
		file >> pos_arr[3 * i + 1];
		file >> pos_arr[3 * i + 2];
		file >> norm_arr[3 * i];
		file >> norm_arr[3 * i + 1];
		file >> norm_arr[3 * i + 2];

		if (filename == "cube.ply" || filename == "pyramid.ply" || filename == "sphere.ply") {
			file >> next; 
			file >> next; 
		}

		if (i == 0) {
			min_bound.x = pos_arr[0];
			min_bound.y = pos_arr[1];
			min_bound.z = pos_arr[2];
			max_bound.x = pos_arr[0];
			max_bound.y = pos_arr[1];
			max_bound.z = pos_arr[2];
		}
		else {
			if (pos_arr[3 * i] < min_bound.x) 
				min_bound.x = pos_arr[3 * i];
			if (pos_arr[3 * i + 1] < min_bound.y) 
				min_bound.y = pos_arr[3 * i + 1];
			if (pos_arr[3 * i + 2] < min_bound.z) 
				min_bound.z = pos_arr[3 * i + 2];
			if (pos_arr[3 * i] > max_bound.x) 
				max_bound.x = pos_arr[3 * i];
			if (pos_arr[3 * i + 1] > max_bound.y) 
				max_bound.y = pos_arr[3 * i + 1];
			if (pos_arr[3 * i + 2] > max_bound.z) 
				max_bound.z = pos_arr[3 * i + 2];
		}
	}

	for (int i = 0; i < faces; i++) {
		file >> next; 
		file >> ind_arr[3 * i];
		file >> ind_arr[3 * i + 1];
		file >> ind_arr[3 * i + 2];
	}

	cout << filename << endl;
	return true;
}

glm::vec3 Mesh::getMinBounds() const
{
	return min_bound;
}

glm::vec3 Mesh::getMaxBounds() const
{
	return max_bound;
}

int Mesh::numVertices() const
{
	return vertices;
}

int Mesh::numTriangles() const
{
	return faces;
}

float* Mesh::positions() const
{
	return pos_arr;
}

float* Mesh::normals() const
{
	return norm_arr;
}

unsigned int* Mesh::indices() const
{
	return ind_arr;
}