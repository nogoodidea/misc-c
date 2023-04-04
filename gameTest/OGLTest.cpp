// trying /w c++ 
// https://www.ogldev.org/index.html
// c style stdlib/stdio 
// it's what i know 
//TODO CHANGE TO C++ style headers
#include<cstdio>

#include<GL/glew.h>
#include<GL/freeglut.h>
#include "math_3d.h"



static void RenderSceneCB(){
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

// glut startup function
bool intGlut(int* argc,char** argv){
  // needs argc/argv don't know why
  glutInit(argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

  const int winW = 600;
  const int winH = 600;
  glutInitWindowSize(winW,winH);
  
  int winX = 400;
  int winY = 400;
  glutInitWindowPosition(winX,winY);
  int win = glutCreateWindow("SUFFERING HERE DOC");
  if(win == 0){fprintf(stderr,"GLUT ERROR: window failed to init");_Exit(1);}
  //R,G,B,A
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  return true;
}

// OpenGl startup function
bool intOGL(){return true;}


int main(int argc, char** argv){
  if(intGlut(&argc,argv) != true){fprintf(stderr,"GLUT INT FAILED");_Exit(1);}
  
  //https://stackoverflow.com/questions/5091570/most-basic-working-vbo-example

  glutDisplayFunc(RenderSceneCB);
  
  glutMainLoop();
  return 0;
}
