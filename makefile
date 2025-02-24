CC = gcc
CFLAGS = -g -Wall -lm
LDFLAGS =
OBJFILES = currency.o memoize.o
TARGET = currency

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET)