
%macro gensys 2
	global sys_%2:function
sys_%2:
	push	r10
	mov	r10, rcx
	mov	rax, %1
	syscall
	pop	r10
	ret
%endmacro

; RDI, RSI, RDX, RCX, R8, R9

	section .data

	section .text

	gensys   0, read
	gensys   1, write
	gensys  13, rt_sigaction
	gensys  14, rt_sigprocmask
	gensys  15, rt_sigreturn
	gensys  34, pause
	gensys  35, nanosleep
	gensys  37, alarm
	gensys  60, exit
	
	global sleep	:function
	global write	:function
	global exit		:function
	global _pause	:function
	global alarm	:function
	global setjmp	:function
	global longjmp	:function
	global sigaction:function
	global sigprocmask:function

sleep:
	sub	rsp, 16
	mov	QWORD [rsp+8], 0
	mov	[rsp], rdi
	xor	rax, rax
	mov	rdi, rsp
	xor	rsi, rsi	; null
	call	sys_nanosleep
	add	rsp, 16
	ret

;

_pause:
	call sys_pause
	ret
;

write:
	call sys_write
	ret
;

exit:
	call sys_exit
	ret
;

alarm:
	call sys_alarm
	ret
;

setjmp:
	mov		QWORD [rdi], rbx		; store rbx into jmp_buf.reg[0]
	mov		QWORD [rdi+8], rsp		; store rsp into jmp_buf.reg[1]
	mov		QWORD [rdi+16], rbp		; store rbp into jmp_buf.reg[2]
	mov		QWORD [rdi+24], r12		; store r12 into jmp_buf.reg[3]
	mov		QWORD [rdi+32], r13		; store r13 into jmp_buf.reg[4]
	mov		QWORD [rdi+40], r14		; store r14 into jmp_buf.reg[5]
	mov		QWORD [rdi+48], r15		; store r15 into jmp_buf.reg[6]
	mov		rdx, QWORD [rsp]		; get return address
	mov		QWORD [rdi+56], rdx		; store return address into jmp_buf.reg[7]
	

	; problem 1 ;
	xor		rsi, rsi				; clear $rsi
	xor		rdi, rdi				; clear $rdi
	lea 	rdx, [rdi+64]			; get the address of sigset_t mask
	call 	sigprocmask				; sigprocmask(0, NULL, &mask); to retrieve sigmask & store it into mask field
	xor 	rax, rax				; return 0
	ret

longjmp:
	
	push	rsi						; holds the return value
	push 	rdi						; holds jmp_buf address
	lea		rsi, [rdi+64]			; get the address of sigset_t mask
	mov		rdi, 2					; SIG_SETMASK == 2
	xor		rdx, rdx				; clear $rdx
	call 	sigprocmask				; sigprocmask(SIG_SETMASK, &mask, NULL); to set sigmask using mask
	pop		rdi						
	pop 	rsi
	xor 	rax, rax				; clear $rax
	mov 	rax, rsi				; pass return value to $rax
	

	; problem 1 ;
	mov 	rbx, QWORD [rdi]		; set rbx using jmp_buf[0]
	mov 	rsp, QWORD [rdi+8]		; set rsp using jmp_buf[1]
	mov 	rbp, QWORD [rdi+16]		; set rbp using jmp_buf[2]
	mov 	r12, QWORD [rdi+24] 	; set r12 using jmp_buf[3]
	mov 	r13, QWORD [rdi+32]		; set r13 using jmp_buf[4]
	mov 	r14, QWORD [rdi+40]		; set r14 using jmp_buf[5]
	mov 	r15, QWORD [rdi+48] 	; set r15 using jmp_buf[6]
	mov 	rdx, QWORD [rdi+56] 	; get return address using jmp_buf[7]
	mov 	QWORD [rsp], rdx		; set return address 
	ret


my_sigreturn:
	mov 	rax, 15
	syscall


	; problem 2 ;  sigaction(int num, const struct sigaction *nact, struct sigaction *oact)
sigaction:
	mov 	rbx, rsi				; $rsi holds sigaction *nact

	; nact->sa_flags |= SA_RESTORER
	mov		ebx, DWORD [rbx+8]		; store sa_flags into edx
	or		ebx, 0x04000000			; sa_flags | RESTORER (0x04000000)
	mov		DWORD [rsi+8], ebx		; store sa_flags back to nact->sa_flags
	
	; nact->sa_restorer = sys_rt_sigreturn
	mov 	QWORD [rsi+16], my_sigreturn	

	; ret = sys_rt_sigaction(how, nact, oact, sizeof(sigset_t));
	mov 	rcx, 8					; sizeof(sigset_t) == 8
	call 	sys_rt_sigaction		; sys_rt_sigaction(num, nact, oact, 8);
	ret 	

sigprocmask:
	mov 	rcx, 8					; sizeof(sigset_t) == 8
	call 	sys_rt_sigprocmask		; sys_rt_sigprocmask(how, set, old_set, 8);
	ret

