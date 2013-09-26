#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/mach_traps.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>
#include <unistd.h>

#define	PAGESIZE	4096
#define	ANYWHERE	1

int main (int argc, char *argv[]) {
	kern_return_t res;
	mach_port_t parent_task, child_task;
	vm_address_t address;
	unsigned int i;

	vm_offset_t data __attribute__ ((aligned (PAGESIZE)));

	parent_task = mach_task_self();

	res = task_create (parent_task, 0, &child_task);
	if (res != KERN_SUCCESS) {
		fprintf(stderr, "Error creating the child task: 0x%x, %s\n", res, mach_error_string(res));
		exit(1);
	}

	res = vm_allocate(child_task, &address, PAGESIZE, ANYWHERE);
	if (res != KERN_SUCCESS) {
		fprintf(stderr, "Error allocating memory: 0x%x, %s\n", res, mach_error_string(res));
		exit(1);
	}

	data = (vm_offset_t) malloc(4096);

	res = vm_write (child_task, address, data, PAGESIZE);
	if (res != KERN_SUCCESS) {
		fprintf(stderr, "Error writing: 0x%x, %s\n", res, mach_error_string(res));
		exit(1);
	}
}
