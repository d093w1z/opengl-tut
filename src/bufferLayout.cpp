#include "bufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
    :mStride(0)
{
}

template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    mElements.push_back({GL_FLOAT, count, GL_FALSE});
    mStride += count * LayoutElement::GetSizeByType(GL_FLOAT);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    mStride += count * LayoutElement::GetSizeByType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    mStride += count * LayoutElement::GetSizeByType(GL_UNSIGNED_BYTE);
}