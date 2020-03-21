	.file	"conv.c"
	.intel_syntax noprefix
	.text
	.globl	a
	.type	a, @function
a:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	r10d, edi
	mov	edi, esi
	mov	esi, edx
	mov	edx, ecx
	mov	ecx, r9d
	mov	eax, DWORD PTR [rbp+16]
	mov	BYTE PTR [rbp-4], r10b
	mov	BYTE PTR [rbp-8], dil
	mov	BYTE PTR [rbp-12], sil
	mov	BYTE PTR [rbp-16], dl
	mov	BYTE PTR [rbp-20], r8b
	mov	BYTE PTR [rbp-24], cl
	mov	BYTE PTR [rbp-28], al
	movzx	eax, BYTE PTR [rbp-28]
	sub	al, BYTE PTR [rbp-24]
	mov	edx, eax
	movzx	eax, BYTE PTR [rbp-20]
	add	eax, edx
	sub	al, BYTE PTR [rbp-16]
	sub	al, BYTE PTR [rbp-16]
	mov	edx, eax
	movzx	eax, BYTE PTR [rbp-12]
	add	eax, edx
	sub	al, BYTE PTR [rbp-8]
	mov	edx, eax
	movzx	eax, BYTE PTR [rbp-4]
	add	eax, edx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	a, .-a
	.globl	b
	.type	b, @function
b:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	r10d, edi
	mov	edi, esi
	mov	esi, edx
	mov	edx, ecx
	mov	ecx, r9d
	mov	eax, DWORD PTR [rbp+16]
	mov	WORD PTR [rbp-4], r10w
	mov	WORD PTR [rbp-8], di
	mov	WORD PTR [rbp-12], si
	mov	WORD PTR [rbp-16], dx
	mov	WORD PTR [rbp-20], r8w
	mov	WORD PTR [rbp-24], cx
	mov	WORD PTR [rbp-28], ax
	movzx	eax, WORD PTR [rbp-28]
	sub	ax, WORD PTR [rbp-24]
	mov	edx, eax
	movzx	eax, WORD PTR [rbp-20]
	add	eax, edx
	sub	ax, WORD PTR [rbp-16]
	sub	ax, WORD PTR [rbp-16]
	mov	edx, eax
	movzx	eax, WORD PTR [rbp-12]
	add	eax, edx
	sub	ax, WORD PTR [rbp-8]
	mov	edx, eax
	movzx	eax, WORD PTR [rbp-4]
	add	eax, edx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	b, .-b
	.globl	c
	.type	c, @function
c:
.LFB2:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR [rbp-4], edi
	mov	DWORD PTR [rbp-8], esi
	mov	DWORD PTR [rbp-12], edx
	mov	DWORD PTR [rbp-16], ecx
	mov	DWORD PTR [rbp-20], r8d
	mov	DWORD PTR [rbp-24], r9d
	mov	eax, DWORD PTR [rbp+16]
	sub	eax, DWORD PTR [rbp-24]
	mov	edx, eax
	mov	eax, DWORD PTR [rbp-20]
	add	eax, edx
	sub	eax, DWORD PTR [rbp-16]
	sub	eax, DWORD PTR [rbp-16]
	mov	edx, eax
	mov	eax, DWORD PTR [rbp-12]
	add	eax, edx
	sub	eax, DWORD PTR [rbp-8]
	mov	edx, eax
	mov	eax, DWORD PTR [rbp-4]
	add	eax, edx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	c, .-c
	.globl	d
	.type	d, @function
