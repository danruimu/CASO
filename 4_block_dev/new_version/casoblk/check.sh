#!/bin/bash

if [ `whoami` != "root" ]
then
	echo "This script must be executed as root!"
	exit 1
fi

FS="vfat ext2 reiserfs reiser4 ext3 ext4"

for i in $FS
do
	echo "----- Checking $i -----"
	if ./check-disk.sh $i
	then
		echo "OK" > /tmp/$i
	else
		echo "FAIL" > /tmp/$i
	fi
done

echo "---------------------------------------------"
echo "---------------------------------------------"

for i in $FS
do
	echo "* $i -> `cat /tmp/$i`"
done
