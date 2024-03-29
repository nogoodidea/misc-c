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
#include "linked.h" // linked list, reused from llTest.c

//cstring
#include<cstring> // for all of your suffering needs

// enum for knowing what shape gen function to call
enum shape_func {sq,sqTx,recTx,cu,tri};
enum tran_func {rot,rotA,tran,scal};

#define MAX_SLIDES 11
// consts for each slide
struct SlideObject {
	enum shape_func shape; // function to run
	char *name; // name to be appened
	char *texPath;
	GLfloat *points;
};

struct FuncObject {
	enum tran_func func; // function to run
	char *name; // name to be checked
	GLfloat *points; // points as args
};

struct Slide {
	size_t amt;
  	size_t funcAmt;
	struct SlideObject *obj;
  struct FuncObject *func;
};


//mallocs an array the size of the c_string 
char* mallocStr(char *in){
	const unsigned int len = strlen(in);
	char *out = (char*) malloc(sizeof(char)*(len+1));
	for(unsigned int i=0;i<len;i+=1){
		out[i] = in[i];
	}
	out[len] = '\0';
	return out;
}

GLfloat* mallocFloat(GLfloat *in,const unsigned int len){
	GLfloat *out = (GLfloat*) malloc(sizeof(GLfloat)*(len+1));
	for(unsigned int i=0;i<len;i+=1){
		out[i] = in[i];
	}
	return out;
}

//slide 0 alloc
struct Slide *returnSlide0(){
  // bad way to do this but it does not work
  // your going to need to free this
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 2;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText0.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  //object 1 
  slide->obj[1].shape = cu;
  char name1[] = "testCube";
  slide->obj[1].name =  mallocStr(name1);
  char path1[] = "";
  slide->obj[1].texPath = mallocStr(path1);
  GLfloat point1[] ={10.0f,-7.0f,0.0f,4.0f,1.0f,0.5f,0.0f};
  slide->obj[1].points = mallocFloat(point1,7); 
  // function section
  slide->funcAmt = 1;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  char name2[] = "testCube";
  slide->func[0].name = mallocStr(name2);
  slide->func[0].func = rot;
  GLfloat point2[] = {0.4f,0.1f,1.0f,0.1f};
  slide->func[0].points = mallocFloat(point2,4);
  return slide;
}

