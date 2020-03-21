; this is Intel format, not AT&T format

	section .data
msg:	db	"hello, world!", 0

extern	puts	; int puts(const char *)

	section .text
	global main
main:
	lea	rdi, [msg wrt rip]
	call	puts wrt ..plt

	mov	rax, 0
	ret
