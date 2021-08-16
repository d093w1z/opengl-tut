#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>

#include "libmygraph.h"
#include "renderer.h"
#include "bufferLayout.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

struct ShaderSource
{
    std::string vs;
    std::string fs;
};

static void loadShaders(const std::string filename, ShaderSource &ss)
{
    std::cout << filename << std::endl;
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == nullptr)
    {
        std::cout << "Failed to open " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    std::string linestr;
    enum class sType
    {
        vertex,
        fragment
    } st;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        linestr = line;
        ssize_t pos = linestr.find("#section");
        if (pos != std::string::npos)
        {
            if (linestr.find("vertex") != std::string::npos)
            {
                st = sType::vertex;
            }
            else if (linestr.find("fragment") != std::string::npos)
            {
                st = sType::fragment;
            }
            continue;
        }
        if (st == sType::vertex)
        {
            ss.vs.append(linestr);
        }
        else if (st == sType::fragment)
        {
            ss.fs.append(linestr);
        }
    }
    // std::cout << "Vertex: " << std::endl;
    // std::cout << ss.vs << std::endl;
    // std::cout << "Frag" << std::endl;
    // std::cout << ss.fs << std::endl;
}

static GLuint compileShader(GLuint shaderType, const char *shaderSource)
{

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint createShader(ShaderSource &ss)
{
    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, ss.vs.c_str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, ss.fs.c_str());
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    // glDetachShader(program, vs);
    // glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main()
{
    // initialise glfw
    if (!glfwInit())
    {
        std::cout << "Error: failed to initialise GLFW." << std::endl;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    // create glfw window
    GLFWwindow *window = glfwCreateWindow(640, 480, "DWDEV-Grapher", NULL, NULL);
    if (!window)
    {
        std::cout << "Error: failed to create window." << std::endl;
    }

    // Get OpenGL context
    glfwMakeContextCurrent(window);

    // Set key callback
    glfwSetKeyCallback(window, KeyCallback);

    // init GLEW(OpenGL initialisation)
    GLenum err = glewInit();
    std::cout << err << std::endl;

    // Print Version of OpenGL
    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    // Define array for vetrices
    // abstraction to shape
    float points[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };
    unsigned int index[] = {
        0, 1, 2,
        2, 3, 0};

    VertexArray va;

    // create a buffer and add data
    VertexBuffer vb(points, sizeof(points));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);


    IndexBuffer ib(index, 6);

    ShaderSource ss;
    loadShaders("../res/glsl/shader.glsl", ss);
    GLuint shaderProgram = createShader(ss);

    glUseProgram(shaderProgram);

    // loops till user terminates
    while (!glfwWindowShouldClose(window))
    {
        // clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    return 0;
}