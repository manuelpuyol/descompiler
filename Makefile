CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c token.c utils.c lexer.c automata.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=descompiler

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
