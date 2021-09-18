#include <stdio.h>


#define TARGET_JUMPADDR 0x44000000


int
main(void)
{
    *(unsigned int *)(TARGET_JUMPADDR + 0x4116c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41170) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41174) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41178) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4117c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4123c) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41258) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4125c) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41260) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41264) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41270) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41274) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4127c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41284) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4128c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41290) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41294) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41298) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4129c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412a0) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412a4) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412a8) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412c4) = 0x00000011;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412c8) = 0x5ff412c8;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412cc) = 0x5ff412c8;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41300) = 0x5ff41300;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41304) = 0x5ff41300;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41308) = 0x5ff41308;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4130c) = 0x5ff41308;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41314) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41318) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41330) = 0x5ff41350;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41348) = 0x5ff41348;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4134c) = 0x5ff41348;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41364) = 0x00000002;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4136c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41370) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41374) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41378) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4138c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41390) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x414bc) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x414c0) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x414f4) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41574) = 0x5ff41574;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41578) = 0x5ff41574;
    *(unsigned int *)(TARGET_JUMPADDR + 0x415e0) = 0xffffffff;
    return 0;
}
