#include <stdio.h>
#include <stdlib.h>
#include "Record.h"
#include "RecordList.h"
#include "HashTable.h"
#include "Index.h"
#include "Operations.h"
#include "Array.h"


/*TopPop functions*/

void insert_array(TownList * townList,TopPop * array){
  
    TownListNode * tmp;
    int i=0;
    
    tmp=townList->fnode;
    
    /*
    for (i=0 ; i < townList->size ; i++){
        
        array[i].town=(char *)malloc(strlen(tmp->town)*sizeof(char)+1);
        strcpy(array[i].town,tmp->town);
        array[i].population=tmp->population;
    
        tmp=tmp->nextTown;
    }
    */
   if(tmp==NULL){printf("insert_array: the townList->fnode Null");} 
    
    while(tmp!=NULL){
        
        array[i].town=(char *)malloc(strlen(tmp->town)*sizeof(char)+1);
        strcpy(array[i].town,tmp->town);
        array[i].population=tmp->population;
    
        i++;
        tmp=tmp->nextTown;
        
    
    }
    
   
}

void quickSort( TopPop * array, int l, int r)
{
   int j;

   if( l < r ) 
   {
        j = partition( array, l, r);
        quickSort( array, l, j-1);
        quickSort( array, j+1, r);
   }
	
}

int partition( TopPop * array, int l, int r) {
   int pivot, i, j; 
   TopPop  * t;
   t=(TopPop *)malloc(sizeof(TopPop));
   pivot = array[l].population;
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( array[i].population >= pivot && i <= r );
   	do --j; while( array[j].population < pivot );
   	if( i >= j ) break;
   	
        t->population = array[i].population; 
        t->town=(char *)malloc(strlen(array[i].town)*sizeof(char)+1);
        strcpy(t->town,array[i].town);
        
        array[i].population = array[j].population;
        free(array[i].town);
        array[i].town=(char *)malloc(strlen(array[j].town)*sizeof(char)+1);
        strcpy(array[i].town,array[j].town);
        
        array[j].population = t->population;
        free(array[j].town);
        array[j].town=(char *)malloc(strlen(t->town)*sizeof(char)+1);
        strcpy(array[j].town,t->town);
        
        free(t->town);
     }
   
   
   t->population = array[l].population; 
   t->town=(char *)malloc(strlen(array[l].town)*sizeof(char)+1);
   strcpy(t->town,array[l].town);
   
   
    
   array[l].population = array[j].population;
   free(array[l].town);
   array[l].town=(char *)malloc(strlen(array[j].town)*sizeof(char)+1);
   strcpy(array[l].town,array[j].town);
   
   
   
   
   array[j].population = t->population;
   free(array[j].town);
   array[j].town=(char *)malloc(strlen(t->town)*sizeof(char)+1);
   strcpy(array[j].town,t->town);
   
   free(t->town);
   free(t);
   
   return j;
}

void print_array(TopPop * array , int l){
    
    int i;
    
    if(array==NULL){
        printf("print_array:No array found\n");
        return;
    }
    
    for(i=0 ; i<l ; i++){
        //printf("Array #%d: %s %d \n",i,array[i].town,array[i].population);
        printf("%s: %d \n",array[i].town,array[i].population);
    }

}

void free_array(TopPop * array , int size){
    
    int i;
    for(i=0; i<size ; i++){
        free((array[i].town));
     }
   
}


/*TopSpend functions*/


void insert_TopSpend(TownList * townList,TopSpend * array){
  
    TownListNode * tmp;
    
    int i;
    
    tmp=townList->fnode;
   
    i=0;
   
    while(tmp!=NULL){
        
    array[i].town=(char *)malloc(strlen(tmp->town)*sizeof(char)+1);
        
     
        strcpy(array[i].town,tmp->town);
        
        array[i].phone=(char *)malloc(strlen(tmp->rpNode->record->phone)*sizeof(char)+1);
        strcpy(array[i].phone,tmp->rpNode->record->phone);
        
        array[i].dept=tmp->rpNode->record->amount;
    
        i++;
        tmp=tmp->nextTown;
    }
}


void print_TopSpend(TopSpend * array , int l){
    
    int i;
    
    if(array==NULL){
        printf("print_TopSpender:No array found\n");
        return;
    }
    
    for(i=0 ; i<l ; i++){
        printf("Top Spender#%d: %s %s %f \n",i,array[i].town,array[i].phone,array[i].dept);
    }

}

void quickSortTS( TopSpend * array, int l, int r)
{
   int j;

   if( l < r ) 
   {
        j = partitionTS( array, l, r);
        quickSortTS( array, l, j-1);
        quickSortTS( array, j+1, r);
   }
	
}


int partitionTS( TopSpend * array, int l, int r) {
   int pivot, i, j; 
   TopSpend  * t;
   t=(TopSpend *)malloc(sizeof(TopSpend));
   pivot = array[l].dept;
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( array[i].dept >= pivot && i <= r );
   	do --j; while( array[j].dept < pivot );
   	if( i >= j ) break;
   	
        
        t->town=(char *)malloc(strlen(array[i].town)*sizeof(char)+1);
        strcpy(t->town,array[i].town);
        t->phone=(char *)malloc(strlen(array[i].phone)*sizeof(char)+1);
        strcpy(t->phone,array[i].phone);
        t->dept = array[i].dept; 
        
        
        
        free(array[i].town);
        free(array[i].phone);
        array[i].town=(char *)malloc(strlen(array[j].town)*sizeof(char)+1);
        strcpy(array[i].town,array[j].town);
        array[i].phone=(char *)malloc(strlen(array[j].phone)*sizeof(char)+1);
        strcpy(array[i].phone,array[j].phone);
        array[i].dept = array[j].dept;
        
        
        
        
        free(array[j].town);
        free(array[j].phone);
        array[j].town=(char *)malloc(strlen(t->town)*sizeof(char)+1);
        strcpy(array[j].town,t->town);
        array[j].phone=(char *)malloc(strlen(t->phone)*sizeof(char)+1);
        strcpy(array[j].phone,t->phone);
        array[j].dept = t->dept;
        
        free(t->town);
        free(t->phone);
     }
   
   
   t->dept = array[l].dept; 
   t->town=(char *)malloc(strlen(array[l].town)*sizeof(char)+1);
   strcpy(t->town,array[l].town);
   t->phone=(char *)malloc(strlen(array[l].phone)*sizeof(char)+1);
   strcpy(t->phone,array[l].phone);
   
    
   array[l].dept = array[j].dept;
   free(array[l].town);
   free(array[l].phone);   
   array[l].town=(char *)malloc(strlen(array[j].town)*sizeof(char)+1);
   strcpy(array[l].town,array[j].town);
   array[l].phone=(char *)malloc(strlen(array[j].phone)*sizeof(char)+1);
   strcpy(array[l].phone,array[j].phone);
   
   array[j].dept = t->dept;
   free(array[j].town);
   free(array[j].phone);
   array[j].town=(char *)malloc(strlen(t->town)*sizeof(char)+1);
   strcpy(array[j].town,t->town);
   array[j].phone=(char *)malloc(strlen(t->phone)*sizeof(char)+1);
   strcpy(array[j].phone,t->phone);
   
   free(t->town);
   t->town=NULL;
   free(t->phone);
   t->phone=NULL;
   free(t);
   t=NULL;
   
   return j;
}


void free_TS(TopSpend * array , int size){
    
    int i;
    for(i=0; i<size ; i++){
        free((array[i].town));
        array[i].town=NULL;
        free((array[i].phone));
        array[i].phone=NULL;
     }
   
}



