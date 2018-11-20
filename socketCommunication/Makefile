all: server.o  client.o multi_server.o select.o
	gcc -o server.o  server.c
	gcc -o client.o  client.c
	gcc -o multi_server multi_server.c -lpthread
	gcc -o select.o select.c

main.o: server.c client.c multi_server.c select.c
	gcc -c server.c
	gcc -c client.c
	gcc -c multi_server.c
	gcc -c select.c

clean:
	rm -rf *.o
