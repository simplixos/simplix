##################################
#	BasicOS Top-Level Makefile
##################################

help:
	@echo "Makefile for BasicOS Operating System."
	@echo "Usage: make [ all | clean | distclean | help ] " 
	@echo ""
	@echo

all:
	@echo "Building Kernel!"
	make -C ./src all

clean:
	make -C ./src clean

distclean:
	rm -rf cross/
	make -C ./src clean

toolchain:
	./scripts/build_toolchain.sh

isoimage:
	./scripts/update_image.sh
