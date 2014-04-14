// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 29.07.2011


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

void Init()
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig
   // durchgef�hrt werden m�ssen
}

void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor( 2.5, 0.5, 0.0, 1.0);

   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   glBegin( GL_POLYGON );
     glColor4f( 0.0, 0.0, 1.0, 1.0);
     glVertex3f( -0.5, -0.5, -0.5 );
     glVertex3f(  0.5, -0.5, -0.5 );
     glVertex3f(  0.5,  0.5, -0.5 );
     glVertex3f( -0.5,  0.5, -0.5 );
   glEnd();
   glFlush(); //Buffer leeren
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Ver�nderung der Gr��e des
   // Graphikfensters statt
}

void Animate (int value)
{
   // Hier werden Berechnungen durchgef�hrt, die zu einer Animation der Szene
   // erforderlich sind. Dieser Prozess l�uft im Hintergrund und wird alle
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins
   // inkrementiert und dem Callback wieder uebergeben.
   std::cout << "value=" << value << std::endl;
   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren; Animate wird so nach 100 msec mit value+=1 aufgerufen
   glutTimerFunc(100, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Name_1; Name_2" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
