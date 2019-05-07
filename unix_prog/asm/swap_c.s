	.file	"swap_c.c"
	.intel_syntax noprefix
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR [rbp-4], eax
	mov	rax, QWORD PTR [rbp-32]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-24]
	mov	DWORD PTR [rax], edx
	mov	rax, QWORD PTR [rbp-32]
	mov	edx, DWORD PTR [rbp-4]
	mov	DWORD PTR [rax], edx
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	swap, .-swap
	.section	.rodata
.LC0:
	.string	"%d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-8], rax
	xor	eax, eax
	mov	DWORD PTR [rbp-16], 1
	mov	DWORD PTR [rbp-12], 2
	mov	edx, DWORD PTR [rbp-12]
	mov	eax, DWORD PTR [rbp-16]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	lea	rdx, [rbp-12]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	swap
	mov	edx, DWORD PTR [rbp-12]
	mov	eax, DWORD PTR [rbp-16]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	mov	eax, 0
	mov	rcx, QWORD PTR [rbp-8]
	xor	rcx, QWORD PTR fs:40
	je	.L4
	call	__stack_chk_fail
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
