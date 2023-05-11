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


// if the user resized update the screen
void fbResizeCallback(GLFWwindow* win,int w,int h){glViewport(0,0,w,h);}

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
  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)){
     std::cerr<<"ERROR::GLAD::INIT_FAILED"<<std::endl;
     return NULL;}

  // redgester the callback function
  glfwSetFramebufferSizeCallback(win,fbResizeCallback);

  //R,G,B,A
  glClearColor(1.1f,1.1f,1.1f,1.0f);
  return win;
}

// OpenGl startup function
void intOGL(){
  //enables that anti-aliasing thingy
  glEnable(GL_MULTISAMPLE);
  // depth testing so shapes don't overlap
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // needed for textureing
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}


int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  std::cout << "INFO::GLUT::STARTED" << std::endl;
  intOGL();
  // shaders used to render colored objects
  Shader shadCol = Shader("shaders/vertCol.vs","shaders/fragCol.fs");
  // shaders used with textured objects
  Shader shadTex = Shader("shaders/vertTex.vs","shaders/fragTex.fs");

  // render obj
  Renderer rend;
  // loads the Object3D
  rend.push(genCube("Test Cube",&shadCol,0.1f,0.1f,0.1f,0.5f,2.5f,0.0f,0.0f));

  rend.push(genCube("Test Cube2",&shadCol,0.0f,-0.5f,0.0f,0.1f,0.0f,2.0f,1.0f));

  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0); // rebound at render loop	

  int testObj = rend.search("Test Cube");
  bool keyPressed = false; // key holding 
  while(!glfwWindowShouldClose(win)){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
   // window inputs
   if(glfwGetKey(win,GLFW_KEY_ESCAPE)==GLFW_PRESS){
      glfwSetWindowShouldClose(win,true);
   }if(glfwGetKey(win,GLFW_KEY_SPACE)){
   if(keyPressed==false){keyPressed=true;rend.get(testObj).rot(1.0f,1.0f,0.0f,0.1f);}
   }else{keyPressed=false;}

   rend.rend();
   
   glBindVertexArray(0);// see bind vao
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   }
  // cleanup
  shadCol.cleanUp();
  shadTex.cleanUp();
  rend.cleanUp(); 

  glfwTerminate();
  return 0;
}
