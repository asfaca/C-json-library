CC=gcc
CFLAGS=-g
TARGET=exe
OBJS=cjson.o

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

cjson.o: cjsonhead.h cjsontype.h cjson.c