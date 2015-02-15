#!/bin/bash

platform='unknown'
uname=$(uname)
if [[ "$uname" == 'Linux' ]]; then
        platform='linux'
elif [[ "$uname" == 'Darwin' ]]; then
        platform='macos'
elif [[ "$uname" == 'SunOS' ]]; then
        platform='solaris'
fi

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
echo $PWD
cp bin/basicosstable.bin ./isodir/boot/basicosstable.bin
cp bin/basicosdev.bin ./isodir/boot/basicosdev.bin
cp scripts/menu.lst ./isodir/boot/grub/menu.lst
cp scripts/stage2_eltorito ./isodir/boot/grub/stage2_eltorito
if [[ $platform == 'solaris' ]]; then
        mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o bin/basicos.iso isodir
else
        genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o bin/basicos.iso isodir
fi
rm -r isodir
