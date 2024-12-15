LIBS = -lSDL2
build:
	gcc ./src/main.c $(LIBS) -o sdl_template
