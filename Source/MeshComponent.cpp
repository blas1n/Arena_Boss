#include "MeshComponent.h"
#include "Entity.h"
#include "RenderManager.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"

namespace ArenaBoss
{
	void MeshComponent::Draw()
	{
		if (!mesh) return;

		auto* shader = GetShader();

		shader->SetUniformValue("uWorldTransform", GetEntity()->GetComponent<Transform>().GetWorldMatrix());
		//shader->SetUniformValue("uSpecularPower", mesh->GetSpecularPower());

		auto t = mesh->GetTexture(textureIndex);
		if (t) t->Activate();

		auto vertexArray = mesh->GetVertexArray();
		vertexArray->Activate();

		glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}

	void MeshComponent::SetShader(Shader* inShader) noexcept
	{
		DrawableComponent::SetShader(inShader);
		Accessor<RenderManager>::GetManager().SetComponentInTree(this);
	}
}