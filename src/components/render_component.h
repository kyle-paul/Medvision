#pragma once
#include "../exlibs.h"

struct RenderComponent
{
    Texture *texture;
    VertexArray *vao;
    IndexBuffer *fbo;
};