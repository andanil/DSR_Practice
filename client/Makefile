SRCS = TCPConnection.c  Logger.c
vpath %.c ../src
OBJS = $(SRCS:.c=.o)

SRCSAPP = NMEAGenerator.c NMEAParser.c JsonParser.c TCPClient.c FileAuthorization.c ServerConnController.c ClientDataController.c ClientView.c
vpath %.c src
OBJSAPP = $(SRCSAPP:.c=.o)

CFLAGS = -I../inc 
CFLAGS += -Iinc 
CFLAGS += -I/usr/include/json-c/

default: all

all: $(OBJS) $(OBJSAPP) client

client: main.o
	gcc -std=c99 -o client main.o $(OBJS) $(OBJSAPP) -ljson-c -pthread 

main.o: main.c
	gcc -O -c -std=c99 main.c $(CFLAGS)

clean:
	rm -f *.o