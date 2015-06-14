#pragma once
#include "Node.h"
#include "Color.h"
namespace Namse
{
	enum LightType
	{
		SPOT_LIGHT,
		DIRECTIONAL_LIGHT,
	};
	
	class Light :
		public Node
	{
	public:
		Light(LightType type)
		: m_LightType(type) {}
		~Light() {}

		LightType m_LightType;
		Color m_Color;
		GLdouble m_LightPower;
	};

	class SpotLight
		: public Light
	{
	public:
		SpotLight()
			:Light(SPOT_LIGHT) {}
		~SpotLight() {}
	};

	class DirectionalLight
		: public Light
	{
	public:
		DirectionalLight()
			:Light(DIRECTIONAL_LIGHT){}
		~DirectionalLight() {}

		Namse::Vector m_Ray;
	};
}

