#!/usr/bin/env bash

###############################################################################
#	SimplixOS Kernel i686 Toolchain Script				      #
#									      #
# 	License:							      #
#	SimplixOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.	      #
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


pwd=$(pwd)
export PREFIX="$pwd/cross/os-toolchain"
echo $PREFIX
export TARGET=i686-simplix
echo $TARGET
export PATH="$PREFIX/bin:$PATH"

# Toolchain Versions
NASM_VERSION=2.12.02
GMP_VERSION=6.1.2
MPC_VERSION=1.0.3
MPFR_VERSION=3.1.5
ISL_VERSION=0.18

platform='unknown'
bits='unknown'
uname=$(uname)
bits=$(getconf LONG_BIT)

retrieve_toolchain() {
	curl -O http://dl.simplixos.org/pub/toolchains/build/$platform/$1/$1-$2_cross-toolchain.tar.bz2
	tar -xvf $1-$2_cross-toolchain.tar.bz2
	rm -f $1-$2_cross-toolchain.tar.bz2
	exit 0
}

case "$bits:$uname" in
	64:Linux)   platform='linux'
		    retrieve_toolchain x86_64 unknown-linux-gnu
		    ;;
	64:Darwin)  platform='darwin'
		    retrieve_toolchain x86_64 apple-darwin16.0.0
		    ;;
	32:SunOS)   platform='solaris'
		    gmake='yes'
		    retrieve_toolchain i386 pc-solaris2.11
		    ;;
	64:CYGWIN*) platform='cygwin'
		    retrieve_toolchain x86_64 pc-cygwin
		    ;;
	32:CYGWIN*) platform='cygwin'
		    retrieve_toolchain i686 pc-cygwin
		    ;;
	64:FreeBSD) platform='bsd/freebsd'
		    gmake='yes'
		    retrieve_toolchain x86_64 freebsd11.0
		    ;;
esac

mkdir cross
cd cross
pwd

mkdir src
cd src
pwd

git clone --depth 1 -b simplix-cross https://git.simplixos.org/pub/scm/toolchain/binutils.git
git clone --depth 1 -b simplix-cross https://git.simplixos.org/pub/scm/toolchain/gcc.git
wget http://www.nasm.us/pub/nasm/releasebuilds/$NASM_VERSION/nasm-$NASM_VERSION.tar.gz

wget http://ftp.gnu.org/gnu/gmp/gmp-$GMP_VERSION.tar.bz2
wget http://ftp.gnu.org/gnu/mpc/mpc-$MPC_VERSION.tar.gz
wget http://ftp.gnu.org/gnu/mpfr/mpfr-$MPFR_VERSION.tar.gz
wget http://isl.gforge.inria.fr/isl-$ISL_VERSION.tar.bz2

tar -xzvf nasm-$NASM_VERSION.tar.gz

tar -xjvf gmp-$GMP_VERSION.tar.bz2
tar -xzvf mpc-$MPC_VERSION.tar.gz
tar -xzvf mpfr-$MPFR_VERSION.tar.gz
tar -xjvf isl-$ISL_VERSION.tar.bz2

rm -f *tar.gz
rm -f *tar.bz2

mkdir build-binutils
cd build-binutils
pwd
../binutils/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror --disable-gdb \
                      --disable-libdecnumber --disable-readline --disable-sim --with-pkgversion="Simplix Cross Binutils" \
                      --disable-shared --enable-static
if [[ $gmake == 'yes' ]]; then
	gmake
	gmake install
else
	make
	make install
fi
cd ..
pwd

mv gmp-$GMP_VERSION/ gcc/gmp/
mv mpc-$MPC_VERSION/ gcc/mpc/
mv mpfr-$MPFR_VERSION/ gcc/mpfr/
mv isl-$ISL_VERSION/ gcc/isl/

mkdir build-gcc
cd build-gcc
pwd
../gcc/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers \
		 --with-pkgversion="Simplix Cross GCC" --enable-static --disable-shared
if [[ $gmake == 'yes' ]]; then
	gmake all-gcc
	gmake all-target-libgcc
	gmake install-gcc
	gmake install-target-libgcc
else
	make all-gcc
	make all-target-libgcc
	make install-gcc
	make install-target-libgcc
fi
cd ..
pwd

cd nasm-$NASM_VERSION/
./configure --prefix="$pwd/cross/os-toolchain" --enable-static --disable-shared
if [[ $gmake == 'yes' ]]; then
	gmake
	gmake install
else
	make
	make install
fi
cd ..
pwd

if [[ $platform == 'macos' ]]; then

git clone --depth 1 git://git.savannah.gnu.org/grub.git

cd grub/
./autogen.sh
cd ..

mkdir build-grub
cd build-grub
../grub/configure --disable-werror \
	TARGET_CC=$PREFIX/bin/$TARGET-gcc \
	TARGET_OBJCOPY=$PREFIX/bin/$TARGET-objcopy \
	TARGET_STRIP=$PREFIX/bin/$TARGET-strip \
	TARGET_NM=$PREFIX/bin/$TARGET-nm \
	TARGET_RANLIB=$PREFIX/bin/$TARGET-ranlib \
	--target=i686-elf --prefix=$PREFIX
make
make install
cd ..
pwd
fi

ls -lah
rm -rf build*
cd ..
rm -rf src/
pwd

os-toolchain/bin/i686-simplix-gcc --version

os-toolchain/bin/nasm -v

if [[ $platform == 'macos' ]]; then
os-toolchain/bin/grub-mkrescue --version
fi

cd ..
pwd

echo " "
echo "Finished building OS-specific toolchain!"
