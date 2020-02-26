#include "RenderManager.h"
#include <algorithm>
#include <exception>
#include <GL/glew.h>
#include <string>
#include "DrawableComponent.h"
#include "RenderTree.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	RenderManager::RenderManager()
		: spriteComponents(),
		renderTree(new RenderTree{}),
		window(WindowAccessor::GetManager().GetWindow()),
		resourceManager(ResourceAccessor::GetManager()),
		context(nullptr)
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

		renderTree->Draw();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		const auto spriteShader =
			resourceManager.GetResource<Shader>("Sprite Shader");

		// Set sprite vertex

		spriteShader->Activate();

		for (auto component : spriteComponents)
			if (component->IsVisible())
				component->Draw();

		// Draw ui

		SDL_GL_SwapWindow(window);
	}

	void RenderManager::RegisterComponent(MeshDrawableComponent* component)
	{
		meshComponents.push_back(component);

		if (component->HaveShader())
			SetComponentInTree(component);
	}

	void RenderManager::UnregisterComponent(MeshDrawableComponent* component)
	{
		const auto iter = std::find(meshComponents.begin(),
			meshComponents.end(), component);
		meshComponents.erase(iter);
	}

	void RenderManager::UnregisterComponent(SpriteDrawableComponent* component)
	{
		const auto iter = std::find(spriteComponents.begin(),
			spriteComponents.end(), component);
		spriteComponents.erase(iter);
	}

	void RenderManager::SetComponentInTree(MeshDrawableComponent* component)
	{
		if (component->HaveShader())
			renderTree->RegisterComponent(component);
		else
			renderTree->UnregisterComponent(component);
	}
}