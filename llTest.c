#include<stdio.h>
#include<stdlib.h>

//linked list struct
struct node {
  int value;
  struct node* next;
};
typedef struct node node_t;

//prints all values in the linked list starting from prt head
void nodeList(node_t *head){
  node_t *temp=head;
  while(temp!=NULL){
    printf("%i|",temp->value);
    temp = temp->next;
  }
}

//Appends a node to the end of the linked list starting at head
void nodeAppend(node_t *head,node_t *node){
  node_t *temp=head;
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
void nodeAppendAfterNode(node_t *target,node_t *nodeToAppend){
  nodeToAppend->next=target->next;
  target->next=nodeToAppend;
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
  node->next=NULL;
  node->value=in;
  return node;
}

//frees the linked list
void nodeFree(node_t *head){
  node_t *temp;
  while(head!=NULL){
    temp=head;
    head=head->next;
    free(temp);
  }
}

//main
int main(int argc,char **argv){
  node_t *head;
  head = nodeGenerate(0);

  // add new nodes to the list
  nodeAppend(head,nodeGenerate(2));
  nodeAppend(head,nodeGenerate(2));
  nodeAppend(head,nodeGenerate(4));
  nodeAppendHead(&head,nodeGenerate(20));
  nodeAppendAfterNode(nodeSearch(head,2),nodeGenerate(55));
  nodeList(head);

  node_t *node = nodeSearch(head,4);
  if(node==NULL){
    printf("nodeSearch Failed!!\n");
  }else{
    printf("nodeSearch Returned %p\n",node);
  }

  printf("\n");
  nodeFree(head);
  return 0;
}
