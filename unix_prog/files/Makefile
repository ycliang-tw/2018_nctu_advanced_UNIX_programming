
CC	= gcc
CXX	= g++
CFLAGS	= -Wall -g

PROGS	= dup tmpnam ioctl uid vbuf

all: $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

%: %.cpp
	$(CXX) -o $@ $(CFLAGS) $< $(LDFLAGS)

clean:
	rm -f *~ $(PROGS)

