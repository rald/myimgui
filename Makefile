game: game.c
	gcc game.c -o game -L. -limgui -lSDL

.PHONY: clean

clean:
	rm game

