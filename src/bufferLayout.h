#pragma once
#include <vector>
#include <GL/glew.h>
#include <cassert>

struct LayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeByType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        assert(false && "Data type not supported.");
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<LayoutElement> mElements;
    unsigned int mStride;

public:
    VertexBufferLayout();

    template <typename T>
    void Push(unsigned int count)
    {
        assert(false && "Data type not supported.");
    }

    inline const std::vector<LayoutElement> &GetElements() const { return mElements; }
    inline unsigned int GetStride() const { return mStride; }
};

