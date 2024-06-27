CC := gcc
CFLAGS := -Wall
DEFINE_ARGS := -D PC
EXEC_NAME := frogger
MODULES := game_logic.o frogger.o 


all: pc

pc: game_logic.o frogger.o
	${CC} -o ${EXEC_NAME} ${MODULES} ${CFLAGS} ${DEFINE_ARGS}

frogger.o: frogger.c
	${CC} -o frogger.o -c frogger.c ${CFLAGS} ${DEFINE_ARGS}

game_logic.o:  game/game_logic.c game/game_logic.h entities/entities.h
	${CC} -o game_logic.o -c game/game_logic.c	${DEFINE_ARGS}




clean:
	rm -r ${MODULES} ${EXEC_NAME}