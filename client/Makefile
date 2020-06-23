SRCS = TCPConnection.c TCPClient.c
vpath %.c ../src

CFLAGS = -I../inc 

OBJS = $(SRCS:.c=.o)

default: all

all: $(OBJS) client

client: client.o
	gcc -std=c99 -o client client.o $(OBJS) 

client.o: client.c
	gcc -O -c -std=c99 client.c $(CFLAGS)

clean:
	rm -f *.o