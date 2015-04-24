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

#define SPEED 100000

//// DIRTY DIRTY GLOBALS ////
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
					displayUpdate(x*10, (y*10)+10, 10, 10);	
				}
			}
		}	
	}	
		
}

// function for reading gamepad and setting direction according to snake rules
uint8_t getDir(void){
	uint8_t prevDir = snakeDir;
	uint8_t dir = getInput();
	if((dir == LEFT) || (dir == RIGHT) || (dir == UP) || (dir == DOWN)){
		if((dir == LEFT) && (prevDir != RIGHT)){
			return dir;
		}
		else if((dir == RIGHT) && (prevDir != LEFT)){
			return dir;
		}
		else if((dir == UP) && (prevDir != DOWN)){
			return dir;
		}
		else if((dir == DOWN) && (prevDir != UP)){
			return dir;
		}
		else{
			return prevDir;
		}			
	}
	else{
		return prevDir;
	}
}

// function for moving snake, allows snake to exit one side and enter the opposite	
void moveSnake(uint8_t direction){
		
	prevtailPos = snakePos[snakeLen-1];

	for(int i = MAP_SIZE-1; i > 0; i--){
		if(i < snakeLen){
			snakePos[i] = snakePos[i-1];
			//printf("snakePos[%u]: %u\n",i,snakePos[i]); 	
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
	//printf("snakePos[0]: %u\n",snakePos[0]);	
}

// delete old tail and draw new head
void drawSnake(void){
	uint16_t x = prevtailPos%32;
	uint16_t y = prevtailPos/32;
	drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, BLACK);
	displayUpdate(x*10, (y*10)+10, 10, 10);
	x = snakePos[0]%32;
	y = snakePos[0]/32;
	drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, WHITE);
	displayUpdate(x*10, (y*10)+10, 10, 10);		
}

// collision detection and handling
uint8_t collisionDetect(void){
	uint8_t x = snakePos[0]%32;
	uint8_t y = snakePos[0]/32;
	// collision with food
	if((foodx == x) && (foody == y)){
		map[foodx][foody] = 0;
		foodEaten = 1;
		snakeLen++;
		score++;
	}
	// collision with self
	for(int i = 1; i < snakeLen; i++){
		if(snakePos[0] == snakePos[i]){
			drawRectangle(0, 10, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
			drawText("You Have Died!", 104, 110);
			displayUpdate(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
			return -1;
		}
	}
	return 0;	
}

void updateScore(void){
	sprintf(scoreChar, "%03u", score);
	drawRectangle(296, 0, DISPLAY_WIDTH, 8, BLACK);
	drawText(scoreChar, 296, 0);
	displayUpdate(296, 0, 3*FONT_WIDTH, FONT_HEIGHT);
}

// init snake
void initSnake(void){
	
	memset(&map, 0, sizeof map); // fill map with zeros	
	placeSnake();
	drawBackground(BLACK);
	drawText("Score: ", 240, 0);
	sprintf(scoreChar, "%03u", score);
	drawText(scoreChar, 296, 0);
	displayUpdate(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);	
	// draw the initial snake
	for(int y = 0; y < MAP_HEIGHT; y++){
		for(int x = 0; x < MAP_WIDTH; x++){
			if(map[x][y] == 1){
				drawRectangle(x*10, (y*10)+10, (x*10)+9, (y*10)+19, WHITE);
				displayUpdate(x*10, (y*10)+10, 10, 10);
			}
		}
	}	
}

int main(int argc, char *argv[])
{
	printf("Hello Overlord, input and display test in the form of snake\n");

	srand(time(NULL));	
	
	displayInit();
	initSnake();
	usleep(SPEED);

	while(1){	
		snakeDir = getDir();
		moveSnake(snakeDir);
		if(collisionDetect()) exit(EXIT_SUCCESS);	
		placeFood();
		placeSnake();
		drawSnake();
		updateScore();
		usleep(SPEED);
	}

	exit(EXIT_SUCCESS);
}
