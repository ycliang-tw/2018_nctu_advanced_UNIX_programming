
CC	= gcc
CXX	= g++
CFLAGS	= -Wall -g
LDFLAGS	=

PROGS	= simple exec echobin fig8.20-exec2 zombie

all: $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

%: %.cpp
	$(CXX) -o $@ $(CFLAGS) $< $(LDFLAGS)

clean:
	rm -f *~ $(PROGS)

