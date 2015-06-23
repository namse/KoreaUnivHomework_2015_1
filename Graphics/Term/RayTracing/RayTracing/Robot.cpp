#include "stdafx.h"
#include "Robot.h"
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
Namse::Robot::Robot()
{
	std::ifstream ifs("Robot.myobj");

	if (!ifs.good())
	{
		printf("LoadModelError");
		int a = GetLastError();
		return;
	}

	std::string line;

	while (ifs.good())
	{
		std::getline(ifs, line);
		std::stringstream sstr(line);

		std::string firstFactor;
		sstr >> firstFactor;
		if (firstFactor.compare("g") == 0)
		{
			continue;
		}
		else if (firstFactor.compare("v") == 0)
		{
			Namse::Vector vec;
			sstr >> vec.m_X >> vec.m_Y >> vec.m_Z;
			Namse::Vector* newVec = new Namse::Vector(vec);
			m_Vertex.push_back(newVec);
		}
		else if (firstFactor.compare("f") == 0)
		{
			int a, b, c;
			sstr >> a >> b >> c;

			Namse::Triangle* tri = new Namse::Triangle(m_Vertex.at(a-1),
				m_Vertex.at(b-1),	
				m_Vertex.at(c-1));

			AddChild(tri);

			m_Triangles.push_back(tri);
		}
	}

}


Namse::Robot::~Robot()
{
	for (auto& tri : m_Triangles)
		delete tri;
	for (auto& vec : m_Vertex)
		delete vec;
}
