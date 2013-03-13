CC=gcc
CFLAGS=-c -Wall

all: secure_client secure_server insecure_client insecure_server

secure_client: secure_client.o client.o common.o
	$(CC) secure_client.o client.o common.o -o acceso-rem-seg

secure_server: secure_server.o server.o common.o user_management.o
	$(CC) secure_server.o server.o common.o user_management.o -o serv-acceso-seg

insecure_client: insecure_client.o client.o common.o
	$(CC) insecure_client.o client.o common.o -o acceso-rem

insecure_server: insecure_server.o server.o common.o user_management.o
	$(CC) insecure_server.o server.o common.o user_management.o -o serv-acceso

secure_client.o: secure_client.c
	$(CC) $(CFLAGS) secure_client.c
  
secure_server.o: secure_server.c
	$(CC) $(CFLAGS) secure_server.c

insecure_client.o: insecure_client.c
	$(CC) $(CFLAGS) insecure_client.c
  
insecure_server.o: insecure_server.c
	$(CC) $(CFLAGS) insecure_server.c

client.o: client.h client.c
	$(CC) $(CFLAGS) client.c

server.o: server.h server.c
	$(CC) $(CFLAGS) server.c

common.o: common.h common.c
	$(CC) $(CFLAGS) common.c
  
user_management.o: user_management.h user_management.c
	$(CC) $(CFLAGS) user_management.c

clean:
	rm -f *.o acceso-rem serv-acceso