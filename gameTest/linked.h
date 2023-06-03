#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<iostream>

#include "render.h"

struct node {
  Object3D *value;
  struct node *prev;
  struct node *next;
};
typedef struct node node_t;

//prints all values in the linked list starting from prt head
void nodeListPrint(node_t *head);

//Appends a node to the end of the linked list starting at head
void nodeAppendTail(node_t **head,node_t *node);

//Appends a node to the front of the linked list
void nodeAppendHead(node_t **head,node_t *node);

//Appends a node after the taget node
void nodeAppendAfter(node_t *target,node_t *node);

//finds a node by checking int, returns a pointer to the node, returns NULL on error
node_t *nodeSearch(node_t *head,std::string value);

//genrates a node with malloc
node_t *nodeGenerate(Object3D *in);

//frees node by node pointer
void nodeFree(node_t **head,node_t *node);

//frees all of the linked list
void nodeFreeAll(node_t *head);

//calls render function on Object3D
void nodeRender(node_t *head,int p,GLfloat w,GLfloat h,GLfloat s,bool reGenBuffer);

#endif //LINKED_LIST_H
