SRCS = TCPConnection.c   Logger.c
vpath %.c ../src
OBJS = $(SRCS:.c=.o)

SRCSAPP =  ServerController.c ServerApp.c TCPServer.c DB.c UserList.c
vpath %.c src
OBJSAPP = $(SRCSAPP:.c=.o) 


CFLAGS = -I../inc 
CFLAGS += -Iinc 
CFLAGS += -I/usr/include/mysql

default: all

all: $(OBJS) $(OBJSAPP) server

server: main.o
	gcc -pthread -std=c99 -o server main.o $(OBJS) $(OBJSAPP) `mysql_config --cflags --libs`

main.o: main.c
	gcc -O -c -std=c99 main.c $(CFLAGS)

clean:
	rm -f *.o