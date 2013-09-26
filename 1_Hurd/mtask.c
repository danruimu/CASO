#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


int main (int argc, char *argv[])
{
   int res, i, j, Npids;
   mach_port_t host_privileged_port; 
   device_t device_privileged_port;
   mach_port_t default_set, processor_set;
   task_array_t task_list;
   mach_msg_type_number_t task_count;

   pid_t *pidsEnt;
   unsigned char res_susp;

  if (argc < 3) {
	fprintf (stderr, "USAGE: %s -r|-s {PID1 PID2...}\n", argv[0]);
	fprintf (stderr, "\t-r: Resume tasks identified by PID's\n");
	fprintf (stderr, "\t-s: Suspend tasks identified by PID's\n");
	exit(1);
  }

	if (strcmp (argv[1], "-r") == 0) res_susp = 1;
	else if (strcmp (argv[1], "-s") == 0) res_susp = 0;
	else {
		fprintf (stderr, "USAGE: %s -r|-s {PID1 PID2...}\n", argv[0]);
		fprintf (stderr, "\t-r: Resume tasks identified by PID's\n");
		fprintf (stderr, "\t-s: Suspend tasks identified by PID's\n");
		exit(1);
	}
	
	pidsEnt = (pid_t *) malloc(sizeof(pid_t) * (argc-2));

	for (i = 2; i < argc; ++i) {
		pidsEnt[i-2] = atoi(argv[i]);
	}

	Npids = argc - 2;

	for (i = 0; i<Npids; ++i) {
		task_t task = pid2task(pidsEnt[i]);

		if(task == MACH_PORT_NULL) {
			fprintf(stderr, "There is no task related to PID %d\n", pidsEnt[i]);
		} else {
			if (res_susp) {
				res = task_resume(task);
				if (res != KERN_SUCCESS) {
					fprintf(stderr, "Error resuming task with PID %d, 0x%x, %s\n", pidsEnt[i], res, mach_error_string(res));
				}
			} else {
				res = task_suspend(task);
				if (res != KERN_SUCCESS) {
					fprintf(stderr, "Error suspending task with PID %d, 0x%x, %s\n", pidsEnt[i], res, mach_error_string(res));
				}
			}
		}
	}

}

