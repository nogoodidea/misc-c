#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// that one struct that makes the world go round
struct MainStruct {int exitCode;SDL_Window* win;SDL_GLContext gCont;GLuint progID;GLuint VBO;GLuint IBO;};


// to be regerseded to run on exit
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
  // Init GL
  //MAJIC CODE
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vertexShaderSource[] = {"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"};
  glShaderSource(vertShader,1,vertexShaderSource,NULL);
  glCompileShader(vertShader);
  
  GLint glError = GL_FALSE;// best name
  glGetShaderiv(vertShader,GL_COMPILE_STATUS,&glError);
  if(glError != GL_TRUE){fprintf(stderr,"GL ERROR: SHADER FAILED");progExit(ctlStruct);}
  glAttachShader(ctlStruct.progID,vertShader);
  
  //mor shaders BLACK MAJIC CODE FROM STACKOVERFLOW SAME AS ABOVE
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragmentShaderSource[] = {"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );"};
  glShaderSource(fragShader,1,fragmentShaderSource,NULL);
  glCompileShader(fragShader);
  
  glGetShaderiv(vertShader,GL_COMPILE_STATUS,&glError);
  if(glError != GL_TRUE){fprintf(stderr,"GL ERROR: SHADER FAILED");progExit(ctlStruct);}
  glAttachShader(ctlStruct.progID,fragShader);
  
  glLinkProgram(ctlStruct.progID);
  glGetProgramiv(ctlStruct.progID,GL_LINK_STATUS,&glError);
  if(glError != GL_TRUE){fprintf(stderr,"GL ERROR: LINKING FAILED");progExit(ctlStruct);}
  
  GLint vertPos = glGetAttribLocation(ctlStruct.progID,"LVertexPos2D");
  if(vertPos == -1){fprintf(stderr,"GL ERROR: think the virtex shader broke IDK");progExit(ctlStruct);}  
  
  //majic color code
  glClearColor(0.f,0.f,0.f,1.f); 
  //VBO
  GLfloat verData[]={-0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5};
  // IBO
  GLuint indexData[]={0,1,2,3};
  // get the pointers for the struct elements
  GLuint VBO;
  GLuint IBO;
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,2*4*sizeof(GLfloat),verData,GL_STATIC_DRAW);
  
  glGenBuffers(1,&IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,4*sizeof(GLuint),indexData,GL_STATIC_DRAW);
  // copy to struct
  ctlStruct.VBO = VBO;
  ctlStruct.IBO = IBO;
  return ctlStruct;
}
//GL Rendering function 3d stuff
int GLRend(struct MainStruct ctlStruct){
  //todo mur OGL
  glUseProgram(ctlStruct.progID);
  GLint virt2D = glGetAttribLocation(ctlStruct.progID,"LVertexPos2D");
  if(virt2D == -1){fprintf(stderr,"OGL Rend Error");progExit(ctlStruct);}
  glEnableVertexAttribArray(virt2D);
  // data vor render
  glBindBuffer(GL_ARRAY_BUFFER,ctlStruct.VBO);
  glVertexAttribPointer(virt2D,2,GL_FLOAT,GL_FALSE,2*sizeof(GLfloat),NULL);
  // data index???????
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ctlStruct.IBO);
  glDrawElements(GL_TRIANGLE_FAN,4,GL_UNSIGNED_INT,NULL);
  glDisableVertexAttribArray(virt2D);
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
