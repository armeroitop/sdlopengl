#pragma once
#include <glad/glad.h>
#include "camera/camera.hpp"


namespace render
{
    class Grid
    {
    private:
        GLuint mVAO, mVBO;
        std::vector<glm::vec3> mVertices;
        GLsizei mVertexCount;
    public:

        Grid(/* args */);
        bool init();

        void draw();
    };
    
 
    
} // namespace render
