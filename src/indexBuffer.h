#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{
private:
    unsigned int mRendererID;
    unsigned int mCount;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void bind();
    void unbind();

    GLuint GetCount() { return mCount; }
};