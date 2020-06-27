SRCS = TCPConnection.c  Logger.c
vpath %.c ../src
OBJS = $(SRCS:.c=.o)

SRCSAPP = TCPClient.c
vpath %.c src
OBJSAPP = $(SRCSAPP:.c=.o)

CFLAGS = -I../inc 
CFLAGS += -Iinc 

default: all

all: $(OBJS) $(OBJSAPP) client

client: main.o
	gcc -std=c99 -o client main.o $(OBJS) $(OBJSAPP) 

main.o: main.c
	gcc -O -c -std=c99 main.c $(CFLAGS)

clean:
	rm -f *.o