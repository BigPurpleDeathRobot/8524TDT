#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240
#define DISPLAY_SIZE 320*240
#define FRAMEBUFFER_SIZE 153600 // width*height*sizeof(uint16_t)

#define FONT_WIDTH 8
#define FONT_HEIGHT 8

// colors for drawing
#define BLACK 0x0000
#define WHITE 0xffff
#define RED   0xf800
#define GREEN 0x07e0
#define BLUE  0x001f

int displayInit(void);
void drawBackground(int color);
void drawRectangle(int x1, int y1, int x2, int y2, int color);
void drawText(char *msg, int x, int y);
void displayUpdate(int dx, int dy, int width, int height);



#endif
