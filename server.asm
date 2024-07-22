
app:	file format elf64-x86-64

Disassembly of section .init:

0000000000001000 <_init>:
    1000: f3 0f 1e fa                  	endbr64
    1004: 48 83 ec 08                  	subq	$0x8, %rsp
    1008: 48 8b 05 c1 2f 00 00         	movq	0x2fc1(%rip), %rax      # 0x3fd0 <socket@GLIBC_2.2.5+0x3fd0>
    100f: 48 85 c0                     	testq	%rax, %rax
    1012: 74 02                        	je	0x1016 <_init+0x16>
    1014: ff d0                        	callq	*%rax
    1016: 48 83 c4 08                  	addq	$0x8, %rsp
    101a: c3                           	retq

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020: ff 35 ca 2f 00 00            	pushq	0x2fca(%rip)            # 0x3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026: ff 25 cc 2f 00 00            	jmpq	*0x2fcc(%rip)           # 0x3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c: 0f 1f 40 00                  	nopl	(%rax)

0000000000001030 <__stack_chk_fail@plt>:
    1030: ff 25 ca 2f 00 00            	jmpq	*0x2fca(%rip)           # 0x4000 <_GLOBAL_OFFSET_TABLE_+0x18>
    1036: 68 00 00 00 00               	pushq	$0x0
    103b: e9 e0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001040 <send@plt>:
    1040: ff 25 c2 2f 00 00            	jmpq	*0x2fc2(%rip)           # 0x4008 <_GLOBAL_OFFSET_TABLE_+0x20>
    1046: 68 01 00 00 00               	pushq	$0x1
    104b: e9 d0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001050 <memset@plt>:
    1050: ff 25 ba 2f 00 00            	jmpq	*0x2fba(%rip)           # 0x4010 <_GLOBAL_OFFSET_TABLE_+0x28>
    1056: 68 02 00 00 00               	pushq	$0x2
    105b: e9 c0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001060 <close@plt>:
    1060: ff 25 b2 2f 00 00            	jmpq	*0x2fb2(%rip)           # 0x4018 <_GLOBAL_OFFSET_TABLE_+0x30>
    1066: 68 03 00 00 00               	pushq	$0x3
    106b: e9 b0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001070 <read@plt>:
    1070: ff 25 aa 2f 00 00            	jmpq	*0x2faa(%rip)           # 0x4020 <_GLOBAL_OFFSET_TABLE_+0x38>
    1076: 68 04 00 00 00               	pushq	$0x4
    107b: e9 a0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001080 <listen@plt>:
    1080: ff 25 a2 2f 00 00            	jmpq	*0x2fa2(%rip)           # 0x4028 <_GLOBAL_OFFSET_TABLE_+0x40>
    1086: 68 05 00 00 00               	pushq	$0x5
    108b: e9 90 ff ff ff               	jmp	0x1020 <.plt>

0000000000001090 <bind@plt>:
    1090: ff 25 9a 2f 00 00            	jmpq	*0x2f9a(%rip)           # 0x4030 <_GLOBAL_OFFSET_TABLE_+0x48>
    1096: 68 06 00 00 00               	pushq	$0x6
    109b: e9 80 ff ff ff               	jmp	0x1020 <.plt>

00000000000010a0 <accept@plt>:
    10a0: ff 25 92 2f 00 00            	jmpq	*0x2f92(%rip)           # 0x4038 <_GLOBAL_OFFSET_TABLE_+0x50>
    10a6: 68 07 00 00 00               	pushq	$0x7
    10ab: e9 70 ff ff ff               	jmp	0x1020 <.plt>

00000000000010b0 <socket@plt>:
    10b0: ff 25 8a 2f 00 00            	jmpq	*0x2f8a(%rip)           # 0x4040 <_GLOBAL_OFFSET_TABLE_+0x58>
    10b6: 68 08 00 00 00               	pushq	$0x8
    10bb: e9 60 ff ff ff               	jmp	0x1020 <.plt>

Disassembly of section .text:

