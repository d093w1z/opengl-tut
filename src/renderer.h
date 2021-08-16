#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam );

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//     {
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
//     }
// }

