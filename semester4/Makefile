# Variables
CC=g++
CFLAGS=-Wall -framework OpenGL -framework GLUT
LDFLAGS=
SOURCES=erweiterungen/*.cpp
INCLUDES=erweiterungen/
EXECUTABLE=main.o

all:

teil_1:
	${CC} ${CFLAGS} -I ${INCLUDES} -o ${EXECUTABLE} teil_1.cpp ${SOURCES}

teil_2:
	${CC} ${CFLAGS} -I ${INCLUDES} -o ${EXECUTABLE} teil_2.cpp ${SOURCES}

teil_3:
	${CC} ${CFLAGS} -I ${INCLUDES} -o ${EXECUTABLE} teil_3.cpp ${SOURCES}

run:
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
