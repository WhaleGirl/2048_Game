2048:game_2048.c
	gcc -o $@ $^ -lcurses

.PHONY:clean

clean:
	rm -f 2048
