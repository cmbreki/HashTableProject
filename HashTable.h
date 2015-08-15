#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "RecordList.h"
#include "Record.h"

typedef struct HashTable HashTable;

struct HashTable{

    int size;
    HeadNode ** table;
};



void create_table(HashTable * hashtable, int tSize);
int hashFunc(HashTable * , char * );
void set_ht(HashTable * hashtable, Node * node);
Record * find_record(HashTable * hashtable, char * phone);
void printHT(HashTable * hashtable);



#endif	/* HASHTABLE_H */

