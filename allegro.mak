pc: allegro.o init.o assets.o menu.o util.o highscore.o text.o pause.o objects.o render.o
	gcc allegro.o init.o assets.o menu.o  util.o text.o highscore.o pause.o render.o objects.o -lallegro -lallegro_font -lallegro_image -lallegro_primitives
allegro.o: allegro/allegro.c allegro/init.h allegro/assets.h allegro/menu.h allegro/highscore.h allegro/pause.h config.h
	gcc allegro/allegro.c -c
init.o: allegro/init.c allegro/init.h allegro/assets.h config.h
	gcc allegro/init.c -c
assets.o: allegro/assets.c allegro/assets.h config.h
	gcc allegro/assets.c -c
menu.o : allegro/menu.c allegro/init.h allegro/assets.h allegro/menu.h allegro/util.h allegro/components/text.h allegro/components/objects.h allegro/render.h config.h
	gcc allegro/menu.c -c
util.o : allegro/util.c allegro/util.h allegro/init.h allegro/assets.h config.h
	gcc allegro/util.c -c
text.o : allegro/components/text.c allegro/components/text.h allegro/init.h allegro/assets.h config.h
	gcc allegro/components/text.c -c
highscore.o: allegro/highscore.c allegro/highscore.h allegro/components/text.h  allegro/init.h config.h
	gcc allegro/highscore.c -c
pause.o: allegro/pause.c allegro/pause.h allegro/components/text.h allegro/init.h config.h
	gcc allegro/pause.c -c
objects.o: allegro/components/objects.c  allegro/init.h allegro/assets.h allegro/components/objects.h config.h
	gcc allegro/components/objects.c -c
render.o: allegro/render.c allegro/render.h entities/entities.h allegro/assets.h allegro/init.h config.h
	gcc allegro/render.c -c