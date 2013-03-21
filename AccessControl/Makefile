CC=gcc
CFLAGS=-c -Wall
SSLFLAGS=-lssl -lcrypto

all: secure_client secure_server insecure_client insecure_server add_users

secure_client: secure_client.o client.o common.o
	$(CC) secure_client.o client.o common.o -o acceso-rem-seg $(SSLFLAGS)
  
secure_server: secure_server.o server.o common.o user_management.o
	$(CC) secure_server.o server.o common.o user_management.o -o serv-acceso-seg $(SSLFLAGS)

insecure_client: insecure_client.o client.o common.o
	$(CC) insecure_client.o client.o common.o -o acceso-rem $(SSLFLAGS)

insecure_server: insecure_server.o server.o common.o user_management.o
	$(CC) insecure_server.o server.o common.o user_management.o -o serv-acceso $(SSLFLAGS)
  
add_users: add_users.o user_management.o
	$(CC) add_users.o user_management.o -o add_users $(SSLFLAGS)

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
	$(CC) $(CFLAGS) user_management.c $(SSLFLAGS)
  
add_users.o: add_users.c
	$(CC) $(CFLAGS) add_users.c

clean:
	rm -f *.o acceso-rem-seg serv-acceso-seg acceso-rem serv-acceso add_users
  