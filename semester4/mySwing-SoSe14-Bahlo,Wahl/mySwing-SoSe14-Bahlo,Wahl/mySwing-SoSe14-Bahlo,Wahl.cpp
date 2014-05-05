#define _USE_MATH_DEFINES
#define NUM_TEXTURES 1           //Anzahl der Texturen

#include <iostream>
#include <math.h>
#include <stdio.h>

#include "erweiterungen/Wuerfel_mit_Normalen.h"
#include "OpenGL_Ergaenzungen/myBitmap.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include "stdafx.h"
#include "GL\freeglut.h"
#endif

GLfloat rotate_y = 0;		//alte L�sung: Drehung des Objektes
GLfloat rotate_x = 0;

float fRotation = 315; //Wert f�r Schaukel Schwingung
float gRotation = 315; //Wert f�r Rotation des gesamten OBjekts

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -2.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

GLenum filterMode = GL_LINEAR;   //Init-Wert fuer die Texturfilterung
GLuint texNum = 0;               //Startwert fuer "level of detail"
GLuint texture[NUM_TEXTURES];    //Textur-Pointer-Array

void ZeichneUmwelt(GLfloat relativ){
	glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten
	glBindTexture(GL_TEXTURE_2D, texture[texNum]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	glBegin(GL_QUADS);
	 //Textur aus einem Bild
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -2.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(2.0, -2.0, 1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, -2.0, 1.0);
	 ////Alternativ dieser Block: Textur aus 2*2 Bildern
	 ////glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
	 ////glTexCoord2f(2.0, 0.0); glVertex3f( 2.0, -2.0, 0.0);
	 ////glTexCoord2f(2.0, 2.0); glVertex3f( 2.0,  2.0, 0.0);
	 ////glTexCoord2f(0.0, 2.0); glVertex3f(-2.0,  2.0, 0.0);
	glEnd();

	//glBegin(GL_POLYGON);   //Bodenflaeche
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glTexCoord2f(0.0, 0.0);
	//glVertex3f(-relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	//glTexCoord2f(1.0, 0.0);
	//glVertex3f(+relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	//glTexCoord2f(1.0, 1.0);
	//glVertex3f(+relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	//glTexCoord2f(0.0, 1.0);
	//glVertex3f(-relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	//glEnd();




	glFlush();
	glDisable(GL_TEXTURE_2D);
}

static void LoadGLTextures()     //Bitmaps laden und in Texturen umwandeln
{
	myRGBImage *textureImage[NUM_TEXTURES];
	int i;
	for (i = 0; i<NUM_TEXTURES; i++) {
		textureImage[i] = (myRGBImage *)malloc(sizeof(myRGBImage));
		if (textureImage[i] == NULL) {
			printf("Fehler bei der Speicherreservierung fuer die Bilddaten");
			exit(0);
		}
	}
	//memset(textureImage,0,sizeof(void *)*1); //sicherheitshalber den Inhalt loeschen
	if (
		LoadBMP("waldboden.bmp", textureImage[0]))  {

		for (i = 0; i<NUM_TEXTURES; i++) {
			glGenTextures(1, &texture[i]);  //Textur erzeugen
			// Textur Erstellung mit Daten vom Bitmap
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexImage2D(GL_TEXTURE_2D,            //target (Gibt an, welche Texture erreicht werden soll)
				0,                          //level (Grad der Mipmap-Reduzierung, 0 ist das Basisbild)
				3,                          //components (1 fuer R, 2 fuer R+A, 3 fuer RGB, 4 fuer RGBA)
				textureImage[i]->sizeX,     //width (Bildbreite in Pixeln)
				textureImage[i]->sizeY,     //height (Bildhoehe in Pixeln)
				0,                          //border (Rand: 0 oder 1)
				GL_RGB,                     //format (z.B. GL_COLOR_INDEX, GL_RGBA, GL_LUMINANCE, ...)
				GL_UNSIGNED_BYTE,           //type (Typ der Daten; z.B. GL_BYTE, GL_INT, GL_FLOAT, ...)
				textureImage[i]->data);     //pixels (eigentlichen Bilddaten)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		}
		//Aufraeumen
		for (i = 0; i<NUM_TEXTURES; i++) {
			if (textureImage[i]) {              //falls existiert
				if (textureImage[i]->data) {     //falls Daten existieren
					free(textureImage[i]->data);  //Datenbereich freigeben
				}
				free(textureImage[i]);          //Bitmap-Struktur freigeben
			}
		}
	}
}

void Zylinder(GLfloat relativ){
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, relativ / 30, relativ / 30, 1, 30, 30);
	glEnd();

}

void Geruest(GLfloat relativ){

	//Querstamm
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.1, 1.3, 0.1);
	Wuerfel_mit_Normalen(relativ*2);
	glPopMatrix();

	//Hauptstamm
	glPushMatrix();
	glTranslatef(-relativ, -relativ, 0);
	glScalef(0.1, 1.5, 0.11);
	Wuerfel_mit_Normalen(relativ*2);
	glPopMatrix();
}

