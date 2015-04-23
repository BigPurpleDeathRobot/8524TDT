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
#define MAP_SIZE MAP_WIDTH*MAP_HEIGHT

#define LEFT 1
#define UP 2
#define RIGHT 4
#define DOWN 8


// DIRTY DIRTY GLOBALS //
uint8_t map[MAP_WIDTH][MAP_HEIGHT];

uint16_t snakePos[MAP_SIZE] = {261, 260, 259, 258};
uint16_t snakeLen = 4;
uint8_t snakeDir = RIGHT;
uint16_t prevtailPos;

uint8_t foodx;
uint8_t foody;  
uint8_t foodEaten = 1;

uint16_t score = 0;
char scoreChar[3];

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
		map[foodx][foody] = 2;
		for(int y = 0; y < MAP_HEIGHT; y++){
			for(int x = 0; x < MAP_WIDTH; x++){
				if(map[x][y] == 2){
					drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, GREEN);
				}
			}
		}	
	}	
		
}

// function for moving snake, allows snake to exit one side and enter the opposite	
void moveSnake(uint8_t direction){
		
	prevtailPos = snakePos[snakeLen-1];

	for(int i = MAP_SIZE-1; i > 0; i--){
		if(i < snakeLen){
			snakePos[i] = snakePos[i-1];
			printf("snakePos[%u]: %u\n",i,snakePos[i]); 	
		}
		else{
			snakePos[i] = 13; // does not matter
		}
	}	
	if(direction == LEFT){
		if(snakePos[0]%MAP_WIDTH == 0){
			snakePos[0] += MAP_WIDTH-1;	
		} 
		else{
			snakePos[0] -= 1;
		}
	}
	if(direction == RIGHT){
		if(snakePos[0]%MAP_WIDTH == 31){
			snakePos[0] -= MAP_WIDTH-1;
		}
		else{
			snakePos[0] += 1;
		}
	}
	if(direction == UP){
		if(snakePos[0] < MAP_WIDTH){
			snakePos[0] += MAP_WIDTH*(MAP_HEIGHT-1);
		}
		else{
			snakePos[0] -= MAP_WIDTH;
		}
	}
	if(direction == DOWN){
		if(snakePos[0] >= MAP_WIDTH*(MAP_HEIGHT-1)){
			snakePos[0] -= MAP_WIDTH*(MAP_HEIGHT-1);
		}
		else{	
			snakePos[0] += MAP_WIDTH;
		}
	}
	printf("snakePos[0]: %u\n",snakePos[0]);	
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

// collision detection and handling
uint8_t collisionDetect(void){
	uint8_t x = snakePos[0]%32;
	uint8_t y = snakePos[0]/32;
	// collision with food
	if((foodx == x) && (foody == y)){
		printf("Food eaten!\n");
		map[foodx][foody] = 0;
		foodEaten = 1;
		snakeLen++;
		score++;
	}
	// collision with self
	for(int i = 1; i < snakeLen; i++){
		if(snakePos[0] == snakePos[i]){
			drawRectangle(0, 10, 319, 239, BLACK);
			drawText("You Have Died!", 104, 110);
			displayUpdate();
			return -1;
		}
	}
	return 0;	
}

void updateScore(void){
	sprintf(scoreChar, "%03u", score);
	drawRectangle(296, 0, 320, 8, BLACK);
	drawText(scoreChar, 296, 0);
}

// init snake
void initSnake(void){
	
	memset(&map, 0, sizeof map);	
	placeSnake();
	drawBackground(BLACK);
	drawText("Score: ", 240, 0);
	sprintf(scoreChar, "%03u", score);
	drawText(scoreChar, 296, 0);	
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

int main(int argc, char *argv[])
{
	printf("Hello Overlord, input and display test\n");

	srand(time(NULL));	
	
	displayInit();
	initSnake();
	displayUpdate();
	usleep(100000);

	while(1){	
		snakeDir = getInput();
		moveSnake(snakeDir);
		if(collisionDetect()) return 0;	
		placeFood();
		placeSnake();
		drawSnake();
		updateScore();
		displayUpdate();
		usleep(100000);
	}

	exit(EXIT_SUCCESS);
}

//char cunt[4];
//sprintf(cunt, "%i", score);
