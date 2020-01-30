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

		inline class Windows& GetWindows() noexcept { return *windows; }
		inline class D3D& GetD3D() noexcept { return *d3d; }

		inline const class Windows& GetWindows() const noexcept { return *windows; }
		inline const class D3D& GetD3D() const noexcept { return *d3d; }

	private:
		Windows* windows;
		D3D* d3d;
	};
}