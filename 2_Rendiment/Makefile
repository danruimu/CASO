PROG=sleep_2 sbrk sbrk-incdec sched_yield getpid write-to-disk read-from-disk fork_waitpid
CC=gcc
CFLAGS=-O

all: $(PROG)

write-to-disk: write-to-disk.c
	$(CC) $(CFLAGS) $^ -o $@

read-from-disk: read-from-disk.c
	$(CC) $(CFLAGS) $^ -o $@

sbrk: sbrk.c
	$(CC) $(CFLAGS) $^ -o $@

sbrk-incdec: sbrk-incdec.c
	$(CC) $(CFLAGS) $^ -o $@

sched_yield: sched_yield.c
	$(CC) $(CFLAGS) $^ -o $@

getpid: getpid.c
	$(CC) $(CFLAGS) $^ -o $@

sleep_2: sleep_2.c
	$(CC) $(CFLAGS) $^ -o $@

fork_waitpid: fork_waitpid.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(PROG)
