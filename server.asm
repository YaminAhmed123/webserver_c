
server:	file format elf64-x86-64

Disassembly of section .init:

0000000000001000 <_init>:
    1000: f3 0f 1e fa                  	endbr64
    1004: 48 83 ec 08                  	subq	$0x8, %rsp
    1008: 48 8b 05 c1 2f 00 00         	movq	0x2fc1(%rip), %rax      # 0x3fd0 <strlen@GLIBC_2.2.5+0x3fd0>
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

0000000000001030 <strlen@plt>:
    1030: ff 25 ca 2f 00 00            	jmpq	*0x2fca(%rip)           # 0x4000 <_GLOBAL_OFFSET_TABLE_+0x18>
    1036: 68 00 00 00 00               	pushq	$0x0
    103b: e9 e0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001040 <__stack_chk_fail@plt>:
    1040: ff 25 c2 2f 00 00            	jmpq	*0x2fc2(%rip)           # 0x4008 <_GLOBAL_OFFSET_TABLE_+0x20>
    1046: 68 01 00 00 00               	pushq	$0x1
    104b: e9 d0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001050 <htons@plt>:
    1050: ff 25 ba 2f 00 00            	jmpq	*0x2fba(%rip)           # 0x4010 <_GLOBAL_OFFSET_TABLE_+0x28>
    1056: 68 02 00 00 00               	pushq	$0x2
    105b: e9 c0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001060 <send@plt>:
    1060: ff 25 b2 2f 00 00            	jmpq	*0x2fb2(%rip)           # 0x4018 <_GLOBAL_OFFSET_TABLE_+0x30>
    1066: 68 03 00 00 00               	pushq	$0x3
    106b: e9 b0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001070 <printf@plt>:
    1070: ff 25 aa 2f 00 00            	jmpq	*0x2faa(%rip)           # 0x4020 <_GLOBAL_OFFSET_TABLE_+0x38>
    1076: 68 04 00 00 00               	pushq	$0x4
    107b: e9 a0 ff ff ff               	jmp	0x1020 <.plt>

0000000000001080 <htonl@plt>:
    1080: ff 25 a2 2f 00 00            	jmpq	*0x2fa2(%rip)           # 0x4028 <_GLOBAL_OFFSET_TABLE_+0x40>
    1086: 68 05 00 00 00               	pushq	$0x5
    108b: e9 90 ff ff ff               	jmp	0x1020 <.plt>

0000000000001090 <memset@plt>:
    1090: ff 25 9a 2f 00 00            	jmpq	*0x2f9a(%rip)           # 0x4030 <_GLOBAL_OFFSET_TABLE_+0x48>
    1096: 68 06 00 00 00               	pushq	$0x6
    109b: e9 80 ff ff ff               	jmp	0x1020 <.plt>

00000000000010a0 <close@plt>:
    10a0: ff 25 92 2f 00 00            	jmpq	*0x2f92(%rip)           # 0x4038 <_GLOBAL_OFFSET_TABLE_+0x50>
    10a6: 68 07 00 00 00               	pushq	$0x7
    10ab: e9 70 ff ff ff               	jmp	0x1020 <.plt>

00000000000010b0 <listen@plt>:
    10b0: ff 25 8a 2f 00 00            	jmpq	*0x2f8a(%rip)           # 0x4040 <_GLOBAL_OFFSET_TABLE_+0x58>
    10b6: 68 08 00 00 00               	pushq	$0x8
    10bb: e9 60 ff ff ff               	jmp	0x1020 <.plt>

00000000000010c0 <bind@plt>:
    10c0: ff 25 82 2f 00 00            	jmpq	*0x2f82(%rip)           # 0x4048 <_GLOBAL_OFFSET_TABLE_+0x60>
    10c6: 68 09 00 00 00               	pushq	$0x9
    10cb: e9 50 ff ff ff               	jmp	0x1020 <.plt>

