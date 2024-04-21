

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"   vertexColor = color;\n"
"}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"in vec3 vertexColor;\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"    fragColor = vec4(vertexColor, 1.0f);\n"
"}\n\0";

void OnFramebufferResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OnInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //GLFW Intitialisation
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create Window
    GLFWwindow* window = glfwCreateWindow(960, 540, "LearningOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Setting GLFW Context
    glfwMakeContextCurrent(window);

    //Initializing OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL" << std::endl;
        return -1;
    }

    //Setting Viewport Dimensions
    glViewport(0, 0, 960, 540);
    glfwSetFramebufferSizeCallback(window, OnFramebufferResize);

    //Shaders
    int result = 0;
    char infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Vertex Input
    float vertices[] = {
        //Positions         //Color
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,    // top left
    };

    GLuint indices[] = {
        0,1,3,
        1,2,3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Creating Vertex Buffer Object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Vertex Data Formatting
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        //Input Processing
        OnInput(window);

        //Rendering Commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Swap Buffers
        glfwSwapBuffers(window);

        //Check and Call events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

	return 0;
}
