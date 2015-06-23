#pragma once
#include "Node.h"
#include "Triangle.h"
namespace Namse
{
	class Robot :
		public Node
	{
	public:
		Robot();
		~Robot();

		std::vector<Namse::Vector*> m_Vertex;
		std::vector<Namse::Triangle*> m_Triangles;
	};
}


