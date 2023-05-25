// trying /w c++ 
// https://www.ogldev.org/index.html
// https://learnopengl.com/Introduction

#include<iostream>
#include<string>
#include<cmath> // IN 3D

// idea ever see that part of jarrasic park?
// #include<filesystem>

// so your going to need to use glad to make the header files/c source
// so use the online version, v2 
// or the cli can be added with pip. pip install glad2
// make glad.h might work, if i added it.
// gl 3.3
// good luck


#include <glad/gl.h>
#include<GLFW/glfw3.h>

#include "shader.h" // does shader things
#include "render.h" // does obj mangment things
#include "shapes.h" // helper functions to make shapes quicker
//#include "text.h"   // lets me write things

//cstring
#include<cstring> // for all of your suffering needs

// enum for knowing what shape gen function to call
enum shape_func {sq,sqTx,recTx,cu,tri};

#define MAX_SLIDES 6
// consts for each slide
struct SlideObject {
	enum shape_func shape; // function to run
	char *name; // name to be appened
	char *texPath;
	GLfloat *points;
};

struct Slide {
	unsigned int amt;
	struct SlideObject *obj;
};


//mallocs an array the size of the c_string 
char* mallocStr(char *in){
	const unsigned int len = strlen(in)+1;
	char *out = (char*) malloc(sizeof(char)*len);
	strcpy(out,in);
	return out;
}

GLfloat* mallocFloat(GLfloat *in,const unsigned int len){
	GLfloat *out = (GLfloat*) malloc(sizeof(GLfloat)*len);
	for(unsigned int i=0;i<len;i+=1){
		out[i] = in[i];
	}
	return out;
}

struct Slide *returnSlide0(){
  // bad way to do this but it works
  // your going to need to free this
  // https://stackoverflow.com/questions/53970133/non-static-initialization-of-a-flexible-array-member
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 2;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt+1));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText2.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  //object 1 
  slide->obj[1].shape = sq;
  char name1[] = "testCube";
  slide->obj[1].name =  mallocStr(name1);
  char path1[] = "";
  slide->obj[1].texPath = mallocStr(path1);
  GLfloat point1[] ={5.0f,-7.0f,0.0f,2.0f};
  slide->obj[1].points = mallocFloat(point1,4); 
  return slide;
}

// function to FREE US ALL BE SAVED BE FREE POINTERS
void freeSlide(struct Slide *slide){
	for(unsigned int i=0;i<slide->amt;i+=1){
		free(slide->obj[i].name);
		free(slide->obj[i].texPath);
		free(slide->obj[i].points);
	}	
	free(slide->obj);
	free(slide);
}
// placeholders are more painfull than a config file said no one ever
struct Slide **intSlides(){
	struct Slide **slides = (struct Slide**) malloc(sizeof(struct Slide*)*MAX_SLIDES);
	slides[0] = returnSlide0();
	return slides;
}
// data setting
void loadSlide(struct Slide **slides,unsigned int slide,Shader *shad,Shader *shadTx,Renderer *rend, Renderer *rendTx){
	// max number of objects
	const unsigned lim = slides[slide]->amt;
	for(unsigned int i = 0; i < lim; i+=1){
		switch (slides[slide]->obj[i].shape){
			case sq:
				rend->push(genSquare(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3]));
				break;
			case sqTx:
				rendTx->push(genTextureSqu(slides[slide]->obj[i].name,shadTx,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].texPath));
				break;
			case recTx:
				rendTx->push(genTextureRect(
				slides[slide]->obj[i].name,shadTx,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].texPath));
				break;
			case cu:
				rend->push(genCube(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].points[6]));
				break;
			case tri:
				rend->push(genTriangle(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].points[6],
				slides[slide]->obj[i].points[7],
				slides[slide]->obj[i].points[8]));
				break;

		}
	}
}


void unloadSlide(unsigned int i){

}
// END OF LOADING FUNCTIONS
// one golobal bool so i can redraw the buffer if the window if moved
bool reGenBuffer = false;
// if the user resized update the screen
void fbResizeCallback(GLFWwindow* win,int w,int h){
	glViewport(0,0,w,h);
	reGenBuffer = true;
}

