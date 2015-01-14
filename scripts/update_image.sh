#!/bin/bash

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
cp src/basicos.bin ./isodir/boot/basicos.bin
cp scripts/menu.lst ./isodir/boot/grub/menu.lst
cp scripts/stage2_eltorito ./isodir/boot/grub/stage2_eltorito
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o basicos.iso isodir
rm -r isodir
