// Gouraund Shading.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include "NamsGraphics.h"
#include <fstream>
#include <string>
#include <sstream>

#include "Color.h"
#include "Model.h"


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
	g_ScreenLength = pow(w * w + h * h, 0.5);
	GLdouble ratio = 1.0f*w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_Eye.m_X, g_Eye.m_Y, g_Eye.m_Z,
		0, 1, 10,
		0, 1, 0);
}

void keyPressed(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
		switch (g_DrawType)
		{
		case Model::DT_NORMAL:
			g_DrawType = Model::DT_SHADING;
			break;
		case Model::DT_SHADING:
			g_DrawType = Model::DT_WIREFRAME;
			break;
		case Model::DT_WIREFRAME:
			g_DrawType = Model::DT_NORMAL;
			break;
		}
		break;
	case 'w':
		g_PointLight.m_Position.m_X += 0.1;
		break;
	case 's':
		g_PointLight.m_Position.m_X -= 0.1;
		break;
	case 'a':
		g_PointLight.m_Position.m_Y += 0.1;
		break;
	case 'd':
		g_PointLight.m_Position.m_Y -= 0.1;
		break;
	case 'z':
		g_PointLight.m_Position.m_Z += 0.1;
		break;
	case 'x':
		g_PointLight.m_Position.m_Z -= 0.1;
		break;
	case 'r':
		g_Rotate = !g_Rotate;
		break;
	}
}
void Display()
{
	//glClearColor(0, 0, 1, 1);
	glClearDepth(100.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	
	
	static float angle = 0;

	glPushMatrix();
	
	// 1. Rotate Coordinate
	glRotatef(angle, 1, 1, 1);
	if(g_Rotate)
		angle += 0.1;
	
	// 2. And Draw Model.
	g_Model.draw(g_DrawType, g_PointLight, g_Eye);
	
	glPopMatrix();

	// 3. Draw Point Light's Position.
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3d(1, 1, 0);
	glVertex3d(g_PointLight.m_Position.m_X,
		g_PointLight.m_Position.m_Y,
		g_PointLight.m_Position.m_Z);

	glEnd();


	glutSwapBuffers();

}
int main(int argc, char* argv[])
{
	LoadModel();
	CalculateNormal();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("2013210111_3");
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyPressed);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutMainLoop();

	return 0;
}

