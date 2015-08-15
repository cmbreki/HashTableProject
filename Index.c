#include <stdio.h>
#include <string.h>

#include "Record.h"
#include "Index.h"

/*Head Town List functions*/

void init_TownList(TownList * townList){
    
    if(townList==NULL){
        printf("The Town List is NULL\n");
        return;}
    
    townList->size=0;
    townList->fnode=NULL;
    townList->lnode=NULL;
}

void destroy_TownList(TownList * townList){
     

   townList->fnode=NULL;
   townList->lnode=NULL;
   free(townList);
   townList=NULL;
   //printf("free the Townlist \n");
}


/*TownListNode functions*/

void create_TownListNode(TownListNode * townListNode, Record * record){
   
    if (townListNode==NULL){
       // printf("The TownlistNode is NULL\n");
        return;
    }
    
    townListNode->town=(char *)malloc(strlen(record->town)*sizeof(char)+1);
    strcpy(townListNode->town,record->town);
    
    townListNode->population=0;
    townListNode->totalMoney=record->amount;
    townListNode->rpNode=NULL;
    townListNode->nextTown=NULL;
    
}

void delete_TownListNode(TownList  * townList){
    
    TownListNode  * tmp, * prev;
    tmp=townList->fnode;
    prev=townList->fnode;
    int found=0;
    
    if(tmp==NULL || prev==NULL){
        printf("delete_TownListNode: The list is empty\n");
        return;
    }
    
    if((tmp->population==0)){
            found=1;
            if(tmp->nextTown==NULL){
                townList->fnode=NULL;
                townList->lnode=NULL;
               // printf("delete_TownListNode: The last element has been deleted from TownList\n");
            }
            else{
            townList->fnode=tmp->nextTown;
           
            //printf("delete_TownListNode: The first element deleted from TownList \n");
            }
            
            townList->size--;
            free_TownListNode(tmp);
            return;
    }
    
    tmp=tmp->nextTown;
    
   
    while(tmp!=NULL){
        
        if((tmp->population == 0)){
            found=1;
            townList->size--;
               if(tmp==townList->lnode){
                   townList->lnode=prev;
                  //printf("delete_TownListNode:The end element deleted TownList \n"); 
               }
            prev->nextTown=tmp->nextTown;
            tmp->nextTown=NULL;
            free_TownListNode(tmp);
          // printf("delete_TownListNode: An element deleted from TownList \n");
            return;
        }      
     prev=tmp;
     tmp=tmp->nextTown;     
    }
    
    
    
  if(found==0){
 // printf("delete_TownListNode:No record found\n ");
  return;}
        
    
}

void insert_TownListNode(TownList *townList , TownListNode * townListNode){
    
    
    if (townList==NULL || townListNode==NULL){
       // printf("insert_TownListNode:NULL\n");
        return;
    }
    // first element in the list
    if(townList->fnode==NULL){
       
        townList->fnode=townListNode;
        townList->lnode=townListNode;
       // printf("insert_TownListNode:First element in TownList \n");
    }
    
    else{
         // printf("insert_TownListNode:The town in townList->lnode is %s \n",townList->lnode->town);
            townList->lnode->nextTown=townListNode;
            townList->lnode=townListNode;
           // printf("insert_TownListNode:The new town in lnode is %s \n",townList->lnode->town);
           // printf("insert_TownListNode:An element in TownList \n");
    }

    townList->size++;
}

TownListNode * search_town(TownList * townList, char * town){
    
    TownListNode * tmp;
    tmp=townList->fnode;
    int found=0;
    
   
    while(tmp!=NULL)
    {
        if(strcmp(tmp->town,town)==0)
        {
           // printf("search_town:Town %s in the list\n",town);
            found=1;
             break;
        }
        else
        {
            tmp=tmp->nextTown;
           
        }
              
    }
    
    if(found==0){
    //printf("search_town:Town %s no found\n",town);
    }
    
    return tmp;
    
   }

