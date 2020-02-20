#pragma once

#include <cstdint>

namespace ArenaBoss
{
	class Game final
	{
	public:
		Game();

		Game(const Game&) = delete;
		Game(Game&&) noexcept = default;

		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) noexcept = default;

		~Game();

		int Run();

	private:
		class WindowManager* windowManager;
		class RenderManager* renderManager;
		class InputManager* inputManager;
		class SceneManager* sceneManager;

		uint32_t ticksCount;
	};
}