/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: Clock.cpp                                            */
/*	                                                            */
/* Autor: W.-D. Groch                                          */
/* letzte Aenderung:	Groch   03.05.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*  Uhrzeit ermitteln und ausgeben                             */
/*	                                                            */
/* ----------------------------------------------------------- */

#include <iostream>      
#include <GL/freeglut.h>         //laedt alles fuer OpenGL
#include <math.h>
#include <time.h>

GLfloat extent = 1.0; // Mass fuer die Ausdehnung des Modells


void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgefuehrt werden muessen

   // Uhrzeit abfragen und ausgeben
   time_t long_time;
   struct tm*  newtime;
   time(&long_time);
   newtime = localtime(&long_time);   // aktuelle Uhrzeit in struct lesen
   std::cout << "aktuelle Stunde =" << newtime->tm_hour << std::endl;   
   std::cout << "aktuelle Minute =" << newtime->tm_min << std::endl;   
}

void RenderScene(void)
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Puffer loeschen
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Veraenderung der Groesse des 
   // Graphikfensters statt
}

void Animate (int value)    
{
   // An dieser Stelle werden Berechnungen durchgefuehrt, die zu einer
   // Animation der Szene erforderlich sind. Dieser Prozess laeuft im Hintergrund.
   // Wird alle wait_msec Milli-Sekunden aufgerufen. Hier wird der Parameter 
   // "value" einfach nur um eins inkrementiert und dem Callback wieder uebergeben.
   std::cout << "value=" << value << std::endl;
   // RenderScene aufrufen.
   glutPostRedisplay();
   // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
   int wait_msec = 1000;
   glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   printf ("Testprogramm: Uhrzeit ermitteln und ausgeben \n\n");
   printf ("Zum Beenden Graphik-Fenster schliessen!\n\n");
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
   glutInitWindowSize ( 600,600 );
   glutCreateWindow ("*** Uhrzeit ermitteln ***");
   glutDisplayFunc ( RenderScene );
   glutReshapeFunc ( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc(10,Animate,0);                 
   Init();
   glutMainLoop ();
   return 0;
}