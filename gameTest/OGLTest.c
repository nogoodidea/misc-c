#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// that one struct that makes the world go round
struct MainStruct {int exitCode;SDL_Window* win;SDL_GLContext gCont;GLuint progID;GLuint VBO;GLuint IBO;};
struct VB {unsigned char v;/*magnitude*/char x;char y; char z;};

// to executed when ever the program needs to exit
void progExit(struct MainStruct ctlStruct){
  if(ctlStruct.progID!=0){glDeleteProgram(ctlStruct.progID);}
  if(ctlStruct.win!=NULL){SDL_DestroyWindow(ctlStruct.win);}
  if(strlen(SDL_GetError())!= 0){fprintf(stderr,"SDL ERROR: %s",SDL_GetError());}
  SDL_Quit();
  fprintf(stderr,"\nEXITING WITH CODE %i\n",ctlStruct.exitCode);
  exit(ctlStruct.exitCode);
}

struct MainStruct progInit(){
  //OH BOY MAIN STRUCT I HOPE IT DOES NOT BREAK EVERYTHING
  struct MainStruct ctlStruct ={.exitCode=EXIT_FAILURE,.win=NULL,.progID=0};
  
  if(SDL_Init(SDL_INIT_VIDEO)<0){progExit(ctlStruct);}
  ctlStruct.win = SDL_CreateWindow("Window Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
  if(ctlStruct.win == NULL){progExit(ctlStruct);}
  //Init Gl Context
  
  //set the gl settings
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
  ctlStruct.gCont = SDL_GL_CreateContext(ctlStruct.win);
  if(ctlStruct.gCont == NULL){progExit(ctlStruct);}
  
  //vsync
  if(SDL_GL_SetSwapInterval(1)<0){fprintf(stderr,"VSync Failed to Init\nContinuing\n");}
  
  // Init GLEW
  glewExperimental = GL_TRUE; 
  GLenum glewError = glewInit();
  if(glewError != GLEW_OK){fprintf(stderr,"GLEW ERROR: %s\n", glewGetErrorString(glewError));progExit(ctlStruct);}

  // redoing all of this
  
  //points
  struct VB Vert={.x=0.0f,.y=0.0f,.z=0.0f.v=0};
  
  GLuint VBO; // VBO
  //https://stackoverflow.com/questions/62121635/passing-data-to-a-glsl-vertex-shader
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  
  glBufferData(GL_ARRAY_BUFFER,sizeof(struct VB),Vert,GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);

  ctlStruct.VBO=VBO;// copy changes
  return ctlStruct;
}
//GL Rendering function 3d stuff
int GLRend(struct MainStruct ctlStruct){
  //todo mur OGL
  glUseProgram(ctlStruct.progID);
  glEnableVertexAttribArray(0);
  // data vor render
  glBindBuffer(GL_ARRAY_BUFFER,ctlStruct.VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // data index???????
  glDrawArrays(GL_POINTS, 0,1);
  glDisableVertexAttribArray(0);
  return 0;
}
// SDL Rendering function 2d stuff


int main(int argc,char** argv){ 
  // init SDL/OpenGL
  struct MainStruct ctlStruct = progInit();
  //Event handler
  SDL_Event e;
  // Loop Ctl
  int quitLoop = 0;
  //MAIN LOOP
  while(quitLoop == 0){
    //EVENT HANDLEING
    while(SDL_PollEvent(&e) != 0){
      if(e.type == SDL_QUIT){quitLoop = 1;} 
    }
    //does the rendering
    GLRend(ctlStruct);
    // MAIN LOOP AFTER HERE 
    
    // update da GL Render
    SDL_GL_SwapWindow(ctlStruct.win); 
  }
  // exits
  ctlStruct.exitCode = EXIT_SUCCESS;
  progExit(ctlStruct);
}
