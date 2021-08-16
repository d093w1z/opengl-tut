#pragma once

#include "bufferLayout.h"
#include "vertexBuffer.h"

class VertexArray
{
private:
    unsigned int mRendererID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
    void bind() const;
    void unbind() const;
};
