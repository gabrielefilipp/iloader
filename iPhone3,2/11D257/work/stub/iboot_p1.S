	.text
	.syntax	unified

	.arm
_entry:
	b	    _entry

    .org    0x5FF1F038
    .thumb
    .thumb_func
_get_current_task:
	bx	    lr

	.org	0x5FF20300
	.thumb_func
_cache_stuff:
	bx	    lr

	.org	0x5FF23260
	.thumb
	.thumb_func
_decompress_lzss:
	bx	    lr

	.org	0x5FF31E64
	.arm
_bcopy:
	bx	    lr

	.org	0x5FF32884
	.thumb
	.thumb_func
_disable_interrupts:
	bx	    lr

	.org	0x5FF44708
	.global	_payload
	.thumb
	.thumb_func
_payload:
    ldr     sp, =0x5FFF8000
    bl      _disable_interrupts
        
    ldr     r4, =0x44000001 @ need to change this after? xD
    ldr     r0, =0x5FF00000
    mov     r1, r4
    ldr     r2, =0x41640
    blx     _bcopy

    @ just go to console
    mov     r1, #0x2400
    strh    r1, [r4, #0xE2C]

    @ go command -> loadaddr
    ldr     r0, =0x3F378
    mov     r1, #0x40000000
    str     r1, [r4, r0]

    @ accept unsigned images
    ldr     r0, =0x19164
    ldr     r1, =0x60182000
    str     r1, [r4, r0]

    bl      _get_current_task
    movs    r1, #0x0
    str     r1, [r0, #0x44]

    ldr     r0, =0x5FF48000
    movs    r1, #0xAC
    ldr     r2, =0x5FF445BC
    movs    r3, #0xA4           @ nettoyeur_sz
    mov     r5, r0
    b       _next

	.align	2

    @ avoid anything in between

    .org    0x5FF44754
_next:
    bl      _decompress_lzss
    ldr     r0, =0x5FF445BC
    blx     r0

    bl      _cache_stuff
    blx     r5
    bx      r4
    
    .align  2