//silde 1 alloc
struct Slide *returnSlide1(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText1.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 2 alloc
struct Slide *returnSlide2(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText2.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 3 alloc
struct Slide *returnSlide3(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText3.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 4 alloc
struct Slide *returnSlide4(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText4.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 5 alloc
struct Slide *returnSlide5(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText5.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 6 alloc
struct Slide *returnSlide6(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText6.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 2;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  char name2[] = "slideText";
  slide->func[0].name = mallocStr(name2);
  slide->func[0].func = scal;
  GLfloat point2[] = {1.001f,1.001f,1.0f,100.0f,0.0f};
  slide->func[0].points = mallocFloat(point2,5);
  slide->func[1].name = mallocStr(name2);
  slide->func[1].func = rot;
  GLfloat point3[] = {0.0f,0.0f,1.0f,0.001f};
  slide->func[1].points = mallocFloat(point3,4);
  return slide;
}

//silde 7 alloc
struct Slide *returnSlide7(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText7.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 8 alloc
struct Slide *returnSlide8(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText8.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 9 alloc
struct Slide *returnSlide9(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 2;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText9.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  
  slide->obj[1].shape = tri;
  char name1[] = "tri";
  slide->obj[1].name =  mallocStr(name1);
  char path1[] = "";
  slide->obj[1].texPath = mallocStr(path1);
  GLfloat point1[] = {4.5f,4.5f,-1.0f,6.5f,6.5f,-1.0f,4.5f,6.5f,-1.0f};
  slide->obj[1].points = mallocFloat(point1,9);

  // function section
  slide->funcAmt = 1;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  slide->func[0].name = mallocStr(name1);
  slide->func[0].func = rot;
  GLfloat point2[] = {0.0f,0.0f,1.0f,0.1f};
  slide->func[0].points = mallocFloat(point2,4);
  return slide;
}

//silde 10 alloc
struct Slide *returnSlide10(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText10.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

//silde 11 alloc
struct Slide *returnSlide11(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/testTexture.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->funcAmt));
  return slide;
}

// function to FREE US ALL BE SAVED BE FREE POINTERS
void freeSlide(struct Slide *slide){
	for(size_t i=0;i<slide->amt;i+=1){
		free(slide->obj[i].name);
		free(slide->obj[i].texPath);
		free(slide->obj[i].points);
	}	
	for(size_t i=0;i<slide->funcAmt;i+=1){
		free(slide->func[i].name);
		free(slide->func[i].points);
	}
	free(slide->obj);
	free(slide->func);
	free(slide);
}

// warper to call freeSlide on every slides
void freeSlides(struct Slide **slides){
  for(size_t i = 0; i < MAX_SLIDES+1;i+=1){
    freeSlide(slides[i]);
    std::cout << "Freeing Slide: " << i << std::endl;
  }
  free(slides);
}

// placeholders are more painfull than a config file said no one ever
struct Slide **intSlides(){
	struct Slide **slides = (struct Slide**) malloc(sizeof(struct Slide*)*(MAX_SLIDES+1));//1+ so we get the right amount of memory
	slides[0] = returnSlide0();
	slides[1] = returnSlide1();
  slides[2] = returnSlide2();
	slides[3] = returnSlide3();
	slides[4] = returnSlide4();
  slides[5] = returnSlide5();
	slides[6] = returnSlide6();
	slides[7] = returnSlide7();
  slides[8] = returnSlide8();
	slides[9] = returnSlide9();
	slides[10] = returnSlide10();
  slides[11] = returnSlide11();
	return slides;
}
// data setting
void loadSlide(struct Slide **slides,unsigned int slide,Shader *shad,Shader *shadTx,node_t **rend, node_t **rendTx){
	// max number of objects
	const size_t lim = slides[slide]->amt;
	for(size_t i = 0; i < lim; i+=1){
		std::cout << "ADD: " << slides[slide]->obj[i].name << std::endl;
		switch (slides[slide]->obj[i].shape){
			case sq:
				nodeAppendTail(rend,nodeGenerate(genSquare(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3])));
				break;
			case sqTx:
				nodeAppendTail(rendTx,nodeGenerate(genTextureSqu(slides[slide]->obj[i].name,shadTx,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].texPath)));
				break;
			case recTx:
				nodeAppendTail(rendTx,nodeGenerate(genTextureRect(
				slides[slide]->obj[i].name,shadTx,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].texPath)));
				break;
			case cu:
				nodeAppendTail(rend,nodeGenerate(genCube(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].points[6])));
				break;
			case tri:
				nodeAppendTail(rend,nodeGenerate(genTriangle(slides[slide]->obj[i].name,shad,
				slides[slide]->obj[i].points[0],
				slides[slide]->obj[i].points[1],
				slides[slide]->obj[i].points[2],
				slides[slide]->obj[i].points[3],
				slides[slide]->obj[i].points[4],
				slides[slide]->obj[i].points[5],
				slides[slide]->obj[i].points[6],
				slides[slide]->obj[i].points[7],
				slides[slide]->obj[i].points[8])));
				break;
		}
	}
	std::cout << "Slide: " << slide << " loaded" << std::endl;
}

void runSlide(struct Slide **slides,unsigned int slide,node_t **rend,node_t **rendTx){
	const size_t lim = slides[slide]->funcAmt;
  node_t *obj;
	for(size_t i = 0; i < lim; i+=1){
	obj = nodeSearch((*rend),slides[slide]->func[i].name);
    	if(obj == NULL){
	  obj = nodeSearch((*rendTx),slides[slide]->func[i].name);
	  if(obj == NULL){continue;}
			
	}
    		  //{rot,rotA,tran,scal};
	  switch(slides[slide]->func[i].func){
		  case rot:
			  obj->value->rot(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2],
				slides[slide]->func[i].points[3]);
				break;
		  case rotA:
			  obj->value->rotA(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2],
				slides[slide]->func[i].points[3]);
				break;
		  case tran:
			obj->value->trans(slides[slide]->obj[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2]);
				break;
		  case scal:
     	slides[slide]->func[i].points[4] += 0.1f;
      if(slides[slide]->func[i].points[4] >= slides[slide]->func[i].points[3]){
			obj->value->scale(
				fabsf(slides[slide]->func[i].points[0]-2),
				fabsf(slides[slide]->func[i].points[1]-2),
				fabsf(slides[slide]->func[i].points[2]-2));
      if(slides[slide]->func[i].points[4] >= slides[slide]->func[i].points[3]*2){slides[slide]->func[i].points[4]=0.0f;}
      }else{
			obj->value->scale(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2]);
        }
				break;
	  	}
	  }
}

