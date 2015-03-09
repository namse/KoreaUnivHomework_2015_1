// DrawPolygon.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "NamsGraphics.h"

void Reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);


	GLdouble centerX, centerY;
	const GLdouble radius = 25.0;

	// Draw Triangle //
	centerX = 25.0, centerY = 75.0;
	DrawRegularPolygon_2D(centerX, centerY, radius, 3);


	// Draw Pentagon //
	centerX = 75.0, centerY = 75.0;
	DrawRegularPolygon_2D(centerX, centerY, radius, 6);


	// Draw Hexagon //
	centerX = 25.0, centerY = 25.0;
	DrawRegularPolygon_2D(centerX, centerY, radius, 8);


	// Draw Dodecagon //
	centerX = 75.0, centerY = 25.0;
	DrawRegularPolygon_2D(centerX, centerY, radius, 12);

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("2013210111");
	//glutCreateWindow("Modeling and Renerding Equilateral Polygon");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}

