
#include "mesh.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <cmath>
#include <iostream>
#include <fstream>

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
	ifstream file(filename);
	if (!file) return false;

	string curr; 
	file >> curr;
	if (curr != "ply") return false;

	while (curr != "vertex") file >> curr;
	file >> vertices;
	while (curr != "face") file >> curr;
	file >> faces;
	while (curr != "end_header") file >> curr;

	pos_arr = new float[vertices * 3];
	norm_arr = new float[vertices * 3];
	ind_arr = new unsigned int[faces * 3];

	for (int i = 0; i < vertices; i++) {
		//vector
		file >> pos_arr[3 * i];
		float xval = pos_arr[3 * i];
		file >> pos_arr[3 * i + 1];
		float yval = pos_arr[3 * i + 1];
		file >> pos_arr[3 * i + 2];
		float zval = pos_arr[3 * i + 2];
		//normal 
		file >> norm_arr[3 * i];
		file >> norm_arr[3 * i + 1];
		file >> norm_arr[3 * i + 2];

		if (i == 0) {
			 min_bound = glm::vec3(pos_arr[0], pos_arr[1], pos_arr[2]);
			 max_bound = glm::vec3(pos_arr[0], pos_arr[1], pos_arr[2]);
		}
		else {
			//check min
			if (xval < min_bound.x) min_bound.x = xval;
			if (yval < min_bound.y) min_bound.y = yval;
			if (zval < min_bound.z) min_bound.z = zval;
			//check max
			if (xval > max_bound.x) max_bound.x = xval;
			if (yval > max_bound.y) max_bound.y = yval;
			if (zval > max_bound.z) max_bound.z = zval;
		}
	}

	for (int i = 0; i < faces; i++) {
		file >> curr;
		file >> ind_arr[3 * i];
		file >> ind_arr[3 * i + 1];
		file >> ind_arr[3 * i + 2];
	}
	file.close();
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

