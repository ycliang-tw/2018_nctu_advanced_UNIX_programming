test0: libminic.asm libminic.h start.asm test0.c 
	yasm -f elf64 libminic.asm -o libminic.o
	gcc -c -g -Wall -fno-stack-protector test0.c
	yasm -f elf64 start.asm -o start.o
	gcc -nostdlib -o test0 test0.o start.o libminic.o
	rm start.o test0.o libminic.o

test1: libminic.asm libminic.h start.asm test1.c 
	yasm -f elf64 libminic.asm -o libminic.o
	gcc -c -g -Wall -fno-stack-protector test1.c
	yasm -f elf64 start.asm -o start.o
	gcc -nostdlib -o test1 test1.o start.o libminic.o
	rm libminic.o start.o test1.o

test2: libminic.asm libminic.h start.asm test2.c 
	yasm -f elf64 libminic.asm -o libminic.o
	gcc -c -g -Wall -fno-stack-protector test2.c
	yasm -f elf64 start.asm -o start.o
	gcc -nostdlib -o test2 test2.o start.o libminic.o
	rm libminic.o start.o test2.o

test3: libminic.asm libminic.h start.asm test3.c 
	yasm -f elf64 libminic.asm -o libminic.o
	gcc -c -g -Wall -fno-stack-protector test3.c
	yasm -f elf64 start.asm -o start.o
	gcc -nostdlib -o test3 test3.o start.o libminic.o
	rm libminic.o start.o test3.o

ans: ans.c
	gcc -Wall -g -o $@ $<

.PHONY: clean
clean:
	@$(RM) test0 test1 test2 ans peda* core*
