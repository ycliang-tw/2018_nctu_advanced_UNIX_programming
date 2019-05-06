EXE = hw1
CC ?= gcc
CFLAGS= -Wall -g -static

all: $(EXE)

$(EXE): $(EXE).o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c $^

.PHONY: clean
clean:
	$(RM) -rf *.o $(EXE) 
