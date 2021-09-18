
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

5ff44708 <_payload>:
5ff44708:	f8df d058 	ldr.w	sp, [pc, #88]	; 5ff44764 <_next+0x10>
5ff4470c:	f7ee f8ba 	bl	5ff32884 <_disable_interrupts>
5ff44710:	4c15      	ldr	r4, [pc, #84]	; (5ff44768 <_next+0x14>)
5ff44712:	4816      	ldr	r0, [pc, #88]	; (5ff4476c <_next+0x18>)
5ff44714:	4621      	mov	r1, r4
5ff44716:	4a16      	ldr	r2, [pc, #88]	; (5ff44770 <_next+0x1c>)
5ff44718:	f7ed eba4 	blx	5ff31e64 <_bcopy>
5ff4471c:	f44f 5110 	mov.w	r1, #9216	; 0x2400
5ff44720:	f8a4 1e2c 	strh.w	r1, [r4, #3628]	; 0xe2c
5ff44724:	4813      	ldr	r0, [pc, #76]	; (5ff44774 <_next+0x20>)
5ff44726:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
5ff4472a:	5021      	str	r1, [r4, r0]
5ff4472c:	4812      	ldr	r0, [pc, #72]	; (5ff44778 <_next+0x24>)
5ff4472e:	4913      	ldr	r1, [pc, #76]	; (5ff4477c <_next+0x28>)
5ff44730:	5021      	str	r1, [r4, r0]
5ff44732:	f7da fc81 	bl	5ff1f038 <_get_current_task>
5ff44736:	2100      	movs	r1, #0
5ff44738:	6441      	str	r1, [r0, #68]	; 0x44
5ff4473a:	4811      	ldr	r0, [pc, #68]	; (5ff44780 <_next+0x2c>)
5ff4473c:	21ac      	movs	r1, #172	; 0xac
5ff4473e:	4a11      	ldr	r2, [pc, #68]	; (5ff44784 <_next+0x30>)
5ff44740:	23a4      	movs	r3, #164	; 0xa4
5ff44742:	4605      	mov	r5, r0
5ff44744:	e006      	b.n	5ff44754 <_next>
5ff44746:	bf00      	nop
	...

5ff44754 <_next>:
5ff44754:	f7de fd84 	bl	5ff23260 <_decompress_lzss>
5ff44758:	480a      	ldr	r0, [pc, #40]	; (5ff44784 <_next+0x30>)
5ff4475a:	4780      	blx	r0
5ff4475c:	f7db fdd0 	bl	5ff20300 <_cache_stuff>
5ff44760:	47a8      	blx	r5
5ff44762:	4720      	bx	r4
5ff44764:	5fff8000 	svcpl	0x00ff8000
5ff44768:	44000001 	strmi	r0, [r0], #-1
5ff4476c:	5ff00000 	svcpl	0x00f00000	; IMB
5ff44770:	00041640 	andeq	r1, r4, r0, asr #12
5ff44774:	0003f378 	andeq	pc, r3, r8, ror r3	; <UNPREDICTABLE>
5ff44778:	00019164 	andeq	r9, r1, r4, ror #2
5ff4477c:	60182000 	andsvs	r2, r8, r0
5ff44780:	5ff48000 	svcpl	0x00f48000
5ff44784:	5ff445bc 	svcpl	0x00f445bc

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

