#include "Record.h"
#include "RecordList.h"
#include <stdio.h>


void create_node(Record * record, Node * node){

 
   if(node==NULL || record==NULL)
       return ;
	  
          node->record=record;
	  node->next=NULL;
          //printf("Node creation success\n");
	 	
		
}

void insert_Tolist(HeadNode * headNode, Node * node ){

    if(headNode==NULL || node==NULL)
       return ;
    
    if(headNode->firstNode == NULL)
    {
    
        headNode->firstNode=node;
        headNode->lastNode=node;
       // printf("The first node has been inserted \n");
        
    }
    else{
        
        headNode->lastNode->next=node;
        headNode->lastNode=node;
        
        //printf("A node has been inserted \n");
        
     }
    
 }

void printList(HeadNode * headNode){

    Node *temp;
    temp=headNode->firstNode;
    
    while(temp!=NULL){
    
   printf("%s %s %s %s %f\n",temp->record->phone,temp->record->lastname,temp->record->firstname,temp->record->town,temp->record->amount);
    temp=temp->next; 
    }
}

void delete_fromList(HeadNode * headNode , char * phone){
    
    int found=0;
    
    if(headNode==NULL){
        return;
    }
    
    Node *tmp,*prev;
    tmp=headNode->firstNode;
    prev=headNode->firstNode;
    
     if(headNode->firstNode== NULL){
         found=1;
        // printf("delete_fromList: No Record List\n");
         return;
     }
    
    
    if((strcmp(tmp->record->phone,phone)==0) ){
              found=1;
              
                if( headNode->firstNode == headNode->lastNode){
                  headNode->lastNode=NULL;
                  headNode->firstNode=NULL;
                 // printf(" delete_fromList: The last record has been deleted from the Record List\n");
                }
              headNode->firstNode=tmp->next;
              free_node(tmp);
             // printf(" delete_fromList: A record has been deleted from the Record List top\n");
              return;
    }
    
    tmp=tmp->next;
    
    while(tmp!=NULL){
        
        if((strcmp(tmp->record->phone,phone)==0) ){
            found=1;
               if (tmp->next==NULL){
                  headNode->lastNode=prev;
               }
            
            prev->next=tmp->next;
            free_node(tmp);
           // printf(" delete_fromList: A record has been deleted for RecordList \n");
            return;
        }
        
        prev=tmp;
        tmp=tmp->next;
        
    }
     
    if(found==0)
    {
        printf("delete_fromList:No record found");
    
    }
        
}


void free_node(Node * node){
       
    free(node->record);
    node->record==NULL;
    free(node);
    node==NULL;
   // printf("free an node \n");
}


 void initHeadNode(HeadNode * headNode ){
 
     if(headNode==NULL){
      printf("No head node\n");
       return;}
     
     headNode->firstNode=NULL;
     headNode->lastNode=NULL;
 
 }