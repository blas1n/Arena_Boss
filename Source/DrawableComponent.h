#pragma once

#include "Component.h"

namespace ArenaBoss
{
	enum class DrawKind { Sprite, Mesh };

	class DrawableComponent : public Component
	{
		GENERATE_COMPONENT(DrawableComponent)

	public:
		virtual void Draw(class Shader* shader) = 0;
		virtual DrawKind GetKind() const noexcept = 0;

		inline bool IsVisible() const noexcept { return visible; }
		inline void SetVisible(bool inVisible) noexcept { visible = inVisible; }

	private:
		bool visible = true;
	};

#define GENERATE_DRAWABLE_COMPONENT(name, kind) \
GENERATE_COMPONENT(name) \
	inline DrawKind GetKind() const noexcept override \
	{ \
		return kind; \
	}
}