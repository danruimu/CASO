all: sleep_2 sbrk sbrk-incdec sched_yield getpid write-to-disk read-from-disk

write-to-disk: write-to-disk.c
	gcc -O -o $@ $<

read-from-disk: read-from-disk.c
	gcc -O -o $@ $<

sbrk: sbrk.c
	gcc -O -o $@ $<

sbrk-incdec: sbrk-incdec.c
	gcc -O -o $@ $<

sched_yield: sched_yield.c
	gcc -O -o $@ $<

getpid: getpid.c
	gcc -O -o $@ $<

sleep_2: sleep_2.c
	gcc -O -o $@ $<


clean:
	rm -f write-to-disk write-to-disk.o read-from-disk read-from-disk.o \
              sbrk sbrk.o sched_yield sched_yield.o getpid getpid.o \
              sleep_2 sleep_2.o
