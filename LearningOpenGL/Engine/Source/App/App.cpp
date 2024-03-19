#include "App\App.h"

struct UniformData
{
	Matrix4X4 world;
};

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
	const F32 polygonVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f, 0.0f,
		 0.0f,  1.0f, 0.0f,

		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.0f, 1.0f,

		 0.5f,  0.5f, 0.0f,
		 1.0f,  1.0f, 0.0f
	};

	VertexAttribute attributes[] = {
		3, // Position
		3  // Color
	};

	m_polygonVAO = m_graphicsEngine->CreateVertexArrayObject(
		{
			(void*)polygonVertices,
			sizeof(F32) * (3 + 3),
			4,
			attributes,
			2
		});

	m_uniformBuffer = m_graphicsEngine->CreateUniformBuffer(
		{
			sizeof(UniformData)
		});

	m_shaderProgram = m_graphicsEngine->CreateShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert", 
			L"Assets/Shaders/BasicShader.frag" 
		});
	
	m_shaderProgram->SetUniformBufferSlot("UniformData", 0);
}

void App::OnUpdate()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();

	if (m_previousTime.time_since_epoch().count())
		elapsedSeconds = currentTime - m_previousTime;

	m_previousTime = currentTime;

	auto deltaTime = (F32)elapsedSeconds.count();

	m_scale += 3.14f * deltaTime;
	auto currentScale = abs(sin(m_scale));

	Matrix4X4 world, temp;

	temp.SetIdentity();
	temp.SetScale(Vector4(currentScale, currentScale, currentScale, 1));

	world *= temp;

	temp.SetIdentity();
	temp.SetTranslation(Vector4(m_scale * 0.1f, 0, 0, 1));
	world *= temp;

	UniformData data = { world };
	m_uniformBuffer->SetData(&data);

	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));

	m_graphicsEngine->SetVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->SetUniformBuffer(m_uniformBuffer, 0);
	m_graphicsEngine->SetShaderProgram(m_shaderProgram);
	m_graphicsEngine->DrawTriangles(TriangleType::TriangleStrip, m_polygonVAO->GetVertexBufferSize(), 0);

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