void print_TownList(TownList *townList){
    
    TownListNode * tmp;
    int i=0;
    
    tmp=townList->fnode;
    while(tmp!=NULL){
      printf("Town #%d:%s\n",i,tmp->town);     
      tmp=tmp->nextTown; 
      i++;
    }
}

void free_TownListNode(TownListNode * townListNode){
   
   free(townListNode->town);
   townListNode->town=NULL;
   townListNode->rpNode=NULL;
   townListNode->nextTown=NULL;
   free (townListNode); 
   townListNode=NULL;
   //printf("free an TownListNode \n");
}


/*RPNode functions*/

void init_RP(RPNode  * rpNode , Record * record){
  
    if(rpNode==NULL){
        return;
    
    }
    
    rpNode->record=record;
    rpNode->next=NULL;
}

void insert_RP(TownListNode * townListNode , RPNode * rpNode){

    RPNode   * temp, * prev;
    temp=townListNode->rpNode;
    prev=townListNode->rpNode;
    
    
    if (temp==NULL){
      
        townListNode->rpNode=rpNode;
       // printf("insert_RP:The first element has been inserted in the RP list\n");
    }
    
  else{
    while(temp!=NULL){
        
        if(rpNode->record->amount > temp->record->amount){
               
           if(temp==townListNode->rpNode){
               townListNode->rpNode=rpNode;
               rpNode->next=temp;
             // printf("insert_RP:An element has been inserted in the top of the RP list\n");
                break;
           }
               
               prev->next = rpNode;
               rpNode->next = temp;
               //printf("insert_RP:An element has been inserted in the RPlist\n");
               break;
        }
           
             
            prev=temp;
            temp=temp->next;    
        
    }
    
    if(temp==NULL){   
    prev->next=rpNode;
    //printf("insert_RP:An element has been inserted in the end of RPlist\n");
    }     
    
  }
}

void delete_RP(TownListNode * townListNode , char * phone){
    
    RPNode * tmp,* prev;
    int found=0;
    
    tmp=townListNode->rpNode; 
    prev=townListNode->rpNode;
    
    
    if((strcmp(tmp->record->phone,phone)==0)){
        found=1;
            if(tmp->next==NULL){
                townListNode->rpNode=NULL;
               // printf("delete_RP: The Last element deleted from RP list\n");
            }
        townListNode->rpNode=tmp->next;
        tmp->record=NULL;
        tmp->next=NULL;
        free_RP(tmp);
       // printf("delete_RP: The first element deleted from RP list\n");
        return;
    }
    
    tmp=tmp->next;
    
   
    while(tmp!=NULL){
        
        if((strcmp(tmp->record->phone,phone)==0)){
            found=1;
            prev->next=tmp->next;
            tmp->record=NULL;
            tmp->next=NULL;
            free_RP(tmp);
           // printf("delete_RP: An element deleted from RP list\n");
            return;
        }      
     prev=tmp;
     tmp=tmp->next;     
    }
    
  if(found==0){
  printf("delete_PR:No record found ");
  return;}
    
       
}
    
void free_RP(RPNode * rpNode){
    rpNode->record=NULL;
    rpNode->next=NULL;
    free(rpNode);
    rpNode=NULL;
   // printf("free an RPnode \n");
}

void print_RPList(TownList *townList){
    
    TownListNode *tmp; 
    RPNode * tmp2;
    int i=0;
    
    tmp=townList->fnode;
    
    while(tmp!=NULL){
      printf("Town #%d:%s,%d\n",i,tmp->town,tmp->population);     
       tmp2=tmp->rpNode;
        
        while(tmp2!=NULL)
         {
         printf("%s, %s, %s,%s,%f \n",tmp2->record->phone,tmp2->record->lastname,tmp2->record->firstname,tmp2->record->town,tmp2->record->amount);       
         tmp2=tmp2->next;
         
         }    
    
       tmp=tmp->nextTown; 
   
    i++;
    printf("**************************\n");
    }
}