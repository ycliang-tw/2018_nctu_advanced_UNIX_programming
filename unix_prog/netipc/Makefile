
CC	= gcc
CXX	= g++
CFLAGS	= -Wall -g
SYS	= $(shell uname -s)
LDFLAGS	=

ifeq ($(SYS),Linux)
LDFLAGS +=
endif

PROGS	= addr \
	  gethostent getprotoent getservent \
	  getaddrinfo getnameinfo echosrv

all: $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

%: %.cpp
	$(CXX) -o $@ $(CFLAGS) $< $(LDFLAGS)

clean:
	rm -f *.o *~ $(PROGS)

