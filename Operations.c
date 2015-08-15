#include <stdio.h>
#include <string.h>

#include "Index.h"
#include "Record.h"
#include "RecordList.h"
#include "HashTable.h"
#include "Operations.h"
#include "Array.h"


void delete(HashTable * hashtable, TownList * townList, char * phone){
    
    Record * recc;
    TownListNode * townListNode;
    HeadNode * headNode;
    int cell;
    
    cell=hashFunc(hashtable , phone);
    
    
    if(hashtable==NULL || townList==NULL){
        printf("delete:Null HashTable or Null Index\n");
        return;
    }
    
    headNode=hashtable->table[cell];
    
    recc=find_record(hashtable,phone);
      
    if(recc==NULL){
          printf("delete:No record found\n");
          return;
    }
    
    townListNode=search_town(townList, recc->town);
    
    if(townListNode==NULL){
    printf("delete:No town found NULL\n"); 
    return;
    }
    
     delete_RP(townListNode ,recc->phone);
     
     townListNode->population--;
     townListNode->totalMoney= townListNode -> totalMoney - recc->amount;
    
     delete_TownListNode(townList);
     
     delete_fromList(headNode ,recc->phone); 
     
    
    
    //printf("delete: %s,%d,%f \n",townListNode->town,townListNode->population,townListNode->totalMoney);
    
    printf("Phone number %s deleted successfully.\n",phone);
    
    
    
   

}

void insert(HashTable * hashtable, TownList * townList, Record * recc){
    
    Node * node;
    TownListNode *curr,* townListNode;
    RPNode * rpNode;
    Record  * record;
    
    
    record=find_record(hashtable,recc->phone);
    
    
    if(record!=NULL){
       
       printf("Record not added: Duplicate phone number exists.\n");
       return;
    }
    
          /*hash table*/
        node=(Node *)malloc(sizeof(Node));
   	create_node(recc,node);
        set_ht(hashtable,node);

        /*Inverted Index*/
        curr=search_town(townList,recc->town);
        
        if(curr==NULL){
            
           // printf("insert: The town not in  the town list\n ");
            townListNode=(TownListNode *)malloc(sizeof(TownListNode));
            create_TownListNode(townListNode,recc);
            townListNode->population ++ ;
            insert_TownListNode(townList,townListNode);
            rpNode=(RPNode *)malloc(sizeof(RPNode));
            init_RP(rpNode , recc);
            insert_RP(townListNode , rpNode);
            printf("Phone number %s added successfully.\n",recc->phone);
 
        }

       else{
           
            //printf("insert: The town already in the town list\n ");
            curr->population++;
            curr->totalMoney= curr->totalMoney + recc->amount;
            rpNode=(RPNode *)malloc(sizeof(RPNode));
            init_RP(rpNode , recc);
            insert_RP(curr, rpNode);
            printf("Phone number %s added successfully.\n",recc->phone);
        }
}

void population(TownList * townList, char * town){
    
    TownListNode * townListNode;
    
    townListNode=search_town(townList,town);
    
    if(townListNode != NULL){
     printf(" %s clients: %d\n",townListNode->town,townListNode->population);
     //printf(" %s total money: %f\n",townListNode->town,townListNode->totalMoney);
    }

}

void sum(TownList * townList, char * town){
    
    TownListNode * townListNode;
    
    townListNode=search_town(townList,town);
    
    if(townListNode != NULL){
        
     printf("%s: %f \n",townListNode->town,townListNode->totalMoney);
    }
    
    else{
        printf("No records found for given town.\n");
    }

}

void query(HashTable * hashtable , char *  phone){
    
    Record * recc;
    
    recc=find_record(hashtable,phone);
    
    if (recc!= NULL){
     printf("%s, %s, %s,%s,%f \n",recc->phone,recc->lastname,recc->firstname,recc->town,recc->amount);
    }
    else{
        printf("Phone number not found\n ");
    
    }    
}

void top_deptors(TownList * townList ,char * town, int l){
    
    TownListNode * townListNode;
    RPNode  * rp;
    int i=0;
    
    
     if (townList==NULL){
        printf("top_deptors:The townList is NULL\n");
        return;
     }
    
   townListNode=search_town(townList, town);
    
    
    if (townListNode==NULL){
        printf("top_deptors:No records found for given town(townListNode=NULL)\n");
        return;
    }
   
              if(townListNode->population<l){
                  l=townListNode->population;
              }
       
        rp=townListNode->rpNode;
    
               if(rp==NULL){
                  printf("top_deptors:No records found(rpNode==NULL)\n");
                  return;
                }
       
       while( rp!=NULL && i<l){       
            //printf("Deptor #%d: %s, %s, %s,%s,%f \n",i,rp->record->phone,rp->record->lastname,rp->record->firstname,rp->record->town,rp->record->amount); 
          
               printf("#%d: %s ,%f \n",i,rp->record->phone,rp->record->amount);
               i++;
           rp=rp->next; 
           
       }
    
}

