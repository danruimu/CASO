#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


        processor_array_t processor_list = NULL;
        mach_msg_type_number_t processor_listCnt = 0;

int main ()
{
   int res, i;
   mach_port_t host_privileged_port; 
   device_t device_privileged_port;
   mach_port_t* host;
   mach_msg_type_number_t procInfoCnt;
   processor_info_t procInfo;

   res = get_privileged_ports(&host_privileged_port, &device_privileged_port);
   if (res != KERN_SUCCESS) {
      printf ("Error getting privileged ports (0x%x), %s\n", res, 
                mach_error_string(res));
      exit(1);
   }

   printf ("privileged ports: host 0x%x  devices 0x%x\n", 
                     host_privileged_port, device_privileged_port);

   printf ("Getting processors at array 0x%x\n", processor_list);

   res = host_processors(host_privileged_port, 
                         &processor_list, &processor_listCnt);
   if (res != KERN_SUCCESS) {
      printf ("Error getting host_processors (0x%x), %s\n", res,
                mach_error_string(res));
      exit(1);
   }

   printf ("        processors at array 0x%x\n", processor_list);
   printf ("processor_listCnt %d\n", processor_listCnt);

	procInfo = (processor_info_t) malloc(512*sizeof(int));
	host = (mach_port_t *) malloc(10*sizeof(mach_port_t));

   for (i=0; i < processor_listCnt; i++) {
	   printf ("processor_list[%d] 0x%x\n", i, processor_list[i]);

	   procInfoCnt = processor_listCnt;
	   res = processor_info (processor_list[i], PROCESSOR_BASIC_INFO, host, procInfo, &procInfoCnt);
	   if (res != KERN_SUCCESS) {
		   fprintf (stderr, "Error getting the processor %d information (0x%x), %s\n", i, res, mach_error_string(res));
		   exit(-1);
	   }
   }
}

