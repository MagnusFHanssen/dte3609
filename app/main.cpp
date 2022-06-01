
#include <windows.h>
#include <gl/glew.h>
#include <GL/freeglut.h>
#include "../include/glext.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../include/Input.hpp"
#include "../include/FpsCounter.hpp"
#include "../include/GameManager.hpp"
#include "../../glm-master/glm/glm.hpp"

#include "../include/stb_implementation.h"

#include <iostream>

std::shared_ptr<GameManager> gm;
siut::FpsCounter counter;

int window;

bool keyPressed[30];
int mousePosX, mousePosY; 
float moveX, moveY;

void init()
{
    GLenum err = glewInit();
    if (err != GL_NO_ERROR)
      std::cout<< "OpenGL error: " << gluErrorString(err) << std::endl;
    std::cout.flush();

  glClearColor(0.7, 0.7, 1.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  counter.start();

  gm.reset(new GameManager());
  gm->init();

  for(int i=0; i<30; i++)
    keyPressed[i]=false;


}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gm->update(counter.fps());
  gm->render();

  if(keyPressed[KEY_ID_W]==true)      gm->getCam()->moveForward();
  if(keyPressed[KEY_ID_A]==true)      gm->getCam()->moveLeft();
  if(keyPressed[KEY_ID_D]==true)      gm->getCam()->moveRight();
  if(keyPressed[KEY_ID_S]==true)      gm->getCam()->moveBackward();
  if(keyPressed[KEY_ID_SPACE]==true)  gm->getCam()->moveUp();
  if(keyPressed[KEY_ID_C]==true)      gm->getCam()->moveDown();
  if(keyPressed[KEY_ID_LEFT]==true)   gm->getMC()->moveLeft();
  if(keyPressed[KEY_ID_RIGHT]==true)  gm->getMC()->moveRight();
  if(keyPressed[KEY_ID_E]==true)      gm->getCam()->turnLeft();
  if(keyPressed[KEY_ID_R]==true)      gm->getCam()->turnRight();
  if(keyPressed[KEY_ID_F]==true)      gm->getCam()->turnUp();
  if(keyPressed[KEY_ID_V]==true)      gm->getCam()->turnDown();

  glutSwapBuffers();
  glutPostRedisplay();

  // Terminating from within game:
  if (gm->isFinished()){
              glutDestroyWindow(window);
        #ifndef _WIN32
              // Must use this with regular glut, since it never returns control to main().
              exit(0);
        #endif
  }

}

void keyDown(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'q':
    case 27:
      glutDestroyWindow(window);
#ifndef _WIN32
      // Must use this with regular glut, since it never returns control to main().
      exit(0);
#endif
      break;
      
    case 'w':
      keyPressed[KEY_ID_W] = true;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = true;
      break;
    case 's':
      keyPressed[KEY_ID_S] = true;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = true;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = true;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = true;
      break;
  case 'e':
      keyPressed[KEY_ID_E] = true;
      break;
  case 'r':
      keyPressed[KEY_ID_R] = true;
      break;
  case 'f':
      keyPressed[KEY_ID_F] = true;
      break;
  case 'v':
      keyPressed[KEY_ID_V] = true;
      break;

    default:
      glutPostRedisplay();
  }
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'w':
      keyPressed[KEY_ID_W] = false;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = false;
      break;
    case 's':
      keyPressed[KEY_ID_S] = false;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = false;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = false;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = false;
      break;
  case 'e':
      keyPressed[KEY_ID_E] = false;
      break;
  case 'r':
      keyPressed[KEY_ID_R] = false;
      break;
  case 'f':
      keyPressed[KEY_ID_F] = false;
      break;
  case 'v':
      keyPressed[KEY_ID_V] = false;
      break;

  }
}

void specKeyDown(int key, int x, int y)
{
    switch(key){
    case GLUT_KEY_UP:
      keyPressed[KEY_ID_UP] = true;
      break;
  case GLUT_KEY_DOWN:
      keyPressed[KEY_ID_DOWN] = true;
      break;
  case GLUT_KEY_LEFT:
      keyPressed[KEY_ID_LEFT] = true;
      break;
  case GLUT_KEY_RIGHT:
      keyPressed[KEY_ID_RIGHT] = true;
      break;
    }
}

void specKeyUp(int key, int x, int y)
{
    switch(key){
    case GLUT_KEY_UP:
      keyPressed[KEY_ID_UP] = false;
      break;
    case GLUT_KEY_DOWN:
      keyPressed[KEY_ID_DOWN] = false;
      break;
    case GLUT_KEY_LEFT:
      keyPressed[KEY_ID_LEFT] = false;
      break;
    case GLUT_KEY_RIGHT:
      keyPressed[KEY_ID_RIGHT] = false;
      break;
    }
}

void mousePressed(int button, int state, int posX, int posY)
{
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    mousePosX = posX;
    mousePosY = posY;
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }  
  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if(keyPressed[MOUSE_LEFT_BUTTON_DOWN])
  {
    int diffX = posX - mousePosX;
    mousePosX = posX;
    int diffY = posY - mousePosY;
    mousePosY = posY;
    
    // Implement quaternion based mouse move

  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.0f, float(w)/float(h) ,1.0f, 3000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Modern OpenGl
  glm::mat4 projection(1.0f);
  projection = glm::perspective(glm::radians(60.0f), float(w)/float(h), 0.1f, 300.0f);
  gm->updateProjectionMatrix(projection);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(900, 700);
  glutInitWindowPosition(10, 10);
  window = glutCreateWindow("Game application");
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutSpecialFunc(specKeyDown);
  glutSpecialUpFunc(specKeyUp);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);
  // Add other callback functions here..

  glutMainLoop();
  return 0;
}
