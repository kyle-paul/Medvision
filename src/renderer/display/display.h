#pragma once
#include "../../exlibs.h"
#include "../../standard.h"
#include "../buffer/VertexArray.h"
#include "../buffer/IndexBuffer.h"
#include "../shaders/shader.h"

class Display
{
public:
    void Draw(const VertexArray &vao, const IndexBuffer &fbo, const Shader &shader) const;
    void Clear() const;
};