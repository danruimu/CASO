#!/bin/bash

if [ `whoami` != "root" ]
then
	echo "This script must be executed as root!"
	exit 1
fi

PROG=./check-disk.sh

for i in ext2 vfat reiserfs
do
	if $PROG $i
	then
		echo "OK!"
	else
		echo "FAIL"
	fi
done
