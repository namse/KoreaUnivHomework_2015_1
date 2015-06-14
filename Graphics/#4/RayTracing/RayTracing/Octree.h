#pragma once
#include "Vector.h"
#include "Triangle.h"
namespace Namse
{
	class Octree
	{
	public:


		Octree();
		~Octree();

		void			Reset(
			Namse::Vector&	center,
			float			width
			);
		void			Clear();
		void			Add(
			Triangle*	triangle
			);

		bool			FindNearestTriangle( 
			IN Vector& startPoint,
			IN Vector& rayVec,
			IN GLdouble maxDistance,
			OUT GLdouble& distance,
			OUT Namse::Vector& contactVector,
			OUT Triangle** triangle);

		bool			m_IsDirty;
	private:
		// for child
		Octree(
			Namse::Vector&	center,
			float			width,
			unsigned	int	depth
			);

		Octree*			m_Next[2][2][2]; // x, y, z
		Namse::Vector	m_Center;
		float			m_Width;

		float			m_MinX;
		float			m_MaxX;
		float			m_MinY;
		float			m_MaxY;
		float			m_MaxZ;
		float			m_MinZ;

		std::vector<Triangle*>	m_Triangles;

		unsigned	int			m_Depth;
		
	};
}
