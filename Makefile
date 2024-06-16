build:
	gcc -Wall -std=c99 ./src/*.c -lm -lSDL2 -L /opt/homebrew/Cellar/sdl2/2.30.3/lib -I /opt/homebrew/Cellar/sdl2/2.30.3/include  -o renderer

run:
	./renderer

clean:
	rm renderer

install:
	brew install sdl2