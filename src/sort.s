	.file	"sort.c"
	.text
	.p2align 4
	.globl	sorting
	.type	sorting, @function
sorting:
.LFB0:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %edx
	testl	%edx, %edx
	jle	.L1
	leaq	8(%rdi), %r9
	.p2align 4,,10
	.p2align 3
.L3:
	subl	$1, %edx
	movq	%rdi, %rax
	movq	%rdx, %r8
	leaq	(%r9,%rdx,8), %rsi
	.p2align 4,,10
	.p2align 3
.L5:
	movq	(%rax), %rdx
	movq	8(%rax), %rcx
	cmpq	%rcx, %rdx
	jle	.L4
	movq	%rcx, (%rax)
	movq	%rdx, 8(%rax)
.L4:
	addq	$8, %rax
	cmpq	%rsi, %rax
	jne	.L5
	movl	%r8d, %edx
	testl	%r8d, %r8d
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	sorting, .-sorting
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4: