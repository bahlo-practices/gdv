# Variables
CC=g++
CFLAGS=-Wall -framework OpenGL -framework GLUT
LDFLAGS=
SOURCES=erweiterungen/*.cpp
INCLUDES=erweiterungen/
EXECUTABLE=main.o

all:
	${CC} ${CFLAGS} -I ${INCLUDES} -o ${EXECUTABLE} mySwing-SoSe14-Bahlo,Wahl.cpp ${SOURCES}

run: all
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
