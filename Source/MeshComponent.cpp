#include "MeshComponent.h"
#include "Entity.h"
#include "JsonHelper.h"
#include "Mesh.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "VertexArray.h"

namespace ArenaBoss
{
	void MeshComponent::Load(const Json::Object& object)
	{
		Super::Load(object);
		
		if (object.HasMember("mesh"))
		{
			const auto& meshObj = object["mesh"];
			const auto meshName = *Json::JsonHelper::GetString(meshObj, "name");
			const auto meshPath = *Json::JsonHelper::GetString(meshObj, "path");

			mesh = Accessor<ResourceManager>::GetManager().CreateResource<Mesh>(meshName, meshPath);
		}
		
		textureIndex = *Json::JsonHelper::GetInt(object, "texture index");
	}

	void MeshComponent::Save(Json::JsonSaver& saver) const
	{
		Super::Save(saver);

		if (mesh)
		{
			rapidjson::Value obj{ rapidjson::kObjectType };
			Json::JsonSaver meshSaver{ saver, obj };

			Json::JsonHelper::AddString(saver, "name", mesh->GetName());
			Json::JsonHelper::AddString(saver, "path", mesh->GetPath());

			saver.object.AddMember("mesh", obj, saver.alloc);
		}

		Json::JsonHelper::AddInt(saver, "texture index", textureIndex);
	}

	void MeshComponent::Draw()
	{
		if (!mesh) return;

		auto* shader = GetShader();

		shader->SetUniformValue("uWorldTransform", GetEntity()->GetComponent<Transform>().GetWorldMatrix());
		shader->SetUniformValue("uSpecularPower", mesh->GetSpecularPower());

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