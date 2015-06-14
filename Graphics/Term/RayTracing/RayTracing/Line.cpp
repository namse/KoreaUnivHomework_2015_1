#include "stdafx.h"
#include "Line.h"


void Namse::Line::Draw()
{
	glBegin(GL_LINES);
	glColor3d(m_Color.m_R, m_Color.m_G, m_Color.m_B);
	glVertex3d(m_From.m_X, m_From.m_Y, m_From.m_Z);
	glVertex3d(m_To.m_X, m_To.m_Y, m_To.m_Z);
	glEnd();
}
