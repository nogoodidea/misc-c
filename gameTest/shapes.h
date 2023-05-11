// shapes
// wrapper functions to int cubes and stuff, and 2d boxes for text/images latter
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"      

GLuint loadTexture(std::string text){
  GLuint texture = 0;
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  GLint w,h,nrC;
  stbi_uc *data = stbi_load(text.c_str(), &w, &h, &nrC, 0);
  // error checking
  if(data){glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,w,h,0,GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{std::cerr<<"ERROR::TEXTURE::FAILED TO LOAD: "<< text <<std::endl;}
  stbi_image_free(data);
  return texture;
}

Object3D genCube(std::string name,Shader *shad,GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat r,GLfloat g,GLfloat b){
  // add colors later
  // should be x,y,z, r,g,b, texture  

  GLfloat vert[] = {
    x+size,y+size,z+size,  r,g,b, 0.0f,0.0f,//0,1
    x+size,y-size,z+size,  r,g,b,  0.0f,0.0f,//0
    x-size,y-size,z+size,  r,g,b,  0.0f,0.0f,//0,1
    x-size,y+size,z+size,  r,g,b, 0.0f,0.0f,//1
    x+size,y+size,z-size,  r,g,b, 0.0f,0.0f,//2,3
    x+size,y-size,z-size,  r,g,b, 0.0f,0.0f,//2
    x-size,y-size,z-size,  r,g,b, 0.0f,0.0f, //2,3
    x-size,y+size,z-size,  r,g,b, 0.0f,0.0f//3
  };

  GLuint t[] = {
	  0,1,2,
	  0,2,3,
	  
	  4,5,6,
	  4,6,7,
	   
	  4,0,1,
	  4,5,1,

	  5,1,2,
	  5,6,2,

	  6,2,3,
	  6,7,3,

	  7,3,0,
	  7,4,0
  };
  return Object3D(name,vert,8,t,12,0,shad);
}

Object3D genSquare(std::string name,Shader *shad,GLfloat x,GLfloat y,GLfloat z,GLfloat size){
 // makes a 2d object 
  GLfloat vert[] = {
    x+size,y+size,z,  0.0f,0.0f,0.0f, 0.0f,0.0f, //0,1
    x+size,y-size,z,  0.0f,0.0f,0.0f, 0.0f,0.0f, //0
    x-size,y-size,z,  0.0f,0.0f,0.0f, 0.0f,0.0f, //0,1
    x-size,y+size,z,  0.0f,0.0f,0.0f, 0.0f,0.0f //1
  };

  GLuint t[] = {
	  0,1,2,
	  0,2,3
  };
  return Object3D(name,vert,4,t,2,0,shad);
}

Object3D genTextureSquare(std::string name,Shader *shad,GLfloat x,GLfloat y,GLfloat z,GLfloat size,std::string text){
  GLuint texture = loadTexture(text);
  GLfloat vert[] = {
    x+size,y+size,z,  0.0f,0.0f,0.0f, 1.0f,1.0f, //0,1
    x+size,y-size,z,  0.0f,0.0f,0.0f, 1.0f,0.0f, //0
    x-size,y-size,z,  0.0f,0.0f,0.0f, 0.0f,0.0f, //0,1
    x-size,y+size,z, 0.0f,0.0f,0.0f, 0.0f,1.0f //1
  };

  GLuint t[] = {
	  0,1,2,
	  0,2,3
  };
  return Object3D(name,vert,4,t,2,texture,shad);
}


