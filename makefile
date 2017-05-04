all : serveur client

serveur : serveur.o socket.o
	cc -g -o serveur serveur.o socket.o

client : client.o socket.o
	cc -g -o client client.o socket.o

serveur.o : serveur.c types.h serveur.h
	cc -c serveur.c

client.o : client.c types.h client.h
	cc -c client.c

socket.o : socket.c types.h socket.h
	cc -c socket.c
