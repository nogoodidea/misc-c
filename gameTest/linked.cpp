#include"render.h"

//linked list struct
struct node {
  Object3D *value;
  struct node *next;
};
typedef struct node node_t;

//prints all values in the linked list starting from prt head
void nodeListPrint(node_t *head){
  node_t *temp=head;
  while(temp!=NULL){
    std::cout << temp->value->name << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

//Appends a node to the end of the linked list starting at head
void nodeAppendTail(node_t **head,node_t *node){
  if(*head == NULL){*head=node;return;}// if the head is NULL set the node to it
  node_t *temp=*head;
  while(temp->next!=NULL){
    temp = temp->next;
  } 
  temp->next = node;
}

//Appends a node to the front of the linked list
void nodeAppendHead(node_t **head,node_t *node){
  node->next = *head;
  *head = node;
}

//Appends a node after the taget node
void nodeAppendAfter(node_t *target,node_t *node){
  node->next=target->next;
  target->next=node;
}

//finds a node by checking int, returns a pointer to the node, returns NULL on error
node_t *nodeSearch(node_t *head,std::string value){
  node_t *node=NULL;
  node_t *temp=head;
  while(temp!=NULL){
    if(temp->value == NULL){continue;}//hopefully will never happen
    if(temp->value->name.compare(value)==0){
      node=temp;
      break;
    }
    temp=temp->next;
  }
  return node;
}

//genrates a node with malloc
node_t *nodeGenerate(Object3D *in){
  node_t *node = (node_t*) malloc(sizeof(node_t));
  if(node == NULL){// malloc checker
    std::cerr << "ERROR:Malloc returned null" << std::endl;
    return NULL;
  }
  node->next=NULL;
  node->value=in;
  return node;
}

//frees all of the linked list
void nodeFreeAll(node_t *head){
  node_t *temp;
  while(head!=NULL){
    temp=head;
    head=head->next;
    temp->value->cleanUp();
    delete (temp->value);
    temp->value= NULL;
    free(temp);
  }
}

//frees node by node pointer
void nodeFree(node_t **head,node_t *node){
  node_t *temp = *head;
  if(*head == node){
    (*head) = temp->next;
    temp->value->cleanUp();
    delete (temp->value);
    temp->value = NULL;
    free(temp);
  }else{
    node_t *prevNode = NULL;
    while(temp != NULL && temp != node){
      prevNode = temp;
      temp=temp->next;
    }
    if(temp == NULL){return;}// can't find it return
    prevNode->next = temp->next;
    temp->value->cleanUp();
    delete (temp->value);
    temp->value = NULL;
    free(temp);
  }
}

//calls render function on Object3D
void nodeRender(node_t *head,int p,GLfloat w,GLfloat h,GLfloat s,bool reGenBuffer){
  node_t *temp;
  temp = head;
  while(temp!=NULL){
    temp->value->rend(p,w,h,s,reGenBuffer);
    temp = temp->next;
  }
}

//EOF
