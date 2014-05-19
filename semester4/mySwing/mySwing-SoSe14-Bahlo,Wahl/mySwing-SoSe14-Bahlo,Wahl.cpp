#define _USE_MATH_DEFINES
#define NUM_TEXTURES 3           //Anzahl der Texturen

#include "stdafx.h"
#include "GL\freeglut.h"
#include "erweiterungen\Wuerfel_mit_Normalen.h"
#include "OpenGL_Ergaenzungen\myBitmap.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

float fRotation = 315; //Wert für Schauckel Schwingung
float gRotation = 315; //Wert für Rotation des gesamten OBjekts

float angle = 0.0;
float bewegunHoch = 0.3;
float kameraY = -0.001;
float kameraZ = 0;
bool kameraYgesperrt = false;
bool textureLoaded = true;

GLenum filterMode = GL_LINEAR;   //Init-Wert fuer die Texturfilterung
GLuint texNum = 0;               //Startwert fuer "level of detail"
GLuint texture[NUM_TEXTURES];    //Textur-Pointer-Array

void ZeichneUmwelt(GLfloat relativ){
	glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	glBegin(GL_POLYGON);   //Bodenflaeche
	if (!textureLoaded) glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-relativ / 1.2f, -0.5, -relativ / 1.2f);
	glTexCoord2f(8.0, 0.0);
	glVertex3f(+relativ / 1.2f,  -0.5, -relativ / 1.2f);
	glTexCoord2f(8.0, 8.0);
	glVertex3f(+relativ / 1.2f, -0.5, +relativ / 1.2f);
	glTexCoord2f(0.0, 8.0);
	glVertex3f(-relativ / 1.2f, -0.5, +relativ / 1.2f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);   //Rueckseite
	if (!textureLoaded) glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Rechte Seite
	if(!textureLoaded)glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(+relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Linke Seite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Vorderseite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+relativ / 2.0f, -relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, +relativ / 2.0f);
	glEnd();


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
		LoadBMP("waldboden.bmp", textureImage[0]) && LoadBMP("himmel.bmp", textureImage[1]) && LoadBMP("baum.bmp", textureImage[2]))  {

		for (i = 0; i < NUM_TEXTURES; i++) {
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
	else{
		textureLoaded = false;		
	}

}

void Zylinder(GLfloat relativ){

	glBegin(GL_POLYGON);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, relativ / 30, relativ / 30, 1, 30, 30);
	glEnd();

}

void Geruest(GLfloat relativ){
		glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	

	//Querstamm
	glPushMatrix();
	if (!textureLoaded) glColor3f(0.5, 0.2, 0);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(relativ / 5 , relativ * 2.6 , relativ / 5);
	Wuerfel_mit_Texturen(relativ*2);

	glPopMatrix();

	//Hauptstamm
	glPushMatrix();
	if (!textureLoaded) glColor3f(0.5, 0.2, 0);
	glTranslatef(-relativ, -relativ, 0);
	glScalef(relativ / 5, relativ * 3, relativ / 4.55);
	Wuerfel_mit_Texturen(relativ*2);
	glPopMatrix();
	glFlush();
}

void Schauckel(GLfloat relativ){
	glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	glRotatef(90 * sin(fRotation / 360 * 2 * M_PI), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -relativ, 0.0);

	//Brett
	glPushMatrix();
	if (!textureLoaded) glColor3f(0.5, 0.2, 0);
	glScalef(relativ*3, relativ / 5, relativ / 2);
	glTranslatef(relativ / 2.5, -relativ*8, 0.0);
	Wuerfel_mit_Texturen(relativ*2.5/2.5);
	glPopMatrix();

	//Rechtes Seil
	glPushMatrix();
	if (!textureLoaded) glColor3f(0, 0, 0);
	glTranslatef(relativ*0.9, relativ, 0.0);
	glRotatef(90, 1, 0, 0);
	Zylinder(relativ);
	glPopMatrix();

	//Linkes Seil
	glPushMatrix();
	if (!textureLoaded) glColor3f(0, 0, 0);
	glTranslatef(0, relativ, 0.0);
	glRotatef(90, 1, 0, 0);
	Zylinder(relativ);
	glPopMatrix();
	glFlush();
	glDisable(GL_TEXTURE_2D);

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
	
	if (key == GLUT_KEY_RIGHT){
		angle = (angle - 1.0);
	}

	else if (key == GLUT_KEY_LEFT){
		angle = (angle + 1.0);
	}

	else if (key == GLUT_KEY_UP){
		if (bewegunHoch < 1.0 && !kameraYgesperrt)
			bewegunHoch = bewegunHoch + 0.2;
	}

	else if (key == GLUT_KEY_DOWN){
		if (bewegunHoch > 0.4  && !kameraYgesperrt)
			bewegunHoch = bewegunHoch - 0.2;
	}

	else if (key == GLUT_KEY_INSERT){
		angle = 0;
		bewegunHoch = 0.3;
		kameraZ = 0;
		kameraY = -0.001;
		kameraYgesperrt = false;
	}

	// RenderScene aufrufen.
	glutPostRedisplay();
}

static void Key(unsigned char key, int x, int y) {
	switch (key) {
	case 'h': bewegunHoch = 1; 
		kameraY = 1.3;
		kameraZ = -0.1;
		kameraYgesperrt = true;
		break;
	}
	glutPostRedisplay();
}

void RenderScene() //Zeichenfunktion
{
	GLfloat relativ = 0.4;
	glClearColor(2.5, 0.5, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(0.8*sin(angle / 180 * M_PI), bewegunHoch, 0.8*cos(angle / 180 * M_PI), 0.0, kameraY, kameraZ, 0.0, 1,0);

	glPushMatrix();
	ZeichneUmwelt(relativ*15);
	glPopMatrix();

	glRotatef(gRotation, 0, 1, 0);

	glTranslatef(relativ, relativ, 0); //Verschiebe schauckel und gerüst in koordinatenursprung

	Geruest(relativ);

	Schauckel(relativ);

	glFlush(); //Buffer leeren
	glutSwapBuffers();


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
	glOrtho(-1., 1., -1., 1., -1.5, 60.0);
	//gluPerspective(0, 1, 1, 100);
	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
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

void ZeigeHilfe(){
	std::cout << "Hilfe zur Bedienung: \n";
	std::cout << "Pfeiltaste Links: Ansicht nach Links drehen\n";
	std::cout << "Pfeiltaste Rechts: Ansicht nach Rechts drehen \n";
	std::cout << "Pfeiltaste Oben: Ansicht nach Oben drehen \n";
	std::cout << "Pfeiltaste Unten: Ansicht nach Unten drehen \n";
	std::cout << "Taste 'h': In den Himmel schauen \n";
	std::cout << "Einfuegen: Ansicht zuruecksetzen.";
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);         // Fenster-Konfiguration
	glutCreateWindow("Arne Bahlo; Johannes Wahl");   // Fenster-Erzeugung

	ZeigeHilfe();
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutSpecialFunc(KeyboardFunc);
	glutKeyboardFunc(Key);

	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}



