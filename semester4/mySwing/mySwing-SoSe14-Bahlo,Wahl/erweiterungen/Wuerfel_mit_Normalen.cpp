/* ----------------------------------------------------------- */
/* Wuerfel_mit_Normalen.cpp  (inkl. Normalen)                  */
/* Autor: W.-D. Groch                                          */
/* letzte Aenderung:	Groch   13.10.2011                        */
/* ----------------------------------------------------------- */
#include <GL/freeglut.h>
#include "Wuerfel_mit_Normalen.h"


void Wuerfel_mit_Normalen(GLfloat fSeitenL)
{ 
	glBegin(GL_POLYGON);   //Vorderseite
        glNormal3f(0.0f, 0.0f, 1.0f);
	    glColor4f(1.0f,0.0f,0.0f,1.0f);	//ROT
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
        glNormal3f(1.0f, 0.0f, 0.0f);
	    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,1.0f,1.0f,1.0f);	//CYAN
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
        glNormal3f(0.0f, 0.0f, -1.0f);
	    glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
        glNormal3f(-1.0f, 0.0f, 0.0f);
	    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT	
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
        glNormal3f(0.0f, 1.0f, 0.0f);
	    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
	    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
	    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
        glNormal3f(0.0f, -1.0f, 0.0f);
	    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
	    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
	    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	    glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT
	    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //ROT

	return;
}

void Wuerfel_mit_Texturen(GLfloat fSeitenL){
	glBegin(GL_POLYGON);   //Vorderseite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //ROT

	return;
}