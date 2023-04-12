// trying /w c++ 
// https://www.ogldev.org/index.html
// https://learnopengl.com/Introduction

#include<iostream>
#include<string>

// idea ever see that part of jarrasic park?
// #include<filesystem>

// so your going to need to use glad to make the header files/c source
// so use the online version, v2 
// or the cli can be added with pip
// make glad.h might work, if i added it.
// gl 3.3
// good luck
#include<glad/gl.h>

#include<GLFW/glfw3.h>


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
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  return win;
}

// OpenGl startup function
bool intOGL(){
  //enables that anti-aliasing thingy
  glEnable(GL_MULTISAMPLE);
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
  //no del it works
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
  glEnableVertexAttribArray(0);
  // see above
   
  int amtPoints = 4;
  GLfloat vertPoints[3*amtPoints]={
  0.5f,0.5f,0.0f,
  0.5f,-0.5f,0.0f,
  -0.5f,-0.5f,0.0f,
  -0.5f,0.5f,0.0f};

  int amtTri = 2;
  GLuint vertIndices[3*amtPoints] = {0,1,3, //tri0
    1,2,3};//tri1  
  
    
  GLuint VBO,EBO,VAO; 
  
  glGenVertexArrays(1,&VAO); // vertex array object
  glGenBuffers(1,&VBO); //Vertex Buffer
  glGenBuffers(1,&EBO);// or Element Buffer Object

  // needs to be bound first
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*amtPoints,vertPoints,GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*3*amtTri,vertIndices,GL_STATIC_DRAW);

  //set the vertexattrib pointer
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
  //notes: do not unbind the EBO when the VAO is used
  glEnableVertexAttribArray(0);
  
  
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0); // rebound at render loop	

  while(!glfwWindowShouldClose(win))//todo get the window pointer here
   {
   
      
   glUseProgram(shadProg);// same as 1 line down
   glBindVertexArray(VAO);// only have one now but if we say had 20 this will be usefull
   
   glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

   glBindVertexArray(0);// see bind vao
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   } 
  
  return 0;
}
