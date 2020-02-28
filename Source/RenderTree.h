#pragma once

#include <functional>
#include <vector>

namespace ArenaBoss
{
	class Shader;
	class MeshDrawableComponent;
	
	class RenderTree
	{
	public:
		struct RenderNode
		{
			RenderNode(Shader* inShader)
				: shader(inShader), components() {}

			Shader* shader;
			std::vector<MeshDrawableComponent*> components;
		};

	public:
		void Draw(std::function<void(Shader&)> fn);

		void RegisterShader(Shader* shader);
		void UnregisterShader(Shader* shader);

		void RegisterComponent(MeshDrawableComponent* component);
		void UnregisterComponent(MeshDrawableComponent* component);

	private:
		std::vector<MeshDrawableComponent*>& GetComponents(Shader* shader);

	private:
		std::vector<RenderNode> nodes;
	};
}