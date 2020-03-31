*ramdiskI.dmg

このexploitはnand_firmwareから'ibob'を持つiBootをロードします。
(ramdiskH.dmgでは4th partitionから/boot/iBECをロードしていました。)
pwnedなiBootのTYPEを'ibob'にしてflashすることで、iOS 7.1.2のiBootからuntetherで未署名iBootにジャンプできます。
ramdiskIを使用することで、ramdiskHよりも起動時間の短縮をはかれるほか、4th partitionが不要になるなどのメリットがあります。

*使い方
1) iBoot32Patcherを使用してpatchしたiBootを用意します。
2) TYPEをibotからibobに書き換えます。
3) patchしたiBootを、 "Firmware/all_flash/all_flash.n90ap.production/iBootB.n90ap.RELEASE.img3" に配置します。
4) "Firmware/all_flash/all_flash.n90ap.production/manifest" に、iBootB.n90ap.RELEASE.img3を追加します。必要に応じてcustomlogoを設置することもできます。
5) このイメージを復元します。exploitを適用すると、ibobを持つpwnediBootをロードすることができます。
