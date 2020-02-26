#include "RenderManager.h"
#include <algorithm>
#include <exception>
#include <GL/glew.h>
#include "DrawableComponent.h"
#include "Game.h"
#include "Log.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	RenderManager::RenderManager()
		: window(GetManager().GetWindow()), context()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		context = SDL_GL_CreateContext(window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::exception{ "Failed to initialize GLEW" };

		glGetError();
	}

	RenderManager::~RenderManager()
	{
		SDL_GL_DeleteContext(context);
	}

	void RenderManager::Draw()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		// Render mesh

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		SDL_GL_SwapWindow(window);
	}

	void RenderManager::RegisterComponent(DrawableComponent* component)
	{
		switch (component->GetKind())
		{
		case DrawKind::Mesh:
			meshComponents.emplace_back(std::move(component));
			break;
		case DrawKind::Sprite:
			spriteComponents.emplace_back(std::move(component));
			break;
		}
	}

	void RenderManager::UnregisterComponent(DrawableComponent* component)
	{
		std::vector<DrawableComponent*>* components = nullptr;

		switch (component->GetKind())
		{
		case DrawKind::Mesh:
			components = &meshComponents;
			break;
		case DrawKind::Sprite:
			components = &spriteComponents;
			break;
		default:
			return;
		}

		const auto iter = std::find(components->begin(),
			components->end(), component);
		components->erase(iter);
	}
}