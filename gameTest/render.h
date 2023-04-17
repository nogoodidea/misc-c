// Holds the class for rendering and objects

#include <glad/gl.h>


// keeps track of the VBO/VAO Points and Colors
class Object3D{
  public:
    GLuint VBO,VAO,EBO;
    GLfloat* vertP;
    GLuint* vertT;
    int amtP,amtT; // amount vertexes, amout T 
    // int function
    Object3D(GLfloat* IvertP,int IamtP,GLuint* IvertT,int IamtT){
      // save the vars so we can do MATH on them
      amtP = IamtP;
      amtT = IamtT;
      vertP = IvertP;
      vertT = IvertT;

      glGenVertexArrays(1,&VAO); // vertex array object
      glGenBuffers(1,&VBO); //Vertex Buffer
      glGenBuffers(1,&EBO);// or Element Buffer Object
      
      glBindVertexArray(VAO);
      // bind VBO
      glBindBuffer(GL_ARRAY_BUFFER,VBO);
      glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*amtP*6,vertP,GL_STATIC_DRAW);
      // bind EBO
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*3*amtT,vertT,GL_STATIC_DRAW);
      // x,y,z pos
      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)0);
      glEnableVertexAttribArray(0);
      // r,g,b color
      glVertexAttribPointer(1, 3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(1);

      // clean up
      //glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

    }
    // rend function
    void rend(){
      // binds the vao, this holds the VAO and the EBO
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES,amtT*3,GL_UNSIGNED_INT,0);// amount of points the render will draw, amtT is 2 times 3 points so 6
      glBindVertexArray(0); // unbind the VBO so if i use snowflake code latter it will not mess up as much
    }
    // clean up
    void del(){
      glDeleteVertexArrays(1,&VAO);
      glDeleteBuffers(1,&VBO);
      glDeleteBuffers(1,&EBO);
      // your going to want to del the object after this
    }
};
