#include "RenderManager.h"
#include <exception>
#include <GL/glew.h>
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

	void RenderManager::Update()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}
}