all: partc

partc: playsong

playsong: playsong.c
	gcc -g -Wall playsong.c -lm -o playsong

clean:
	rm -f *~ all playsong
	rm -r playsong.dSYM
	rm Makefile~