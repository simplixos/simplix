#!/bin/sh

pwd=$(pwd)
export PREFIX="$pwd/cross/os-toolchain"
echo $PREFIX
export TARGET=i686-elf
echo $TARGET
export PATH="$PREFIX/bin:$PATH"

platform='unknown'
unamestr = $(uname)
if [[ "$unamestr" == 'Linux' ]]; then
	platform='linux'
elif [[ "$unamestr" == 'Darwin' ]]; then
	platform='macos'
elif [[ "$unamestr" == 'SunOS' ]]; then
	platform='solaris'
fi

mkdir cross
cd cross
pwd

mkdir src
cd src
pwd

wget http://ftp.gnu.org/gnu/binutils/binutils-2.25.tar.gz
wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.4/gcc-4.8.4.tar.bz2

tar -xzf binutils-2.25.tar.gz
tar -xf gcc-4.8.4.tar.bz2

rm -f *tar.gz
rm -f *tar.bz2

mkdir build-binutils
cd build-binutils
pwd
../binutils-2.25/configure --target=i686-elf --prefix="$pwd/cross/os-toolchain" --with-sysroot --disable-nls --disable-werror
if [[ $platform == 'solaris' ]]; then
	gmake
else
	make
fi
if [[ $platform == 'solaris' ]]; then
	gmake install
else
	make install
fi
cd ..
pwd

mkdir build-gcc
cd build-gcc
pwd
../gcc-4.8.4/configure --target=i686-elf --prefix="$pwd/cross/os-toolchain" --disable-nls --enable-languages=c,c++ --without-headers
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
ls -la
rm -rf build*
cd ..
rm -rf src/
pwd

os-toolchain/bin/i686-elf-gcc --version

cd ..
pwd
ls -la

echo " "
echo "Finished building OS-specific toolchain!"
