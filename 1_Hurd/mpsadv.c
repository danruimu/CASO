#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


int main ()
{
   int res, i;
   mach_port_t host_privileged_port; 
   device_t device_privileged_port;
   mach_port_t default_set, processor_set;
   task_array_t task_list;
   mach_msg_type_number_t task_count;

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
	   Print_Task_info (task_list[i]);
   }
  
   exit(0);
}

 


   

