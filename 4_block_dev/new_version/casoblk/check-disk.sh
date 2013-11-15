#!/bin/bash

if [ `whoami` != "root" ]
then
	echo "This script must be executed as root!"
	exit -1
fi

if [ ! -e myblkdrv.ko ]
then
	echo "** module is not compiled, trying to compile it **"
	if make
	then
		echo "** Success! **"
	else
		echo "** Failure... Exiting :-( **"
		exit -1
	fi
fi

dir_owner=`ls -ld . | awk '{ print $3 }'`
dir_group=`ls -ld . | awk '{ print $4 }'`

if [ $dir_owner != "root" -o $dir_group != "root" ]
then
	echo "** Folder must pertain to root to execute this script! **"
	echo "** Modifying owner and group **"
	chown root.root `ls -d .`
fi

if [ ! -d /mnt/point ]
	echo "** /mnt/point doesn't exist! **"
	echo "** Creating the folder **"
	mkdir /mnt/point
fi

aux=`mount | grep /mnt/point`
if [ -n "$aux" ]
then
	echo "** /mnt/point is currently mounted... unmounting **"
	umount /mnt/point
fi

if [ x$1 == xvfat ]; then
   fs=vfat

elif [ x$1 == xext2 ]; then
   fs=ext2

elif [ x$1 == xreiserfs ]; then
   fs=reiserfs
   journal_size=2048

elif [ x$1 == xreiser4 ]; then
   fs=reiser4
   journal_size=2048

elif [ x$1 == xext3 ]; then
   fs=ext3
elif [ x$1 == xext4 ]; then
   fs=ext4
else
   echo "Us: check-disk.sh <filesystem-type>"
   exit 1
fi
echo "** using $fs filesystem *******"

#if [[ `lsmod | grep myblkdrv` ]]; then
#   echo "** Module myblkdrv is correctly loaded *******"
#else
#   echo "** Loading module myblkdrv *******"
#   insmod myblkdrv.ko
#fi

if ./reload_module.pl 1
then
	echo "** Module myblkdrv is correctly loaded *******"
else
    echo "** Failed loading myblkdrv module *******"
    exit -1
fi

if [ -d /mnt/point ]; then

   success=0;

   echo "** creating $fs filesystem *******" && sleep 1 &&
   if [ x$fs == xreiser4 ]; then
       mkfs -t $fs -f -s $journal_size /dev/xrd1
   elif [ x$fs == xreiserfs ]; then
       mkfs -t $fs -s $journal_size /dev/xrd1
   else 
       mkfs -t $fs /dev/xrd1 
   fi &&
   sleep 1 && echo "** checking $fs filesystem *******" && sleep 1 &&
   fsck -t $fs /dev/xrd1 &&
   sleep 1 && echo "** mounting device *******" && sleep 1 &&
   mount /dev/xrd1 /mnt/point &&
   sleep 1 && echo "** copying files *******" && sleep 1 &&
   tar cf - . | (cd /mnt/point; tar  xf -; exit 0) &&
   sleep 1 && echo "** verifying files *******" && sleep 1 &&
   for i in `ls`; do echo "  ** comparing $i *******"; cmp $i /mnt/point/$i; done &&
   sleep 1 && echo "** unmounting device *******" && sleep 1 &&
   umount /mnt/point && success=1
else
   echo "Please create an empty directory /mnt/point"
fi

echo "** Removing module myblkdrv *******"
sync
sleep 1
aux=`mount | grep /mnt/point`
if [ -n "$aux" ]
then
	umount /mnt/point
fi
rmmod myblkdrv

if [ x$success == x1 ]; then
	echo "Test   SUCCESSFUL!!"
else
	echo "Test UNSUCCESSFUL!!!!"
	exit 1
fi