// glfw startup function
GLFWwindow* intGlfw(){
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES,4);//anti aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  // debuging stuff
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  const int winW = 640;
  const int winH = 480;

  GLFWwindow* win = glfwCreateWindow(winW,winH,"SUFFER",NULL,NULL);
  glfwMakeContextCurrent(win);
  // glad
  int v;
  if (!(v=gladLoadGL((GLADloadfunc)glfwGetProcAddress))){
     std::cerr<<"ERROR::GLAD::INIT_FAILED"<<std::endl;
     return NULL;}
  std::cout<<"OpenGL Version " << GLAD_VERSION_MAJOR(v) <<"."<<GLAD_VERSION_MINOR(v) << " Loaded" << std::endl;

  // redgester the callback function
  glfwSetFramebufferSizeCallback(win,fbResizeCallback);

  //R,G,B,A
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  return win;
}

// OpenGl startup function
void intOGL(){
  //enables that anti-aliasing thingy
  glEnable(GL_MULTISAMPLE);
  // depth testing so shapes don't overlap
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // blending so textures look ok
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  intOGL();

  struct Slide *slideobj = returnSlide0();

  std::cout << slideobj->obj[0].name << std::endl;
  std::cout << slideobj->obj[1].name << std::endl;

  // window size used for matrix stuff
  int bufW,bufH;
  GLfloat scaler;// round((h/w)*(21/9))

  //slide number
  unsigned int slide = 0;
  // shaders used to render colored objects
  Shader shadCol = Shader("shaders/vertCol.vs","shaders/normal.gio","shaders/fragCol.fs");
  // shaders used with textured objects
  Shader shadTex = Shader("shaders/vertTex.vs","shaders/normal.gio","shaders/fragTex.fs");

  // render obj
  Renderer rend3d;
  Renderer rend3dt; // transperent objects need to be rendered after
  // loads the Object3D
  rend3d.push(genCube("Test Cube",&shadCol,10.0f,-7.0f,0.0f,8.4f,2.0f,0.0f,1.0f));

  rend3d.push(genCube("Test Cube2",&shadCol,0.0f,-5.0f,0.0f,1.0f,0.0f,2.0f,1.0f));

  rend3dt.push(genTextureRect("Slide0",&shadTex,21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f,"textures/SlideText2.png"));

  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0); // rebound at render loop	

  bool keyPressed = false; // key holding 
  while(!glfwWindowShouldClose(win)){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
   // window inputs
   if(glfwGetKey(win,GLFW_KEY_ESCAPE)==GLFW_PRESS){
      glfwSetWindowShouldClose(win,true);
   }if(glfwGetKey(win,GLFW_KEY_SPACE)){
   if(keyPressed==false){keyPressed=true;slide+=1;}
   }else{keyPressed=false;}

   //rend3d.get(testObj).rot(1.0f,0.0f,0.0f,0.01f);
   
   //uniforms for ambient lighting TODO shader array
   //if you need to to it twice you can use an array
   shadCol.setVec3("ambColor",1.0f,1.0f,1.0f);
   shadCol.setFloat("ambStr",0.1f);
   shadTex.setVec3("ambColor",1.0f,1.0f,1.0f);
   shadTex.setFloat("ambStr",0.1f);

   // use buffer size not window size 
   glfwGetFramebufferSize(win,&bufW,&bufH);
   scaler = getScaler(bufW,bufH);

   shadCol.setFloat("width",bufW);
   shadCol.setFloat("hight",bufH);
   shadTex.setFloat("width",bufW);
   shadTex.setFloat("hight",bufH);

   //1 means ortho, 2 might work
   rend3d.rend(1,bufW,bufH,scaler,reGenBuffer);
   rend3dt.rend(1,bufW,bufH,scaler,reGenBuffer);// transparent objects need to be rendered after
						// also ... lets me call diffrent matrixes for both
   if(reGenBuffer == true){
	reGenBuffer = false;
   }
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   }
  // cleanup
  shadCol.cleanUp();
  rend3d.cleanUp(); 
  rend3dt.cleanUp();

  glfwTerminate();
  return 0;
}
