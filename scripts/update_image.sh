#!/bin/sh

###############################################################################
#	BasicOS Kernel ISO Image Creation/Update Script			      #
#									      #
# 	License:							      #
#	BasicOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015 Aun-Ali Zaidi and its contributors.		      #
#									      #
#	This program is free software: you can redistribute it and/or modify  #
#	it under the terms of the GNU General Public License as published by  #
#	the Free Software Foundation, either version 3 of the License, or     #
#	(at your option) any later version.				      #
#									      #
#	This program is distributed in the hope that it will be useful,	      #
#	but WITHOUT ANY WARRANTY; without even the implied warranty of	      #
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the	      #
#	GNU General Public License for more details.			      #
#									      #
#	You should have received a copy of the GNU General Public License     #
#	along with this program. If not, see <http://www.gnu.org/licenses/>.  #
###############################################################################

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
cp bin/basicos_stable.bin ./isodir/boot/basicos_stable.bin
cp bin/basicos_dbg.bin ./isodir/boot/basicos_dbg.bin
cp scripts/grub.cfg ./isodir/boot/grub/grub.cfg
cp scripts/stage2_eltorito ./isodir/boot/grub/stage2_eltorito
if [[ $platform == 'solaris' ]]; then
        mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o bin/basicos.iso isodir
else
	grub-mkrescue -o bin/basicos.iso isodir
fi
rm -r isodir
