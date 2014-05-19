/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: SpecialFunc.cpp                                      */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                            */
/* Autor: W. Kestner, W.-D. Groch                              */
/* letzte Aenderung:	Groch   03.05.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*  Beobachten Sie die Ausgabe im Konsole-Fenster waehrend Sie  */
/*  eine Funktionstaste druecken                               */
/*	                                                            */
/* ----------------------------------------------------------- */

/*glutSpecialFunc sets the special keyboard callback for the 
current window.
Usage
void glutSpecialFunc(void (*func)(int key, int x, int y));
func The new special callback function.
Description
glutSpecialFunc sets the special keyboard callback for the current 
window. The special keyboard callback is triggered when keyboard 
function or directional keys are pressed. The key callback parameter 
is a GLUT KEY * constant for the special key pressed. The x and y 
callback parameters indicate the mouse in window relative 
coordinates when the key was pressed. When a new window is created, 
no special callback is initially registered and special key strokes 
in the window are ignored. Passing NULL to glutSpecialFunc
disables the generation of special callbacks. During a special 
callback, glutGetModifiers may be called to determine the state of 
modifier keys when the keystroke generating the callback occurred.
An implementation should do its best to provide ways to generate 
all the GLUT KEY * special keys. The available GLUT KEY * values are:
GLUT_KEY_F1 F1 function key.
GLUT_KEY_F2 F2 function key.
GLUT_KEY_F3 F3 function key.
GLUT_KEY_F4 F4 function key.
GLUT_KEY_F5 F5 function key.
GLUT_KEY_F6 F6 function key.
GLUT_KEY_F7 F7 function key.
GLUT_KEY_F8 F8 function key.
GLUT_KEY_F9 F9 function key.
GLUT_KEY_F10 F10 function key.
GLUT_KEY_F11 F11 function key.
GLUT_KEY_F12 F12 function key.
GLUT_KEY_LEFT Left directional key.
GLUT_KEY_UP Up directional key.
GLUT_KEY_RIGHT Right directional key.
GLUT_KEY_DOWN Down directional key.
GLUT_KEY_PAGE_UP Page up directional key.
GLUT_KEY_PAGE_DOWN Page down directional key.
GLUT_KEY_HOME Home directional key.
GLUT_KEY_END End directional key.
GLUT_KEY_INSERT Inset directional key.

Note that the escape, backspace, and delete keys are generated as an 
ASCII character.*/ 

#include <windows.h>
#include <GL/freeglut.h>         //laedt alles fuer OpenGL
#include <iostream>
#include <math.h>
#include "Wuerfel_mit_Normalen.h"

GLfloat extent = 1.0f;// Mass fuer die Ausdehnung des Modells
GLfloat x_winkel=0.0, y_winkel=0.0;


void Init()	
{
// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
// durchgefuehrt werden muessen
    glClearColor ( 0.33f, 0.225f, 0.0f, 1.0f);	//Hintergrundfarbe definieren
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
}

void RenderScene(void)
{
// Hier befindet sich der Code der in jedem frame ausgefuehrt werden muss
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Puffer loeschen
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // Kamera von vorne
    glRotatef(x_winkel, 1.0f, 0.0f, 0.0f);
    glRotatef(y_winkel, 0.0f, 1.0f, 0.0f);
    Wuerfel_mit_Normalen(extent);
    glutSwapBuffers(); 
    glFlush();
}

void Reshape(int width,int height)
{
// Hier finden die Reaktionen auf eine Veraenderung der Groesse des 
// Graphikfensters statt
    glMatrixMode(GL_PROJECTION); //Matrix fuer Transf. Frustum->viewport
    glLoadIdentity();
    glViewport(0,0,width,height);
    gluPerspective(90.0, 1.0, 1.0, +3.0*extent);

    glMatrixMode(GL_MODELVIEW); //Modellierungs/Viewing-Matrix
}

	void SpecialFunc ( int key, int x, int y )
// Funktions- und Pfeil-Tasten abfragen
{
    GLfloat xMousePos = float(x);
    GLfloat yMousePos = float(y);
    if (key<=12)		
        std::cout <<"GLUT_KEY_F"<< key <<"  "<< xMousePos<<", "<<yMousePos<<std::endl;
    else
    switch (key) {
        case GLUT_KEY_LEFT:
            std::cout <<"GLUT_KEY_LEFT "<< xMousePos<<", "<<yMousePos<<std::endl;
            y_winkel = y_winkel + 5.0f;
            if (y_winkel>360.0)
                y_winkel=0.0f;
            break;
        case GLUT_KEY_UP:
            std::cout <<"GLUT_KEY_UP "<< xMousePos<<", "<<yMousePos<<std::endl;
            x_winkel = x_winkel - 5.0f;
            if (x_winkel<0.0)
                x_winkel=360.0f;
            break;
        case GLUT_KEY_RIGHT:
            std::cout <<"GLUT_KEY_RIGHT "<< xMousePos<<", "<<yMousePos<<std::endl;
            y_winkel = y_winkel - 5.0f;
            if (y_winkel<0.0)
                y_winkel=360.0f;
            break;
        case GLUT_KEY_DOWN:
            std::cout <<"GLUT_KEY_DOWN "<< xMousePos<<", "<<yMousePos<<std::endl;
            x_winkel = x_winkel + 5.0f;
            if (x_winkel>360.0)
                x_winkel=0.0f;
            break;	
        case GLUT_KEY_PAGE_UP:
            std::cout <<"GLUT_KEY_PAGE_UP "<< xMousePos<<", "<<yMousePos<<std::endl;
            break;	
        case GLUT_KEY_PAGE_DOWN:
            std::cout <<"LUT_KEY_PAGE_DOWN "<< xMousePos<<", "<<yMousePos<<std::endl;
            break;	
        case GLUT_KEY_HOME:
            std::cout <<"GLUT_KEY_HOME "<< xMousePos<<", "<<yMousePos<<std::endl;
            break;	
        case GLUT_KEY_END:
            std::cout <<"GLUT_KEY_END "<< xMousePos<<", "<<yMousePos<<std::endl;
            glLoadIdentity();
            break;	
        case GLUT_KEY_INSERT:
            std::cout <<"GLUT_KEY_INSERT "<< xMousePos<<", "<<yMousePos<<std::endl;
            break;
    }
    // RenderScene aufrufen.
    glutPostRedisplay();
}

void Animate (int value)
{
   // Hier werden Berechnungen durchgefuehrt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess laeuft im Hintergrund und wird alle 
   // wait_msec Milli-Sekunden aufgerufen. 
   // RenderScene aufrufen.
   glutPostRedisplay();
   // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   std::cout<<"Grundlegende Interaktionen:"<<std::endl;
    std::cout<<"Klicken Sie zunaechst ins Grafikfenster;"<<std::endl;
    std::cout<<"druecken Sie die Pfeiltasten und die Funktionstasten"<<std::endl;
    std::cout<<"und beobachten Sie die Ausgaben an der Konsole."<<std::endl<<std::endl;
    std::cout<<"Zum Beenden Graphik-Fenster schliessen!"<<std::endl<<std::endl;
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );
    glutCreateWindow ("*** SpecialFunc ***");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    glutSpecialFunc( SpecialFunc );     //NEU
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
