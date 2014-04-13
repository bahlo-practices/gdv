# Variables
CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=
MAIN=teil_1.cpp
EXECUTABLE=main.o

# Tasks
all:
	${CC} ${CFLAGS} -o ${EXECUTABLE} ${MAIN} ${SOURCES}

run: all
	./${EXECUTABLE}

debug: all
	./${EXECUTABLE} debug

clean:
	rm `find . -name "*o"`
