// Holds the class for rendering and objects

#include <glad/gl.h>

#include <cmath> // math
#include <vector>
#include <algorithm>
#include <iostream> // string comp 
// pi
#define PI 3.14159f

GLfloat getScaler(GLfloat w,GLfloat h){
  GLfloat fw=floorf(w/42);
  GLfloat fh=floorf(h/18);
  if(fw<=fh){return fw;}
  else{return fh;}
}

// keeps track of the VBO/VAO Points and Colors
class Object3D{
  public:
    std::string name;
    GLuint VBO,VAO,EBO;
    GLfloat* vertP=NULL;
    GLuint* vertT=NULL;
    GLuint texture;
    //refrance to the shader we want to use
    Shader *shad=NULL;

    // bools for updateing stuff
    bool *upBuf; //0 C 1 P

    GLfloat midPoint[3] = {0.0f,0.0f,0.0f}; // hold the mid point used for transform matrix
    int amtP,amtT; // amount vertexes, amout T 
    
    // int function
    Object3D(std::string Iname,GLfloat* IvertP,int IamtP,GLuint* IvertT,int IamtT,GLuint Itexture,Shader *Ishad){
      // save the vars so we can do MATH on them
      name = Iname;
      amtP = IamtP;
      amtT = IamtT;
      vertT = IvertT;
      vertP = IvertP;
      texture = Itexture;
      shad = Ishad;
      upBuf = new bool[2] {false,true} ;// do i use this to much?


      glGenVertexArrays(1,&VAO); // vertex array object
      glGenBuffers(1,&VBO); //Vertex Buffer
      glGenBuffers(1,&EBO);// or Element Buffer Object
      
      glBindVertexArray(VAO);
      // bind VBO
      glBindBuffer(GL_ARRAY_BUFFER,VBO);
      glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*amtP*8,vertP,GL_STATIC_DRAW);
      // bind EBO
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*3*amtT,vertT,GL_STATIC_DRAW);
      // x,y,z pos
      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)0);
      glEnableVertexAttribArray(0);
      // r,g,b color
      glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(1);
      // texture
      glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,8*sizeof(GLfloat),(void*)(6*sizeof(GLfloat)));
      glEnableVertexAttribArray(2);

      // clean up
      glBindVertexArray(0);

      //find the midpoint needed for stuff
      findMidpoint(midPoint); // zero + something is something
    }
    // does all the transforms and matrix *
    void trans(GLfloat x,GLfloat y,GLfloat z){ // in the form of x,y,z , r,g,b is an other function
      // transfroms the shape by the vertex transform, does not change the colors
      for(int v=0;v<amtP;v+=1){
        vertP[v*8+0]+=x;
	vertP[v*8+1]+=y;
	vertP[v*8+2]+=z;
      }
      upBuf[1]=true;
          }

    void scale(GLfloat x,GLfloat y,GLfloat z){// copy and past from above but =* 
      int v;
      for(v=0;v<amtP;v+=1){
          vertP[v*8]*=x;
          vertP[v*8+1]*=y;
          vertP[v*8+2]*=z;
      }upBuf[1]=true;
    }
    // x y z
    void rot(GLfloat rx,GLfloat ry,GLfloat rz,GLfloat theta){ //rotate
      GLfloat ox,oy,oz;// old x,y,z
      int v;
      // turn thata in to radions
      //theta *= (PI/180);
      // normalise the rot vector
      float len = sqrtf(rx*rx+ry*ry+rz*rz);
      // 0 dev by len return nan we don't like nan
      if(len!=0.0f){
      if(rx!=0.0f){rx = rx/len;} 
      if(ry!=0.0f){ry = ry/len;}
      if(rz!=0.0f){rz = rz/len;}
      }
      //maths that will need to be called a lot
      GLfloat ct = cosf(theta), st = sinf(theta);
      GLfloat t = 1.0 - ct;
      for(v=0;v<amtP;v+=1){
	      // 0-midpoint should work
          ox=vertP[v*8]+(0-midPoint[0]); //v6 = x
          oy=vertP[v*8+1]+(0-midPoint[1]); // v6+1 = y
          oz=vertP[v*8+2]+(0-midPoint[2]); // v6+2 = z
          // matrix is from
          vertP[v*8]=((ct+rx*rx*t)*ox+(rx*ry*t-rz*st)*oy+(rx*rz*t+ry*st)*oz)-(0-midPoint[0]);
          vertP[v*8+1]=((rx*ry*t+rz*st)*ox+(ct+ry*ry*t)*oy+(ry*rz*t-rx*st)*oz)-(0-midPoint[1]);
          vertP[v*8+2]=((rz*rx*t-ry*st)*ox+(rz*ry*t+rx*st)*oy+(ct+rz*rz*t)*oz)-(0-midPoint[2]);
          // update vbo
      }
      findMidpoint(midPoint);
      upBuf[1]=true;
    }
    // rotate around the origin 0,0,0
    void rotA(GLfloat rx,GLfloat ry,GLfloat rz,GLfloat theta){ //rotate
      GLfloat ox,oy,oz;// old x,y,z
      int v;
      // turn thata in to radions
      //theta *= (PI/180);
      // normalise the rot vector
      float len = sqrtf(rx*rx+ry*ry+rz*rz);
      // 0 dev by len return nan we don't like nan
      if(len!=0.0f){
      if(rx!=0.0f){rx = rx/len;} 
      if(ry!=0.0f){ry = ry/len;}
      if(rz!=0.0f){rz = rz/len;}
      }
      //maths that will need to be called a lot
      GLfloat ct = cosf(theta), st = sinf(theta);
      GLfloat t = 1.0 - ct;
      // so ummm oh god basicly rewriteing someone elses code
      // https://rosettacode.org/wiki/Rodrigues%E2%80%99_rotation_formula#C
      
      // https://mathworld.wolfram.com/RodriguesRotationFormula.html
      // might want to take a look at this 
      // https://www.3dgep.com/understanding-quaternions/
      for(v=0;v<amtP;v+=1){
          ox=vertP[v*8]; //v6 = x
          oy=vertP[v*8+1]; // v6+1 = y
          oz=vertP[v*8+2]; // v6+2 = z
          // matrix is from
          vertP[v*8]=(ct+rx*rx*t)*ox+(rx*ry*t-rz*st)*oy+(rx*rz*t+ry*st)*oz;
          vertP[v*8+1]=(rx*ry*t+rz*st)*ox+(ct+ry*ry*t)*oy+(ry*rz*t-rx*st)*oz;
          vertP[v*8+2]=(rz*rx*t-ry*st)*ox+(rz*ry*t+rx*st)*oy+(ct+rz*rz*t)*oz;
      }
      upBuf[1]=true;
    }
    //updates the buffer, does ALL vaules
    void upBuffers(){
	  for(int i=0;i<amtP*8;i+=1){
	  glNamedBufferSubData(VBO,(i)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i]);
	    }
    }
    void upBufPoint(){
	GLfloat x,y,z;
	for(int i=0;i<amtP;i+=1){
		x=vertP[i*8]/21;
		y=vertP[i*8+1]/9;
		z=vertP[i*8+2]/21;
		glNamedBufferSubData(VBO,(i*8)*sizeof(GLfloat),sizeof(GLfloat),&x);
		glNamedBufferSubData(VBO,(i*8+1)*sizeof(GLfloat),sizeof(GLfloat),&y);
		glNamedBufferSubData(VBO,(i*8+2)*sizeof(GLfloat),sizeof(GLfloat),&z);
	}
    }
    void upBufColor(){
	for(int i=0;i<amtP;i+=1){
		glNamedBufferSubData(VBO,(i*8+3)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i*8+3]);
		glNamedBufferSubData(VBO,(i*8+4)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i*8+4]);
		glNamedBufferSubData(VBO,(i*8+5)*sizeof(GLfloat),sizeof(GLfloat),&vertP[i*8+5]);
	}
    }
    // updates the buffer with the matrix, translates
    void frustumMatrix(GLfloat w,GLfloat h,GLfloat s){
	GLfloat x,y,z;
	for(int i=0;i<amtP;i+=1){
		x=vertP[i*8]*s*((2.0f*1.0f)/(h))+vertP[i*8+2];
		y=vertP[i*8+1]*s*((2.0f*1.0f)/(h))+vertP[i*8+2];
		z=vertP[i*8+2]*s*(-1.0f*((w+1.0f)/(w-1.0f)))+-1.0f*((2.0f*w*1.0f)/(w-1.0f));
		glNamedBufferSubData(VBO,(i*8)*sizeof(GLfloat),sizeof(GLfloat),(void*)&x);
		glNamedBufferSubData(VBO,(i*8+1)*sizeof(GLfloat),sizeof(GLfloat),(void*)&y);
		glNamedBufferSubData(VBO,(i*8+2)*sizeof(GLfloat),sizeof(GLfloat),(void*)&z);
	}
    }
    // updates the point buffer
    void orthoMatrix(GLfloat w, GLfloat h,GLfloat s){
	    GLfloat x,y,z;
	for(int i=0;i<amtP;i+=1){
		x=vertP[i*8]*s*(2.0f/w);
		y=vertP[i*8+1]*s*(2.0f/h);
		z=vertP[i*8+2]*s*(-2.0f/w);
		glNamedBufferSubData(VBO,(i*8)*sizeof(GLfloat),sizeof(GLfloat),(void*)&x);
		glNamedBufferSubData(VBO,(i*8+1)*sizeof(GLfloat),sizeof(GLfloat),(void*)&y);
		glNamedBufferSubData(VBO,(i*8+2)*sizeof(GLfloat),sizeof(GLfloat),(void*)&z);
	}
	
    }
    // rend function
    void rend(int p,GLfloat w,GLfloat h,GLfloat s,bool reGenBuffer){
      if(texture!=0){//if we added a texture bind it
        glBindTexture(GL_TEXTURE_2D, texture); 
      }
      //updates colors
      if(upBuf[0]){
	      upBufColor();
	      upBuf[0]=false;
      }
      //updates the points
        if(upBuf[1]||reGenBuffer){
          switch(p){
            default:
              upBufPoint();
              break;
            case 1:
              orthoMatrix(w,h,s);
              break;
            case 2:
              frustumMatrix(w,h,s);
              break;
        }
	upBuf[1]=false;
      }
      // binds the vao, this holds the VAO and the EBO
      glBindVertexArray(VAO);
      shad->use();
      glDrawElements(GL_TRIANGLES,amtT*3,GL_UNSIGNED_INT,0);// amount of points the render will draw, amtT is 2 times 3 points so 6
      glBindVertexArray(0); // unbind the VBO so if i use snowflake code latter it will not mess up as much
      glBindTexture(GL_TEXTURE_2D,0);
    }
    // clean up
    void cleanUp(){
      glDeleteVertexArrays(1,&VAO);
      glDeleteBuffers(1,&VBO);
      glDeleteBuffers(1,&EBO);
      delete [] upBuf;
      delete [] vertP;
      delete [] vertT;
      // your going to want to del the object after this
      // names are not removed as they are malloced in an other place
    }
    
    void findMidpoint(GLfloat *out){
    // find the mid point
    int i;
    GLfloat avg=0.f;
    for(i=0;i<amtP;i+=1){
      avg+=vertP[i*8]; //x
      }
    out[0]=avg/amtP; //y
    avg=0.0f;
    for(i=0;i<amtP;i+=1){
      avg+=vertP[(i*8)+1];
      }
    out[1]=avg/amtP;
    avg=0.0f;
    for(i=0;i<amtP;i+=1){
      avg+=vertP[(i*8)+2]; //z
      }
    out[2]=avg/amtP;
    }
};