d:
.LFB3:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	QWORD PTR [rbp-32], rcx
	mov	QWORD PTR [rbp-40], r8
	mov	QWORD PTR [rbp-48], r9
	mov	rax, QWORD PTR [rbp+16]
	sub	rax, QWORD PTR [rbp-48]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-40]
	add	rax, rdx
	sub	rax, QWORD PTR [rbp-32]
	sub	rax, QWORD PTR [rbp-32]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	add	rax, rdx
	sub	rax, QWORD PTR [rbp-16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	d, .-d
	.globl	f
	.type	f, @function
f:
.LFB4:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	movss	DWORD PTR [rbp-4], xmm0
	movss	DWORD PTR [rbp-8], xmm1
	movss	DWORD PTR [rbp-12], xmm2
	movss	DWORD PTR [rbp-16], xmm3
	movss	DWORD PTR [rbp-20], xmm4
	movss	DWORD PTR [rbp-24], xmm5
	movss	DWORD PTR [rbp-28], xmm6
	movss	xmm0, DWORD PTR [rbp-28]
	subss	xmm0, DWORD PTR [rbp-24]
	addss	xmm0, DWORD PTR [rbp-20]
	subss	xmm0, DWORD PTR [rbp-16]
	subss	xmm0, DWORD PTR [rbp-16]
	addss	xmm0, DWORD PTR [rbp-12]
	subss	xmm0, DWORD PTR [rbp-8]
	addss	xmm0, DWORD PTR [rbp-4]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	f, .-f
	.globl	g
	.type	g, @function
g:
.LFB5:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	movsd	QWORD PTR [rbp-8], xmm0
	movsd	QWORD PTR [rbp-16], xmm1
	movsd	QWORD PTR [rbp-24], xmm2
	movsd	QWORD PTR [rbp-32], xmm3
	movsd	QWORD PTR [rbp-40], xmm4
	movsd	QWORD PTR [rbp-48], xmm5
	movsd	QWORD PTR [rbp-56], xmm6
	movsd	xmm0, QWORD PTR [rbp-56]
	subsd	xmm0, QWORD PTR [rbp-48]
	addsd	xmm0, QWORD PTR [rbp-40]
	subsd	xmm0, QWORD PTR [rbp-32]
	subsd	xmm0, QWORD PTR [rbp-32]
	addsd	xmm0, QWORD PTR [rbp-24]
	subsd	xmm0, QWORD PTR [rbp-16]
	addsd	xmm0, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	g, .-g
	.globl	k
	.type	k, @function
k:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	eax, esi
	mov	DWORD PTR [rbp-12], edx
	mov	QWORD PTR [rbp-24], rcx
	movss	DWORD PTR [rbp-16], xmm0
	movsd	QWORD PTR [rbp-32], xmm1
	movsd	QWORD PTR [rbp-40], xmm2
	mov	BYTE PTR [rbp-4], dil
	mov	WORD PTR [rbp-8], ax
	movsd	xmm0, QWORD PTR [rbp-40]
	movapd	xmm1, xmm0
	subsd	xmm1, QWORD PTR [rbp-32]
	cvtss2sd	xmm0, DWORD PTR [rbp-16]
	addsd	xmm1, xmm0
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	js	.L14
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rax
	jmp	.L15
.L14:
	mov	rdx, rax
	shr	rdx
	and	eax, 1
	or	rdx, rax
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rdx
	addsd	xmm0, xmm0
.L15:
	subsd	xmm1, xmm0
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	js	.L16
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rax
	jmp	.L17
.L16:
	mov	rdx, rax
	shr	rdx
	and	eax, 1
	or	rdx, rax
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rdx
	addsd	xmm0, xmm0
.L17:
	subsd	xmm1, xmm0
	mov	eax, DWORD PTR [rbp-12]
	test	rax, rax
	js	.L18
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rax
	jmp	.L19
.L18:
	mov	rdx, rax
	shr	rdx
	and	eax, 1
	or	rdx, rax
	pxor	xmm0, xmm0
	cvtsi2sdq	xmm0, rdx
	addsd	xmm0, xmm0
.L19:
	addsd	xmm0, xmm1
	movzx	eax, WORD PTR [rbp-8]
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, eax
	subsd	xmm0, xmm1
	movapd	xmm1, xmm0
	movzx	eax, BYTE PTR [rbp-4]
	pxor	xmm0, xmm0
	cvtsi2sd	xmm0, eax
	addsd	xmm0, xmm1
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	k, .-k
	.section	.rodata
.LC0:
	.string	"%u\n"
.LC1:
	.string	"%lu\n"
.LC9:
	.string	"%.2f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	push	7
	mov	r9d, 6
	mov	r8d, 5
	mov	ecx, 4
	mov	edx, 3
	mov	esi, 2
	mov	edi, 1
	call	a
	add	rsp, 8
	movzx	eax, al
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	sub	rsp, 8
	push	17
	mov	r9d, 16
	mov	r8d, 15
	mov	ecx, 14
	mov	edx, 13
	mov	esi, 12
	mov	edi, 11
	call	b
	add	rsp, 16
	movzx	eax, ax
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	sub	rsp, 8
	push	27
	mov	r9d, 26
	mov	r8d, 25
	mov	ecx, 24
	mov	edx, 23
	mov	esi, 22
	mov	edi, 21
	call	c
	add	rsp, 16
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	sub	rsp, 8
	push	37
	mov	r9d, 36
	mov	r8d, 35
	mov	ecx, 34
	mov	edx, 33
	mov	esi, 32
	mov	edi, 31
	call	d
	add	rsp, 16
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC1
	mov	eax, 0
	call	printf
	movss	xmm6, DWORD PTR .LC2[rip]
	movss	xmm5, DWORD PTR .LC3[rip]
	movss	xmm4, DWORD PTR .LC4[rip]
	movss	xmm3, DWORD PTR .LC5[rip]
	movss	xmm2, DWORD PTR .LC6[rip]
	movss	xmm1, DWORD PTR .LC7[rip]
	movss	xmm0, DWORD PTR .LC8[rip]
	call	f
	cvtss2sd	xmm0, xmm0
	mov	edi, OFFSET FLAT:.LC9
	mov	eax, 1
	call	printf
	movsd	xmm5, QWORD PTR .LC10[rip]
	movsd	xmm4, QWORD PTR .LC11[rip]
	movsd	xmm3, QWORD PTR .LC12[rip]
	movsd	xmm2, QWORD PTR .LC13[rip]
	movsd	xmm1, QWORD PTR .LC14[rip]
	movsd	xmm0, QWORD PTR .LC15[rip]
	movabs	rax, 4632374429215621120
	movapd	xmm6, xmm5
	movapd	xmm5, xmm4
	movapd	xmm4, xmm3
	movapd	xmm3, xmm2
	movapd	xmm2, xmm1
	movapd	xmm1, xmm0
	mov	QWORD PTR [rbp-8], rax
	movsd	xmm0, QWORD PTR [rbp-8]
	call	g
	mov	edi, OFFSET FLAT:.LC9
	mov	eax, 1
	call	printf
	movsd	xmm1, QWORD PTR .LC17[rip]
	movsd	xmm0, QWORD PTR .LC18[rip]
	movapd	xmm2, xmm1
	movapd	xmm1, xmm0
	movss	xmm0, DWORD PTR .LC19[rip]
	mov	ecx, 64
	mov	edx, 63
	mov	esi, 62
	mov	edi, 61
	call	k
	mov	edi, OFFSET FLAT:.LC9
	mov	eax, 1
	call	printf
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC2:
	.long	1111228416
	.align 4
.LC3:
	.long	1110966272
	.align 4
.LC4:
	.long	1110704128
	.align 4
.LC5:
	.long	1110441984
	.align 4
.LC6:
	.long	1110179840
	.align 4
.LC7:
	.long	1109917696
	.align 4
.LC8:
	.long	1109655552
	.align 8
.LC10:
	.long	0
	.long	1078755328
	.align 8
.LC11:
	.long	0
	.long	1078722560
	.align 8
.LC12:
	.long	0
	.long	1078689792
	.align 8
.LC13:
	.long	0
	.long	1078657024
	.align 8
.LC14:
	.long	0
	.long	1078624256
	.align 8
.LC15:
	.long	0
	.long	1078591488
	.align 8
.LC17:
	.long	0
	.long	1079033856
	.align 8
.LC18:
	.long	0
	.long	1079017472
	.align 4
.LC19:
	.long	1115815936
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
