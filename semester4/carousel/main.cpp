#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include "stdafx.h"
#include <gl\freeglut.h>
#endif

void Init() {
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
}

void RenderScene() {
  // Set background
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 1., 0);

  // Reset matrix
  glLoadIdentity();

  // Display wirecube
  glutWireCube(0.2);

  glPushMatrix();
    // Draw ground
    float size = 1.0f;
    glBegin(GL_POLYGON);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glVertex3f(-size/2.0f,-size/2.0f,-size/2.0f);
      glVertex3f(+size/2.0f,-size/2.0f,-size/2.0f);
      glVertex3f(+size/2.0f,-size/2.0f,+size/2.0f);
      glVertex3f(-size/2.0f,-size/2.0f,+size/2.0f);
    glEnd();

    glBegin(GL_POLYGON);
      glColor4f(1.0f,0.0f,1.0f,1.0f);
      glVertex3f(+size/2.0f,+size/2.0f,-size/2.0f);
      glVertex3f(+size/2.0f,-size/2.0f,-size/2.0f);
      glVertex3f(-size/2.0f,-size/2.0f,-size/2.0f);
      glVertex3f(-size/2.0f,+size/2.0f,-size/2.0f);
    glEnd();
  glPopMatrix();

  // Define camera
  gluLookAt(1., 1., 1.,
            0., 0., 0.,
            0., 1., 0.);

  // Empty buffer
  glFlush();
}

void Reshape(int width, int height) {
  glMatrixMode(GL_PROJECTION);

  // Reset matrix
  glLoadIdentity();

  glViewport(0, 0, width, height);
  // glOrtho( -1., 1., -1., 1., 0.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void Animate(int value) {
  glutPostRedisplay();

  glutTimerFunc(100, Animate, ++value);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Carousel");

  glutDisplayFunc(RenderScene);
  glutReshapeFunc(Reshape);
  glutTimerFunc(10, Animate, 0);

  Init();
  glutMainLoop();
  
  return 0;
}
