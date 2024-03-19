#pragma once

#include <chrono>

#include "Platform\CoreWindow.h"
#include "Math\Matrix4X4.h"
#include "Graphics\GraphicsEngine.h"
#include "Graphics\ShaderProgram.h"
#include "Graphics\UniformBuffer.h"

class App
{
public:
	App();
	~App();

public:
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnQuit();

public:
	void Run();
	void Quit();

private:
	bool m_isRunning = true;
	std::unique_ptr<CoreWindow> m_display;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;

	VertexArrayObjectPtr m_polygonVAO;
	ShaderProgramPtr m_shaderProgram;
	UniformBufferPtr m_uniformBuffer;

	std::chrono::system_clock::time_point m_previousTime;
	F32 m_scale = 1.0f;
};
