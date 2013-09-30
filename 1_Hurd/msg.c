#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <hurd.h>
#include <mach/message.h>

int main () {

	kern_return_t res;
	mach_msg_return_t msg_res;
	pid_t pid;
	mach_port_t host_privileged_port;
	device_t device_privileged_port;

	res = get_privileged_ports(&host_privileged_port, &device_privileged_port);
	if (res != KERN_SUCCESS) {
		fprintf(stderr, "Error getting privileged ports: 0x%x, %s\n", res, mach_error_string(res));
		exit (1);
	}

	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "Error creating the child with fork\n");
		exit(1);
	}

	if (pid == 0) {	//CHILD - SENDER
		//TODO: Prepare the message header to be send
		mach_msg_header_t sHeader;
		sHeader.msgh_bits = MACH_MSGH_BITS_REMOTE_MASK; //mach_msg_type_t
		sHeader.msgh_size  = sizeof(mach_msg_header_t); //mach_msg_size_t
		sHeader.msgh_remote_port  = host_privileged_port; //mach_port_t
		sHeader.msgh_local_port  = MACH_PORT_NULL; //mach_port_t
		//sHeader->msgh_seqno  = ; //mach_port_seqno_t IGNORED ON SENT MESSAGES
		//sHeader->msgh_id  = ; //mach_msg_id_t NOT SET OR NULL BY mach_msg

		//Sending the message
		msg_res = mach_msg_send(&sHeader);
		if (msg_res != MACH_MSG_SUCCESS) {
			fprintf(stderr, "Error on sending message: 0x%x, %s\n", msg_res, mach_error_string(msg_res));
			exit(1);
		}
		exit(0);

	} else {		//PARENT - RECEIVER
		//TODO: Prepare the message header to be receive
		mach_msg_header_t rHeader;
		rHeader.msgh_bits = MACH_MSGH_BITS_LOCAL_MASK; //mach_msg_type_t
		//rHeader->msgh_size  = ; //mach_msg_size_t - TO BE READ
		rHeader.msgh_remote_port  = MACH_PORT_NULL; //mach_port_t
		rHeader.msgh_local_port  = host_privileged_port; //mach_port_t
		//rHeader->msgh_seqno  = ; //mach_port_seqno_t - TO BE READ
		//rHeader->msgh_id  = ; //mach_msg_id_t - NOT SET OR NULL by mach_msg

		// Receiving the message
		msg_res = mach_msg_receive(&rHeader);
		if (msg_res != MACH_MSG_SUCCESS) {
			fprintf(stderr, "Error on receiving message: 0x%x, %s\n", msg_res, mach_error_string(msg_res));
			exit(1);
		}
		//TODO: check if the message is the one the child sent
		exit(0);

	}
}
