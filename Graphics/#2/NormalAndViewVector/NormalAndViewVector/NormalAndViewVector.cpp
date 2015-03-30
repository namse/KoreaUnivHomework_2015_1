// NormalAndViewVector.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "NamsGraphics.h"

void Reshape(int w, int h)
{
/*	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	*/

	GLdouble ratio = 1.0f*w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0, 1, -10,
	//	0, 1, 10,
	//	0, 1, 0);
}

void Display()
{
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3d(-2, -2, -5.0);
	glVertex3d(2, 0, -5.0);
	glVertex3d(0, 2, -5.0);
	glEnd();
	glutSwapBuffers();
	*/
	
	//glClearColor(0, 0, 1, 1);
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glPointSize(5);


	// Set Triangle
	static Namse::Triangle triangle(Namse::Vector(-2, -2.5, -5),
		Namse::Vector(2, -0.5, -5), Namse::Vector(0, 1.5, -5));
	triangle.SetColor(1.0, 0, -5);


	// For Rotation
	static int previousTime = glutGet(GLUT_ELAPSED_TIME);
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int dTime = currentTime - previousTime;
	previousTime = currentTime;

	triangle.RotateBy(0, 0.001 * dTime, 0);


	// View Vector
	static Namse::Vector ViewStartPoint(2, 0, -6);
	static Namse::Vector ViewEndPoint(0, 0, -6);

	Namse::Line viewLine(ViewStartPoint, ViewEndPoint);
	viewLine.SetColor(0, 1, 0);



	// calculate Triangle's Normal Vector
	auto centerOfTriangle = triangle.GetCenter();
	auto triangleEdgeVector1 = triangle.m_Vector[1] - triangle.m_Vector[0];
	auto triangleEdgeVector2 = triangle.m_Vector[2] - triangle.m_Vector[1];
	auto normalVector = triangleEdgeVector2.CrossProduct(triangleEdgeVector1);
	normalVector = normalVector.Unit();



	Namse::Line normalVectorLine(centerOfTriangle, centerOfTriangle + normalVector * 2);
	normalVectorLine.SetColor(1, 1, 0);



	Namse::Line triangleEdgeLine1(triangle.m_Vector[0], triangle.m_Vector[1]);
	Namse::Line triangleEdgeLine2(triangle.m_Vector[1], triangle.m_Vector[2]);
	Namse::Line triangleEdgeLine3(triangle.m_Vector[2], triangle.m_Vector[0]);

	triangleEdgeLine1.SetColor(0, 0, 1);
	triangleEdgeLine2.SetColor(0, 0, 1);
	triangleEdgeLine3.SetColor(0, 0, 1);


	// 평면의 방정식
	// Ax + By + Cz + D = 0;
	GLdouble A, B, C, D;
#define x1 triangle.m_Vector[0].m_X
#define x2 triangle.m_Vector[1].m_X
#define x3 triangle.m_Vector[2].m_X
#define y1 triangle.m_Vector[0].m_Y
#define y2 triangle.m_Vector[1].m_Y
#define y3 triangle.m_Vector[2].m_Y
#define z1 triangle.m_Vector[0].m_Z
#define z2 triangle.m_Vector[1].m_Z
#define z3 triangle.m_Vector[2].m_Z

	A = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	B = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	C = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
	D = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));

	Namse::Vector viewVector(ViewStartPoint - ViewEndPoint);

	GLdouble t = -(A * ViewStartPoint.m_X + B * ViewStartPoint.m_Y + C * ViewStartPoint.m_Z + D)
		/ (A * viewVector.m_X + B * viewVector.m_Y + C * viewVector.m_Z);


	// Intersection between triangle and viewVector
	Namse::Vector intersectionPoint(viewVector.m_X * t + ViewStartPoint.m_X,
		viewVector.m_Y * t + ViewStartPoint.m_Y,
		viewVector.m_Z * t + ViewStartPoint.m_Z);

	intersectionPoint.SetColor(0, 0, 1);


	// cullling Test
	if (normalVector.DotProduct(viewVector) < 0)
		triangle.SetColor(0, 1, 0);



	triangle.Draw();
	viewLine.Draw();
	normalVectorLine.Draw();

	triangleEdgeLine1.Draw();
	triangleEdgeLine2.Draw();
	triangleEdgeLine3.Draw();
	intersectionPoint.Draw();

	glutSwapBuffers();
	
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("2013210111_2");
	//glutCreateWindow("Normal Vector and View Vector, Visibility");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutMainLoop();
	return 0;
}