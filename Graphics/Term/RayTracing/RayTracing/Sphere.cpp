#include "stdafx.h"
#include "Sphere.h"


#include <math.h>
#define X .525731112119133606 
#define Z .850650808352039932

static float vdata[12][3] = {
	{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
	{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
	{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
};
static GLuint tindices[20][3] = {
	{ 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },
	{ 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
	{ 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
	{ 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 } };


void Namse::Sphere::normalize(float *a) {
	float d = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] /= d; a[1] /= d; a[2] /= d;
}

void Namse::Sphere::drawtri(float *a, float *b, float *c, int div, float r) {
	if (div <= 0) {
		Namse::Vector* V1 = new Namse::Vector(a[0] * r, a[1] * r, a[2] * r);
		Namse::Vector* V2 = new Namse::Vector(b[0] * r, b[1] * r, b[2] * r);
		Namse::Vector* V3 = new Namse::Vector(c[0] * r, c[1] * r, c[2] * r);

		Namse::Triangle* triangle = new Namse::Triangle(V1, V3, V2);
		AddChild(triangle);

		m_Vertex.push_back(V1);
		m_Vertex.push_back(V2);
		m_Vertex.push_back(V3);
		m_Triangles.push_back(triangle);
	}
	else {
		float ab[3], ac[3], bc[3];
		for (int i = 0; i<3; i++) {
			ab[i] = (a[i] + b[i]) / 2;
			ac[i] = (a[i] + c[i]) / 2;
			bc[i] = (b[i] + c[i]) / 2;
		}
		normalize(ab); normalize(ac); normalize(bc);
		drawtri(a, ab, ac, div - 1, r);
		drawtri(b, bc, ab, div - 1, r);
		drawtri(c, ac, bc, div - 1, r);
		drawtri(ab, bc, ac, div - 1, r);  //<--Comment this line and sphere looks really cool!
	}
}

Namse::Sphere::Sphere(float r)
{
	// below code from https://www.daniweb.com/software-development/cpp/threads/404742/create-a-sphere-using-triangles
	int ndiv = 1;
	float radius = r;
	for (int i = 0; i < 20; i++)
		drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], ndiv, radius);
}

Namse::Sphere::~Sphere()
{
	for (auto& vec : m_Vertex)
		delete vec;
	for (auto& tri : m_Triangles)
		delete tri;
}


void Namse::Sphere::OnDraw(Vector& BasePosition)
{
	Node::OnDraw(BasePosition);
}