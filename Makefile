CFLAGS=-g
http-server : main.o args.o tcp.o
	gcc $(CFLAGS) main.o args.o tcp.o -o http-server
main.o : src/main.c
	gcc $(CFLAGS) -c src/main.c
args.o : src/args.c
	gcc $(CFLAGS) -c src/args.c
tcp.o : src/tcp.c
	gcc $(CFLAGS) -c src/tcp.c
