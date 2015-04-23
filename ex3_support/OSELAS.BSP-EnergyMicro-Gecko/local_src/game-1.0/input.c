#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "input.h"

uint8_t data = 4;
int input_fd;
char buf;

uint8_t getInput(void){
	if((input_fd = open("/dev/gamepad", O_RDONLY)) < 0){
		printf("error on open()\n");
		return -1;
	}       
	if(read(input_fd, &buf, 1) < 0){
		printf("error on read()\n");
		return -1;
	}
	close(input_fd);
	if((uint8_t)buf != 0) data = (uint8_t)buf;
	return data;
	
}
