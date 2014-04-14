# Variables
CC=g++
CFLAGS=-Wall -framework OpenGL -framework GLUT
LDFLAGS=
SOURCES=
EXECUTABLE=main.o

all:

teil_1:
	${CC} ${CFLAGS} -o ${EXECUTABLE} teil_1.cpp ${SOURCES}

teil_2:
	${CC} ${CFLAGS} -o ${EXECUTABLE} teil_2.cpp ${SOURCES}

run:
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
