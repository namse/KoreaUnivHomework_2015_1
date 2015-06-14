#include "stdafx.h"
#include "Cube.h"



Namse::Cube::Cube()
{
	Vertex[0] = new Namse::Vector(0.5f, 0.5f, 0.5f);
	Vertex[1] = new Namse::Vector(0.5f, 0.5f, -0.5f);
	Vertex[2] = new Namse::Vector(0.5f, -0.5f, 0.5f);
	Vertex[3] = new Namse::Vector(0.5f, -0.5f, -0.5f);
	Vertex[4] = new Namse::Vector(-0.5f, 0.5f, 0.5f);
	Vertex[5] = new Namse::Vector(-0.5f, 0.5f, -0.5f);
	Vertex[6] = new Namse::Vector(-0.5f, -0.5f, 0.5f);
	Vertex[7] = new Namse::Vector(-0.5f, -0.5f, -0.5f);

	Triangles[0] = new Namse::Triangle(Vertex[2], Vertex[3], Vertex[1]);
	Triangles[1] = new Namse::Triangle(Vertex[1], Vertex[0], Vertex[2]);
	Triangles[2] = new Namse::Triangle(Vertex[7], Vertex[6], Vertex[4]);
	Triangles[3] = new Namse::Triangle(Vertex[4], Vertex[5], Vertex[7]);
	Triangles[4] = new Namse::Triangle(Vertex[4], Vertex[0], Vertex[1]);
	Triangles[5] = new Namse::Triangle(Vertex[1], Vertex[5], Vertex[4]);
	Triangles[6] = new Namse::Triangle(Vertex[7], Vertex[3], Vertex[2]);
	Triangles[7] = new Namse::Triangle(Vertex[2], Vertex[6], Vertex[7]);
	Triangles[8] = new Namse::Triangle(Vertex[2], Vertex[4], Vertex[6]);
	Triangles[9] = new Namse::Triangle(Vertex[2], Vertex[0], Vertex[4]);
	Triangles[10] = new Namse::Triangle(Vertex[3], Vertex[7], Vertex[5]);
	Triangles[11] = new Namse::Triangle(Vertex[5], Vertex[1], Vertex[3]);

	for (int i = 0; i < sizeof(Triangles) / sizeof(Triangles[0]); i++)
		AddChild(Triangles[i]);
}


Namse::Cube::~Cube()
{
	for (int i = 0; i < sizeof(Vertex) / sizeof(Vertex[0]); i++)
		delete Vertex[i];

	for (int i = 0; i < sizeof(Triangles) / sizeof(Triangles[0]); i++)
		delete Triangles[i];
}

void Namse::Cube::OnDraw(Vector& BasePosition)
{
	Node::OnDraw(BasePosition);
}