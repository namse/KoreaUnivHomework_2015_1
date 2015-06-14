#pragma once
#include "Node.h"
#include "Triangle.h"

namespace Namse
{
	class Sphere :
		public Node
	{
	public:
		Sphere(float r);
		~Sphere();

		virtual void OnDraw(Vector& BasePosition);

		std::vector<Namse::Vector*> m_Vertex;
		std::vector<Namse::Triangle*> m_Triangles;

	private:
		void normalize(float *a);

		void drawtri(float *a, float *b, float *c, int div, float r);
	};
}

