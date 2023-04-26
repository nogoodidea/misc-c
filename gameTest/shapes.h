// shapes
// wrapper functions to int cubes and stuff, and 2d boxes for text/images latter
//


Object3D genCube(std::string name,GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat offX,GLfloat offY, GLfloat offZ){
  // add colors later
  // hope you like red
  // should be x,y,z, r,g,b 
  size = 0.5f;
  x=0.0f;
  y=0.0f;
  z=0.0f;

  GLfloat vert[] = {
    x+size+offX,y+size+offY,z+size+offZ,  1.5f,0.0f,0.0f,//0,1
    x+size+offX,y-size+offY,z+size+offZ,  1.5f,0.0f,0.0f,//0
    x-size+offX,y-size+offY,z+size+offZ,  1.5f,0.0f,0.0f,//0,1
    x-size+offX,y+size+offY,z+size+offZ,  1.5f,0.0f,0.0f,//1
    x+size+offX,y+size+offY,z-size+offZ,  1.5f,0.0f,0.0f,//2,3
    x+size+offX,y-size+offY,z-size+offZ,  1.5f,0.0f,0.0f,//2
    x-size+offX,y-size+offY,z-size+offZ,  1.5f,0.0f,0.0f, //2,3
    x-size+offX,y+size+offY,z-size+offZ,  1.5f,0.0f,0.0f //3
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
  return Object3D(name,vert,8,t,12);
}

Object3D genSquare(std::string name){


  //return Object3D(name);
}