void Schaukel(GLfloat relativ){

	glRotatef(90 * sin(fRotation / 360 * 2 * M_PI), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);

	//Brett
	glPushMatrix();
	glScalef(1.5, 0.1, 0.25);
	glTranslatef(0.17, -1.5, 0.0);
	Wuerfel_mit_Normalen(relativ*2/2.5);
	glPopMatrix();

	//Rechtes Seil
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(90, 1, 0, 0);
	Zylinder(relativ);
	glPopMatrix();

	//Linkes Seil
	glPushMatrix();
	glTranslatef(0, 0.5, 0.0);
	glRotatef(90, 1, 0, 0);
	Zylinder(relativ);
	glPopMatrix();

}

void Init()
{
	LoadGLTextures();            //Texturen Laden
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig
	// durchgefuehrt werden muessen
	glClearColor(0.33f, 0.225f, 0.0f, 1.0f);	// Hintergrundfarbe definieren
	// Licht
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 2.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	// z-Buffer
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	// Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
	glEnable(GL_NORMALIZE);
}

void KeyboardFunc(int key, int x, int y)
{
	//float fraction = 0.1f;

	//switch (key) {
	//case GLUT_KEY_LEFT:
	//	std::cout << "Links";
	//	angle -= 0.01f;
	//	lx = sin(angle);
	//	lz = -cos(angle);
	//	break;
	//case GLUT_KEY_RIGHT:
	//	angle += 0.01f;
	//	lx = sin(angle);
	//	lz = -cos(angle);
	//	break;
	//case GLUT_KEY_UP:
	//	x += lx * fraction;
	//	z += lz * fraction;
	//	break;
	//case GLUT_KEY_DOWN:
	//	x -= lx * fraction;
	//	z -= lz * fraction;
	//	break;
	//}

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT){
		rotate_y += 5;
		std::cout << "Rechte TASTE!";
	}

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	// RenderScene aufrufen.
	glutPostRedisplay();
}

void RenderScene() //Zeichenfunktion
{
	GLfloat relativ = 0.5;
	glClearColor(2.5, 0.5, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	glRotatef(rotate_x, 1.0, 0.0, 0.0);  //alte L�sung: Drehung des Objektes
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//gluLookAt(x, 0.0f, z, x + lx, 0.0f, z + lz, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	//Wuerfel_mit_Normalen(5);
	ZeichneUmwelt(relativ*10);
	glPopMatrix();

	//Zur Orientierung im Urpsrung
	glPushMatrix();
	glutWireCube(relativ);
	glPopMatrix();

	glRotatef(gRotation, 0, 1, 0);

	glTranslatef(0.5, 1, 0); //Verschiebe schauckel und ger�st in koordinatenursprung

	Geruest(relativ);

	Schaukel(relativ);

	glFlush(); //Buffer leeren
	glutSwapBuffers();


}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Ver�nderung der Gr��e des
	// Graphikfensters statt
 	// Matrix f�r Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten)
	glOrtho(-1., 1., -1., 1., -2, 10.0);
	// Matrix f�r Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	// Hier werden Berechnungen durchgef�hrt, die zu einer Animation der Szene
	// erforderlich sind. Dieser Prozess l�uft im Hintergrund und wird alle
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins
	// inkrementiert und dem Callback wieder uebergeben.
	//std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen

	gRotation = gRotation - 1;
	fRotation = fRotation - 5.0; // Rotationswinkel aendern
	if (fRotation <= 0.0) {
		fRotation = fRotation + 360.0;
	}

	glutPostRedisplay();
	// Timer wieder registrieren; Animate wird so nach 100 msec mit value+=1 aufgerufen
	glutTimerFunc(100, Animate, ++value);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);         // Fenster-Konfiguration
	glutCreateWindow("Arne Bahlo; Johannes Wahl");   // Fenster-Erzeugung

	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutSpecialFunc(KeyboardFunc);

	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
