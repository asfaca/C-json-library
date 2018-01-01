CC=gcc
CFLAGS=-g
TARGET=exe
OBJS=cjson_parse.o

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

cjson_parse.o: cjsonhead.h cjsontype.h cjson_parse.c