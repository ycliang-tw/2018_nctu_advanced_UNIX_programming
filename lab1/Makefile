EXE    = sis # secure interactive shell
CC     = gcc -std=gnu99
CFLAGS = -Wall -g -static
BIN    = $(shell pwd)/bin
OBJS   = util/builtins.o util/shell.o main.o

all: clean $(EXE)
	mkdir $(BIN)
	$(RM) $(OBJS)
	strip $(EXE)
	mv $(EXE) $(BIN)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
    
%.o: %.c
	$(CC) -c $^ -o $@

debug: all

.PHONY: clean
clean:
	$(RM) -r *.o $(EXE) $(BIN)
