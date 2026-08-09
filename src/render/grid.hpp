#pragma once
#include <glad/glad.h>
#include "camera/camera.hpp"
#include "geometry/vertex.hpp"

using  app::geometry::Vertex;
namespace render
{
    class Grid
    {
    private:
        GLuint mVAO, mVBO;
        Vertex vertice;
        std::vector<Vertex> mVertices;
        GLsizei mVertexCount;
    public:

        Grid(/* args */);
        bool init();

        void draw();
    };
    
 
    
} // namespace render
