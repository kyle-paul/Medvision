#pragma once
#include "../exlibs.h"
#include "../standard.h"
#include "../renderer/buffer/VertexArray.h"
#include "../renderer/buffer/VertexBuffer.h"
#include "../renderer/buffer/IndexBuffer.h"

class Factory
{
public:
    Factory();
    ~Factory();
    void create_cube();
    void draw() const;

private:
    unsigned int EntityMade;
    std::unordered_map<unsigned int, VertexArray *> VAOs;
    std::unordered_map<unsigned int, IndexBuffer *> FBOs;
};