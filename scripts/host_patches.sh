#!/bin/sh

platform='unknown'
uname=$(uname)
if [[ "$uname" == 'Linux' ]]; then
	platform='linux'
elif [[ "$uname" == 'Darwin' ]]; then
	platform='macos'
elif [[ "$uname" == 'SunOS' ]]; then
	platform='solaris'
fi

if [[ $platform == 'solaris' ]]; then
	patch < ./scripts/solaris.patch
fi
