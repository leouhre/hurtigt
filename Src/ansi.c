#define ESC 0x1B

#include "ansi.h"

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
// move cursor to beginning and clear
    printf("%c[0;0H", ESC);
    printf("%c[2J",ESC);
}

void clreol() {
// clear rest of current line
    printf("%c[K", ESC);
}

void gotoxy(uint8_t x, uint8_t y) {
// move cursor to x,y
    printf("%c[%d;%dH", ESC,y,x);
}

void underline(uint8_t on) {
// underline on/off
    uint8_t n = 24;
    if (on == 1) {
        n = 4;
    }
    printf("%c[%dm", ESC,n);
}

void blink(uint8_t on) {
// blinking text on/off
    uint8_t n = 25;
    if (on == 1) {
        n = 5;
    }
    printf("%c[%dm", ESC,n);
}

void inverse(uint8_t on) {
// inverse colors on/off
    uint8_t n = 27;
    if (on == 1) {
        n = 7;
    }
    printf("%c[%dm", ESC,n);
}

void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* s, uint8_t style) {
    uint8_t length = strlen(s), sizex = x2 - x1, sizey = y2 - y1, i;
    gotoxy(x1,y1);
    if (style == 0) {
        printf("%c", 218);
        printf("%c", 180);
        inverse(1);
        printf("  ");
        printf("%s", s);
        for (i = 0; i < sizex - length - 5; i++) {
        printf(" ");
        }
        inverse(0);
        printf("%c", 195);
        printf("%c", 191);
        for (i = 0; i < sizey - 1; i++) {
            printf("%c[1B", ESC);
            printf("%c[%dD", ESC,sizex + 1);
            printf("%c", 179);
            printf("%c[%dC", ESC,sizex - 1);
            printf("%c", 179);
        }
        printf("%c[1B", ESC);
        printf("%c[%dD", ESC,sizex + 1);
        printf("%c", 192);
        for (i = 0; i < sizex - 1; i++) {
        printf("%c", 196);
        }
        printf("%c", 217);
    } else if(style == 1) {
        printf("%c", 201);
        printf("%c", 185);
        inverse(1);
        printf("  ");
        printf("%s", s);
        printf("  ");
        inverse(0);
        printf("%c", 204);
        for (i = 0; i < sizex - length - 7; i++) {
        printf("%c", 205);
        }
        printf("%c", 187);
        for (i = 0; i < sizey - 1; i++) {
            printf("%c[1B", ESC);
            printf("%c[%dD", ESC,sizex + 1);
            printf("%c", 186);
            printf("%c[%dC", ESC,sizex - 1);
            printf("%c", 186);
        }
        printf("%c[1B", ESC);
        printf("%c[%dD", ESC,sizex + 1);
        printf("%c", 200);
        for (i = 0; i < sizex - 1; i++) {
        printf("%c", 205);
        }
        printf("%c", 188);
        }
}
