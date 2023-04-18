// Holds the class for rendering and objects

#include <glad/gl.h>

#include <cmath> // math

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
      glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(1);

      // clean up
      //glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

    }
    // does all the transforms and matrix *
    void trans(GLfloat transform[3]){ // in the form of x,y,z , r,g,b is an other function
      // transfroms the shape by the vertex transform, does not change the colors
      int v,i;
      for(v=0;v<amtP;v+=1){
        for(i=0;i<3;i+=1){
          // does 2 things 1 updaes vertP to the new data,2 updates the VBO with new data
          vertP[i+v*6]+=transform[i];// v*6 because 1 verticy is 6 floats.
          glNamedBufferSubData(VBO,(i+v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i+v*6]);
        }
      }
    }

    void scale(GLfloat transform[3]){// copy and past from above but =* 
      int v,i;
      for(v=0;v<amtP;v+=1){
        for(i=0;i<3;i+=1){
          vertP[i+v*6]*=transform[i];// v*6 because 1 verticy is 6 floats.
          glNamedBufferSubData(VBO,(i+v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i+v*6]);
        }
      }
    }
    // x y z
    void rotx(GLfloat thata){ //rot on the x
      GLfloat oy,oz;// old y,z placeholders
                    //
                    // well time to read up on linear algebra
                    // https://www.khanacademy.org/math/linear-algebra/matrix-transformations/linear-transformations/v/vector-transformations
      int v,i;
      for(v=0;v<amtP;v+=1){
          oy=vertP[v*6+1]; // v6+1 = y
          oz=vertP[v*6+2]; // v6+2 = z

          vertP[v*6+1]=;// y
          glNamedBufferSubData(VBO,(i+v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i+v*6]);
      }
      
    }
    void roty(){ //rot on the y
      
    }
    void rotz(){ //rot on the z

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
