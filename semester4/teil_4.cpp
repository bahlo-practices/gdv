// opengleinfuehrung.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "erweiterungen/Wuerfel_mit_Normalen.h"
#else
#include "stdafx.h"
#include <gl\freeglut.h>
#include "erweiterungen\Wuerfel_mit_Normalen.h"
#endif

float fRotation = 315.0;

void Init()
{
  // Hier finden jene Aktionen statt, die zum Programmstart einmalig
  // durchgeführt werden müssen
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
  glClearColor(2.5, 0.5, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
  glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

  glutWireCube(0.2);
  glRotatef(fRotation, 0.0f, 0.0f, 1.0f);

  //Oberarm
  glPushMatrix();
    glScalef(1,0.5,0);
    glTranslatef(0.25, 0, 0);
    Wuerfel_mit_Normalen(0.4);
  glPopMatrix();

  //Unterarm
  glPushMatrix();
    glScalef(1, 0.25, 0);
    glTranslatef(0.65, 0, 0);
    Wuerfel_mit_Normalen(0.4);
  glPopMatrix();

  gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.);

  glFlush(); //Buffer leeren
}

void Reshape(int width, int height)
{
  // Hier finden die Reaktionen auf eine Veränderung der Größe des
  // Graphikfensters statt
  // Matrix für Transformation: Frustum->viewport
  glMatrixMode(GL_PROJECTION);
  // Aktuelle Transformations-Matrix zuruecksetzen
  glLoadIdentity();
  // Viewport definieren
  glViewport(0, 0, width, height);
  // Frustum definieren (siehe unten)
  glOrtho( -1., 1., -1., 1., 0.0, 1.0);
  // Matrix für Modellierung/Viewing
  glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
  // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene
  // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle
  // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins
  // inkrementiert und dem Callback wieder uebergeben.
  std::cout << "value=" << value << std::endl;

  // Rotate
  fRotation = fRotation - 1.0;  // Rotationswinkel aendern
  if (fRotation <= 0.0) {
     fRotation = fRotation + 360.0;
  }

  // RenderScene aufrufen
  glutPostRedisplay();
  // Timer wieder registrieren; Animate wird so nach 100 msec mit value+=1 aufgerufen
  glutTimerFunc(100, Animate, ++value);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);                // GLUT initialisieren
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);         // Fenster-Konfiguration
  glutCreateWindow("Arne Bahlo; Johannes Wahl");   // Fenster-Erzeugung

  glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
  glutReshapeFunc(Reshape);
  // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0
  glutTimerFunc(10, Animate, 0);
  Init();
  glutMainLoop();
  return 0;
}

