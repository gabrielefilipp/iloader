
iboot_p1.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <_entry>:
       0:	eafffffe 	b	0 <_entry>
	...

0001efe6 <_get_current_task>:
   1efe6:	4770      	bx	lr
	...

00020300 <_sub_5FF20300>:
   20300:	4770      	bx	lr
	...

00023260 <_decompress_lzss>:
   23260:	4770      	bx	lr
	...

00031e64 <_bcopy>:
   31e64:	e12fff1e 	bx	lr
	...

00032884 <_disable_interrupts>:
   32884:	4770      	bx	lr
	...

00044708 <_payload>:
   44708:	f8df d048 	ldr.w	sp, [pc, #72]	; 44754 <next>
   4470c:	f7ee f8ba 	bl	32884 <_disable_interrupts>
   44710:	4c11      	ldr	r4, [pc, #68]	; (44758 <next+0x4>)
   44712:	4812      	ldr	r0, [pc, #72]	; (4475c <next+0x8>)
   44714:	4621      	mov	r1, r4
   44716:	4a12      	ldr	r2, [pc, #72]	; (44760 <next+0xc>)
   44718:	f7ed eba4 	blx	31e64 <_bcopy>
   4471c:	f44f 5110 	mov.w	r1, #9216	; 0x2400
   44720:	f8a4 1e2c 	strh.w	r1, [r4, #3628]	; 0xe2c
   44724:	480f      	ldr	r0, [pc, #60]	; (44764 <next+0x10>)
   44726:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
   4472a:	5021      	str	r1, [r4, r0]
   4472c:	480e      	ldr	r0, [pc, #56]	; (44768 <next+0x14>)
   4472e:	490f      	ldr	r1, [pc, #60]	; (4476c <next+0x18>)
   44730:	5021      	str	r1, [r4, r0]
   44732:	480f      	ldr	r0, [pc, #60]	; (44770 <next+0x1c>)
   44734:	21fc      	movs	r1, #252	; 0xfc
   44736:	4a0f      	ldr	r2, [pc, #60]	; (44774 <next+0x20>)
   44738:	23a4      	movs	r3, #164	; 0xa4
   4473a:	b401      	push	{r0}
   4473c:	f7de fd90 	bl	23260 <_decompress_lzss>
   44740:	480c      	ldr	r0, [pc, #48]	; (44774 <next+0x20>)
   44742:	4780      	blx	r0
   44744:	46a6      	mov	lr, r4
   44746:	bd00      	pop	{pc}
	...

00044754 <next>:
   44754:	5fff8000 	svcpl	0x00ff8000
   44758:	44000000 	strmi	r0, [r0]
   4475c:	5ff00000 	svcpl	0x00f00000	; IMB
   44760:	00041640 	andeq	r1, r4, r0, asr #12
   44764:	0003f378 	andeq	pc, r3, r8, ror r3	; <UNPREDICTABLE>
   44768:	00019164 	andeq	r9, r1, r4, ror #2
   4476c:	60182000 	andsvs	r2, r8, r0
   44770:	5ff48000 	svcpl	0x00f48000
   44774:	5ff445bc 	svcpl	0x00f445bc

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

