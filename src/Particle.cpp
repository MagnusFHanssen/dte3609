#include "../include/Particle.hpp"
#include "../include/stb_image.h"

#include <iostream>
#include <random>

Particle::Particle(){}

Particle::Particle(glm::vec3 pos, glm::vec3 fall) : pos_{pos}, fall_{fall}{}

Particle::~Particle(){}

void Particle::privateInit(){
    initVariables();

    for (loop_ = 0; loop_ < MAX_PARTICLES; loop_++){
        particles[loop_].active = true;
        particleInit(loop_);
    }

    loadTexture();
}

void Particle::privateRender(){
    glDisable(GL_FOG);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName_);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glLoadIdentity();
    draw();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);


    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_FOG);
}

void Particle::privateUpdate(){}

void Particle::draw(){
    for (loop_ = 0 ; loop_ < MAX_PARTICLES ; loop_++){					// Loop Through All The Particles
        if (particles[loop_].active){							// If The Particle Is Active
            float x = particles[loop_].x;						// Grab Our Particle X Position
            float y = particles[loop_].y;						// Grab Our Particle Y Position
            float z = particles[loop_].z + zoom_;					// Particle Z Pos + Zoom

            glColor3f(1.0f, 1.0f, 1.0f);

            glBegin(GL_TRIANGLE_STRIP);
                glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2d(1,1); glVertex3f(x + size_, y + size_, z); // Top Right
                glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2d(0,1); glVertex3f(x - size_, y + size_, z); // Top Left
                glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2d(1,0); glVertex3f(x + size_, y - size_, z); // Bottom Right
                glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2d(0,0); glVertex3f(x - size_, y - size_, z); // Bottom Left
            glEnd();

            particles[loop_].x += particles[loop_].x_v/(slow_.x);
            particles[loop_].y += particles[loop_].y_v/(slow_.y);
            particles[loop_].z += particles[loop_].z_v/(slow_.z);

            particles[loop_].x_v += particles[loop_].x_a;
            particles[loop_].y_v += particles[loop_].y_a;
            particles[loop_].z_v += particles[loop_].z_a;

            particles[loop_].life -= particles[loop_].fade;

            if (particles[loop_].life < 0.0f){// If Particle Is Burned Out
                particleInit(loop_);
            }
        }
    }

}


bool Particle::loadTexture()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName_);

    glBindTexture(GL_TEXTURE_2D, texName_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./resources/textures/particle.jpg", &width, &height, &nrChannels, 0);

    if(data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        return false;

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, NULL);

    return true;
}

void Particle::particleInit(GLuint loop)
{
    particles[loop].x = pos_.x;
    particles[loop].y = pos_.y;
    particles[loop].z = pos_.z;

    particles[loop].life = life_;								// Give All The Particles Full Life
    particles[loop].fade = float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed

    particles[loop].x_v = float((rand()%60)-30.0f);	// X component of velocity
    particles[loop].y_v = float((rand()%60)-30.0f);	// Y component of velocity
    particles[loop].z_v = float((rand()%60)-30.0f);	// Z component of velocity

    particles[loop].x_a = fall_.x;
    particles[loop].y_a = fall_.y;
    particles[loop].z_a = fall_.z;

}

void Particle::initVariables()
{
    slow_ = {3000.0f, 500000.0f, 3000.0f};

    size_ = 0.5f;
    life_ = 20.0f;
    zoom_ = -50.0f;
}
