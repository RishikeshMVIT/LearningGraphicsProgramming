#pragma once

#include "Platform\CoreWindow.h"
#include "Graphics\GraphicsEngine.h"

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

	VertexArrayObjectPtr m_triangleVAO;
	ShaderProgramPtr m_shaderProgram;
};
