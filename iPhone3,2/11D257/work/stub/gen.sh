#!/bin/sh

arm-none-eabi-gcc -march=armv7-a -c iboot_p1.S
arm-none-eabi-objdump -D iboot_p1.o > iboot_p1.asm
cat iboot_p1.asm
