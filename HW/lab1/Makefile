EXE    = hw1
CC     = gcc -std=gnu99
CFLAGS = -Wall -g -static
BIN    = $(shell pwd)/bin

all: $(EXE)
	mkdir $(BIN); cp $(EXE) $(BIN)

$(EXE): $(EXE).o 
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c $^

.PHONY: clean
clean:
	$(RM) -rf *.o $(EXE);
	$(RM) -rf $(BIN)
