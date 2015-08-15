#ifndef INDEX_H
#define	INDEX_H

#include "Record.h"

typedef struct TownList TownList;
typedef struct TownListNode TownListNode;
typedef struct RPNode  RPNode;

struct TownListNode{
    
    char   * town;
    int    population;
    float   totalMoney;
    RPNode * rpNode;
    TownListNode * nextTown;    
};


struct TownList{
    
    int size;
    TownListNode * fnode;
    TownListNode * lnode;
};


struct RPNode{
    Record * record;
    RPNode * next;
};

/* TownList functions*/

void init_TownList(TownList * townList);
void destroy_TownList(TownList * townList);

/*TownListNode functions*/

void create_TownListNode(TownListNode * townListNode, Record * record);
TownListNode * search_town(TownList * townList, char * town);
void insert_TownListNode(TownList *townList , TownListNode * townListNode);
void delete_TownListNode(TownList  * townList);
void free_TownListNode(TownListNode * townListNode);


/*RPNode functions*/

void insert_RP(TownListNode * townListNode , RPNode * rpNode);
void print_RPList(TownList *townList);
void delete_RP(TownListNode * townListNode , char * phone);
void free_RP(RPNode * rpNode);



#endif

