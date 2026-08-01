#include "framebuffer.hpp"

namespace render {
Framebuffer::Framebuffer() {
}

Framebuffer::~Framebuffer() {
    destroy();
}

bool Framebuffer::create(int width, int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    printf("Framebuffer FBO ID: %u\n", mFbo);

    // Crear una txtura
    glGenTextures(1, &mColorTexture);
    glBindTexture(GL_TEXTURE_2D, mColorTexture);

    // Reserva de memoria pra la textura
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        mColorTexture,
        0
    );

    glGenRenderbuffers(1, &mDepthRenderbuffer);

    glBindRenderbuffer(
        GL_RENDERBUFFER,
        mDepthRenderbuffer
    );

    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        width,
        height
    );

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        mDepthRenderbuffer
    );

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer incompleto: \n");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void Framebuffer::destroy() {
    if (mDepthRenderbuffer != 0) {
        glDeleteRenderbuffers(1, &mDepthRenderbuffer);
        mDepthRenderbuffer = 0;
    }

    if (mColorTexture != 0) {
        glDeleteTextures(1, &mColorTexture);
        mColorTexture = 0;
    }

    if (mFbo != 0) {
        glDeleteFramebuffers(1, &mFbo);
        mFbo = 0;
    }

    mWidth = 0;
    mHeight = 0;
}

void Framebuffer::resize(int width, int height) {
    if (width <= 0 || height <= 0)
        return;
        
    // Evitar recrear si no cambia el tamaño
    if (width == mWidth && height == mHeight)
        return;

    destroy();
    create(width, height);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Framebuffer::getTexture() const {
    return mColorTexture;
}

int Framebuffer::width() const {
    return mWidth;
}

int Framebuffer::height() const {
    return mHeight;
}


} // namespace render


