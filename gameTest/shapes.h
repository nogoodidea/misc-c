// shapes
// wrapper functions to int cubes and stuff, and 2d boxes for text/images latter
//


Object3D genCube(std::string name,GLfloat x,GLfloat y,GLfloat z,GLfloat size){
  // add colors later
  // hope you like red
  // should be x,y,z, r,g,b 

  GLfloat vert[] = {
    x+size,y+size,z+size,  0.0f,0.0f,0.0f,//0,1
    x+size,y-size,z+size,  0.0f,0.0f,0.0f,//0
    x-size,y-size,z+size,  0.0f,0.0f,0.0f,//0,1
    x-size,y+size,z+size,  0.0f,0.0f,0.0f,//1
    x+size,y+size,z-size,  0.0f,0.0f,0.0f,//2,3
    x+size,y-size,z-size,  0.0f,0.0f,0.0f,//2
    x-size,y-size,z-size,  0.0f,0.0f,0.0f, //2,3
    x-size,y+size,z-size,  0.0f,0.0f,0.0f //3
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

/*Object3D genSquare(std::string name){


  return NULL;
}*/
