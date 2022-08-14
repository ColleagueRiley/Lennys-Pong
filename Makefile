OUTPUT = Lennys-Pong
GXX = g++
SOURCE = source/*.cpp
LIBS = $(shell RSGL-static)

build:
	mkdir build
	$(GXX) $(SOURCE) $(LIBS) -o build/$(OUTPUT)
	cp -r res ./build

install:
	chmod +x $(OUTPUT)
	cp $(OUTPUT) /usr/bin
	mkdir /usr/share/$(OUTPUT)
	cp -r build/* /usr/share/$(OUTPUT)