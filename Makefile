game: game.c imgui.h
	gcc game.c -o game -L. -lSDL

.PHONY: clean

clean:
	rm game

