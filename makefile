CC = gcc

CFLAGS = -Wall -lpthread

TARGET = rwmain

SRC = main.c readerwriter.c

HEADER = readerwriter.h

OBJ = main.o readerwriter.o

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJ)