/*
  Name: texture.cpp
  zusaetzlich benoetigt: myBitmap.h, bus128.bmp, bush.bmp

  Author: Florian Muecke (flo_AT_mueckeimnetz.de)
  Copyright: Florian Muecke, Uni-Augsburg, 2005/2006
  Date: 03.07.05 13:34
  Modified: 15.07.06 09:46
  Description: Beispielprogramm fuer BMPLoader

  Last Update:  13.10.2011   W.-D. Groch
*/ 

#include <GL/freeglut.h>
#include "myBitmap.h"

GLfloat rotX = 0.0, rotZ = 0.0, eyeZ = 10.0, angle = 0.0;
GLenum filterMode = GL_LINEAR;   //Init-Wert fuer die Texturfilterung
GLuint texNum = 0;               //Startwert fuer "level of detail"

#define NUM_TEXTURES 2           //Anzahl der Texturen
GLuint texture[NUM_TEXTURES];    //Textur-Pointer-Array

static void LoadGLTextures()     //Bitmaps laden und in Texturen umwandeln
{
  myRGBImage *textureImage[NUM_TEXTURES];
  int i;
  for (i=0; i<NUM_TEXTURES; i++) {
      textureImage[i] = (myRGBImage *) malloc(sizeof(myRGBImage));
      if (textureImage[i] == NULL) {
         printf("Fehler bei der Speicherreservierung fuer die Bilddaten");
         exit(0);
      } 
  }  
  //memset(textureImage,0,sizeof(void *)*1); //sicherheitshalber den Inhalt loeschen
	if (
     (LoadBMP("bus128.bmp", textureImage[0])) &&
     (LoadBMP("bush.bmp", textureImage[1])) ) {

     for (i=0; i<NUM_TEXTURES; i++) {
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
     for (i=0; i<NUM_TEXTURES; i++) {
         if (textureImage[i]) {              //falls existiert
	         if (textureImage[i]->data) {     //falls Daten existieren
   	         free(textureImage[i]->data);  //Datenbereich freigeben
           }
		       free(textureImage[i]);          //Bitmap-Struktur freigeben
         }
     }
  }
}

static void drawChessboard() {
    glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten
    glBindTexture(GL_TEXTURE_2D, texture[texNum]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    
    glBegin(GL_QUADS);
         // Textur aus einem Bild
         glNormal3f(0.0, 0.0, 1.0);
         glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
         glTexCoord2f(1.0, 0.0); glVertex3f( 2.0, -2.0, 0.0);
         glTexCoord2f(1.0, 1.0); glVertex3f( 2.0,  2.0, 0.0);
         glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,  2.0, 0.0);
         // Alternativ dieser Block: Textur aus 2*2 Bildern
         // glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
         // glTexCoord2f(2.0, 0.0); glVertex3f( 2.0, -2.0, 0.0);
         // glTexCoord2f(2.0, 2.0); glVertex3f( 2.0,  2.0, 0.0);
         // glTexCoord2f(0.0, 2.0); glVertex3f(-2.0,  2.0, 0.0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);   
}       

static void Init(void) {
    LoadGLTextures();            //Texturen Laden
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
    glEnable(GL_DEPTH_TEST);
}  

static void Reshape(int width, int height) {
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void Key(unsigned char key, int x, int y) {
    switch (key) { 
        case 27: exit(1); break;
        case '+': eyeZ -= 0.1; break;
        case '-': eyeZ += 0.1; break;
        case 'l': if (texNum == 0) texNum=1; else texNum = 0; break;
        case 'f': if (filterMode == GL_NEAREST) filterMode = GL_LINEAR;
                  else filterMode = GL_NEAREST;
                  break;
    }
    glutPostRedisplay();
}

static void SpecialKey(int key, int x, int y) {
    switch (key) { 
        case GLUT_KEY_UP: rotX += 5; break;
        case GLUT_KEY_DOWN: rotX -= 5; break;
        case GLUT_KEY_LEFT: rotZ -= 5; break;
        case GLUT_KEY_RIGHT: rotZ += 5; break;
        default: return;
    }
    glutPostRedisplay();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, eyeZ, 0, 0, 0, 0, 1, 0); 
    glRotatef (rotZ, 0.0, 0.0, 1.0);
    glRotatef (rotX, 1.0, 0.0, 0.0);
    drawChessboard();  //Schachbrett zeichnen
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    printf("Tasten: \n");
    printf("  ESC ....... Abbrechen\n");
    printf("  +/- ....... Zoom\n");
    printf("  LEFT/RIGHT. Rotation um z-Achse (Winkel verringern/vergroessern)\n");
    printf("  DOWN/UP ... Rotation um x-Achse (Winkel verringern/vergroessern)\n");
    printf("  l ......... Level of Detail (wechselt die Texturen)\n");
    printf("  f ......... Filtermodus (Bilineare Texturfilterung An/Aus)\n");
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    if (glutCreateWindow("BMPLoader Beispiel") == GL_FALSE) exit(1);
    Init();
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutSpecialFunc(SpecialKey);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
