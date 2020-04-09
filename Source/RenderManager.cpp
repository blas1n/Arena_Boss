#include "RenderManager.h"
#include <algorithm>
#include <exception>
#include <GL/glew.h>
#include <string>
#include "DrawableComponent.h"
#include "MathFunctions.h"
#include "Matrix4x4.h"
#include "MeshComponent.h"
#include "RenderTree.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SpriteComponent.h"
#include "VertexArray.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	RenderManager::RenderManager()
		: spriteComponents(),
		renderTree(new RenderTree{}),
		window(nullptr),
		resourceManager(ResourceAccessor::GetManager()),
		context(nullptr),
		view(),
		projection(),
		width(0u),
		height(0u)
	{
		auto& windowManager = WindowAccessor::GetManager();
		window = windowManager.GetWindow();
		width = windowManager.GetWidth();
		height = windowManager.GetHeight();

		view = Math::Matrix4x4::CreateLookAt(Math::Vector3::ZERO(), Math::Vector3::RIGHT(), Math::Vector3::FORWARD());

		projection = Math::Matrix4x4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
			static_cast<float>(width), static_cast<float>(height), 25.0f, 10000.0f);

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

		GenerateSpriteResource();
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

		renderTree->Draw([this, viewProj = view * projection](auto& shader)
		{
			shader.SetUniformValue("uViewProjection", viewProj);
			SetLightUniforms(shader);
		});

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		resourceManager.GetResource<Shader>("Sprite Shader")->Activate();
		resourceManager.GetResource<VertexArray>("Sprite Vertex")->Activate();

		for (auto component : spriteComponents)
			if (component->IsVisible())
				component->Draw();

		// Draw ui

		SDL_GL_SwapWindow(window);
	}

	void RenderManager::SetComponentInTree(MeshComponent* component)
	{
		if (component->HaveShader())
			renderTree->RegisterComponent(component);
		else
			renderTree->UnregisterComponent(component);
	}

	void RenderManager::RegisterComponent(MeshComponent* component)
	{
		meshComponents.push_back(component);

		if (component->HaveShader())
			renderTree->RegisterComponent(component);
	}

	void RenderManager::UnregisterComponent(MeshComponent* component)
	{
		const auto iter = std::find(meshComponents.begin(),
			meshComponents.end(), component);
		meshComponents.erase(iter);
	}

	void RenderManager::UnregisterComponent(SpriteComponent* component)
	{
		const auto iter = std::find(spriteComponents.begin(),
			spriteComponents.end(), component);
		spriteComponents.erase(iter);
	}

	void RenderManager::GenerateSpriteResource()
	{
		auto shader = resourceManager.CreateResource<Shader>
			("Sprite Shader", "Sprite.vert", "Sprite.frag");

		shader->Activate();

		const Math::Matrix4x4 viewProjection
		{
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f
		};

		shader->SetUniformValue("uViewProjection", viewProjection);

		constexpr float vertices[]
		{
			-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,
			0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,
			0.5f, -0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,
			-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f
		};

		constexpr uint indices[]
		{
			0, 1, 2,
			2, 3, 0
		};

		VertexArrayParam param{ VertexLayout::PosNormTex, vertices, 4, indices, 6 };
		resourceManager.CreateResource<VertexArray>("Sprite Vertex", std::move(param));
	}

	void RenderManager::SetLightUniforms(Shader& shader)
	{
		auto invView = view.Invert();

		shader.SetUniformValue("uCameraPos", invView.GetTranslation());

		shader.SetUniformValue("uAmbientLight", ambientLight);

		shader.SetUniformValue("uDirLight.direction", dirLight.direction);
		shader.SetUniformValue("uDirLight.diffuseColor", dirLight.diffuseColor);
		shader.SetUniformValue("uDirLight.specularColor", dirLight.specularColor);
	}
}