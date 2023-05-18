// trying /w c++ 
// https://www.ogldev.org/index.html
// https://learnopengl.com/Introduction

#include<iostream>
#include<string>
#include<cmath> // IN 3D

// idea ever see that part of jarrasic park?
// #include<filesystem>

// so your going to need to use glad to make the header files/c source
// so use the online version, v2 
// or the cli can be added with pip. pip install glad2
// make glad.h might work, if i added it.
// gl 3.3
// good luck


#include <glad/gl.h>
#include<GLFW/glfw3.h>

#include "shader.h" // does shader things
#include "render.h" // does obj mangment things
#include "shapes.h" // helper functions to make shapes quicker
#include "text.h"   // lets me write things


// if the user resized update the screen
void fbResizeCallback(GLFWwindow* win,int w,int h){glViewport(0,0,w,h);
  glOrthro(w/2,w/2-0.0f,h/2,h/2-0.0f, 0.0f,4.0f);
}

// glfw startup function
GLFWwindow* intGlfw(){
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES,4);//anti aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  const int winW = 600;
  const int winH = 600;

  GLFWwindow* win = glfwCreateWindow(winW,winH,"SUFFER",NULL,NULL);
  glfwMakeContextCurrent(win);
  // glad
  int v;
  if (!(v=gladLoadGL((GLADloadfunc)glfwGetProcAddress))){
     std::cerr<<"ERROR::GLAD::INIT_FAILED"<<std::endl;
     return NULL;}
  std::cout<<"OpenGL Version " << GLAD_VERSION_MAJOR(v) <<"."<<GLAD_VERSION_MINOR(v) << " Loaded" << std::endl;

  // redgester the callback function
  glfwSetFramebufferSizeCallback(win,fbResizeCallback);

  //R,G,B,A
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  return win;
}

// OpenGl startup function
void intOGL(){
  glMatrixMode(GL_PROJECTION);
  //enables that anti-aliasing thingy
  glEnable(GL_MULTISAMPLE);
  // depth testing so shapes don't overlap
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}


int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  intOGL();
  // shaders used to render colored objects
  Shader shadCol = Shader("shaders/vertCol.vs","shaders/fragCol.fs");
  // shaders used with textured objects
  Shader shadTex = Shader("shaders/vertTex.vs","shaders/fragTex.fs");
  //
  Shader shadChar = Shader("shaders/vertChar.vs","shaders/fragChar.fs");
  // freetype for fonts
  FT_Library ftLib=intFT();

  FT_Face ftFace=intFTFont(ftLib,"/usr/share/fonts/dejavu-sans-mono-fonts/DejaVuSansMono.ttf");

  std::map<char,Char> font = loadFTglyph(ftFace);

  // text object, TODO cleanup/ render text 1 time and update it if the string changes

  objectText text(&shadChar,"THIS IS A TEST OF THE SYSTEM",0.0f,0.0f,0.0f,font);

  // render obj
  Renderer rend3d;
  // loads the Object3D
  rend3d.push(genCube("Test Cube",&shadCol,-0.91f,0.1f,0.0f,0.1f,2.5f,0.0f,0.0f));

  rend3d.push(genCube("Test Cube2",&shadCol,0.0f,-0.5f,0.0f,0.1f,0.0f,2.0f,1.0f));

  rend3d.push(genTextureSquare("Texture Box",&shadTex,0.0f,0.0f,0.0f,0.5f,"textures/testTexture.png"));

  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0); // rebound at render loop	

  int testObj = rend3d.search("Test Cube");
  bool keyPressed = false; // key holding 
  while(!glfwWindowShouldClose(win)){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
   // window inputs
   if(glfwGetKey(win,GLFW_KEY_ESCAPE)==GLFW_PRESS){
      glfwSetWindowShouldClose(win,true);
   }if(glfwGetKey(win,GLFW_KEY_SPACE)){
   if(keyPressed==false){keyPressed=true;rend3d.get(testObj).rot(1.0f,1.0f,0.0f,0.1f);}
   }else{keyPressed=false;}

   rend3d.rend();
   text.rend();
   
   glBindVertexArray(0);// see bind vao
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   }
  // cleanup
  shadCol.cleanUp();
  shadTex.cleanUp();
  rend3d.cleanUp(); 

  glfwTerminate();
  return 0;
}
