#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:
    unsigned int mRendererID;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};