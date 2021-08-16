#include "vertexArray.h"

VertexArray::VertexArray(/* args */)
{
    glGenVertexArrays(1, &mRendererID);

}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();
    unsigned int offset = 0;

    const auto &elements = layout.GetElements();

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        // enable attribute of the array
        glEnableVertexAttribArray(i);

        // set layout       ( index, size, type, normalized, stride, pointer)
        glVertexAttribPointer(i, element.count, element.type, elements[i].normalized, layout.GetStride(), (const GLvoid *)offset);

        offset += element.count * LayoutElement::GetSizeByType(element.type);
    }
}

void VertexArray::bind() const{
    glBindVertexArray(mRendererID);
}
void VertexArray::unbind() const{
    glBindVertexArray(0);
}