BasicOS
=======

[![Build Status](https://travis-ci.org/aunali1/BasicOS.svg?branch=master)](https://travis-ci.org/aunali1/BasicOS)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/4010/badge.svg)](https://scan.coverity.com/projects/4010)

![Demo1](https://aunali1.com/demo1.png)

This repository contains the sample code for my personal
operating system.

All code in this repository is subject to the terms in the
LICENSE document.

## Compiling:

To compile this operating system your build system must have the following prerequisites:

    * POSIX Compliant Operating System (Linux, BSD, etc.)
    * GCC-4.8.x C Compiler Toolchain
    * G++-4.8.x C++ Compiler Toolchain
    * Binutils 2.22.x
    * GNU Make
    * GNU Bison
    * Flex
    * GNU libiconv
    * GNU GMP
    * GNU MPFR
    * GNU MPC
    * ISL
    * CLooG

Begin by building the OS-specific toolchain:

    $ make toolchain

Once the toolchain has finished, run the following to compile the kernel:

    $ make all

Currently the kernel architecture is 32-bit, and a ix86 compiler toolchain is supported.

To create a live ISO image of the operating system, execute the following:

    $ make isoimage