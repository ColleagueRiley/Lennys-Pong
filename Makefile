all:
	gcc source/main.c -o Lennys-Pong -lX11 -lGLX -lm -I./include
	strip Lennys-Pong