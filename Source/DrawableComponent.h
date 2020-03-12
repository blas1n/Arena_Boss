#pragma once

#include "Accessor.h"
#include "Component.h"

namespace ArenaBoss
{
	class Shader;

	class DrawableComponent : public Component
	{
		GENERATE_COMPONENT(DrawableComponent)

	public:
		virtual void Draw() = 0;
		
		inline Shader* GetShader() noexcept { return shader; }
		inline const Shader* GetShader() const noexcept { return shader; }
		inline virtual void SetShader(Shader* inShader) noexcept { shader = inShader; }

		inline bool HaveShader() const noexcept { return shader != nullptr; }
		inline void ClearShader() noexcept { SetShader(nullptr); }

		inline bool IsVisible() const noexcept { return visible; }
		inline void SetVisible(bool inVisible) noexcept { visible = inVisible; }

	private:
		Shader* shader;
		bool visible = true;
	};

	class MeshDrawableComponent : public DrawableComponent, private Accessor<class RenderManager>
	{
		// Use GENRRATE_COMPONENT (__VA_ARGS__)
		GENERATE_COMPONENT_CUSTOM(MeshDrawableComponent, DrawableComponent)

	public:
		void SetShader(Shader* inShader) noexcept override;
	};

	class SpriteDrawableComponent : public DrawableComponent
	{
		// Use GENRRATE_COMPONENT (__VA_ARGS__)
		GENERATE_COMPONENT_CUSTOM(SpriteDrawableComponent,DrawableComponent)
	};
}