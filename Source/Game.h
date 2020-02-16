#pragma once

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
	};
}