00000000000010c0 <_start>:
    10c0: f3 0f 1e fa                  	endbr64
    10c4: 31 ed                        	xorl	%ebp, %ebp
    10c6: 49 89 d1                     	movq	%rdx, %r9
    10c9: 5e                           	popq	%rsi
    10ca: 48 89 e2                     	movq	%rsp, %rdx
    10cd: 48 83 e4 f0                  	andq	$-0x10, %rsp
    10d1: 50                           	pushq	%rax
    10d2: 54                           	pushq	%rsp
    10d3: 45 31 c0                     	xorl	%r8d, %r8d
    10d6: 31 c9                        	xorl	%ecx, %ecx
    10d8: 48 8d 3d e1 00 00 00         	leaq	0xe1(%rip), %rdi        # 0x11c0 <main>
    10df: ff 15 db 2e 00 00            	callq	*0x2edb(%rip)           # 0x3fc0 <socket@GLIBC_2.2.5+0x3fc0>
    10e5: f4                           	hlt
    10e6: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%rax,%rax)
    10f0: 48 8d 3d 61 2f 00 00         	leaq	0x2f61(%rip), %rdi      # 0x4058 <__bss_start>
    10f7: 48 8d 05 5a 2f 00 00         	leaq	0x2f5a(%rip), %rax      # 0x4058 <__bss_start>
    10fe: 48 39 f8                     	cmpq	%rdi, %rax
    1101: 74 15                        	je	0x1118 <_start+0x58>
    1103: 48 8b 05 be 2e 00 00         	movq	0x2ebe(%rip), %rax      # 0x3fc8 <socket@GLIBC_2.2.5+0x3fc8>
    110a: 48 85 c0                     	testq	%rax, %rax
    110d: 74 09                        	je	0x1118 <_start+0x58>
    110f: ff e0                        	jmpq	*%rax
    1111: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1118: c3                           	retq
    1119: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1120: 48 8d 3d 31 2f 00 00         	leaq	0x2f31(%rip), %rdi      # 0x4058 <__bss_start>
    1127: 48 8d 35 2a 2f 00 00         	leaq	0x2f2a(%rip), %rsi      # 0x4058 <__bss_start>
    112e: 48 29 fe                     	subq	%rdi, %rsi
    1131: 48 89 f0                     	movq	%rsi, %rax
    1134: 48 c1 ee 3f                  	shrq	$0x3f, %rsi
    1138: 48 c1 f8 03                  	sarq	$0x3, %rax
    113c: 48 01 c6                     	addq	%rax, %rsi
    113f: 48 d1 fe                     	sarq	%rsi
    1142: 74 14                        	je	0x1158 <_start+0x98>
    1144: 48 8b 05 8d 2e 00 00         	movq	0x2e8d(%rip), %rax      # 0x3fd8 <socket@GLIBC_2.2.5+0x3fd8>
    114b: 48 85 c0                     	testq	%rax, %rax
    114e: 74 08                        	je	0x1158 <_start+0x98>
    1150: ff e0                        	jmpq	*%rax
    1152: 66 0f 1f 44 00 00            	nopw	(%rax,%rax)
    1158: c3                           	retq
    1159: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1160: f3 0f 1e fa                  	endbr64
    1164: 80 3d ed 2e 00 00 00         	cmpb	$0x0, 0x2eed(%rip)      # 0x4058 <__bss_start>
    116b: 75 33                        	jne	0x11a0 <_start+0xe0>
    116d: 55                           	pushq	%rbp
    116e: 48 83 3d 6a 2e 00 00 00      	cmpq	$0x0, 0x2e6a(%rip)      # 0x3fe0 <socket@GLIBC_2.2.5+0x3fe0>
    1176: 48 89 e5                     	movq	%rsp, %rbp
    1179: 74 0d                        	je	0x1188 <_start+0xc8>
    117b: 48 8b 3d ce 2e 00 00         	movq	0x2ece(%rip), %rdi      # 0x4050 <__dso_handle>
    1182: ff 15 58 2e 00 00            	callq	*0x2e58(%rip)           # 0x3fe0 <socket@GLIBC_2.2.5+0x3fe0>
    1188: e8 63 ff ff ff               	callq	0x10f0 <_start+0x30>
    118d: c6 05 c4 2e 00 00 01         	movb	$0x1, 0x2ec4(%rip)      # 0x4058 <__bss_start>
    1194: 5d                           	popq	%rbp
    1195: c3                           	retq
    1196: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%rax,%rax)
    11a0: c3                           	retq
    11a1: 66 66 2e 0f 1f 84 00 00 00 00 00     	nopw	%cs:(%rax,%rax)
    11ac: 0f 1f 40 00                  	nopl	(%rax)
    11b0: f3 0f 1e fa                  	endbr64
    11b4: e9 67 ff ff ff               	jmp	0x1120 <_start+0x60>
    11b9: 0f 1f 80 00 00 00 00         	nopl	(%rax)

