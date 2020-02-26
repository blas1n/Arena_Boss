#include "DrawableComponent.h"
#include "RenderManager.h"

namespace ArenaBoss
{
	void MeshDrawableComponent::SetShader(Shader* inShader) noexcept
	{
		DrawableComponent::SetShader(inShader);
		Accessor<RenderManager>::GetManager().SetComponentInTree(this);
	}
}