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
   int res, i, j;
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

	procInfo = (processor_info_t) malloc(PROCESSOR_INFO_MAX*sizeof(int));
	host = (mach_port_t *) malloc(10*sizeof(mach_port_t));

   for (i=0; i < processor_listCnt; i++) {
	   printf ("processor_list[%d] 0x%x\n", i, processor_list[i]);

	   procInfoCnt = sizeof(int)*PROCESSOR_INFO_MAX;
	   res = processor_info (processor_list[i], PROCESSOR_BASIC_INFO, host, procInfo, &procInfoCnt);
	   if( res != KERN_SUCCESS) {
		   fprintf(stderr, "Error getting the processor %d information (0x%x), %s\n", i, res, mach_error_string(res));
		   exit(1);
	   }

	   for (j=0; j< procInfoCnt; ++j) {
		   processor_basic_info_t procBasicInfo = (processor_basic_info_t) &procInfo[j];
		   fprintf(stdout, "------------CPU %d------------\n", j);
		   fprintf(stdout, "CPU Type:\t\t%d\n", procBasicInfo->cpu_type);
		   fprintf(stdout, "CPU Subtype:\t\t%d\n", procBasicInfo->cpu_subtype);
		   if(procBasicInfo->running) fprintf(stdout, "Running?:\t\tYES\n");
		   else fprintf(stdout, "Running?:\t\tNO\n");
		   fprintf(stdout, "Slot number:\t\t%d\n", procBasicInfo->slot_num);
		   if(procBasicInfo->is_master) fprintf(stdout, "Master?:\t\tYES\n");
		   else fprintf(stdout, "Master?:\t\tNO\n");
		   fprintf(stdout, "-----------------------------\n");
	   }

   }
}

