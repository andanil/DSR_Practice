SRCS = TCPConnection.c   Logger.c
vpath %.c ../src
OBJS = $(SRCS:.c=.o)

SRCSAPP =  JsonParser.c ServerController.c ServerApp.c TCPServer.c DB.c UserList.c
vpath %.c src
OBJSAPP = $(SRCSAPP:.c=.o) 


CFLAGS = -I../inc 
CFLAGS += -Iinc 
CFLAGS += -I/usr/include/mysql
CFLAGS += -I/usr/include/json-c/

default: all

all: $(OBJS) $(OBJSAPP) server

server: main.o
	gcc -pthread -std=c99 -o server main.o $(OBJS) $(OBJSAPP) `mysql_config --cflags --libs` -ljson-c

main.o: main.c
	gcc -O -c -std=c99 main.c $(CFLAGS)

clean:
	rm -f *.o