// trying /w c++ 
// https://www.ogldev.org/index.html
// https://learnopengl.com/Introduction

#include<iostream>
#include<string>

// idea ever see that part of jarrasic park?
// #include<filesystem>

// so your going to need to use glad to make the header files
// make glad.h might work, if i added it.
// gl 3.3
// good luck
#include<glad/gl.h>

#include<GLFW/glfw3.h>


// if the user resized the window god forbid
void fbResizeCallback(GLFWwindow* win,int w,int h){glViewport(0,0,w,h);/*_Exit(1);*/}
// glut startup function
GLFWwindow* intGlfw(){
  // needs argc/argv don't know why
  glfwInit();
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
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  return win;
}

// OpenGl startup function
bool intOGL(){
  // vertex shader
  // going to be baked in as i don't give an
  //https://learnopengl.com/Getting-started/Hello-Triangle
  const char *vertShadSc ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
  const char *fragShadSc = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){FragColor = vec4(1.0f,0.5f,0.2f,1.0f);}\0";
  
  //vertex
  GLuint vertShad;
  vertShad = glCreateShader(GL_VERTEX_SHADER); // errors out here SEGFULT
  glShaderSource(vertShad,1,&vertShadSc,NULL);
  glCompileShader(vertShad);

  // error checking
  GLint error;
  char errorLog[512];
  glGetShaderiv(vertShad,GL_COMPILE_STATUS,&error);
  if(!error){
    glGetShaderInfoLog(vertShad,512,NULL,errorLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << errorLog;
  return NULL;
  }
  
  //fragment
  GLuint fragShad;
  fragShad = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShad,1,&fragShadSc,NULL);
  glCompileShader(fragShad);

  glGetShaderiv(fragShad,GL_COMPILE_STATUS,&error);
  
  if(!error){
    glGetShaderInfoLog(fragShad,512,NULL,errorLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << errorLog;
  return 0;
  } 
  //shader program
  GLuint shadProg;
  shadProg = glCreateProgram();

  glAttachShader(shadProg,vertShad);
  glAttachShader(shadProg,fragShad);
  glLinkProgram(shadProg);
  // error checking
  glGetProgramiv(shadProg,GL_LINK_STATUS, &error);
  if(!error){
    glGetShaderInfoLog(shadProg,512,NULL,errorLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << errorLog;
  return 0;
  }
  glUseProgram(shadProg);
  //bye
  glDeleteShader(vertShad);
  glDeleteShader(fragShad);

  return shadProg;
  }


int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  std::cout << "INFO::GLUT::STARTED\n";
  std::cout << std::endl;
  GLuint shadProg = intOGL();
  if(shadProg==0/*hopefully it can never be zero*/){std::cerr<<std::endl;
    glfwTerminate(); // same deal
    _Exit(1);}

  //https://stackoverflow.com/questions/5091570/most-basic-working-vbo-example
  //https://learnopengl.com/Getting-started/Hello-Triangle
  // now with ... PAIN
  // 3 * 3, 3 points 

  //virtex atrib 0, 3 vaules per vertix, floats,not normalized, mem size of vert, offset poniter of array????
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
  glEnableVertexAttribArray(0);
   
  int amtPoints = 3;
  GLfloat vertPoints[3*amtPoints]={
  -0.5f,-0.5f,0.0f,
  0.5f,-0.5f,0.0f,
  0.0f,0.5f,0.0f};
  GLuint VBO;
  //vertex buffer 
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*amtPoints,vertPoints,GL_STATIC_DRAW);
  
  // use OUR program
  glUseProgram(shadProg);
	
  // vertex array object
  GLuint VAO;
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*amtPoints,vertPoints,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
  glEnableVertexAttribArray(0);

  while(!glfwWindowShouldClose(win))//todo get the window pointer here
   {glfwSwapBuffers(win);
   glfwPollEvents();

   glUseProgram(shadProg);
   glBindVertexArray(VAO);
   glDrawArrays(GL_TRIANGLES,0,3);
   } 
  
  return 0;
}
