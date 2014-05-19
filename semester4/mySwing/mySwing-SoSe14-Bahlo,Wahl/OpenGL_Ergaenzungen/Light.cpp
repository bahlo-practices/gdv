/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: Light.cpp                                            */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                            */
/* Autor: W.-D. Groch                                          */
/* letzte Aenderung:	Groch   13.10.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*  Wuerfel selbst beleuchten; (einer mit eigenen Normalen     */
/*	                                                            */
/* ----------------------------------------------------------- */

#include <windows.h>
#include <GL/freeglut.h>         //laedt alles fuer OpenGL
#include <stdio.h>
#include <math.h>
#include "Wuerfel_mit_Normalen.h"

GLfloat extent = 1.0;   // Mass fuer die Ausdehnung des Modells
GLfloat winkel=0.0; 	   // fuer Rotationen um die Y-Achse


void Init()	
{
// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
// durchgefuehrt werden muessen
    glClearColor(0.33f,0.225f,0.0f,1.0f);	// Hintergrundfarbe definieren
    // Licht
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    GLfloat light_position [] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position ); // Licht Nr. 0 rechts oben
    glEnable(GL_COLOR_MATERIAL);
    // z-Buffer
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    // Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
    glEnable(GL_NORMALIZE);
}

void RenderScene(void)
{
// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Puffer loeschen
    glLoadIdentity ();
    gluLookAt (0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Kamera von vorne oben

    // Test mit eigenem Wuerfel inkl. Normalen
    glRotatef(winkel, 0.0, 1.0, 0.0);   // Wuerfel in Drehung versetzen
    Wuerfel_mit_Normalen(0.5);
    // Vordefinierter Wuerfel (bringt seine Normalen mit)
    glTranslatef ( 0.0, 0.0, 0.5 );
    glColor4f(0.0f,1.0f,0.0f,1.0f);	    // GRUEN
    glutSolidCube(0.3);

    glutSwapBuffers();
    glFlush ();
}

void Reshape(int width,int height)
{
// Hier finden die Reaktionen auf eine Veraenderung der Groesse des 
// Graphikfensters statt	
    glMatrixMode(GL_PROJECTION); //Matrix fuer Transf. Frustum->Viewport
    glLoadIdentity();
    glViewport(0,0,width,height);
    gluPerspective(50.0, 1.0, 1.0, +5.0*extent);
    glMatrixMode(GL_MODELVIEW); //Modellierungs/Viewing-Matrix
}

void Animate (int value) 
{
// An dieser Stelle werden Berechnungen durchgefuehrt, die zu einer
// Animation der Szene erforderlich sind. Dieser Prozess laeuft im Hintergrund.
    winkel = winkel + 5.0f; // Rotationswinkel
    if (winkel>360.0f)
        winkel = winkel-360.0f;

    // RenderScene aufrufen.
    glutPostRedisplay();
    // Timer wieder registrieren - Animate also nach wait_msec Milli-Sekunden wieder aufrufen
    int wait_msec = 50;
    glutTimerFunc(wait_msec, Animate, ++value);           
}

int main(int argc, char **argv)
{
    printf ("Testprogramm: Beleuchtete Wuerfel um y-Achse drehen \n\n");
    printf ("Zum Beenden Graphik-Fenster schliessen!\n\n");
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );	
    glutCreateWindow ("Beleuchtete Wuerfel um y-Achse drehen");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
