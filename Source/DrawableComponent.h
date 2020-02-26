#pragma once

#include "Component.h"

namespace ArenaBoss
{
	class DrawableComponent : public Component
	{
		GENERATE_COMPONENT(DrawableComponent)

	public:
		virtual void Draw(class Shader* shader) = 0;
	};
}