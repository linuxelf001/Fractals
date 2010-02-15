/* Author's: Joe McKenzie, Rakesh Ginjupalli
to compile:  gcc -o mandsdl mandsdl.c -lSDL
*/

#include <stdio.h>
#include <SDL/SDL.h>

#define WIDTH 1024	//N800 screen is 800x480
#define HEIGHT 768
#define DEPTH 8	//8-bit/256 color : using default palette
#define FILENAME "mand.bmp"	//WTF, SDL only saves Windows BMPs!?

int main(int argc, char **argv) {
	SDL_Surface *screen;
	Uint8 *p;
	int x,y,i,t;
	double ozr, zr, zi, cr, ci;
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	screen=SDL_SetVideoMode(WIDTH,HEIGHT,DEPTH,SDL_SWSURFACE);
//	screen=SDL_CreateRGBSurface(SDL_SWSURFACE,WIDTH,HEIGHT,DEPTH,0,0,0,0);
	if(screen==NULL) {
		printf("Failed to create SDL surface!\n");
		exit(1);
	}
	p=(Uint8*)screen->pixels;
	//surface creation failing on N800 if we start in fullscreen...
//	SDL_WM_ToggleFullScreen(screen);
	for(y=0; y<HEIGHT; y++) {
		for(x=0; x<WIDTH; x++) {
			zr=zi=0;
			if(WIDTH>HEIGHT) t=WIDTH/4; else t=HEIGHT/4;
			cr=(x-(WIDTH/2))*(1.0/t);
			ci=(y-(HEIGHT/2))*(1.0/t);
			for(i=0; i<100000 && (zr*zr+zi*zi)<4; i++) {
				ozr=zr;
				zr=zr*zr-zi*zi+cr;
				zi=2*ozr*zi+ci;
			}
			p[x+WIDTH*y]=i;	//WARNING: only works for 8-bit; should use SDL's format stuff
		}
		//update after each line so you can watch it render
		SDL_UpdateRect(screen,0,0,0,0);
	}
	SDL_SaveBMP(screen,FILENAME);
	printf("Done, " FILENAME " saved\n");
	return 0;
}
