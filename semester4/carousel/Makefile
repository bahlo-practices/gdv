# Variables
CC=g++
CFLAGS=-Wall -framework OpenGL -framework GLUT
LDFLAGS=
SOURCES=
EXECUTABLE=main.o

all:
	${CC} ${CFLAGS} -o ${EXECUTABLE} main.cpp ${SOURCES}

run: all
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
