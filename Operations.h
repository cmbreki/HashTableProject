#ifndef OPERATIONS_H
#define	OPERATIONS_H

#include "Index.h"
#include "Record.h"
#include "RecordList.h"
#include "HashTable.h"
#include "Operations.h"

void delete(HashTable * hashtable, TownList * townList, char * phone);
void insert(HashTable * hashtable, TownList * townList, Record * record);
void population(TownList * townList, char * town);
void sum(TownList * townList, char * town);
void query(HashTable * hashtable , char *  phone);
void top_deptors(TownList * townList ,char * town, int l);
void top_spender(TownList * townList);
void min(HashTable * hashtable);
void max(HashTable * hashtable);
void exit_pro(HashTable * hashtable , TownList * townList);


void last_node(TownList * townList);



#endif

