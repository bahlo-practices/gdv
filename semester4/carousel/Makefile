# Variables
CC=g++
CFLAGS=-Wall -framework OpenGL -framework GLUT
LDFLAGS=
SOURCES=
INCLUDES=
EXECUTABLE=main.o

all:
	${CC} ${CFLAGS} -I ${INCLUDES} -o ${EXECUTABLE} main.cpp ${SOURCES}

run: all
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
