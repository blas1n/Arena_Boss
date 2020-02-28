#include "RenderTree.h"
#include <algorithm>
#include <exception>
#include <string>
#include "DrawableComponent.h"
#include "IteratorFinder.h"
#include "Shader.h"

namespace ArenaBoss
{
	namespace
	{
		struct NodeLess
		{
			constexpr bool operator()(const RenderTree::RenderNode& lhs, const Shader* rhs) const
			{
				return lhs.shader < rhs;
			}
		};

		struct NodeEqual
		{
			constexpr bool operator()(const RenderTree::RenderNode& lhs, const Shader* rhs) const
			{
				return lhs.shader == rhs;
			}
		};

		struct NodeNonEqual
		{
			constexpr bool operator()(const RenderTree::RenderNode& lhs, const Shader* rhs) const
			{
				return lhs.shader != rhs;
			}
		};

		using ComponentLess = std::less<MeshDrawableComponent*>;
		using ComponentEqual = std::equal_to<MeshDrawableComponent*>;
		using ComponentNonEqual = std::not_equal_to<MeshDrawableComponent*>;

		template <class Comp, class Confirmer, class T, class U>
		decltype(auto) FindIter(std::vector<T>& vec, const U& value, const std::string& msg)
		{
			const auto iter = std::lower_bound(vec.begin(),
				vec.end(), value, Comp{});

			if (!Confirmer{}(*iter, value))
				throw std::exception{ msg.c_str() };

			return iter;
		}
	}

	void RenderTree::Draw(std::function<void(Shader&)> fn)
	{
		for (auto& node : nodes)
		{
			node.shader->Activate();
			fn(*node.shader);

			for (auto component : node.components)
				if (component->IsVisible())
					component->Draw();
		}
	}

	void RenderTree::RegisterShader(Shader* shader)
	{
		const auto iter = FindIter<NodeLess, NodeNonEqual>(
			nodes, shader, "This shader already exists.");

		nodes.emplace_back(RenderNode{ shader });
		std::rotate(nodes.rbegin(), nodes.rbegin() + 1,
			std::reverse_iterator{ iter });
	}

	void RenderTree::UnregisterShader(Shader* shader)
	{
		const auto iter = FindIter<NodeLess, NodeEqual>(
			nodes, shader, "This shader doesn't exists.");
		nodes.erase(iter);
	}

	void RenderTree::RegisterComponent(MeshDrawableComponent* component)
	{
		auto& components = GetComponents(component->GetShader());
		const auto nodeIter = FindIter<ComponentLess, ComponentNonEqual>(
			components, component, "This component already exists.");

		components.emplace_back(component);
		std::rotate(components.rbegin(), components.rbegin() + 1,
			std::reverse_iterator{ nodeIter });
	}

	void RenderTree::UnregisterComponent(MeshDrawableComponent* component)
	{
		auto& components = GetComponents(component->GetShader());
		const auto nodeIter = FindIter<ComponentLess, ComponentEqual>(
			components, component, "This component doesn't exists.");
		components.erase(nodeIter);
	}

	std::vector<MeshDrawableComponent*>& RenderTree::GetComponents(Shader* shader)
	{
		const auto iter = FindIter<NodeLess, NodeEqual>(
			nodes, shader, "This shader doesn't exists.");
		return iter->components;
	}
}