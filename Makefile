CFLAGS=-g
http-server : main.o
	gcc $(CFLAGS) main.o -o http-server
main.o : src/main.c
	gcc $(CFLAGS) -c src/main.c
