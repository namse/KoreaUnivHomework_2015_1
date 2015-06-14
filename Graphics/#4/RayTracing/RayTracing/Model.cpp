#include "stdafx.h"
#include "Model.h"
#include "Color.h"


void Model::draw(DrawType type, PointLight& pointLight, Namse::Vector eye)
{
	for (auto& face : m_Faces)
	{
		switch (type)
		{
		case Model::DT_WIREFRAME:
		{
			glBegin(GL_LINE_LOOP);
			glColor3d(1, 1, 1);
			for (int i = 0; i < 3; i++)
			{
				auto vertex = m_Vertexes[face.m_VertexIndex[i] - 1];
				glVertex3d(vertex.m_X,
					vertex.m_Y,
					vertex.m_Z);

			}
			glEnd();
		}
		break;
		case Model::DT_SHADING:
		{
			glBegin(GL_TRIANGLE_FAN);

			Namse::Color vertexColor[3];

			for (int i = 0; i < 3; i++)
			{
				auto vertex = m_Vertexes[face.m_VertexIndex[i] - 1];
				auto normalVector = m_NormalVectors[face.m_VertexIndex[i] - 1];
				auto toLightVector = pointLight.m_Position - vertex;
				auto toEyeVector = eye - vertex;
				vertexColor[i] = pointLight.m_Color * normalVector.DotProduct(toLightVector);
				vertexColor[i] += pointLight.m_Color * toEyeVector.DotProduct(normalVector * toLightVector.DotProduct(normalVector) * 2 - toLightVector);
				glColor3d(vertexColor[i].m_R, vertexColor[i].m_G, vertexColor[i].m_B);
				//glColor3d(0.5, 0.2, 0.3);
				glVertex3d(vertex.m_X,
					vertex.m_Y,
					vertex.m_Z);
			}
			glEnd();
		}
		break;
		case DT_NORMAL:
		{
			glBegin(GL_LINE_LOOP);
			glColor3d(1, 1, 1);
			for (int i = 0; i < 3; i++)
			{
				auto vertex = m_Vertexes[face.m_VertexIndex[i] - 1];
				glVertex3d(vertex.m_X,
					vertex.m_Y,
					vertex.m_Z);

			}
			glEnd();

			for (int i = 0; i < 3; i++)
			{
				glBegin(GL_LINES);
				glColor3d(1, 1, 1);
				auto vertex = m_Vertexes[face.m_VertexIndex[i] - 1];
				auto vertexAddNormal = vertex + m_NormalVectors[face.m_VertexIndex[i] - 1] * g_ScreenLength * 0.01;

				glVertex3d(vertex.m_X,
					vertex.m_Y,
					vertex.m_Z);

				glColor3d(1, 0, 0);
				glVertex3d(vertexAddNormal.m_X,
					vertexAddNormal.m_Y,
					vertexAddNormal.m_Z);
				glEnd();
			}
		}break;
		default:
			break;
		}
	}
}