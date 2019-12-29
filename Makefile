CFLAGS=-Wall -g

all:
	rm -f main
	make main
	./main

clean:
	rm -f main
