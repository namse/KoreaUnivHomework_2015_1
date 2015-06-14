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

#include "Threading.h"

#include "Cube.h"
#include "Sphere.h"
#include "Robot.h"


void Reshape(int w, int h)
{
	g_RayTracingEngine->ReserveReshape(w, h);
	
}

void keyPressed(unsigned char key, int x, int y) {
	g_RayTracingEngine->OnKeyDown(key);
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

	
	g_RayTracingEngine = new Namse::RayTracingEngine();

	g_RayTracingEngine->GetCamera()->Look(Namse::Vector(0, 0, 2.5f), Namse::Vector(0, 0, 0.f), false);

	g_RayTracingEngine->ThreadSetup();

	
	Namse::DirectionalLight directionalLight;
	directionalLight.m_Color = Namse::Color(1, 1, 1);
	directionalLight.m_LightPower = 1;
	directionalLight.m_Ray = Namse::Vector(1, 0, 1).Unit();
	g_RayTracingEngine->AddLight(&directionalLight);

	
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

	
	Namse::Sphere sphere(0.5);
	sphere.m_Position = Namse::Vector(0, 1, -2.f);

	g_RayTracingEngine->AddChild(&sphere);


	Namse::Robot robot;
	robot.m_Position = Namse::Vector(0, 0, 0.5);
	g_RayTracingEngine->AddChild(&robot);


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

