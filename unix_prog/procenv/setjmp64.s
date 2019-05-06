	.file	"setjmp.c"
	.comm	jb,200,32
	.section	.rodata
	.align 8
.LC0:
	.string	"f1: a=%d b=%d c=%d (befoer setjmp)\n"
	.align 8
.LC1:
	.string	"f1: a=%d b=%d c=%d (longjmp'ed)\n"
	.align 8
.LC2:
	.string	"f1: a=%d b=%d c=%d (after setjmp)\n"
	.text
	.globl	f1
	.type	f1, @function
f1:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1, -12(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$jb, %edi
	call	_setjmp
	testl	%eax, %eax
	je	.L2
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$101, -12(%rbp)
	movl	$102, -8(%rbp)
	movl	$103, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	f1, .-f1
	.section	.rodata
.LC3:
	.string	"f2: a=%d b=%d c=%d\n"
	.text
	.globl	f2
	.type	f2, @function
f2:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	$201, -12(%rbp)
	movl	$202, -8(%rbp)
	movl	$203, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	f2, .-f2
	.section	.rodata
.LC4:
	.string	"f3: a=%d b=%d\n"
	.text
	.globl	f3
	.type	f3, @function
f3:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$301, -8(%rbp)
	movl	$302, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %esi
	movl	$jb, %edi
	call	longjmp
	.cfi_endproc
.LFE2:
	.size	f3, .-f3
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	f1
	testl	%eax, %eax
	je	.L8
	movl	$0, %eax
	jmp	.L9
.L8:
	movl	$903, %edx
	movl	$902, %esi
	movl	$901, %edi
	call	f2
	movl	$0, %eax
	call	f3
	movl	$0, %eax
.L9:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