00000000000011c0 <main>:
    11c0: 55                           	pushq	%rbp
    11c1: 41 56                        	pushq	%r14
    11c3: 53                           	pushq	%rbx
    11c4: 48 81 ec 40 04 00 00         	subq	$0x440, %rsp            # imm = 0x440
    11cb: 64 48 8b 04 25 28 00 00 00   	movq	%fs:0x28, %rax
    11d4: 4c 8d 74 24 10               	leaq	0x10(%rsp), %r14
    11d9: ba 00 04 00 00               	movl	$0x400, %edx            # imm = 0x400
    11de: 31 f6                        	xorl	%esi, %esi
    11e0: 4c 89 f7                     	movq	%r14, %rdi
    11e3: 48 89 84 24 38 04 00 00      	movq	%rax, 0x438(%rsp)
    11eb: c7 44 24 0c 10 00 00 00      	movl	$0x10, 0xc(%rsp)
    11f3: e8 58 fe ff ff               	callq	0x1050 <memset@plt>
    11f8: bf 02 00 00 00               	movl	$0x2, %edi
    11fd: be 01 00 00 00               	movl	$0x1, %esi
    1202: 31 d2                        	xorl	%edx, %edx
    1204: e8 a7 fe ff ff               	callq	0x10b0 <socket@plt>
    1209: 89 c3                        	movl	%eax, %ebx
    120b: b8 02 00 1f 90               	movl	$0x901f0002, %eax       # imm = 0x901F0002
    1210: 48 8d b4 24 28 04 00 00      	leaq	0x428(%rsp), %rsi
    1218: ba 10 00 00 00               	movl	$0x10, %edx
    121d: 89 df                        	movl	%ebx, %edi
    121f: 48 89 84 24 28 04 00 00      	movq	%rax, 0x428(%rsp)
    1227: e8 64 fe ff ff               	callq	0x1090 <bind@plt>
    122c: 89 df                        	movl	%ebx, %edi
    122e: be 05 00 00 00               	movl	$0x5, %esi
    1233: e8 48 fe ff ff               	callq	0x1080 <listen@plt>
    1238: 48 8d b4 24 18 04 00 00      	leaq	0x418(%rsp), %rsi
    1240: 48 8d 54 24 0c               	leaq	0xc(%rsp), %rdx
    1245: 89 df                        	movl	%ebx, %edi
    1247: e8 54 fe ff ff               	callq	0x10a0 <accept@plt>
    124c: ba 00 04 00 00               	movl	$0x400, %edx            # imm = 0x400
    1251: 89 c7                        	movl	%eax, %edi
    1253: 4c 89 f6                     	movq	%r14, %rsi
    1256: 89 c5                        	movl	%eax, %ebp
    1258: e8 13 fe ff ff               	callq	0x1070 <read@plt>
    125d: 48 8d 35 a0 0d 00 00         	leaq	0xda0(%rip), %rsi       # 0x2004 <_IO_stdin_used+0x4>
    1264: ba 3f 00 00 00               	movl	$0x3f, %edx
    1269: 89 ef                        	movl	%ebp, %edi
    126b: 31 c9                        	xorl	%ecx, %ecx
    126d: e8 ce fd ff ff               	callq	0x1040 <send@plt>
    1272: 89 ef                        	movl	%ebp, %edi
    1274: e8 e7 fd ff ff               	callq	0x1060 <close@plt>
    1279: 89 df                        	movl	%ebx, %edi
    127b: e8 e0 fd ff ff               	callq	0x1060 <close@plt>
    1280: 64 48 8b 04 25 28 00 00 00   	movq	%fs:0x28, %rax
    1289: 48 3b 84 24 38 04 00 00      	cmpq	0x438(%rsp), %rax
    1291: 75 0e                        	jne	0x12a1 <main+0xe1>
    1293: 31 c0                        	xorl	%eax, %eax
    1295: 48 81 c4 40 04 00 00         	addq	$0x440, %rsp            # imm = 0x440
    129c: 5b                           	popq	%rbx
    129d: 41 5e                        	popq	%r14
    129f: 5d                           	popq	%rbp
    12a0: c3                           	retq
    12a1: e8 8a fd ff ff               	callq	0x1030 <__stack_chk_fail@plt>

Disassembly of section .fini:

00000000000012a8 <_fini>:
    12a8: f3 0f 1e fa                  	endbr64
    12ac: 48 83 ec 08                  	subq	$0x8, %rsp
    12b0: 48 83 c4 08                  	addq	$0x8, %rsp
    12b4: c3                           	retq