void unloadSlide(struct Slide **slides,unsigned int slide,node_t **rend,node_t **rendTx){
  std::cout << "Slide: " << slide << " try unload" << std::endl;
  const size_t lim = slides[slide]->amt;
  node_t *obj;
  for(size_t i = 0; i < lim; i+=1){
    obj = nodeSearch((*rend),slides[slide]->obj[i].name);
    if(obj == NULL){
      obj = nodeSearch((*rendTx),slides[slide]->obj[i].name);
      if(obj == NULL){continue;}
      else{nodeFree(rendTx,obj);}      
    }else{nodeFree(rend,obj);}
  }
  std::cout << "Slide: " << slide << " unloaded" << std::endl;
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

//Gens Scaler for screen size scaleing
GLfloat getScaler(GLfloat w,GLfloat h){
  GLfloat fw=floorf(w/42);
  GLfloat fh=floorf(h/18);
  if(fw<=fh){return fw;}
  else{return fh;}
}

int main(int argc, char** argv){
  // int GLFW/GLAD
  GLFWwindow* win = intGlfw();
  if(win==NULL){std::cerr<<"ERROR::GLFW::WINDOW_CREATION"<<std::endl;
    glfwTerminate(); // can't recover from it
    _Exit(1);}

  intOGL();

  // loads all the slides into ram
  struct Slide **slideobj = intSlides();

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
  node_t *rend3d = NULL;
  node_t *rend3dt = NULL; // transperent objects need to be rendered after

  loadSlide(slideobj,slide,&shadCol,&shadTex,&rend3d,&rend3dt);

  bool keyPressed = false; // key holding 
  while(!glfwWindowShouldClose(win)){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
   // window inputs
   if(glfwGetKey(win,GLFW_KEY_ESCAPE)==GLFW_PRESS){
      glfwSetWindowShouldClose(win,true);
   }
   
   if(glfwGetKey(win,GLFW_KEY_SPACE)){
   	if(keyPressed==false){keyPressed=true;
		unloadSlide(slideobj,slide,&rend3d,&rend3dt);
    if(glfwGetKey(win,GLFW_KEY_LEFT_SHIFT)){
      if(slide == 0){slide=MAX_SLIDES;}
      else{slide-=1;}
    }else if(slide==MAX_SLIDES){slide = 0;
    }else{slide+=1;}
		loadSlide(slideobj,slide,&shadCol,&shadTex,&rend3d,&rend3dt);
   		}
   	}else{keyPressed=false;}

   runSlide(slideobj,slide,&rend3d,&rend3dt);

   // use buffer size not window size 
   glfwGetFramebufferSize(win,&bufW,&bufH);
   scaler = getScaler(bufW,bufH);

   //1 means ortho, 2 might work
   nodeRender(rend3d,1,bufW,bufH,scaler,reGenBuffer);
   nodeRender(rend3dt,1,bufW,bufH,scaler,reGenBuffer);// transparent objects need to be rendered after
   
   if(reGenBuffer == true){
	reGenBuffer = false;
   }
   
   glfwSwapBuffers(win);
   glfwPollEvents();
   }
  // cleanup
  shadCol.cleanUp();
  shadTex.cleanUp();
  nodeFreeAll(rend3d); 
  nodeFreeAll(rend3dt);
  freeSlides(slideobj);

  glfwTerminate();
  return 0;
}
