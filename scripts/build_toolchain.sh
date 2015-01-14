#!/bin/sh

pwd=$(pwd)
export PREFIX="$pwd/cross/os-toolchain"
echo $PREFIX
export TARGET=i686-elf
echo $TARGET
export PATH="$PREFIX/bin:$PATH"

mkdir cross
cd cross
pwd

mkdir src
cd src
pwd

wget http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz
wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.3/gcc-4.8.3.tar.bz2

tar -xzf binutils-2.24.tar.gz
tar -xf gcc-4.8.3.tar.bz2

rm -f *tar.gz
rm -f *tar.bz2

mkdir build-binutils
cd build-binutils
pwd
../binutils-2.24/configure --target=i686-elf --prefix="$pwd/cross/os-toolchain" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..
pwd

mkdir build-gcc
cd build-gcc
pwd
../gcc-4.8.3/configure --target=i686-elf --prefix="$pwd/cross/os-toolchain" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..
ls -la
rm -rf build*
cd ..
pwd

os-toolchain/bin/i686-elf-gcc --version

cd ..
pwd
ls -la

echo " "
echo "Finished building OS-specific toolchain!"