00000000000010d0 <accept@plt>:
    10d0: ff 25 7a 2f 00 00            	jmpq	*0x2f7a(%rip)           # 0x4050 <_GLOBAL_OFFSET_TABLE_+0x68>
    10d6: 68 0a 00 00 00               	pushq	$0xa
    10db: e9 40 ff ff ff               	jmp	0x1020 <.plt>

00000000000010e0 <socket@plt>:
    10e0: ff 25 72 2f 00 00            	jmpq	*0x2f72(%rip)           # 0x4058 <_GLOBAL_OFFSET_TABLE_+0x70>
    10e6: 68 0b 00 00 00               	pushq	$0xb
    10eb: e9 30 ff ff ff               	jmp	0x1020 <.plt>

Disassembly of section .text:

00000000000010f0 <_start>:
    10f0: f3 0f 1e fa                  	endbr64
    10f4: 31 ed                        	xorl	%ebp, %ebp
    10f6: 49 89 d1                     	movq	%rdx, %r9
    10f9: 5e                           	popq	%rsi
    10fa: 48 89 e2                     	movq	%rsp, %rdx
    10fd: 48 83 e4 f0                  	andq	$-0x10, %rsp
    1101: 50                           	pushq	%rax
    1102: 54                           	pushq	%rsp
    1103: 45 31 c0                     	xorl	%r8d, %r8d
    1106: 31 c9                        	xorl	%ecx, %ecx
    1108: 48 8d 3d e1 00 00 00         	leaq	0xe1(%rip), %rdi        # 0x11f0 <main>
    110f: ff 15 ab 2e 00 00            	callq	*0x2eab(%rip)           # 0x3fc0 <strlen@GLIBC_2.2.5+0x3fc0>
    1115: f4                           	hlt
    1116: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%rax,%rax)
    1120: 48 8d 3d 49 2f 00 00         	leaq	0x2f49(%rip), %rdi      # 0x4070 <__bss_start>
    1127: 48 8d 05 42 2f 00 00         	leaq	0x2f42(%rip), %rax      # 0x4070 <__bss_start>
    112e: 48 39 f8                     	cmpq	%rdi, %rax
    1131: 74 15                        	je	0x1148 <_start+0x58>
    1133: 48 8b 05 8e 2e 00 00         	movq	0x2e8e(%rip), %rax      # 0x3fc8 <strlen@GLIBC_2.2.5+0x3fc8>
    113a: 48 85 c0                     	testq	%rax, %rax
    113d: 74 09                        	je	0x1148 <_start+0x58>
    113f: ff e0                        	jmpq	*%rax
    1141: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1148: c3                           	retq
    1149: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1150: 48 8d 3d 19 2f 00 00         	leaq	0x2f19(%rip), %rdi      # 0x4070 <__bss_start>
    1157: 48 8d 35 12 2f 00 00         	leaq	0x2f12(%rip), %rsi      # 0x4070 <__bss_start>
    115e: 48 29 fe                     	subq	%rdi, %rsi
    1161: 48 89 f0                     	movq	%rsi, %rax
    1164: 48 c1 ee 3f                  	shrq	$0x3f, %rsi
    1168: 48 c1 f8 03                  	sarq	$0x3, %rax
    116c: 48 01 c6                     	addq	%rax, %rsi
    116f: 48 d1 fe                     	sarq	%rsi
    1172: 74 14                        	je	0x1188 <_start+0x98>
    1174: 48 8b 05 5d 2e 00 00         	movq	0x2e5d(%rip), %rax      # 0x3fd8 <strlen@GLIBC_2.2.5+0x3fd8>
    117b: 48 85 c0                     	testq	%rax, %rax
    117e: 74 08                        	je	0x1188 <_start+0x98>
    1180: ff e0                        	jmpq	*%rax
    1182: 66 0f 1f 44 00 00            	nopw	(%rax,%rax)
    1188: c3                           	retq
    1189: 0f 1f 80 00 00 00 00         	nopl	(%rax)
    1190: f3 0f 1e fa                  	endbr64
    1194: 80 3d d5 2e 00 00 00         	cmpb	$0x0, 0x2ed5(%rip)      # 0x4070 <__bss_start>
    119b: 75 33                        	jne	0x11d0 <_start+0xe0>
    119d: 55                           	pushq	%rbp
    119e: 48 83 3d 3a 2e 00 00 00      	cmpq	$0x0, 0x2e3a(%rip)      # 0x3fe0 <strlen@GLIBC_2.2.5+0x3fe0>
    11a6: 48 89 e5                     	movq	%rsp, %rbp
    11a9: 74 0d                        	je	0x11b8 <_start+0xc8>
    11ab: 48 8b 3d b6 2e 00 00         	movq	0x2eb6(%rip), %rdi      # 0x4068 <__dso_handle>
    11b2: ff 15 28 2e 00 00            	callq	*0x2e28(%rip)           # 0x3fe0 <strlen@GLIBC_2.2.5+0x3fe0>
    11b8: e8 63 ff ff ff               	callq	0x1120 <_start+0x30>
    11bd: c6 05 ac 2e 00 00 01         	movb	$0x1, 0x2eac(%rip)      # 0x4070 <__bss_start>
    11c4: 5d                           	popq	%rbp
    11c5: c3                           	retq
    11c6: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%rax,%rax)
    11d0: c3                           	retq
    11d1: 66 66 2e 0f 1f 84 00 00 00 00 00     	nopw	%cs:(%rax,%rax)
    11dc: 0f 1f 40 00                  	nopl	(%rax)
    11e0: f3 0f 1e fa                  	endbr64
    11e4: e9 67 ff ff ff               	jmp	0x1150 <_start+0x60>
    11e9: 0f 1f 80 00 00 00 00         	nopl	(%rax)

