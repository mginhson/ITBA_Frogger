CC := gcc
CFLAGS := -Wall
DEFINE_ARGS := #-D PC
EXEC_NAME := frogger
MODULES := game_logic.o frogger.o entities.o


all: pc

pc: ${MODULES}
	${CC} -o ${EXEC_NAME} ${MODULES} ${CFLAGS} ${DEFINE_ARGS}

frogger.o: frogger.c game/game_logic.h
	${CC} -o frogger.o -c frogger.c ${CFLAGS} ${DEFINE_ARGS}

game_logic.o:  game/game_logic.c game/game_logic.h entities.o
	${CC} -o game_logic.o -c game/game_logic.c	${DEFINE_ARGS} ${CFLAGS}

entities.o: entities/entities.c entities/entities.h config.h
	${CC} -o entities.o -c entities/entities.c ${CFLAGS} ${DEFINE_ARGS}


clean:
	rm -r ${MODULES} ${EXEC_NAME}