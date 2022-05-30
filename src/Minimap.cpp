#include "../include/Minimap.hpp"

#include <iostream>


const unsigned int MAP_WIDTH = 600;
const unsigned int MAP_HEIGHT = 400;

Minimap::Minimap()
{

}

Minimap::~Minimap(){}

void Minimap::privateInit(){
    glGenTextures(1, &frameBuffer_);

    // Color attachment
    glGenTextures(1, &textureColorBuffer_);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAP_WIDTH, MAP_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer_, 0);

    glGenRenderbuffers(1, &renderBuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, MAP_WIDTH, MAP_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer_);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Minimap::startFB(){
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0f, float(MAP_WIDTH)/float(MAP_HEIGHT), 1.0f, 3000.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, 100.0f, 0.0f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
}

void Minimap::endFB(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Minimap::privateUpdate(){}

void Minimap::privateRender(){
}



