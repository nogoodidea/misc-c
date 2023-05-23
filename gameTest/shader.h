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
    Shader(std::string vertPath,std::string geomPath,std::string fragPath){
      // onto compiling
      GLuint vert,frag,geom;
      
      //Vertix Shader
      const char *vertCode = readFile(vertPath);
      vert = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vert,1,&vertCode,NULL);
      glCompileShader(vert);
      checkError(vert,"VERT");

      //Geometry Shader
      const char *geomCode = readFile(geomPath);
      if(geomCode!=NULL){// if the string is null it will output 0 chars + the null terminator
      geom = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(geom,1,&geomCode,NULL);
      glCompileShader(geom);
      checkError(geom,"GEOM");
      }

      //Fragment Shader
      const char *fragCode = readFile(fragPath);
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
    // cleanup
    void cleanUp(){glDeleteProgram(ID);}
    
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
    const char *readFile(std::string fileName){
      std::string str;
      std::ifstream file;
      std::stringstream stream;
    
      file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      try{
        file.open(fileName); // read
        stream << file.rdbuf();
        // closeing files
        file.close();
        str = stream.str();
      }catch (std::ifstream::failure& e){
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
      return str.c_str();

    }
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
