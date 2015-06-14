#pragma once
#include "Octree.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include <thread>
#include "Threading.h"
namespace Namse
{
	class RayTracingEngine
	{
	public:
		RayTracingEngine();
		~RayTracingEngine();

		void	PushTriangleToOctree(Triangle* triangle);

		void	OnDisplay();
		void	AddChild(Node* node);
		void	RemoveChild(Node* node);

		Color	RayTrace(Namse::Vector& from, Namse::Vector& ray);
		Color	RayTrace(Namse::Triangle* triangle, Namse::Vector& contactPoint, Namse::Vector& ray, unsigned int currentHop);

		Camera*	GetCamera(){ return &m_Camera; }

		void	AddLight(Light* light) { m_LightList.push_back(light); }


		Namse::Vector m_MinVector;
		Namse::Vector m_MaxVector;

		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;
		Camera m_Camera;
		Namse::Color* m_ColorBuffer;

		void	ThreadSetup();

		void	ReserveReshape(int w, int h);
		
	private:
		void	Reshape(int w, int h);

		unsigned int GetBufferSize()
		{
			return m_WindowHeight * m_WindowHeight * 3;
		}


		Octree m_Octree;


		size_t m_BufferSize;

		Node	m_RootNode;

		std::vector<Light*> m_LightList;

		std::thread m_Threads[ThreadWidth * ThreadHeight];

		bool m_IsReshapeReserved;
		int m_ReservedWidth;
		int m_ReservedHeight;
	};
}

extern Namse::RayTracingEngine* g_RayTracingEngine;