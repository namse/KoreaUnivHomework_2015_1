#pragma once
#include "Node.h"
#include "GLMath.h"
namespace Namse
{ 
	// Camera Base is from http://www.3dcpptutorials.sk/index.php?id=51
	class Camera :
		public Node
	{
	public:
		Camera();
		~Camera();

		mat4x4 m_RayMatrix;
		mat4x4 m_Pin;
		mat4x4 m_VPin;

		void Look(const Namse::Vector &Position, const Namse::Vector &Reference, bool RotateAroundReference);
	

		bool OnKeyDown(unsigned int nChar);
		

		void OnMouseMove(int dx, int dy);

		void OnMouseWheel(short zDelta);
	
		void OnReshpae(int w, int h);
	private:
		void CalculateRayMatrix();


		Namse::Vector m_X, m_Y, m_Z, m_Reference;



		/*
		gluPerspective(45,, 1, 100);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(g_Eye.m_X, g_Eye.m_Y, g_Eye.m_Z,
			0, 1, 10,
			0, 1, 0);
			*/
	};
}
