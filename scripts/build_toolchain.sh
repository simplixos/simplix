#!/usr/bin/env bash

###############################################################################
#	SimplixOS Kernel i686 Toolchain Script				      #
#									      #
# 	License:							      #
#	SimplixOS Operating System - An experimental operating system	      #
#	Copyright (C) 2016 Aun-Ali Zaidi and its contributors.		      #
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

platform='unknown'
uname=$(uname)
if [ "$uname" == 'Linux' ]; then
	platform='linux'
	if [ `getconf LONG_BIT` = "64" ]; then
		wget http://dl.simplixos.org/pub/toolchains/build/linux/x86_64/x86_64-unknown-linux-gnu_build-toolchain.tar.bz2
		tar -xvf x86_64-unknown-linux-gnu_build-toolchain.tar.bz2
		rm -f x86_64-unknown-linux-gnu_build-toolchain.tar.bz2
		exit 0
	fi
elif [ "$uname" == 'Darwin' ]; then
	platform='macos'
	if [ `getconf LONG_BIT` = "64" ]; then
		wget http://dl.simplixos.org/pub/toolchains/build/darwin/x86_64/x86_64-apple-darwin15.0.0_build-toolchain.tar.bz2
		tar -xvf x86_64-apple-darwin15.0.0_build-toolchain.tar.bz2
		rm -f x86_64-apple-darwin15.0.0_build-toolchain.tar.bz2
		exit 0
	fi
elif [ "$uname" == 'SunOS' ]; then
	platform='solaris'
	if [ `getconf LONG_BIT` = "64" ]; then
		wget http://dl.simplixos.org/pub/toolchains/build/solaris/x86_64/x86_64-pc-solaris2.11_build-toolchain.tar.bz2
		tar -xvf x86_64-pc-solaris2.11_build-toolchain.tar.bz2
		rm -f x86_64-pc-solaris2.11_build-toolchain.tar.bz2
		exit 0
	fi
elif [ "$uname" == 'Cygwin' ]; then
	platform='cygwin'
	if [ `getconf LONG_BIT` = "64" ]; then
		wget http://dl.simplixos.org/pub/toolchains/build/cygwin/x86_64/x86_64-pc-cygwin_build-toolchain.tar.bz2
		tar -xvf x86_64-pc-cygwin_build-toolchain.tar.bz2
		rm -f x86_64-pc-cygwin_build-toolchain.tar.bz2
		exit 0
	elif [ `getconf LONG_BIT` = "32" ]; then
		wget https://dl.simplixos.org/pub/toolchains/build/cygwin/i686/i686-pc-cygwin_build-toolchain.tar.bz2
		tar -xvf i686-pc-cygwin_build-toolchain.tar.bz2
		rm -f i686-pc-cygwin_build-toolchain.tar.bz2
		exit 0
	fi
elif [ "$uname" == 'FreeBSD' ]; then
	platform='freebsd'
	if [ `getconf LONG_BIT` = "64" ]; then
		wget https://dl.simplixos.org/pub/toolchains/build/bsd/freebsd/x86_64/x86_64-freebsd10.1_build-toolchain.tar.bz2
		tar -xjvf x86_64-freebsd10.1_build-toolchain.tar.bz2
		rm -f x86_64-freebsd10.1_build-toolchain.tar.bz2
	fi
fi

mkdir cross
cd cross
pwd

mkdir src
cd src
pwd

wget http://dl.simplixos.org/pub/toolchains/binutils/binutils-2.25.1.tar.bz2
wget http://dl.simplixos.org/pub/toolchains/gcc/gcc-4.9.3/gcc-4.9.3.tar.bz2
wget http://www.nasm.us/pub/nasm/releasebuilds/2.11.08/nasm-2.11.08.tar.gz

wget http://ftp.gnu.org/gnu/gmp/gmp-6.0.0a.tar.bz2
wget http://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
wget http://ftp.gnu.org/gnu/mpfr/mpfr-3.1.3.tar.gz
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/isl-0.14.tar.bz2
wget http://www.bastoul.net/cloog/pages/download/cloog-0.18.4.tar.gz

tar -xvf binutils-2.25.1.tar.bz2
tar -xvf gcc-4.9.3.tar.bz2
tar -xzvf nasm-2.11.08.tar.gz

tar -xvf gmp-6.0.0a.tar.bz2
tar -xzvf mpc-1.0.3.tar.gz
tar -xzvf mpfr-3.1.3.tar.gz
tar -xvf isl-0.14.tar.bz2
tar -xzvf cloog-0.18.4.tar.gz

rm -f *tar.gz
rm -f *tar.bz2

mkdir build-binutils
cd build-binutils
pwd
../binutils-2.25.1/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
if [[ $platform == 'solaris' ]]; then
	gmake
	gmake install
else
	make
	make install
fi
cd ..
pwd

mv gmp-6.0.0/ gcc-4.9.3/gmp/
mv mpc-1.0.3/ gcc-4.9.3/mpc/
mv mpfr-3.1.3/ gcc-4.9.3/mpfr/
mv isl-0.14/ gcc-4.9.3/isl/
mv cloog-0.18.4/ gcc-4.9.3/cloog/

mkdir build-gcc
cd build-gcc
pwd
../gcc-4.9.3/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
if [[ $platform == 'solaris' ]]; then
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

cd nasm-2.11.08/
./configure --prefix="$pwd/cross/os-toolchain"
if [[ $platform == 'solaris' ]]; then
	gmake
	gmake install
else
	make
	make install
fi
cd ..
ls -lah
rm -rf build*
cd ..
rm -rf src/
pwd

os-toolchain/bin/i686-simplix-gcc --version

os-toolchain/bin/nasm -v

cd ..
pwd
ls -la

if [[ $platform == 'solaris' ]]; then
        echo "Applying Solaris patches:"
        ./scripts/host_patches.sh
fi

echo " "
echo "Finished building OS-specific toolchain!"
