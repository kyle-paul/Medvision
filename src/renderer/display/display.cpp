#include "display.h"

void Display::Draw(const VertexArray &vao, const IndexBuffer &fbo, const Shader &shader) const
{
    shader.Bind();
    vao.Bind();
    fbo.Bind();
    glDrawElements(GL_TRIANGLES, fbo.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
}

void Display::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}