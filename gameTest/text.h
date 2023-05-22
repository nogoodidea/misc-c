// uses free type
//https://www.freetype.org/freetype2/docs/

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <map>
struct Char { 
  GLuint TID;
  GLuint sizeX;
  GLint sizeY;
  GLint64 bearingX;
  GLint64 bearingY;
  unsigned int adv; // next char
};
FT_Library intFT(){
  FT_Library  library;
  
  if(FT_Init_FreeType(&library)){
  std::cerr << "ERROR::FREETYPE: Unable to init" << std::endl;
  }
  return library;  
}
FT_Face intFTFont(FT_Library library,std::string fontPath){
  FT_Face face;
  if(FT_New_Face(library,fontPath.c_str(),0,&face)){
  std::cerr << "ERROR::FREETYPE: Unable to load font face " << fontPath << std::endl;
  }
  return face;
}
std::map<char, Char> loadFTglyph(FT_Face face){
	std::map<char, Char> Chars;
	for (unsigned char c=0;c<128;c+=1){
	if(FT_Load_Char(face,c,FT_LOAD_RENDER)){std::cout << "ERROR::FREETYPE: Failed to load glyph " << c << std::endl;continue;}
	unsigned int text; // it's a pun
	glGenTextures(1,&text);
	glBindTexture(GL_TEXTURE_2D,text);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Char character = {text,face->glyph->bitmap.width,face->glyph->bitmap.rows,face->glyph->bitmap_left,face->glyph->bitmap_top,face->glyph->advance.x};
	std::cout << (unsigned char) text << character.sizeX << character.sizeY << character.bearingX << character.bearingY << std::endl;

	Chars.insert(std::make_pair(c,character));
		}
	return Chars; // return the map of char/Char
}
// text object
class objectText{
  public:
    int size;
    std::string string;
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    GLfloat z = 0.0f;
    Shader *shad=NULL;
    std::map<char, Char> font;

    objectText(Shader *ishad,std::string istring,GLfloat ix,GLfloat iy, GLfloat iz,std::map<char,Char> ifont){
    	string = istring; // apparently this works 
      std::cout << "ptr0: " << &string << " ptr1: " << &istring << std::endl;
	    x = ix;
	    y = iy;
	    z = iz;
	    font = ifont;
      shad = ishad;
    }

    void rend(GLfloat scale){
       GLuint VBO; //TODO come up with a better system then regenarating every textUre every frame
       std::string::const_iterator c;
       for(c=string.begin();c!=string.end();c++){
	        Char ch = font[*c];
		      GLfloat xpos = x + ch.bearingX;
          		GLfloat ypos = y + ch.bearingY;
		      GLfloat w = ch.sizeX*scale;
		      GLfloat h = ch.sizeY*scale;

		      GLfloat vert[] = {
            xpos,     ypos + h, 1.0f,1.0f,1.0f,  0.0f, 0.0f,            
            xpos,     ypos, 1.0f,1.0f,1.0f,      0.0f, 1.0f,
            xpos + w, ypos, 1.0f,1.0f,1.0f,       1.0f, 1.0f,

            xpos,     ypos + h, 1.0f,1.0f,1.0f,  0.0f, 0.0f,
            xpos + w, ypos, 1.0f,1.0f,1.0f,      1.0f, 1.0f,
            xpos + w, ypos + h, 1.0f,1.0f,1.0f,  1.0f, 0.0f          
        	};
		    glBindTexture(GL_TEXTURE_2D,ch.TID);
    
        glGenBuffers(1,&VBO);
		    glBindBuffer(GL_ARRAY_BUFFER,VBO);
		
        glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*7,(void*)vert,GL_STATIC_DRAW);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,7*sizeof(GLfloat),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,7*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,7*sizeof(GLfloat),(void*)(5*sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
		    glBindBuffer(GL_ARRAY_BUFFER,0);

		    glDrawArrays(GL_TRIANGLES,0,6);
		    x += (ch.adv >> 6)*scale; //????? majic code is majjic looks like bit shifting
       }
       glBindVertexArray(0);
       glBindTexture(GL_TEXTURE_2D, 0);
    }
};



