#pragma once
#include "Octree.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
namespace Namse
{
	class RayTracingEngine
	{
	public:
		RayTracingEngine();
		~RayTracingEngine();

		void	PushTriangleToOctree(Triangle* triangle);

		void	Reshape(int w, int h);
		void	OnDisplay();
		void	AddChild(Node* node);
		void	RemoveChild(Node* node);

		Color	RayTrace(Namse::Vector& from, Namse::Vector& ray, unsigned int currentHop);

		Camera*	GetCamera(){ return &m_Camera; }

		void	AddLight(Light* light) { m_LightList.push_back(light); }


		Namse::Vector m_MinVector;
		Namse::Vector m_MaxVector;
	private:
		unsigned int GetBufferSize()
		{
			return m_WindowHeight * m_WindowHeight * 3;
		}


		Octree m_Octree;
		Camera m_Camera;

		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

		Namse::Color* m_ColorBuffer;
		size_t m_BufferSize;

		Node	m_RootNode;

		std::vector<Light*> m_LightList;

	};
}

extern Namse::RayTracingEngine* g_RayTracingEngine;