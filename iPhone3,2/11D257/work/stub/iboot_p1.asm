
iboot_p1.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <_entry>:
       0:	eafffffe 	b	0 <_entry>
	...

5ff1f038 <_get_current_task>:
5ff1f038:	4770      	bx	lr
	...

5ff20300 <_cache_stuff>:
5ff20300:	4770      	bx	lr
	...

5ff23260 <_decompress_lzss>:
5ff23260:	4770      	bx	lr
	...

5ff31e64 <_bcopy>:
5ff31e64:	e12fff1e 	bx	lr
	...

5ff32884 <_disable_interrupts>:
5ff32884:	4770      	bx	lr
	...

5ff443e0 <_vh>:
5ff443e0:	48db      	ldr	r0, [pc, #876]	; (5ff44750 <_payload+0x20>)
5ff443e2:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
5ff443e6:	5021      	str	r1, [r4, r0]
5ff443e8:	48da      	ldr	r0, [pc, #872]	; (5ff44754 <_payload+0x24>)
5ff443ea:	49db      	ldr	r1, [pc, #876]	; (5ff44758 <_payload+0x28>)
5ff443ec:	5021      	str	r1, [r4, r0]
5ff443ee:	f7da fe23 	bl	5ff1f038 <_get_current_task>
5ff443f2:	2100      	movs	r1, #0
5ff443f4:	6441      	str	r1, [r0, #68]	; 0x44
5ff443f6:	48d9      	ldr	r0, [pc, #868]	; (5ff4475c <_payload+0x2c>)
5ff443f8:	21f8      	movs	r1, #248	; 0xf8
5ff443fa:	4ad9      	ldr	r2, [pc, #868]	; (5ff44760 <_payload+0x30>)
5ff443fc:	23de      	movs	r3, #222	; 0xde
5ff443fe:	4605      	mov	r5, r0
5ff44400:	f7de ff2e 	bl	5ff23260 <_decompress_lzss>
5ff44404:	48d6      	ldr	r0, [pc, #856]	; (5ff44760 <_payload+0x30>)
5ff44406:	4780      	blx	r0
5ff44408:	f7db ff7a 	bl	5ff20300 <_cache_stuff>
5ff4440c:	47a8      	blx	r5
5ff4440e:	4720      	bx	r4
	...

5ff44730 <_payload>:
5ff44730:	f8df d030 	ldr.w	sp, [pc, #48]	; 5ff44764 <_payload+0x34>
5ff44734:	f7ee f8a6 	bl	5ff32884 <_disable_interrupts>
5ff44738:	f04f 4488 	mov.w	r4, #1140850688	; 0x44000000
5ff4473c:	480a      	ldr	r0, [pc, #40]	; (5ff44768 <_payload+0x38>)
5ff4473e:	4621      	mov	r1, r4
5ff44740:	4a0a      	ldr	r2, [pc, #40]	; (5ff4476c <_payload+0x3c>)
5ff44742:	f7ed eb90 	blx	5ff31e64 <_bcopy>
5ff44746:	f44f 5110 	mov.w	r1, #9216	; 0x2400
5ff4474a:	f8a4 1e2c 	strh.w	r1, [r4, #3628]	; 0xe2c
5ff4474e:	e647      	b.n	5ff443e0 <_vh>
5ff44750:	0003f378 	andeq	pc, r3, r8, ror r3	; <UNPREDICTABLE>
5ff44754:	00019164 	andeq	r9, r1, r4, ror #2
5ff44758:	60182000 	andsvs	r2, r8, r0
5ff4475c:	5ff48000 	svcpl	0x00f48000
5ff44760:	5ff445bc 	svcpl	0x00f445bc
5ff44764:	5fff8000 	svcpl	0x00ff8000
5ff44768:	5ff00000 	svcpl	0x00f00000	; IMB
5ff4476c:	00041640 	andeq	r1, r4, r0, asr #12

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00001c41 	andeq	r1, r0, r1, asr #24
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000012 	andeq	r0, r0, r2, lsl r0
  10:	412d3705 			; <UNDEFINED> instruction: 0x412d3705
  14:	070a0600 	streq	r0, [sl, -r0, lsl #12]
  18:	09010841 	stmdbeq	r1, {r0, r6, fp}
  1c:	Address 0x000000000000001c is out of bounds.

