PROG=proc procadv mps mtask thread vm vm-read msg
CFLAGS=-D_GNU_SOURCE -O

all: $(PROG)

proc: proc.c 
	gcc $(CFLAGS) $< -o $@

procadv: procadv.c 
	gcc $(CFLAGS) $< -o $@

mps: mps.c print-task-info.c
	gcc $(CFLAGS) -o $@ $^

mtask: mtask.c print-task-info.c
	gcc $(CFLAGS) -o $@ $^

thread: thread.c
	gcc $(CFLAGS) $< -o $@

msg: msg.c
	cc $(CFLAGS) $< -o $@

vm: vm.c
	cc $(CFLAGS) $< -o $@

vm-read: vm-read.c
	cc $(CFLAGS) $< -o $@

clean:
	rm -f $(PROG)
