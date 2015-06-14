#pragma once
#include "Node.h"
#include "Triangle.h"
namespace Namse
{
	class Cube :
		public Node
	{
	public:
		Cube();
		~Cube();

		virtual void OnDraw(Vector& BasePosition);

		Vector* Vertex[8];
		Triangle* Triangles[12];
	};
}