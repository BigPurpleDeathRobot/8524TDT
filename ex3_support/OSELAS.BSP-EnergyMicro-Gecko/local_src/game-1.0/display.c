#include <stdio.h>
#include <stdint.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "display.h"
#include "font_8x8.h"

//// GLOBALS ////
static int framebuffer_fd; // variable to open fb0 device file
static uint16_t *fb_ptr; // holds addresses from mmap()
static struct fb_copyarea rect; 

int displayInit(void){
	// open framebuffer device file with read/write permission
	if((framebuffer_fd = open("/dev/fb0", O_RDWR)) < 0){
		printf("failed to open framebufer fb0\n");
		return -1;
	}
	// map fb0 to memory using mmap()
	fb_ptr = (uint16_t*) mmap(
		NULL, 			// kernel chooses the address ath which to create the mapping
		FRAMEBUFFER_SIZE, 
		PROT_READ | PROT_WRITE,	// read/write permission on the memory 
		MAP_SHARED,		// ...
		framebuffer_fd,		// file to be mapped
		0); 			// offset
	if(fb_ptr == MAP_FAILED){
		printf("failed to map fb0 to memory\n");
		return -1;
	}

	return 0;
}

void drawRectangle(int x1, int y1, int x2, int y2, int color){
	// draw rectangle
	for(int i = y1; i <= y2; i++){
		for(int j = x1; j <= x2; j++){
			fb_ptr[j + (i * DISPLAY_WIDTH)] = color;
		}
	}

}
	
void drawBackground(int color){
	// fill screen with some color
	for(int i = 0; i<DISPLAY_SIZE; i++){
		fb_ptr[i] = color;
	}
}

void drawText(char *msg, int x, int y){
	uint8_t shift = 0;
	uint8_t position = 0;

	while(*msg){
		for(int i = 0; i < FONT_HEIGHT; i++){ 
			for(int j = 0; j < FONT_WIDTH; j++){
				uint8_t charPiece = font[*msg - 32][j];
				if(((charPiece & (1 << shift))>>shift) == 1){
					fb_ptr[j + x + position + (i+y)*DISPLAY_WIDTH] = WHITE;
				};
			} 
			shift++;
			if(shift == 8) shift = 0;
		}
		position += 8;
		*msg++;
	}	
}

void displayUpdate(int dx, int dy, int width, int height){
	rect.dx = dx;
	rect.dy = dy;
	rect.width = width;
	rect.height = height;
	ioctl(framebuffer_fd, 0x4680, &rect);
}
