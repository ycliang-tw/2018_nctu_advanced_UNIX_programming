	.file	"setjmp.c"
	.comm	jb,156,32
	.section	.rodata
	.align 4
.LC0:
	.string	"f1: a=%d b=%d c=%d (befoer setjmp)\n"
	.align 4
.LC1:
	.string	"f1: a=%d b=%d c=%d (longjmp'ed)\n"
	.align 4
.LC2:
	.string	"f1: a=%d b=%d c=%d (after setjmp)\n"
	.text
	.globl	f1
	.type	f1, @function
f1:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$1, -20(%ebp)
	movl	$2, -16(%ebp)
	movl	$3, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$jb, (%esp)
	call	_setjmp
	testl	%eax, %eax
	je	.L2
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$101, -20(%ebp)
	movl	$102, -16(%ebp)
	movl	$103, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	movl	$0, %eax
.L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
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
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$201, -20(%ebp)
	movl	$202, -16(%ebp)
	movl	$203, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
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
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$301, -16(%ebp)
	movl	$302, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	$1, 4(%esp)
	movl	$jb, (%esp)
	call	longjmp
	.cfi_endproc
.LFE2:
	.size	f3, .-f3
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	f1
	testl	%eax, %eax
	je	.L8
	movl	$0, %eax
	jmp	.L9
.L8:
	movl	$903, 8(%esp)
	movl	$902, 4(%esp)
	movl	$901, (%esp)
	call	f2
	call	f3
	movl	$0, %eax
.L9:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
