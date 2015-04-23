#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#include "display.h"
#include "input.h"

#define MAP_WIDTH 32
#define MAP_HEIGHT 23
#define MAP_SIZE (MAP_WIDTH*MAP_HEIGHT)

#define LEFT 1
#define UP 2
#define RIGHT 4
#define DOWN 8

int main(int argc, char *argv[])
{
	printf("Hello Overlord, input and display test\n");

	uint8_t map[MAP_WIDTH][MAP_HEIGHT];
	memset(map, 0, sizeof map);
	
	uint16_t snakePos[MAP_SIZE] = {261, 260, 259, 258};
	uint16_t snakeLen = 4;
	uint8_t snakeDir = RIGHT;
	uint16_t prevtailPos;

	uint8_t foodx = 9;
	uint8_t foody = 8;  
	uint8_t foodEaten = 0;

	srand(time(NULL));	
	
	// function for placing snake on map
	void placeSnake(void){			 
		uint16_t x;
		uint16_t y;
		for(int i = 0; i < snakeLen; i++){
			x = snakePos[i]%32;
			y = snakePos[i]/32;
			map[x][y] = 1;
		}
		x = prevtailPos%32;
		y = prevtailPos/32;
		map[x][y] = 0;
	}

	// function for placing food on map
	void placeFood(void){
	if(foodEaten == 1){
		foodx = rand() % (MAP_WIDTH-1);
		foody = rand() % (MAP_HEIGHT-1);
		printf("foodx: %u\n", foodx);
		printf("foody: %u\n", foody);
		foodEaten = 0;
	}	
	map[foodx][foody] = 2;
		for(int y = 0; y < MAP_HEIGHT; y++){
			for(int x = 0; x < MAP_WIDTH; x++){
				if(map[x][y] == 2){
					drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, GREEN);
				}
			}
		}	
	}	
	
	// init snake
	void initSnake(void){
	placeSnake();
	drawBackground(BLACK);
	drawText("Snake###############", 0, 0);
	drawText("##########Score: 000", 160, 0);	
	// draw the initial snake
		for(int y = 0; y < MAP_HEIGHT; y++){
			for(int x = 0; x < MAP_WIDTH; x++){
				if(map[x][y] == 1){
					drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, WHITE);
				}
				if(map[x][y] == 0){
					drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, BLACK);
				}
			}
		}	
	}
	
	// draw new head and delete old tail
	void drawSnake(void){
		uint16_t x = snakePos[0]%32;
		uint16_t y = snakePos[0]/32;
		drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, WHITE);
		x = prevtailPos%32;
		y = prevtailPos/32;
		drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, BLACK);	
	}	

	// function for moving snake	
	void moveSnake(uint8_t direction){
		
		prevtailPos = snakePos[snakeLen-1];

		for(int i = MAP_SIZE; i > 0; i--){
			if(i < snakeLen){
				snakePos[i] = snakePos[i-1]; 	
			}
			else{
				snakePos[i] = 0;
			}
		}
//		for(int i=0;i<snakeLen;i++){
//			printf("snakePos[%u]: %u\n",i, snakePos[i]);
//		}	
		if(direction == LEFT){
			snakePos[0] -= 1;
		}
		if(direction == RIGHT){
			snakePos[0] += 1;
		}
		if(direction == UP){
			snakePos[0] -= 32;
		}
		if(direction == DOWN){
			snakePos[0] += 32;
		}
	}

	// collision detection and handling
	void collisionDetect(void){
		uint8_t x = snakePos[0]%32;
		uint8_t y = snakePos[0]/32;
		if((foodx == x) && (foody == y)){
			printf("Food eaten bitch!\n");
			map[foodx][foody] = 0;
			foodEaten = 1;
			snakeLen++;
		}
	}
	
	displayInit();
	initSnake();
	displayUpdate();
	sleep(1);

	while(1){
		printf("foodx: %u\n", foodx);
		printf("foody: %u\n", foody);	
		snakeDir = getInput();
		moveSnake(snakeDir);
		collisionDetect();
		printf("foodEaten: %u\n", foodEaten);	
		placeFood();
		placeSnake();
		drawSnake();
		displayUpdate();
		sleep(1);
	}

	exit(EXIT_SUCCESS);
}
