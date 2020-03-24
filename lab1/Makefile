EXE    = sis # secure interactive shell
CC     = gcc -std=gnu99
CFLAGS = -Wall -g -static
BIN    = $(shell pwd)/bin
OBJS   = builtins.o shell.o main.o

all: $(EXE)
	mkdir $(BIN)
	$(RM) $(OBJS)
	mv $(EXE) $(BIN)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	strip $(EXE)
    
%.o: %.c
	$(CC) -c $^

.PHONY: clean
clean:
	$(RM) -rf *.o $(EXE)
	$(RM) -rf $(BIN)
