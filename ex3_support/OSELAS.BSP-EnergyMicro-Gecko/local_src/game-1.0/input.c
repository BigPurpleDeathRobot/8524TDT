#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// why?
#define HAVE_ARCH_STRUCT_FLOCK
#include <asm-generic/fcntl.h>

#include "input.h"

static volatile int input_fd;
//uint8_t buf;

int initGamepad(void){
	if((input_fd = open("/dev/gamepad", O_RDONLY)) < 0){
		printf("error on open()\n");
		return -1;
	}	
	if(signal(SIGIO, &getInput) == SIG_ERR){
		printf("opening singal handler failed\n");
		return -1;
	}
	if(fcntl(input_fd, F_SETOWN, getpid()) < 0){
		printf("setting process as owner failed\n");
		return -1;
	}
	long oflags = fcntl(input_fd, F_GETFL);
	if(fcntl(input_fd, F_SETFL, oflags | FASYNC) > 0){
		printf("setiing FASYNC flag failed\n");
		return -1;
	}
	
	return 0;
}

// interrupt handler
void getInput(void){;       
	if(read(input_fd, &buf, 1) < 0){
		printf("error on read()\n");
	}
}
