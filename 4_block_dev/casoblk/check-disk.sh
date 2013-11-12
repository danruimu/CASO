#!/bin/bash

if [ `whoami` != "root" ]
then
	echo "This script must be executed as root!"
	exit -1
fi

fs=ext2

if [ x$1 == xvfat ]; then
   fs=vfat
fi
if [ x$1 == xext2 ]; then
   fs=ext2
fi
if [ x$1 == xreiserfs ]; then
   fs=reiserfs
   journal_size=2048
fi
echo "** using $fs filesystem *******"

if [[ `lsmod | grep myblkdrv` ]]; then
   echo "** Module myblkdrv is correctly loaded *******"
else
   echo "** loading module myblkdrv *******"
   insmod myblkdrv.ko
fi



if [ -d /mnt/point ]; then

   success=0;

   echo "** creating $fs filesystem *******" && sleep 1 &&
   if [ x$journal_size == x ]; then
       mkfs -t $fs /dev/xrd1 
   else 
       mkfs -t $fs -s $journal_size /dev/xrd1
   fi &&
   sleep 1 && echo "** checking $fs filesystem *******" && sleep 1 &&
   fsck /dev/xrd1 &&
   sleep 1 && echo "** mounting device *******" && sleep 1 &&
   mount /dev/xrd1 /mnt/point &&
   sleep 1 && echo "** copying files *******" && sleep 1 &&
   tar cf - . | tar xf - -C /mnt/point &&
   sleep 1 && echo "** verifying files *******" && sleep 1 &&
   for i in `ls`; do echo "  ** comparing $i *******"; cmp $i /mnt/point/$i; done &&
   sleep 1 && echo "** unmounting device *******" && sleep 1 &&
   umount /mnt/point && success=1
   if [ x$success == x1 ]; then
      echo "Test   SUCCESSFUL!!"
   else
      echo "Test UNSUCCESSFUL!!!!"!
   fi
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
rmmod myblkdrv.ko
