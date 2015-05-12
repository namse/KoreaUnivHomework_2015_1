#include <vector>
#include <stdlib.h>
#include "NamsGraphics.h"
#include "Color.h"
struct PointLight
{
	Namse::Vector m_Position;
	Color m_Color;
	double m_Power;

	PointLight()
		: m_Position(3, 0, 0), m_Power(1), m_Color(0.25, 0.75, 0.25)
	{
	}
};

struct Face
{
	Face()
	{
		memset(m_VertexIndex, 0, sizeof(m_VertexIndex));
	}
	unsigned int m_VertexIndex[3];
};

struct Model
{
	std::vector<Namse::Vector> m_Vertexes;
	std::vector<Namse::Vector> m_NormalVectors;
	std::vector<Face> m_Faces;

	enum DrawType
	{
		DT_WIREFRAME,
		DT_SHADING,
		DT_NORMAL,
	};
	void draw(DrawType type, PointLight& pointLight, Namse::Vector eye);
};