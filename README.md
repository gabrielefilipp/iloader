iBoot loader by xerub: https://xerub.github.io/ios/iboot/2018/05/10/de-rebus-antiquis.html

iPhone3,2/11D257 was the bundle added, inside iloader it works fine. The ramdiskF_iloader.dmg is the dmg that contains the patches to work inside iloder (mostly addresses relocation). The payload (shellcode) inside ramdiskF.dmg needs to be updated to be usable in the real boot-chain. Also aside from iloader nothing was tested in the real bootchain.