// render object
// has a list of all Object3D and renders them squentuly
// does new list and all that
//
class Renderer{
  public:
    std::vector<Object3D*> obj;
    
    void push(Object3D *item){
      std::cout << "rend/rendTx added: "<< item->name << std::endl;
      obj.insert(obj.end(),item);
    }

    void rend(int p,GLfloat w,GLfloat h,GLfloat s,bool reGenBuffer){
     for(std::vector<Object3D*>::iterator i = obj.begin();i< obj.end();i++){
      	 (*i)->rend(p,w,h,s,reGenBuffer);
      }
    }
    
    Object3D* search(std::string name){
      for(std::vector<Object3D*>::iterator i = obj.begin();i< obj.end();i++){
        if(name.compare((*i)->name)==0){return (*i);}
      }
      return NULL;// return null if unfound 
    }

    void del(Object3D *item){
      for(std::vector<Object3D*>::iterator i = obj.begin();i< obj.end();i++){
	if((*i) == item){
      	  (*i)->cleanUp();
      	  delete (*i);
	  //how is this understandable 
        }
      }
      obj.erase(std::remove(obj.begin(),obj.end(),item),obj.end());
      std::cout << "rend/rendTx removed: "<< item->name << std::endl;
    }

    void cleanUp(){//del all
     for(std::vector<Object3D*>::iterator i = obj.begin();i< obj.end();i++){
        (*i)->cleanUp();
	delete (*i);
	(*i) = NULL;
	obj.erase(i);
      }
     obj.clear();
     obj.shrink_to_fit();
    }
};

