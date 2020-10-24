	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB16:
	.cfi_startproc
	endbr64
	movq	%rsi, %r9
	subq	$1, %r9
	je	.L1
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L6:
	movq	%rcx, %r8
	addq	$1, %rcx
	cmpq	%rcx, %rsi
	jbe	.L3
	movq	%rcx, %rax
	movq	%r8, %rdx
	.p2align 4,,10
	.p2align 3
.L5:
	movq	(%rdi,%rdx,8), %r10
	cmpq	%r10, (%rdi,%rax,8)
	cmovl	%rax, %rdx
	addq	$1, %rax
	cmpq	%rax, %rsi
	jne	.L5
	cmpq	%r8, %rdx
	je	.L3
	leaq	(%rdi,%rdx,8), %rax
	movq	-8(%rdi,%rcx,8), %r8
	movq	(%rax), %rdx
	movq	%rdx, -8(%rdi,%rcx,8)
	movq	%r8, (%rax)
.L3:
	cmpq	%r9, %rcx
	jne	.L6
.L1:
	ret
	.cfi_endproc
.LFE16:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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