CC=gcc

IDIR =include
CFLAGS=-I$(IDIR)

SRCDIR=src
ODIR=obj

VPATH=$(SRCDIR)

_DEPS = lexer.h token.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o lexer.o token.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

print-%  : ; @echo $* = $($*)