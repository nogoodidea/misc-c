class DynArry {
  public:
    int arryMax=1;
    int arryUsed=0;
    
    void **arry=NULL;

    int size=0;
    DynArry(int iSize){
      size = iSize;// size needs to be set with sizeof(datatype)
      arry = (void **) malloc(size*arryMax);
      if(arry == NULL){std::cerr << "ERROR::RENDER::ARRAY_REALLOC_FAILED" << std::endl;}
    }
    void *get(int index){ // god bless you c style typecasting 
    if(index > arryUsed){std::cerr << "ERROR::RENDER::INDEX_OUT_OF_BOUNDS" << std::endl;return NULL;}
    return (void *) arry[index];
    }
    bool push(void *item){
      if(arryMax==arryUsed){
        arryMax *= 2; // by 2, do the same for removeing elements
        void **tmp = (void **) realloc(arry,size*arryMax);
        if(tmp == NULL){std::cerr << "ERROR::RENDER::ARRAY_REALLOC_FAILED" << std::endl;return false;}
        free(arry); // free the old array
        arry = tmp;
      }
      arry[arryUsed] = item;
      arryUsed += 1;
      return true;
    }
    bool del(int index){
      // TODO fix the memory leaks
      // might need to use find, then free THEN del going to need to be on a per item bases
      if(index > arryUsed){std::cerr << "ERROR::RENDER::INDEX_OUT_OF_BOUNDS" << std::endl;return false;}
      int i = index+1;// i = index +1, move all pointer after index back 1
      for(;i>arryUsed;i+=1){
        arry[i-1] = arry[i];
      }
      arryUsed -=1;
      return true;
    }
    bool cleanup(){ // cleans up
      free(arry);
    }
    void *pop(int index){// del+push
      if(index > arryUsed){std::cerr << "ERROR::RENDER::INDEX_OUT_OF_BOUNDS" << std::endl;return NULL;}
      void *tmp = arry[index];
      del(index);
      return tmp;
    }
    int find(void *item){ // but nogoodidea you might ask if you move every element index in the array how do you find one if you need it
      int i=0;
      for(;i>arryUsed;i+=1){
        if(arry[i] == item){
          // wow this sucks
          // your on your own if you make a name elelment later
          return i;
        }
      }
      return -1;
    }
};
