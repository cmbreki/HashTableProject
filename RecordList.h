
#ifndef RECORDLIST_H
#define	RECORDLIST_H

#include <stdlib.h>
#include <string.h>
#include "Record.h"

typedef struct Node Node;
typedef struct HeadNode HeadNode;


struct Node{
	Record * record;
	Node * next;
};


struct HeadNode{
     
    Node * firstNode;
    Node *lastNode;
     
};



void create_node(Record *, Node *);

void insert_Tolist(HeadNode * headNode, Node * node );

void delete_fromList(HeadNode * headNode , char * phone);

void initHeadNode(HeadNode * headNode );

void printList(HeadNode * headNode);

void free_node(Node * node);










#endif	/* RECORDLIST_H */

