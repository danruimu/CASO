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

   res = get_privileged_ports(&host_privileged_port, &device_privileged_port);
   if (res != KERN_SUCCESS) {
      printf ("Error getting privileged ports (0x%x), %s\n", res, 
                mach_error_string(res));
      exit(1);
   }

   printf ("privileged ports: host 0x%x  devices 0x%x\n", 
                     host_privileged_port, device_privileged_port);

   res = processor_set_default (host_privileged_port, &default_set);
   if (res != KERN_SUCCESS) {
	   fprintf(stderr, "Error getting the default processor set: (0x%x), %s\n", res, mach_error_string(res));
	   exit(1);
   }

   res = host_processor_set_priv (host_privileged_port, default_set, &processor_set);
   if (res != KERN_SUCCESS) {
	   fprintf (stderr, "Error getting the processor set control port: (0x%x), %s\n", res, mach_error_string(res));
	   exit(1);
   }

   res = processor_set_tasks (processor_set, &task_list, &task_count);
   if (res != KERN_SUCCESS) {
	   fprintf(stderr, "Error getting task array: (0x%x), %s\n", res, mach_error_string(res));
	   exit(1);
   }

   for ( i=0; i<task_count; ++i) {
	   task_basic_info_data_t task_data;
	   task_info_t ta_info = (task_info_t) &task_data;
	   mach_msg_type_number_t task_info_outCnt = TASK_BASIC_INFO_COUNT;

	   res = task_info (task_list[i], TASK_BASIC_INFO, ta_info, &task_info_outCnt);
	   if (res != KERN_SUCCESS) {
		   fprintf (stderr, "Error getting task_info (%d), %s\n", res, mach_error_string(res));
		   exit(1);
	   }

	   pid_t pid = task2pid(task_list[i]);

	   for( j = 0; j<Npids; ++j) {
		   if (pid==pidsEnt[j]) {
				if (res_susp) {
					res = task_resume (task_list[i]);
					if (res != KERN_SUCCESS) {
						fprintf (stderr, "Error resuming the task %d, (%d), %s\n", pidsEnt[j], res, mach_error_string(res));
						exit (1);
					}
					fprintf (stdout, "Task identified by PID %d resumed\n", pidsEnt[j]);
				} else {
					res = task_suspend (task_list[i]);
					if (res != KERN_SUCCESS) {
						fprintf (stderr, "Error suspending the task %d, (%d), %s\n", pidsEnt[j], res, mach_error_string(res));
						exit (1);
					}
					fprintf (stdout, "Task identified by PID %d suspended\n", pidsEnt[j]);
				}
		   }
	   }
   }
  
   exit(0);
}

