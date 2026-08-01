#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>


namespace render {
class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();

    bool create(int width, int height);
    void destroy();

    void resize(int width, int height);

    void bind();
    void unbind();

    GLuint getTexture() const;

    int width() const;
    int height() const;

private:
    GLuint mFbo = 0;
    GLuint mColorTexture = 0;
    GLuint mDepthRbo = 0;
    GLuint mDepthRenderbuffer = 0;

    int mWidth = 0;
    int mHeight = 0;
};
} // namespace render