00000000000011f0 <main>:
    11f0: 55                           	pushq	%rbp
    11f1: 48 89 e5                     	movq	%rsp, %rbp
    11f4: 48 83 ec 50                  	subq	$0x50, %rsp
    11f8: 64 48 8b 04 25 28 00 00 00   	movq	%fs:0x28, %rax
    1201: 48 89 45 f8                  	movq	%rax, -0x8(%rbp)
    1205: c7 45 d0 00 00 00 00         	movl	$0x0, -0x30(%rbp)
    120c: c7 45 c8 10 00 00 00         	movl	$0x10, -0x38(%rbp)
    1213: 48 8d 05 ea 0d 00 00         	leaq	0xdea(%rip), %rax       # 0x2004 <_IO_stdin_used+0x4>
    121a: 48 89 45 c0                  	movq	%rax, -0x40(%rbp)
    121e: 48 8d 7d d8                  	leaq	-0x28(%rbp), %rdi
    1222: 31 f6                        	xorl	%esi, %esi
    1224: ba 10 00 00 00               	movl	$0x10, %edx
    1229: e8 62 fe ff ff               	callq	0x1090 <memset@plt>
    122e: 66 c7 45 d8 02 00            	movw	$0x2, -0x28(%rbp)
    1234: 31 ff                        	xorl	%edi, %edi
    1236: e8 45 fe ff ff               	callq	0x1080 <htonl@plt>
    123b: 89 45 dc                     	movl	%eax, -0x24(%rbp)
    123e: bf 90 1f 00 00               	movl	$0x1f90, %edi           # imm = 0x1F90
    1243: e8 08 fe ff ff               	callq	0x1050 <htons@plt>
    1248: 66 89 45 da                  	movw	%ax, -0x26(%rbp)
    124c: bf 02 00 00 00               	movl	$0x2, %edi
    1251: be 01 00 00 00               	movl	$0x1, %esi
    1256: 31 d2                        	xorl	%edx, %edx
    1258: e8 83 fe ff ff               	callq	0x10e0 <socket@plt>
    125d: 89 45 cc                     	movl	%eax, -0x34(%rbp)
    1260: 8b 7d cc                     	movl	-0x34(%rbp), %edi
    1263: 48 8d 75 d8                  	leaq	-0x28(%rbp), %rsi
    1267: ba 10 00 00 00               	movl	$0x10, %edx
    126c: e8 4f fe ff ff               	callq	0x10c0 <bind@plt>
    1271: 8b 7d cc                     	movl	-0x34(%rbp), %edi
    1274: be 01 00 00 00               	movl	$0x1, %esi
    1279: e8 32 fe ff ff               	callq	0x10b0 <listen@plt>
    127e: 8b 7d cc                     	movl	-0x34(%rbp), %edi
    1281: 48 8d 75 e8                  	leaq	-0x18(%rbp), %rsi
    1285: 48 8d 55 d4                  	leaq	-0x2c(%rbp), %rdx
    1289: e8 42 fe ff ff               	callq	0x10d0 <accept@plt>
    128e: 89 45 d4                     	movl	%eax, -0x2c(%rbp)
    1291: 83 7d d4 00                  	cmpl	$0x0, -0x2c(%rbp)
    1295: 0f 84 56 00 00 00            	je	0x12f1 <main+0x101>
    129b: 8b 45 d4                     	movl	-0x2c(%rbp), %eax
    129e: 89 45 b4                     	movl	%eax, -0x4c(%rbp)
    12a1: 48 8b 45 c0                  	movq	-0x40(%rbp), %rax
    12a5: 48 89 45 b8                  	movq	%rax, -0x48(%rbp)
    12a9: 48 8b 7d c0                  	movq	-0x40(%rbp), %rdi
    12ad: e8 7e fd ff ff               	callq	0x1030 <strlen@plt>
    12b2: 8b 7d b4                     	movl	-0x4c(%rbp), %edi
    12b5: 48 8b 75 b8                  	movq	-0x48(%rbp), %rsi
    12b9: 48 89 c2                     	movq	%rax, %rdx
    12bc: 31 c9                        	xorl	%ecx, %ecx
    12be: e8 9d fd ff ff               	callq	0x1060 <send@plt>
    12c3: 48 8d 3d 61 0d 00 00         	leaq	0xd61(%rip), %rdi       # 0x202b <_IO_stdin_used+0x2b>
    12ca: b0 00                        	movb	$0x0, %al
    12cc: e8 9f fd ff ff               	callq	0x1070 <printf@plt>
    12d1: 8b 7d d4                     	movl	-0x2c(%rbp), %edi
    12d4: e8 c7 fd ff ff               	callq	0x10a0 <close@plt>
    12d9: 8b 7d cc                     	movl	-0x34(%rbp), %edi
    12dc: 48 8d 75 e8                  	leaq	-0x18(%rbp), %rsi
    12e0: 48 8d 55 d4                  	leaq	-0x2c(%rbp), %rdx
    12e4: e8 e7 fd ff ff               	callq	0x10d0 <accept@plt>
    12e9: 89 45 d4                     	movl	%eax, -0x2c(%rbp)
    12ec: e9 a0 ff ff ff               	jmp	0x1291 <main+0xa1>
    12f1: 64 48 8b 04 25 28 00 00 00   	movq	%fs:0x28, %rax
    12fa: 48 8b 4d f8                  	movq	-0x8(%rbp), %rcx
    12fe: 48 39 c8                     	cmpq	%rcx, %rax
    1301: 0f 85 08 00 00 00            	jne	0x130f <main+0x11f>
    1307: 31 c0                        	xorl	%eax, %eax
    1309: 48 83 c4 50                  	addq	$0x50, %rsp
    130d: 5d                           	popq	%rbp
    130e: c3                           	retq
    130f: e8 2c fd ff ff               	callq	0x1040 <__stack_chk_fail@plt>

Disassembly of section .fini:

0000000000001314 <_fini>:
    1314: f3 0f 1e fa                  	endbr64
    1318: 48 83 ec 08                  	subq	$0x8, %rsp
    131c: 48 83 c4 08                  	addq	$0x8, %rsp
    1320: c3                           	retq