#include <stdio.h>
#include <time.h> //needed for random number gen
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// IDEAS Pass a x/y corrd of an image so the window only shows it if it's own pos will let it
// ridget body physics with window movement reaction.

// messing around with structs nothing can go wrong here
struct rgb {int r; int g; int b; int t;}; // red, green, blue AND TRANCPARENCY all of the colors you know and love

//clean up prog
void exitProg(int returnCode,SDL_Window* win,SDL_Renderer* rend,SDL_Texture* text){
  if(rend != NULL){
    SDL_DestroyRenderer(rend);
  }
  if(win != NULL){
		SDL_DestroyWindow(win);
	}
  if(text != NULL){
    SDL_DestroyTexture(text);
  }
  if(returnCode != 0){
    fprintf(stderr,"SDL ERROR: %s\n",SDL_GetError());
  }
	SDL_Quit();
	exit(returnCode);	
}

// init SDL handle errors before threads have started
void initSDL(Uint32 flags){
	if( SDL_Init( flags ) < 0 ) { 
	printf("SDL_Error: %s\n", SDL_GetError());
	exit(1);	
	}
}

// makes a random rgb struct t set to 255 
struct rgb randRGB(){
  struct rgb rgbRand;
  rgbRand.r = rand()%255;
  rgbRand.b = rand()%255;
  rgbRand.g = rand()%255;
  rgbRand.t = 255;
  return rgbRand;
}

int main(int argc, char **argv){
	// int SDL for video
	initSDL(SDL_INIT_VIDEO);
  // start the random number gen
  srand(time(NULL)); // RNG IS A GOOD THING GUYS
  
  SDL_Window* win = NULL;
	SDL_Renderer* gRend = NULL;

  win = SDL_CreateWindow("Window Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, SDL_WINDOW_SHOWN );
	if (win == NULL){
		exitProg(1,win,gRend,NULL);// texture pointer refrances go here
  }
  // LET THE PLAYER RESIZE THE WINDOW
  SDL_SetWindowResizable(win,SDL_TRUE);

  // renderer
  //set the texture filtering
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
  gRend = SDL_CreateRenderer(win,-1,0);
  if ( gRend == NULL){
    exitProg(1,win,gRend,NULL);//same here
  }
  // init the color
  SDL_SetRenderDrawColor(gRend, 0xFF,0xFF,0xFF,0xFF);
    
	//window size
	int winW = 0; // winWidth
	int winH = 0; //winHight
  SDL_GetWindowSize(win,&winW,&winH);

  int randX = rand()%winW;
  int randY = rand()%winH;
  struct rgb rectRGB = randRGB();
	
	// handle input and redraw the window
	SDL_Event e; 
	bool quit = false;
	while(!quit){
    // get window size
    SDL_GetWindowSize(win,&winW,&winH);
		// while there are events in the queue handle them
		while(SDL_PollEvent( &e )!= 0){
			if(e.type == SDL_QUIT){ 
				quit = true;
			}else if (e.type == SDL_KEYDOWN){
          // handle key presses
          randX = rand()%winW;
          randY = rand()%winH;
          rectRGB = randRGB();
          fprintf(stderr,"KEYPRESS %i,%i\n",randX,randY);
			  }
		  }
		  // clear rend
		  SDL_SetRenderDrawColor(gRend,255,255,255,255);
		  SDL_RenderClear(gRend);
     
      //Render COLOR filled quad
      SDL_Rect fillRect = {randX,randY,30+randX,30+randY};
      SDL_SetRenderDrawColor(gRend,rectRGB.r,rectRGB.g,rectRGB.b,rectRGB.t);        
      SDL_RenderFillRect( gRend, &fillRect ); 
		  
      // show da render
		  SDL_RenderPresent(gRend);
	  }
	// clean up
  exitProg(0,win,gRend,NULL);// here too
}
