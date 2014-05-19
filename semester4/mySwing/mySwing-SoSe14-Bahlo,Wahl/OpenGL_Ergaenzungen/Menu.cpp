/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: Menu.cpp                                             */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                            */
/* Autor: W. Kestner, W.-D. Groch                              */
/* letzte Aenderung:	Groch   03.05.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*  Rechte Maustaste um Menu zu oeffnen                        */
/*	                                                            */
/* ----------------------------------------------------------- */

/* Menu Management
GLUT supports simple cascading pop-up menus. They are designed to 
let a user select various modes within a program. The functionality
is simple and minimalistic and is meant to be that way. Do not 
mistake GLUT’s pop-up menu facility with an attempt to create a 
full-featured user interface. It is illegal to create or destroy
menus, or change, add, or remove menu items while a menu (and any 
cascaded sub-menus) are in use (that is, popped up).

glutCreateMenu creates a new pop-up menu.
Usage
int glutCreateMenu(void (*func)(int value));
func The callback function for the menu that is called when a menu 
entry from the menu is selected. The value passed to the callback 
is determined by the value for the selected menu entry.
Description
glutCreateMenu creates a new pop-up menu and returns a unique small 
integer identifier. The range of allocated identifiers starts at one. 
The menu identifier range is separate from the window identifier 
range. Implicitly, the current menu is set to the newly created menu. 
This menu identifier can be used when calling glutSetMenu.
When the menu callback is called because a menu entry is selected 
for the menu, the current menu will be implicitly set to the menu 
with the selected entry before the callback is made.

glutAddMenuEntry adds a menu entry to the bottom of the current menu.
Usage
void glutAddMenuEntry(char *name, int value);
name: ASCII character string to display in the menu entry.
value: Value to return to the menu’s callback function if the menu 
entry is selected.
Description
glutAddMenuEntry adds a menu entry to the bottom of the current 
menu. The string name will be displayed for the newly added menu 
entry. If the menu entry is selected by the user, the menu’s 
callback will be called passing value as the callback’s parameter.

glutAddSubMenu adds a sub-menu trigger to the bottom of the current menu.
Usage
void glutAddSubMenu(char *name, int menu);
name: ASCII character string to display in the menu item from which 
to cascade the sub-menu.
menu: Identifier of the menu to cascade from this sub-menu menu item.
Description
glutAddSubMenu adds a sub-menu trigger to the bottom of the current menu. 
The string name will be displayed for the newly added sub-menu trigger. 
If the sub-menu trigger is entered, the sub-menu numbered menu
will be cascaded, allowing sub-menu menu items to be selected.
*/ 

#include <windows.h>
#include <GL/freeglut.h>         //laedt alles fuer OpenGL
#include <iostream>
#include <math.h>
#include "Wuerfel_mit_Normalen.h"

GLfloat extent = 1.0f;// Mass fuer die Ausdehnung des Modells

void mainMenu(int item)
{	
    switch(item)
    {
    case 1 :
        std::cout <<"Exit"<<std::endl;
        exit(0);
    }
}

void backGroundColor (int item)
{   
    switch(item)
    {
        case 1 :
        {
            glClearColor(1.0f,1.0f,1.0f,1.0f);	// Hintergrundfarbe weiss definieren 
            // RenderScene aufrufen.
            glutPostRedisplay();
            break;
        }
        case 2 :
        {
            glClearColor(1.0f,0.0f,0.0f,1.0f);	// Hintergrundfarbe rot definieren 
            // RenderScene aufrufen.
            glutPostRedisplay();
            break;
        }
        case 3 :
        {
            glClearColor(0.33f,0.225f,0.0f,1.0f);// Hintergrundfarbe gold definieren 
            // RenderScene aufrufen.
            glutPostRedisplay();
            break;
        }
    }
}

void Init()	
{
// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
// durchgefuehrt werden muessen
    glClearColor ( 0.33f, 0.225f, 0.0f, 1.0f);	//Hintergrundfarbe definieren
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0); 

    // Unter-Menu
    int submenu1; 
    submenu1 = glutCreateMenu(backGroundColor);
    glutAddMenuEntry("BackgroundColor WHITE", 1);
    glutAddMenuEntry("BackgroundColor RED", 2);
    glutAddMenuEntry("BackgroundColor GOLD", 3);

    // Haupt-Menu
    glutCreateMenu(mainMenu);
    glutAddSubMenu("Background color", submenu1);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void RenderScene(void)
{
// Hier befindet sich der Code der in jedem frame ausgefuehrt werden muss
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Puffer loeschen
    glLoadIdentity();
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
    glOrtho(-extent*2.0,+extent*2.0,-extent*2.0,+extent*2.0,-extent*2.0,+extent*2.0); //Frustum
    glMatrixMode(GL_MODELVIEW); //Modellierungs/Viewing-Matrix
}


void Animate (int value)
{
   // Hier werden Berechnungen durchgefuehrt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess laeuft im Hintergrund und wird alle 
   // wait_msec Milli-Sekunden aufgerufen. Der Parameter "value" wird einfach  
   // nur um eins inkrementiert und dem Callback wieder uebergeben. 
   std::cout << "value=" << value << std::endl;
   // RenderScene aufrufen.
   glutPostRedisplay();
   // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
   int wait_msec = 1000;
   glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   std::cout<<"Grundlegende Interaktionen:"<<std::endl;
    std::cout<<"Rechte Maustaste (ueber dem Graphik-Fenster)"<<std::endl;
    std::cout<<"zum Oeffnen des Menus verwenden"<<std::endl<<std::endl;
    std::cout<<"Beenden: Graphik-Fenster schliessen oder per Menu!"<<std::endl<<std::endl;
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );
    glutCreateWindow ("*** Menu-Management ***");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
