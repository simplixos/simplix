###############################################################################
#	BasicOS Top-Level Makefile					      #
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

.PHONY: help

help:
	@echo "Makefile for BasicOS Operating System."
	@echo "Usage: make [ all | debug | stable | clean | distclean | help ] ARCH = x86 or x86_64"
	@echo ""
	@echo

all:
	@echo "Building Kernel and ISO!"
	@mkdir -p bin
	make -C ./src all
	./scripts/update_image.sh

dev:
	@echo "Building Bleeding-Edge Kernel with Debugging Symbols!"
	@mkdir -p bin
	make -C ./src debug

stable:
	@echo "Building Stable Kernel!"
	@mkdir -p bin
	make -C ./src stable

clean:
	make -C ./src clean

distclean:
	rm -rf cross/
	make -C ./src clean

toolchain-x86:
	bash ./scripts/build_toolchain.sh

toolchain-x86_64:
	bash ./scripts/build_toolchain64.sh

isoimage:
	./scripts/update_image.sh
