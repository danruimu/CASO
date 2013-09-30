PROG=proc procadv mps mtask thread thread-print msg vm vm-read mpsadv
CFLAGS=-D_GNU_SOURCE -O
CC=gcc

all: $(PROG)

proc: proc.c 
	$(CC) $(CFLAGS) $< -o $@

procadv: procadv.c 
	$(CC) $(CFLAGS) $< -o $@

mps: mps.c print-task-info.c
	$(CC) $(CFLAGS) -o $@ $^

mtask: mtask.c print-task-info.c
	$(CC) $(CFLAGS) -o $@ $^

thread: thread.c
	$(CC) $(CFLAGS) $< -o $@

thread-print: thread.c
	$(CC) $(CFLAGS) $< -o $@ -DPRINT

msg: msg.c
	$(CC) $(CFLAGS) $< -o $@

vm: vm.c
	$(CC) $(CFLAGS) $< -o $@

vm-read: vm-read.c
	$(CC) $(CFLAGS) $< -o $@

mpsadv: mpsadv.c print-task-info.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROG)
