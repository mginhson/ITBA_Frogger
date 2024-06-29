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

inicialization.o: inicialization/inicialization.c  inicialization/inicialization.h driv/formas.h driv/disdrv.h driv/joydrv.h
	gcc -Wall -c inicialization/inicialization.c

formas.o: driv/formas.c driv/formas.h driv/disdrv.h
	gcc -Wall -c driv/formas.c

menu.o: menus/menu.c menus/menu.h driv/disdrv.h driv/joydrv.h driv/formas.h
	gcc -Wall -c menus/menu.c

pause.o: menus/pause.c menus/pause.h driv/disdrv.h driv/joydrv.h driv/formas.h
	gcc -Wall -c menus/pause.c

top.o: menus/top.c menus/top.h driv/disdrv.h driv/joydrv.h driv/formas.h
	gcc -Wall -c menus/top.c

final.o: finalAnimation/final.c finalAnimation/final.h driv/disdrv.h driv/joydrv.h driv/formas.h
	gcc -Wall -c finalAnimation/final.c

clean:
	rm -r ${MODULES} ${EXEC_NAME} *.o