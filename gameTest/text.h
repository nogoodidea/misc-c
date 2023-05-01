// uses free type
//https://www.freetype.org/freetype2/docs/

#include <ft2build.h>
#include FT_FREETYPE_H


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
// text object
class objectText{
  public:
  int size;
  

};
struct Char { 
  GLUint TID;
}
