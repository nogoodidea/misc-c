#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void stop(int code, Display *display){ 
    XCloseDisplay(display);
    printf("EXIT %i\n",code);
    exit(code);
}
int main(int argv,char **argc){
    Display *display;
    Window window;
    XEvent event;
    display = XOpenDisplay(NULL);
    char *msg ="Hello World";
    if (display== NULL){fprintf(stderr,"Cannot open display\nEXIT 1");exit(1);}
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 100, 100, 1,BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display,screen, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    //window loop do all the things here
    while (1) {
        XNextEvent(display,&event);
        if (event.type == Expose) {
            //draw 
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, screen), 10, 50, msg, strlen(msg));
        }
        if (event.type == KeyPress){stop(0,display);}
    }
}

