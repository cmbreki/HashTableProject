#include <stdio.h>

#include "Record.h"
#include "RecordList.h"
#include "HashTable.h"


void create_ht (HashTable * hashtable , int size){

    int i;
    
    /*Allocate memory for the headnodes pointers*/
    hashtable->table=malloc(sizeof(HeadNode *)*size);
    if(hashtable->table==NULL){return ;}
    
    for(i=0; i<size; i++){
        hashtable->table[i]=NULL;
    }
    
    hashtable->size=size;
    
   // printf("The hashtable creation success \n");
}

int hashFunc(HashTable * table , char * phone ){

long long ph;    
int val;

ph=atoll(phone);
val=ph%10000;

//printf("The cell no is %d \n",val%table->size);
return val%table->size;

}


void set_ht( HashTable * hashtable, Node * node){

    int cell=0;
    
    HeadNode * headNode;
    
    
    cell=hashFunc(hashtable,node->record->phone);
    
    
    if((hashtable->table[cell])== NULL) {
         
        headNode=(HeadNode *)malloc(sizeof(HeadNode));
        initHeadNode(headNode);
        hashtable->table[cell]=headNode;
        insert_Tolist(headNode,node);
        
    }
    
    else
    {
        
        insert_Tolist(hashtable->table[cell],node);
        
    }
       
        
    
}
    

void printHT(HashTable * hashtable){
    int i;
    
    for(i=0;i<hashtable->size;i++){
        if(hashtable->table[i]==NULL){
            printf("No records \n");}
        else{
        printf("Cell NO: %d \n",i);    
        printList(hashtable->table[i]);}
        
        printf("*********************** \n\n");
    }

   }

Record * find_record(HashTable * hashtable, char * phone){
    
    HeadNode * headNode;
    Node * node;
    int cell;
    Record * rec=NULL;
    
    cell=hashFunc(hashtable,phone);
    
    headNode=hashtable->table[cell];
    
    if(headNode==NULL){
       // printf("find_record: The HeadNode is NULL\n");
        return NULL;
    }
    
    
    node=headNode->firstNode;
    
    if(node==NULL){
       //printf("find_record: The List is empty\n");
        return NULL;
    }
    
    while(node!=NULL){
       
        if(strcmp(node->record->phone,phone)==0){
         
           // printf("find_record: The record is found\n");
            rec=node->record;
            return rec;
        }
      
      node=node->next;
    
    }
    
    if(rec==NULL){
      //printf("find_record:No record found \n");
      return rec;
    }
}
    
    
    


