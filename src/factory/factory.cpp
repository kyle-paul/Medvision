#include "factory.h"

Factory::Factory()
{
    EntityMade = 1;
}

Factory::~Factory()
{
    for (const auto &element : VAOs)
    {
        delete element.second;
    }
    for (const auto &element : FBOs)
    {
        delete element.second;
    }
}

void Factory::create_cube()
{
    float l = 0.5f;
    float w = 0.5f;
    float h = 0.5f;

    std::vector<float> positions = {
        l, w, -h, l, -w, -h, -l, -w, -h, -l, w, -h,
        -l, -w, h, l, -w, h, l, w, h, -l, w, h};

    std::vector<float> normals = {
        0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    std::vector<float> texCoords = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    std::vector<unsigned int> faces = {
        0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7,
        3, 2, 7, 2, 4, 7, 0, 1, 6, 0, 6, 5,
        1, 2, 5, 2, 4, 5, 0, 3, 7, 0, 7, 6};

    VertexArray *vao = new VertexArray();
    IndexBuffer *fbo = new IndexBuffer(faces);

    VertexBuffer *vbo = new VertexBuffer(positions);
    VertexBuffer *nbo = new VertexBuffer(normals);
    VertexBuffer *tbo = new VertexBuffer(texCoords);

    VertexBufferLayout positions_layout;
    VertexBufferLayout normals_layout;
    VertexBufferLayout texCoord_layout;

    positions_layout.AddFloat(3);
    normals_layout.AddFloat(3);
    texCoord_layout.AddFloat(2);

    vao->Bind();
    vao->receiveBuffer(0, *vbo, positions_layout);
    vao->receiveBuffer(1, *nbo, normals_layout);
    vao->receiveBuffer(2, *tbo, texCoord_layout);

    VAOs[EntityMade] = vao;
    FBOs[EntityMade++] = fbo;
}

void Factory::draw() const
{
    for (const auto &element : VAOs)
    {
        element.second->Bind();
        FBOs.at(element.first)->Bind();
        glDrawElements(GL_TRIANGLES, FBOs.at(element.first)->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
    }
}