void top_population(TownList * townList, int l){

    TopPop *  array;
    
    if(townList==NULL){
        printf("top_population: Town List is NULL\n");
        return;
    }
    
    if (townList->fnode==NULL){
        printf("top_population:No towns found \n");
        return;
    }
     
    int r=townList->size-1;
    
    if(l>townList->size){
       l=townList->size;
    }

    array=(TopPop *)malloc (townList->size * sizeof(TopPop));
    
    insert_array(townList, array);
    
    quickSort(array,0,r);
    
    print_array(array,l);
   
    free_array(array,townList->size);
    
    free(array);
    
    array=NULL;
     
    //print_array(array,l);
    

}

void top_spender(TownList * townList){
    
    TopSpend * array;
   
    int r=townList->size;
    
    if(townList==NULL){
        printf("top_spender: The Town List is NULL\n");
        return;}
    
    if (townList->fnode==NULL){
        printf("top_spender:No top spenders found\n");
        return;
    }
      
   array=(TopSpend *) malloc (r * sizeof(TopSpend));
   
   insert_TopSpend(townList,array);
   
   quickSortTS(array,0,r-1);
   
   print_TopSpend(array,r);
  
   free_TS(array,r);
   
   free(array);
    
   array=NULL;
   

}

void min(HashTable * hashtable){
    
    
    long long min=0,test;
    Node  *tmp;
    int i,flag=0;
    
   
    
    
    
    for (i=0 ; i < hashtable->size ; i++){
    
        if(hashtable->table[i] != NULL && hashtable->table[i]->firstNode != NULL){
          min=atoll(hashtable->table[i]->firstNode->record->phone);
          flag=1;
          break;
        }
    }
    
    if(flag==0){
         printf("min: %lld \n",min);
         return;
    }
    
    
    
    for (i=0 ; i < hashtable->size ; i++){
           
      if(hashtable->table[i]!=NULL){ 
   
          tmp=hashtable->table[i]->firstNode;
         
             while(tmp!=NULL ){
           
                  test=atoll(tmp->record->phone);
                      if(test<min)
                       {
                         min=test;
                       }
            
                  tmp=tmp->next;
        
            }
        }
    }

    printf("min: %lld \n",min);
}

void max(HashTable * hashtable){
    long long max=0,test;
    Node  *tmp;
    int i,flag;
    
    
    for (i=0 ; i < hashtable->size ; i++){

        if(hashtable->table[i] != NULL && hashtable->table[i]->firstNode != NULL ){
          max=atoll(hashtable->table[i]->firstNode->record->phone);
          flag=1;
          break;
        }
    }
    
    if(flag==0){
         printf("max: %lld \n",max);
         return;
    }
    
    for (i=0 ; i < hashtable->size ; i++){
         
        if(hashtable->table[i]!=NULL){          
             
               tmp=hashtable->table[i]->firstNode;
              
                   while(tmp!=NULL){
                       
                      test=atoll(tmp->record->phone);
        
                       if(test>max)
                       {
                         max=test;
                       }
            
                     tmp=tmp->next;
                   }
        }     
    }

    printf("max: %lld \n",max);

}

void exit_pro(HashTable * hashtable , TownList * townList){
 
    int i;
    Node * tmp , * tmpII;
    TownListNode * tln ,* tlnII ;
    RPNode *rpn , *rpnII;
  
    //destroy townList
    
    tln=townList->fnode;
    
    for(i=0 ; i<townList->size ; i++){
    
        rpn=tln->rpNode;
        
           while(rpn!=NULL)
            {
               rpnII=rpn;
               rpn=rpn->next;
               free_RP(rpnII);
               
            }
            
     tlnII=tln;
     tln=tln->nextTown;
     free_TownListNode(tlnII);
    }
    
   destroy_TownList(townList);
    
    
// destroy hashtable
   
    for(i=0 ; i < hashtable->size ; i++){
           if(hashtable->table[i]!=NULL){
             tmp=hashtable->table[i]->firstNode;
        
                 while(tmp!=NULL)
                 {
                    tmpII=tmp;
                    tmp=tmp->next;
                    free_node(tmpII);
                    
                  }
        
        
            }
        free(hashtable->table[i]);
        hashtable->table[i]== NULL;
       // printf("free an headNode \n");
        
    }
    
    free(hashtable);
    hashtable==NULL;
    //printf("free the HashTable \n");
        
}  


void last_node(TownList * townList) 
{

    printf("last_node: The last no is %s \n",townList->lnode->town);
    printf("last_node: The first no is %s \n",townList->fnode->town);
}
         
        
       
        
        
        
        
    
    
    
    
  
    


