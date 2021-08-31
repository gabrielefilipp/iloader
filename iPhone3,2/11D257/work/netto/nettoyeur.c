#include <stdio.h>


#define TARGET_JUMPADDR 0x44000000


int
main(void)
{
    *(unsigned int *)(TARGET_JUMPADDR + 0x41170) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41174) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41178) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4117c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4123c) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412c8) = 0x5ff412c8;
    *(unsigned int *)(TARGET_JUMPADDR + 0x412cc) = 0x5ff412c8;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41308) = 0x5ff41308;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4130c) = 0x5ff41308;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41314) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41318) = 0xffffffff;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41330) = 0x5ff41350;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41348) = 0x5ff41348;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4134c) = 0x5ff41348;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41364) = 0x00000002;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41368) = 0x00000001;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4136c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41370) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41374) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41378) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41380) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41388) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x4138c) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41390) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x414bc) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x414c0) = 0x00000000;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41574) = 0x5ff41574;
    *(unsigned int *)(TARGET_JUMPADDR + 0x41578) = 0x5ff41574;
    return 0;
}
