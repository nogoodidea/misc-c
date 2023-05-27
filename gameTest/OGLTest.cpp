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
enum tran_func {rot,rotA,tran,scal};

#define MAX_SLIDES 6
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
	unsigned int amt;
  unsigned int funcAmt;
	struct SlideObject *obj;
  struct FuncObject *func;
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
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->amt+1));
  char name2[] = "testCube";
  slide->func[0].name = mallocStr(name2);
  slide->func[0].func = rot;
  GLfloat point2[] = {0.1f,0.1f,1.0f,0.001f};
  slide->func[0].points = mallocFloat(point2,4);
  return slide;
}
struct Slide *returnSlide1(){
  struct Slide *slide = (struct Slide*) malloc(sizeof(struct Slide));
  slide->amt = 1;
  slide->obj = (struct SlideObject*) malloc(sizeof(struct SlideObject)*(slide->amt+1));
  slide->obj[0].shape = recTx;
  char name0[] = "slideText";
  slide->obj[0].name =  mallocStr(name0);
  char path0[] = "textures/SlideText1.png";
  slide->obj[0].texPath = mallocStr(path0);
  GLfloat point0[] = {21.0f,9.0f,0.0f,-21.0f,-9.0f,0.0f};
  slide->obj[0].points = mallocFloat(point0,6);
  // function section
  slide->funcAmt = 0;
  slide->func = (struct FuncObject*) malloc(sizeof(struct FuncObject)*(slide->amt+1));
  return slide;
}
// function to FREE US ALL BE SAVED BE FREE POINTERS
void freeSlide(struct Slide *slide){
	for(unsigned int i=0;i<slide->amt;i+=1){
		free(slide->obj[i].name);
		free(slide->obj[i].texPath);
		free(slide->obj[i].points);
	}	
	for(unsigned int i=0;i<slide->funcAmt;i+=1){
		free(slide->func[i].name);
		free(slide->obj[i].points);
	}
	free(slide->obj);
	free(slide->func);
	free(slide);
}
// placeholders are more painfull than a config file said no one ever
struct Slide **intSlides(){
	struct Slide **slides = (struct Slide**) malloc(sizeof(struct Slide*)*MAX_SLIDES);
	slides[0] = returnSlide0();
	slides[1] = returnSlide0();
  slides[2] = returnSlide0();
	return slides;
}
// data setting
void loadSlide(struct Slide **slides,unsigned int slide,Shader *shad,Shader *shadTx,Renderer *rend, Renderer *rendTx){
	// max number of objects
	const unsigned int lim = slides[slide]->amt;
	for(unsigned int i = 0; i < lim; i+=1){
		std::cout << "ADD: " << slides[slide]->obj[i].name << std::endl;
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
	std::cout << "Slide: " << slide << " loaded" << std::endl;
}
void runSlide(struct Slide **slides,unsigned int slide,Renderer rend,Renderer rendTx){
	const unsigned int lim = slides[slide]->funcAmt;
	int rendArrI=0;
  int obj;
	Renderer rendArr[] = {rend,rendTx};
	for(unsigned int i = 0; i < lim; i+=1){
	  rendArrI=0;
	  obj = rend.search(slides[slide]->func[i].name);
    	  if(obj == -1){ obj = rendTx.search(slides[slide]->func[i].name);rendArrI=1;}
	  //{rot,rotA,tran,scal};
	  switch(slides[slide]->func[i].func){
		  case rot:
			  rendArr[rendArrI].get(obj)->rot(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2],
				slides[slide]->func[i].points[3]);
				break;
		  case rotA:
			  rendArr[rendArrI].get(obj)->rotA(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2],
				slides[slide]->func[i].points[3]);
				break;
		  case tran:
			rendArr[rendArrI].get(obj)->trans(slides[slide]->obj[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2]);
				break;
		  case scal:
			rendArr[rendArrI].get(obj)->scale(
				slides[slide]->func[i].points[0],
				slides[slide]->func[i].points[1],
				slides[slide]->func[i].points[2]);
				break;
	  	}
	  }
}


void unloadSlide(struct Slide **slides,unsigned int slide,Renderer rend,Renderer rendTx){
  const unsigned int lim = slides[slide]->amt;
  int rendArrI=2;
  int obj;
	Renderer rendArr[] = {rend,rendTx};
  for(unsigned int i = 0; i < lim; i+=1){
	  rendArrI=2;

	  obj = rend.search(slides[slide]->func[i].name);	  
    if(obj == -1){obj = rendTx.search(slides[slide]->func[i].name);
      if(obj != -1){rendArrI=1;}
    }
    else{rendArrI=0;}

    if(rendArrI != 2){
    rendArr[i].del(obj);
    }
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
  Renderer rend3d;
  Renderer rend3dt; // transperent objects need to be rendered after

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
		unloadSlide(slideobj,slide,rend3d,rend3dt);
		slide+=1;
		loadSlide(slideobj,slide,&shadCol,&shadTex,&rend3d,&rend3dt);
   		}
   	}else{keyPressed=false;}


   runSlide(slideobj,slide,rend3d,rend3dt);

   // use buffer size not window size 
   glfwGetFramebufferSize(win,&bufW,&bufH);
   scaler = getScaler(bufW,bufH);

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
