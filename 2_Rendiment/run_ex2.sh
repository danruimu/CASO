#!/bin/bash

PROG_W=write-to-disk-plot

if [ $# -ne 2 ]
then
	echo "USAGE: `basename $0` INIT_SIZE END_SIZE"
	echo "    INIT_SIZE: size in MB of the first file writed and readed"
	echo "    END_SIZE: size in MB of the final file writed and readed"
	echo "    NOTE that increments would be of 10MB"
	exit 1
fi

INIT_SIZE=$1
END_SIZE=$2
OUT_USB=/tmp/pene
OUT_HDD=/dev/sda6
OUT_FILE_USB=usb.out
OUT_FILE_HDD=hdd.out

if [ ! -d plots ]
then
	mkdir plots
fi

echo "Starting executions!"
echo " "

for i in $OUT_USB $OUT_HDD
do
	if [ -e plots/$i.out ]
	then
		rm -f plots/$i.out
	fi

	if [ ! -e $PROG_W ]
	then
		make $PROG_W
	fi
	
	N=$INIT_SIZE
	echo -n "Executing $PROG_W"
	while [ $N -le $END_SIZE ]
	do
		sync
		if [ $i == $OUT_USB ]
		then
			./$PROG_W $i $N >> plots/$OUT_FILE_USB
		else
			./$PROG_W $i $N >> plots/$OUT_FILE_HDD
		fi
		let N=$N+10
		echo -n "."
	done
	echo " "
done

echo " "
echo "Executions finished! Let's start to generate the plots :-)"

cd plots

gnuplot -e "set xlabel 'Size in MB'; set ylabel 'Bandwidth in MB/s'; plot 'usb.out' using 1:2 with lines title 'Write to USB'; set term png; set output 'write_usb.png'; replot;"
gnuplot -e "set xlabel 'Size in MB'; set ylabel 'Bandwidth in MB/s'; plot 'hdd.out' using 1:2 with lines title 'Write to HDD'; set term png; set output 'write_hdd.png'; replot;"

cd ../

echo "Plots generated! You will find two images at plots folder :-)"
echo "Bye!"
