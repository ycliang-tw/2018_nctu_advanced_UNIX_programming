EXEC 	= lanchat
CC	= gcc -std=gnu99 
CFLAGS	= -g -Wall
OBJS 	= lanchat.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJS)
	$(CC) -o $@ $<
	strip $@

.PHONY: clean
clean:
	@$(RM) -rf $(OBJS) $(EXEC) peda*
