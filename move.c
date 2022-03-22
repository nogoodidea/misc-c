#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>


// does cleanup, called when execution is done and on term singles
void cleanup(int signum){
	endwin();
	if (signum != 0){
	printf("signal %i, exiting...\n",signum); 
	exit(EXIT_FAILURE);
	}
	else {
	exit(EXIT_SUCCESS);
	}
}
//setup ncurces and set handling for term singles
void setup(){
	initscr();
	cbreak();
	//noecho();
	raw();
	signal(SIGINT, cleanup);
}
int main(){
	setup();
	int winsize[1];
	int done = false;
	struct playerstruct {
    		int x;
		int y;
		char icon[1];
	};
	getmaxyx(stdscr,winsize[0],winsize[1]);
	//player int
	struct playerstruct player;
	// MIGHT LOOK AT MOLLIC LATER for seting an char
	player.x =1;
	player.y =1;
	//sets icon, can be a string
	player.icon[0]='@';
	printw("%i",player.x);
	printw("%i",player.y);
	while(done != true){
		mvprintw(player.y,player.x,player.icon);
		switch (getch()){
			case 77:
				if ( player.y+1 == winsize[0]){break;}
				player.y++;
			case 73:
				if ( player.y-1 == 0){break;}
				player.y--;
			case 61:
				if ( player.x+1 == winsize[1]){break;}
				player.x++;
			case 100:
				if ( player.x-1 == 0){break;}
				player.x--;
			default:
		}
		refresh();
	}
	cleanup(0);
}
