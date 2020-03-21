EXE 	= ps
CC     ?= gcc
CFLAGS 	= -Wall -O3 -g

$(EXE): main.o
	$(CC) $(CFLAGS) -o $@ $< 

%.o: %.c
	$(CC) -c $^

.PHONY: clean
clean:
	$(RM) -rf *.o $(EXE)
