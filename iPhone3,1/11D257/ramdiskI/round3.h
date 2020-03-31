/*
 * ramdiskI: pseudo_code
 *
 * Created by dora2_yururi on 2020/02/06.
 * Copyright (c) 2019 - 2020 dora2_yururi. All rights reserved.
 *
 */

// 1) image_load_type
int image_load_type(addr_t *addr, size_t *length, uint32_t type);
// Use image_load_type() func to load an image with 'type' into addr.

// 2) payload for loading new-image
// For n90, image_jump_addr = 0x44000000.
// Using shadowLee19's method, load a new iBoot image with ibob into image_jump_addr.
// https://www.pmbonneau.com/multiboot/patching_llb_iboot.php
// After loading the image, execute do_go_target() func to jump to the new iBoot.

// 2) pseudo code
void _image_load_func() {
    addr_t addr = 0x44000000; // jump address
    size_t length = 0x100000;
    uint32_t type = 0x69626F62; // type = 'ibob'
    image_load_type(addr, length, type);
    _jump_go_command();
}

void _jump_go_command() {
    _do_go_target();
}

int _do_go_target(..) {
    _printf("jumping into image at %p\n", 0x44000000);
    ..
}

// 3) Execute the payload with untether
// This payload possible to jump flashed unsigned images with untether using De Rebus Antiquis.
void _payload_n90_11d257_DRA() { // pseudo code
    // move back SP
    sp = IMAGE_START + IMAGE_SIZE + IMAGE_HEAP_SIZE + IMAGE_STACK_SIZE; // sp = 0x5fff8000
    
    // disable interrupts
    _disable_interrupts();
    
    // Copy memory : image_start -> image_jump_addr (sz: bss_start - image_start)
    _bcopy(IMAGE_START, IMAGE_JUMPADDR, IMAGE_BSS_START - IMAGE_START);
    
    { // apply patches
        *(IMAGE_JUMPADDR + OFFSETOF_RSA) = INSN2_MOV_R0_0__STR_R0_R3; // accept unsigned images
        
        // *ramdiskI
        //  In addition to the De Rebus Antiquis payload, put the payload in part2 above in ramdisk.
        //  Use iloader to see where the ramdisk is loaded.
        //  After grasping the ramdisk address, copy the payload using bcopy().
        _bcopy(OFFSETOF_PAYLOAD, PAYLOAD_ADDR, payload_sz); // write the payload of part2
        *(IMAGE_JUMPADDR + 0xcd6) = INSN2_BL_imageload; // hook image_load_func(): hook the payload after nand_firmware is executed.

    }
    
    // uncompress nettoyeur
    _decompress_lzss(dst, dst_sz, nettoyeur, nettoyeur_sz);
    
    // run nettoyeur
    _nettoyeur();
    
    _sub_5ff20000(); // Cache related??
    
    // jump back to iBoot start point and let it re-run
    _IMAGE_JUMPADDR(); // 0x44000000
}

// After exploited De Rebus Antiquis, reload the image patched with {apply patches}.
// Next, after executing nand_firmware, the payload is hooked and load new iBoot with type = 'ibob'.

/*
 *                        [copy iboot and injecting payload]
 *                                   |
 *                                   v
 *                           +-----------+   +--[load payload]
 *                           |           |   |
 *                           |           v   v
 * secureROM -> 'illb' -> 'ibot'  ->  'ibot' -> 'ibob' -> Boot unsigned image
 *                |          |    ^     |         |
 *             [signed by apple]  |     |  [new "PWNED" iBoot (unsigned)]
 *                                |     |
 *                        [run exploit] |
 *                                      |
 *                            [trigger payload image]
 */
