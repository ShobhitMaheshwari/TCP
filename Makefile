all: client server

client: client.c
	gcc -std=c99 -o $@out $^

server: server.c
	gcc -std=c99 -o $@out $^

clean:
	rm serverout clientout
