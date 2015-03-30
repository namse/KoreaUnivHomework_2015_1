#include "stdafx.h"
#include "Triangle.h"


Namse::Vector Namse::Triangle::GetCenter()
{
	return (m_Vector[0] + m_Vector[1] + m_Vector[2]) / 3.0;
}



void Namse::Triangle::Draw()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(m_R, m_G, m_B);
	for (int i = 0; i < 3; i++)
	{
		glVertex3d(m_Vector[i].m_X, m_Vector[i].m_Y, m_Vector[i].m_Z);
	}
	glEnd();
}

void Namse::Triangle::RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ)
{
	auto center = GetCenter();

	MoveBy(-center);

	for (auto& vector : m_Vector)
		vector.RotateBy(_angleX, _angleY, _angleZ);

	MoveBy(center);
}

void Namse::Triangle::MoveBy(Vector _vector)
{
	for (auto& vector : m_Vector)
		vector.MoveBy(_vector);
}