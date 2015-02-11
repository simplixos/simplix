#!/bin/sh

pwd=$(pwd)
export PREFIX="$pwd/cross64/os-toolchain"
echo $PREFIX
export TARGET=x86_64-elf
echo $TARGET
export PATH="$PREFIX/bin:$PATH"

platform='unknown'
uname=$(uname)
if [[ "$uname" == 'Linux' ]]; then
	platform='linux'
elif [[ "$uname" == 'Darwin' ]]; then
	platform='macos'
elif [[ "$uname" == 'SunOS' ]]; then
	platform='solaris'
fi

mkdir cross64
cd cross64
pwd

mkdir src
cd src
pwd

wget http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz
wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.3/gcc-4.8.3.tar.bz2
wget http://www.nasm.us/pub/nasm/releasebuilds/2.11.06/nasm-2.11.06.tar.gz

tar -xzf binutils-2.24.tar.gz
tar -xf gcc-4.8.3.tar.bz2
tar -xzf nasm-2.11.06.tar.gz

rm -f *tar.gz
rm -f *tar.bz2

mkdir build-binutils
cd build-binutils
pwd
../binutils-2.24/configure --target=x86_64-elf --prefix="$pwd/cross64/os-toolchain" --with-sysroot --disable-nls --disable-werror
if [[ $platform == 'solaris' ]]; then
	gmake
	gmake install
else
	make
	make install
fi
cd ..
pwd

mkdir build-gcc
cd build-gcc
pwd
../gcc-4.8.3/configure --target=x86_64-elf --prefix="$pwd/cross64/os-toolchain" --disable-nls --enable-languages=c,c++ --without-headers
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

cd nasm-2.11.06/
./configure --prefix="$pwd/cross64/os-toolchain"
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

os-toolchain/bin/i686-elf-gcc --version

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
