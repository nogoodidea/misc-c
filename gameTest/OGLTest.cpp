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

// if the user resized update the screen
void fbResizeCallback(GLFWwindow* win,int w,int h){glViewport(0,0,w,h);/*_Exit(1);*/}

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
  glClearColor(1.0f,0.0f,0.5f,1.0f);
  return win;
}

// OpenGl startup function
Shader intOGL(){
  //enables that anti-aliasing thingy
  glEnable(GL_MULTISAMPLE);
  
  //refractoring shaders to an obj, following https://learnopengl.com/Getting-started/Shaders
  Shader shad("vertShad.vs","fragShad.fs");

  return shad;
}


int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  std::cout << "INFO::GLUT::STARTED\n";
  std::cout << std::endl;
  Shader shadProg = intOGL();

  //https://stackoverflow.com/questions/5091570/most-basic-working-vbo-example
  //https://learnopengl.com/Getting-started/Hello-Triangle
  // now with ... PAIN
  // 3 * 3, 3 points 

  //virtex atrib 0, 3 vaules per vertix, floats,not normalized, mem size of vert, offset poniter of array????
  //no del it works
  // see above
 
  // should be x,y,z, r,g,b  
  GLfloat vert[] = {
    0.5f,0.5f,0.0f,   0.0f,0.0f,0.0f,//0,1
    0.5f,-0.5f,0.0f,  0.0f, 0.0f, 0.0f,//0
    -0.5f,-0.5f,0.0f,   0.0f, 0.0f, 0.0f,//0,1
    -0.5f,0.5f,0.0f,   0.0f,0.0f,0.0f //1
  };

  GLuint t[] = {0,1,2,0,2,3};
  // loads the Object3D
  Object3D testObj(vert,4,t,2);
  
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0); // rebound at render loop	

  while(!glfwWindowShouldClose(win)){
   glClear(GL_COLOR_BUFFER_BIT);

   shadProg.use();// same as 1 line down
   
   //rend the stuff attatched to VAO

   testObj.rend();

   glBindVertexArray(0);// see bind vao
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   }
  // cleanup
  shadProg.del();
  testObj.del(); 

  glfwTerminate();
  return 0;
}
