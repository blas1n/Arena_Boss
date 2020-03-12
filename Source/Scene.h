#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Entity;

	class Scene final
	{
	public:
		Scene(const Scene&) = delete;
		Scene(Scene&&) = default;

		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = default;

		~Scene() = default;

		Entity* AddEntity(const std::string& name);
		Entity* AddEntity(Entity* entity);

		void RemoveEntity(const std::string& name);
		void RemoveEntity(Entity* entity);

		Entity* GetEntity(const std::string& name);

		inline const std::string& GetName() const noexcept { return name; }
		inline bool IsAvailable() const noexcept { return isAvailable; }

	private:
		friend class SceneManager;
		Scene();

		void Load(const std::string& inName);
		void Save();

		std::string name;
		std::vector<Entity*> entities;

		bool isAvailable;
	};
}