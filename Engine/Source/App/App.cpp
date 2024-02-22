#include "App\App.h"

App::App()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<CoreWindow>();

	m_display->MakeCurrentContext();
	m_graphicsEngine->SetViewport(m_display->GetWindowSize());
}

App::~App()
{
}

void App::OnCreate()
{
	const F32 triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};



	m_triangleVAO = m_graphicsEngine->CreateVertexArrayObject({(void*)triangleVertices, sizeof(F32) * 3, 3});
	m_shaderProgram = m_graphicsEngine->CreateShaderProgram({});
}

void App::OnUpdate()
{
	m_graphicsEngine->Clear(Vector4(1, 0, 0, 1));

	m_graphicsEngine->SetVertexArrayObject(m_triangleVAO);
	m_graphicsEngine->SetShaderProgram(m_shaderProgram);
	m_graphicsEngine->DrawTriangles(m_triangleVAO->GetVertexBufferSize(), 0);

	m_display->Present(false);
}

void App::OnQuit()
{
}

void App::Run()
{
	OnCreate();

	MSG msg = {};
	while (m_isRunning)
	{
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				m_isRunning = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}

		OnUpdate();
	}

	OnQuit();
}

void App::Quit()
{
	m_isRunning = false;
}
