CC=gcc
CFLAGS=-c -Wall

all:  insecure_client insecure_server

insecure_client: insecure_client.o utilities.o
	$(CC) insecure_client.o utilities.o -o acceso-rem

insecure_server: insecure_server.o utilities.o user_management.o
	$(CC) insecure_server.o utilities.o user_management.o -o serv-acceso

insecure_client.o: insecure_client.c
	$(CC) $(CFLAGS) insecure_client.c
  
insecure_server.o: insecure_server.c
	$(CC) $(CFLAGS) insecure_server.c

utilities.o: utilities.h utilities.c
	$(CC) $(CFLAGS) utilities.c
  
user_management.o: user_management.h user_management.c
	$(CC) $(CFLAGS) user_management.c

clean:
	rm -f *.o acceso-rem serv-acceso