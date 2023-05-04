// uses free type
//https://www.freetype.org/freetype2/docs/

#include <ft2build.h>
#include FT_FREETYPE_H

struct Char { 
  GLUint TID;
  sizeX;
  sizeY;
  bearingX;
  bearingY;
  unsigned int adv; // next char
}
FT_Library intFT(){
  FT_Library  library;
  
  if(FT_Init_FreeType(&library){
  std::cerr << "ERROR::FREETYPE: Unable to init" << std::endl;
  }
  return library;  
}
FT_Face intFTFont(FT_Library library,std::string fontPath){
  FT_Face face;
  if(FT_NEW_Face(library,fontPath.c_str,0,&face)){
  td::cerr << "ERROR::FREETYPE: Unable to load font face " << fontPath << std::endl;
  }
  return face;
}
std::map loadFTglyph(FT_Face face){
	std::map<char, Char> Chars;
	for (unsigned char c=0;c<128;c+=1){
	if(FT_Load_Char(fase,c,FT_LOAD_RENDER)){std::cout << "ERROR::FREETYPE: Failed to load glyph " << c << std::endl;continue}
	unsigned int text; // it's a pun
	glGenTextures(1,&text);
	glBindTexture(GL_TEXTURE_2D,text);
	    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Char character = {text,face->glyph->bitmap.width,face->glyph->bitmap.rows,face->glyph->bitmap_left,face->glyph->bitmap_top,face->glyph->advance.x};
	Chars.insert(std::pair<char, Char>(c,Char));
		}
	return Chars // return the map of char/Char
}
// text object
class objectText{
  public:
    int size;
    std::string string;
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    GLfloat z = 0.0f;

    objectText(std::string istring,GLfloat ix,GLfloat iy, GLfloat iz){
    	string = istring;
	x = ix;
	y = iy;
	z = iz;
    }

    void rend(){
    }
};



