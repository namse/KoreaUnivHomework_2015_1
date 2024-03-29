#include "stdafx.h"
#include "NamsGraphics.h"


void DrawRegularPolygon_2D(GLdouble centerX, GLdouble centerY, GLdouble radius, int polyCount)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < polyCount; i++)
	{
		glVertex3d(centerX + radius * cos(2 * M_PI * i / (double)polyCount)
			, centerY + radius * sin(2 * M_PI * i / (double)polyCount)
			, 0);
	}
	glEnd();
}