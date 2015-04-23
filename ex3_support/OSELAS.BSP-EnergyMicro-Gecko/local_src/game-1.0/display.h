#ifndef DISPLAY_H
#define DISPLAY_H

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
void displayUpdate(void);



#endif
