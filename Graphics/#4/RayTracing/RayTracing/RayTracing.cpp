// Gouraund Shading.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "RayTracing.h"
#include <vector>
#include "NamsGraphics.h"
#include <fstream>
#include <string>
#include <sstream>
#include "RayTracingEngine.h"

#include "Color.h"
#include "Model.h"

#include "Threading.h"

#include "Cube.h"


Namse::Vector g_Eye(0, 0, -10);

Model::DrawType g_DrawType;

PointLight g_PointLight;

Model g_Model;

bool g_Rotate = true;


bool LoadModel()
{
	std::ifstream ifs("cube.obj");

	if (!ifs.good())
	{
		printf("LoadModelError");
		return false;
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
			g_Model.m_Vertexes.push_back(vec);
		}
		else if (firstFactor.compare("f") == 0)
		{
			Face face;
			std::string temp;
			for (int i = 0; i < 3; i++)
			{
				sstr >> temp;
				char* ptr;
				for (ptr = (char*)temp.c_str();
					*ptr != '/' && *ptr != NULL;
					ptr++)
				{
					face.m_VertexIndex[i] *= 10;
					face.m_VertexIndex[i] += *ptr - '0';
				}
			}
			g_Model.m_Faces.push_back(face);
		}
	}

	return true;
}

void CalculateNormal()
{
	std::vector<unsigned int> faceCount;
	for (int i = 0; i < g_Model.m_Vertexes.size(); i++)
	{
		faceCount.push_back(0);
		g_Model.m_NormalVectors.push_back(Namse::Vector(0, 0, 0));
	}

	// how to get average normal vector

	// 1. Add All of Normal Vector of Triangle To Vertex.
	// >> 1 normal vector -> add into 3 vertex's variables.
	// 2. then count 'how many normal vector added into that vertex.'
	// 3. finally, 그 카운트 갯수만큼 나눠주기.
	
	for (auto& face : g_Model.m_Faces)
	{
		auto vertex1 = g_Model.m_Vertexes[face.m_VertexIndex[0]-1];
		auto vertex2 = g_Model.m_Vertexes[face.m_VertexIndex[1]-1];
		auto vertex3 = g_Model.m_Vertexes[face.m_VertexIndex[2]-1];
		
		Namse::Vector crossVector((vertex2 - vertex1).CrossProduct(vertex3 - vertex2));
		
		Namse::Vector normalVector = crossVector / crossVector.Norm();

		
		for (int i = 0; i < 3; i++)
		{
			faceCount[face.m_VertexIndex[i]-1]++;
			g_Model.m_NormalVectors[face.m_VertexIndex[i]-1] += normalVector;
		}
	}

	for (int i = 0; i < g_Model.m_NormalVectors.size(); i++)
	{
		g_Model.m_NormalVectors[i] /= faceCount[i];
	}
}


void Reshape(int w, int h)
{
	g_RayTracingEngine->ReserveReshape(w, h);
	
}

void keyPressed(unsigned char key, int x, int y) {
	g_RayTracingEngine->GetCamera()->OnKeyDown(key);
}
void mouseClicked(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			IsLeftClicked = false;
			printf("~~~~~~~~~~\n");
		}
		if (state == GLUT_DOWN)
		{
			prevX = x;
			prevY = y;
			IsLeftClicked = true;
			printf("CLICKED!!!!!\n");
		}
	}
	printf("##################   %d\n", state);

}
void mouseMoved( int x, int y)
{
	if (IsLeftClicked == true)
	{
		g_RayTracingEngine->GetCamera()->OnMouseMove(x - prevX, y - prevY);

		prevX = x;
		prevY = y;
	}
	printf("(%d , %d)\n", prevX, prevY);
}
void Display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	g_RayTracingEngine->OnDisplay();

	glutSwapBuffers();

}
int main(int argc, char* argv[])
{

	IsLeftClicked = false;

	int a = sizeof(Namse::Color);
	g_RayTracingEngine = new Namse::RayTracingEngine();

	g_RayTracingEngine->GetCamera()->Look(Namse::Vector(0, 0, 2.5f), Namse::Vector(0, 0, 0.f), false);

	g_RayTracingEngine->ThreadSetup();

	Namse::DirectionalLight directionalLight;
	directionalLight.m_Color = Namse::Color(0, 0, 1);
	directionalLight.m_LightPower = 1;
	directionalLight.m_Ray = Namse::Vector(-1, -1, -1).Unit();
	//g_RayTracingEngine->AddLight(&directionalLight);

	Namse::SpotLight light;
	light.m_Position = Namse::Vector(2, 1, 1);
	light.m_Color = Namse::Color(1, 0.5f, 0.5f);
	light.m_LightPower = 5;
	g_RayTracingEngine->AddLight(&light);

	Namse::Cube cube1;
	cube1.m_Position = Namse::Vector(1.f, 0.f, 0);
	Namse::Cube cube2;
	cube2.MoveTo(Namse::Vector(-1, 0, 0));

	g_RayTracingEngine->AddChild(&cube1);
	g_RayTracingEngine->AddChild(&cube2);


	LoadModel();
	CalculateNormal();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("2013210111_3");
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mouseClicked);
	glutMotionFunc(mouseMoved);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutMainLoop();

	delete g_RayTracingEngine;
	return 0;
}

