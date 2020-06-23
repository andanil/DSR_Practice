SRCS = TCPConnection.c ServerApp.c TCPServer.c
vpath %.c ../src

CFLAGS = -I../inc 

OBJS = $(SRCS:.c=.o)

default: all

all: $(OBJS) server

server: server.o
	gcc -pthread -std=c99 -o server server.o $(OBJS) 

server.o: server.c
	gcc -O -c -std=c99 server.c $(CFLAGS)

clean:
	rm -f *.o