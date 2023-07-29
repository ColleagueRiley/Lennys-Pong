all:
	@if [ $(shell uname) = Windows_NT ] ; then\
		$(CC) source/main.c -O3 -I./include -lopengl32 -lshell32 -lgdi32 -lm -o lennys-pong.exe;\
	fi

	@if [ $(shell uname) = Darwin ]; then\
		$(CC) source/main.c -O3 -I./include -I./include/deps/Silicon *.o -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -o lennys-pong;\
	fi

	@if [ $(shell uname) != Windows_NT ] && [ $(shell uname -s) != Darwin ]; then\
		$(CC) source/main.c -O3 -I./include -lX11 -lGLX -lm -o lennys-pong;\
	fi

	strip lennys-pong

debug:
	@if [ $(shell uname) = Windows_NT ] ; then\
		$(CC) source/main.c -I./include -lopengl32 -lshell32 -lgdi32 -lm -o lennys-pong.exe;\
	fi

	@if [ $(shell uname) = Darwin ]; then\
		$(CC) source/main.c -I./include -I./include/deps/Silicon *.o -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -o lennys-pong;\
	fi

	@if [ $(shell uname) != Windows_NT ] && [ $(shell uname -s) != Darwin ]; then\
		$(CC) source/main.c -I./include -lX11 -lGLX -lm -o lennys-pong;\
	fi

	./lennys-pong