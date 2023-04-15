#ifndef SHADER_H
#define SHADER_H

//glad
#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
  public:
    // compiled program id
    GLuint ID;
    Shader(const char* vertPath,const char* fragPath){
      // read the path
      std::string vertStr,fragStr;
      std::ifstream vertFile,fragFile;
      std::stringstream vertStream,fragStream;
    
      //trying out c++ error catching
      vertFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      fragFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      try{
        vertFile.open(vertPath); // read
        fragFile.open(fragPath); // read
        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();
        // closeing files
        vertFile.close();
        fragFile.close();
        vertStr = vertStream.str();
        fragStr = fragStream.str();
      }catch (std::ifstream::failure& e){
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
      const char* vertCode = vertStr.c_str();
      const char* fragCode = fragStr.c_str();

      // onto compiling
      GLuint vert,frag;
      
      //Vertix Shader
      vert = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vert,1,&vertCode,NULL);
      glCompileShader(vert);
      checkError(vert,"VERT");

      //Fragment Shader
      frag = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(frag,1,&fragCode,NULL);
      glCompileShader(frag);
      checkError(frag,"FRAG");
      
      //Shader Program
      ID = glCreateProgram();
      glAttachShader(ID,vert);
      glAttachShader(ID,frag);
      glLinkProgram(ID);
      checkError(ID,"PROG");
      // clean up
      glDeleteShader(vert);
      glDeleteShader(frag);
    }

    void use(){glUseProgram(ID);}
    
    // functions for messing with uniforms
    // not like that sicko
    void setBool(const std::string &name,bool value)const{
       glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name,int value)const{
       glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name,float value){
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
  private:
    void checkError(GLuint shad,std::string type){
      GLint error;
      char log[1024];
      if(type != "PROG"){
        glGetShaderiv(shad,GL_COMPILE_STATUS,&error);
        if(!error){
          glGetShaderInfoLog(shad, 1024, NULL, log);
          std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << log << std::endl;
        }
      }else{
        glGetProgramiv(shad,GL_LINK_STATUS,&error);
        if(!error){
          glGetShaderInfoLog(shad, 1024, NULL, log);
          std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << log << std::endl;
        }
      }
    }
};
#endif
