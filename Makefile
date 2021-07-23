CC=gcc

SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)

OBJECTS=$(SOURCES:%.c=%.o)

TARGET=$(notdir $(CURDIR))

CFLAGS=-Wall -g -c

.PHONY: all
all: $(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): %.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

