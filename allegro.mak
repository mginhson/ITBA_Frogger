pc: allegro.o init.o assets.o menu.o util.o
	gcc allegro.o init.o assets.o menu.o -lallegro util.o -lallegro_font -lallegro_image -lallegro_primitives
allegro.o: allegro/allegro.c allegro/init.h allegro/assets.h allegro/menu.h
	gcc allegro/allegro.c -c
init.o: allegro/init.c allegro/init.h allegro/assets.h
	gcc allegro/init.c -c
assets.o: allegro/assets.c allegro/assets.h
	gcc allegro/assets.c -c
menu.o : allegro/menu.c allegro/init.h allegro/assets.h allegro/menu.h allegro/util.h
	gcc allegro/menu.c -c
util.o : allegro/util.c allegro/util.h allegro/init.h allegro/assets.h
	gcc allegro/util.c -c