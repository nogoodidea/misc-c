// trying /w c++ 
// https://www.ogldev.org/index.html
// https://learnopengl.com/Introduction

#include<iostream>
#include<string>

#include<GL/glew.h>
#include<GL/freeglut.h>



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
bool intOGL(){
  // vertex shader
  // going to be baked in as i don't give an
  //https://learnopengl.com/Getting-started/Hello-Triangle
  const char *vertShadSc = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){gl_Postion = vec4(aPos.x,aPos.y,aPos,z,1);}";
  const char *fragShadSc = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){FragColor = vec4(1.0f,0.5f,0.2f,1.0f);}";
  
  //vertex
  GLuint vertShad = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShad,1,&vertShadSc,NULL);
  glCompileShader(vertShad);
  
  // error checking
  GLint error;
  char GlLog[512];
  glGetShaderiv(vertShad,GL_COMPILE_STATUS,&error);
  
  if(!error){
    glGetShaderInfoLog(vertShad,512,NULL,GlLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << GlLog <<std::endl;
  return false;
  }
  //fragment
  GLuint fragShad = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShad,1,&fragShadSc,NULL);
  glCompileShader(fragShad);

  glGetShaderiv(fragShad,GL_COMPILE_STATUS,&error);
  
  if(!error){
    glGetShaderInfoLog(fragShad,512,NULL,GlLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << GlLog <<std::endl;
  return false;
  } 
  std::cout << "INFO::SHADER::PROGRAM_COMPILATION_DONE";
  return true;
  }


int main(int argc, char** argv){
  std::cout << "INFO::STARTED";
  if(intGlut(&argc,argv) != true){std::cout << "ERROR::GLUT::INT_FAILED";_Exit(1);}
  std::cout << "INFO::GLUT::STARTED";
  intOGL();
  
  //https://stackoverflow.com/questions/5091570/most-basic-working-vbo-example
  //https://learnopengl.com/Getting-started/Hello-Triangle
  // now with ... PAIN
  // 3 * 3, 3 points 
  
  int amtPoints = 3;
  GLfloat vertPoints[3*amtPoints]={
  -0.5f,-0.5f,0.0f,
  0.5f,-0.5f,0.0f,
  0.0f,0.5f,0.0f};
  GLuint VBO;
  //buffer 
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*amtPoints,vertPoints,GL_STATIC_DRAW);
  
  
  glutDisplayFunc(RenderSceneCB);
  
  glutMainLoop();
  return 0;
}
