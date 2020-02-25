#pragma once

#include "Component.h"

namespace ArenaBoss
{
	class Shader;

	class DrawableComponent : public Component
	{
		GENERATE_COMPONENT(DrawableComponent)

	public:
		virtual void Draw() = 0;

		Shader* GetShader() noexcept { return shader; }
		void SetShader(Shader* inShader) noexcept { shader = inShader; }

	private:
		Shader* shader;
	};
}