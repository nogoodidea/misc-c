// Holds the class for rendering and objects

#include <glad/gl.h>

#include <cmath> // math

// pi
#define PI 3.14159

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

    void scale(double transform[3]){// copy and past from above but =* 
      int v,i;
      for(v=0;v<amtP;v+=1){
        for(i=0;i<3;i+=1){
          vertP[i+v*6]*=transform[i];// v*6 because 1 verticy is 6 floats.
          glNamedBufferSubData(VBO,(i+v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i+v*6]);
        }
      }
    }
    // x y z
    void rot(GLfloat theta[3]){ //rotate
      GLfloat ox,oy,oz;// old x,y,z
                    //
                    // well time to read up on linear algebra
                    // https://www.khanacademy.org/math/linear-algebra/matrix-transformations/linear-transformations/v/vector-transformations
      int v,i;
      // turn thata in to radions
      for(i=0;i<3;i+=1){theta[i]*=(PI/180);}
      for(v=0;v<amtP;v+=1){
          ox=vertP[v*6];
          oy=vertP[v*6+1]; // v6+1 = y
          oz=vertP[v*6+2]; // v6+2 = z
          // matrix is from 
          std::cout<<ox<<"|"<<oy<<"|"<<oz<<std::endl;
          vertP[v*6]=(ox*(cos(theta[0])+(ox*ox)*(1-cos(theta[0]))))+(oy*(ox*oy*(1-cos(theta[0]))-oz*sin(theta[0])))+(oz*(ox*oz*(1-cos(theta[0]))+oy*sin(theta[0])));// x
          glNamedBufferSubData(VBO,(v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6]);
          vertP[v*6+1]=(ox*(oy*ox*(1-cos(theta[1]))+oz*sin(theta[1])))+(oy*(cos(theta[1])+(oy*oy)*(1-cos(theta[1]))))+(oz*(oy*oz*(1-cos(theta[1]))-ox*sin(theta[1])));// y
          glNamedBufferSubData(VBO,(v*6+1)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+1]);
          vertP[v*6+1]=(ox*(oz*ox*(1-cos(theta[2]))-oy*sin(theta[2])))+(oy*(oz*oy*(1-cos(theta[2]))+ox*sin(theta[2])))+(oz*(cos(theta[2])+(oz*oz)*(1-cos(theta[2]))));// z
          glNamedBufferSubData(VBO,(v*6+2)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+2]);
      }
    }
    void rotz(GLfloat theta){ //rotate around z
      GLfloat ox,oy,oz;// old x,y,z
      int v;
      theta*=(PI/180);
      for(v=0;v<amtP;v+=1){
          ox=vertP[v*6];
          oy=vertP[v*6+1]; // v6+1 = y
          oz=vertP[v*6+2]; // v6+2 = z
          // matrix is from 
          std::cout<<ox<<"|"<<oy<<"|"<<oz<<std::endl;
          vertP[v*6]=(cos(theta)*ox)-(sin(theta)*oy);// x
          glNamedBufferSubData(VBO,(v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6]);
          vertP[v*6+1]=(sin(theta)*ox)+(cos(theta)*oy);// y
          glNamedBufferSubData(VBO,(v*6+1)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+1]);
      }
    }
    void rotx(GLfloat theta){ //rotate around x
      GLfloat ox,oy,oz;// old x,y,z
      int v;
      theta*=(PI/180);
      for(v=0;v<amtP;v+=1){
          ox=vertP[v*6];
          oy=vertP[v*6+1]; // v6+1 = y
          oz=vertP[v*6+2]; // v6+2 = z
          // matrix is from 
          std::cout<<ox<<"|"<<oy<<"|"<<oz<<std::endl;
          vertP[v*6+1]=(cos(theta)*oy)-(sin(theta)*oz);// y
          glNamedBufferSubData(VBO,(v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+1]);
          vertP[v*6+2]=(sin(theta)*oy)+(cos(theta)*oz);// z
          glNamedBufferSubData(VBO,(v*6+1)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+2]);
      }
    }
    void roty(GLfloat theta){ //rotate around y
      GLfloat ox,oy,oz;// old x,y,z
      int v;
      theta*=(PI/180);
      for(v=0;v<amtP;v+=1){
          ox=vertP[v*6];
          oy=vertP[v*6+1]; // v6+1 = y
          oz=vertP[v*6+2]; // v6+2 = z
          // matrix is from 
          std::cout<<ox<<"|"<<oy<<"|"<<oz<<std::endl;
          vertP[v*6]=(cos(theta)*ox)-(sin(theta)*oz);// x
          glNamedBufferSubData(VBO,(v*6)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6]);
          vertP[v*6+2]=(-1*sin(theta)*ox)+(cos(theta)*oz);// z
          glNamedBufferSubData(VBO,(v*6+1)*sizeof(GLfloat),sizeof(GLfloat),&vertP[v*6+2]);
      }
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
