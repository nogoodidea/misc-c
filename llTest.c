#include<stdio.h>
#include<stdlib.h>

//linked list struct
struct node {
  int value;
  struct node *prev;
  struct node *next;
};
typedef struct node node_t;

//prints all values in the linked list starting from prt head
void nodeListPrint(node_t *head){
  node_t *temp=head;
  while(temp!=NULL){
    printf("%i|",temp->value);
    temp = temp->next;
  }
  printf("\n");
}

//Appends a node to the end of the linked list starting at head
void nodeAppendTail(node_t *head,node_t *node){
  node_t *temp=head;
  while(temp->next!=NULL){
    temp = temp->next;
  } 
  temp->next = node;
  node->prev = temp;
}

//Appends a node to the front of the linked list
void nodeAppendHead(node_t **head,node_t *node){
  node->next = *head;
  (*head)->prev = node;
  *head = node;
}

//Appends a node after the taget node
void nodeAppendAfter(node_t *target,node_t *node){
  node->next=target->next;
  node->prev=target;
  target->next=node;
  node->next->prev = node;
}

//finds a node by checking int, returns a pointer to the node, returns NULL on error
node_t *nodeSearch(node_t *head,int value){
  node_t *node=NULL;
  node_t *temp=head;
  while(temp!=NULL){
    if(temp->value==value){
      node=temp;
      break;
    }
    temp=temp->next;
  }
  return node;
}

//genrates a node with malloc
node_t *nodeGenerate(int in){
  node_t *node = malloc(sizeof(node_t));
  if(node == NULL){// malloc checker
    fprintf(stderr,"ERROR:Malloc returned null");
  }
  node->next=NULL;
  node->prev=NULL;
  node->value=in;
  return node;
}

//frees all of the linked list
void nodeFreeAll(node_t *head){
  node_t *temp;
  while(head!=NULL){
    temp=head;
    head=head->next;
    free(temp);
  }
}

//frees node by node pointer
void nodeFree(node_t **head,node_t *node){
  node_t *temp = *head;
  if(*head == node){
    *head = temp->next;
    (*head)->prev = NULL;
    free(temp);
  }else{
    node_t *temp = *head;
    while(temp != NULL && temp != node){
      temp=temp->next;
    }
    if(temp == NULL){return;}// can't find it return
    temp->prev->next = temp->next;
    if(temp->next != NULL){
      temp->next->prev = temp->prev;
    }
    free(temp);
  }
}

//checks the linked list genaration, runs the linked list fowards then backwards to see if we return to the head
//or if we see the same pointer 2 times in a row
//does not find multi entry errors
// returns 0 if no error
// 1 if error
int nodeListCheck(node_t *head){
  node_t *temp = head;
  node_t *temp_old;
  while(temp!=NULL){
    if(temp == temp->next){
      return 1;
    }
    printf("|>%i",temp->value);
    temp_old = temp;
    temp = temp->next;
  }
  temp = temp_old;
  while(temp->prev!=NULL){
    if(temp == temp->prev){
      return 1;
    }
    printf("|<%i",temp->value);
    temp_old = temp;
    temp = temp->prev;
  }
  if(temp_old != head){
    return 1;
  } else{
    return 0;
  }
}

//main
int main(int argc,char **argv){
  node_t *head;
  head = nodeGenerate(0);

  nodeListPrint(head);
  
  // add new nodes to the list
  nodeAppendTail(head,nodeGenerate(2));
  nodeAppendTail(head,nodeGenerate(2));
  nodeAppendTail(head,nodeGenerate(4));
  nodeAppendHead(&head,nodeGenerate(20));
  nodeAppendAfter(nodeSearch(head,2),nodeGenerate(55));
  nodeListPrint(head);
 
  //nodeFree(&head,nodeSearch(head,2));
  
  //nodeListPrint(head);
  
  if(nodeListCheck(head)){
    printf("linked list passed sanity check\n");
  }else{
    printf("error linked list failed sanity check\n");
  }
  
  nodeFreeAll(head);
  return 0;
}
