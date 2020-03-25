#pragma once

#include "DrawableComponent.h"

namespace ArenaBoss
{
	class Mesh;

	class MeshComponent : public DrawableComponent, private Accessor<class RenderManager>
	{
		GENERATE_COMPONENT2(MeshComponent, DrawableComponent)

	public:
		void Draw() override;

		virtual void SetMesh(Mesh* inMesh) noexcept { mesh = inMesh; }
		inline void SetTexutreIndex(size_t inTextureIndex) noexcept { textureIndex = inTextureIndex; }

		void SetShader(Shader* inShader) noexcept override;

	private:
		Mesh* mesh = nullptr;
		size_t textureIndex = 0u;
	};
}