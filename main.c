#include <stdio.h>
#include <string.h>
#include "Record.h"
#include "RecordList.h"
#include "HashTable.h"
#include "Index.h"
#include "Operations.h"
#include <unistd.h>

int main (int argc, char** argv) {
   FILE *fpb,*fpb2,*fpb3;
   Record rec,*recc,recop;
   HashTable * hashtable;
   long lSize;
   TownList *townList;
   int numOfrecords, i ,tSize;
   int c,l,end=0;
   char line[128];
   char  datafile[32];
   char  opfile[32];
   char option[3];
   char phone[11];
   char town[32];
   
   
   memset(datafile,'\0',32*sizeof(char));
   memset(opfile,'\0',32*sizeof(char));
   memset(line,'\0',128*sizeof(char));
   memset(phone,'\0',11*sizeof(char));
   memset(town,'\0',32*sizeof(char));
   memset(option,'\0',3*sizeof(char));
   
  
   
   if (argc!=7) {
      	printf("Invalid use of arguments\n");
      	return(1);
   	}
   
   while((c= getopt(argc, argv, "l:o:"))!=-1)
       switch (c)
       {
           
          case'l':
            
              strcpy(datafile,optarg);
              break;
               
           
          case'o':
              
             strcpy(opfile,optarg);
             break;
                   
           case'c':
           break;

          default:
           
               printf("Unknown character in getopt\n");
       }
   
       
   
      
       
       
     // datafiles  
   fpb = fopen (datafile,"rb");
   if (fpb==NULL) {
      	printf("Cannot open datafile\n");  
      }

   // operations file
   
   fpb2 = fopen (opfile,"rb");
   if (fpb2==NULL) {
      	printf("Cannot open operationsfile\n");
        return 1;
   }

   if(fpb!=NULL){
   
        // check number of records
        fseek (fpb , 0 , SEEK_END);
        lSize = ftell (fpb);
        rewind (fpb);
        numOfrecords = (int) lSize/sizeof(rec);
        tSize=numOfrecords/10;  // the Hash Table size
   

         // create hash table
        hashtable=(HashTable *)malloc(sizeof(HashTable));
        create_ht(hashtable,tSize);
   
         //create Index
         townList=(TownList*)malloc(sizeof(TownList));
         init_TownList(townList);

              //insert the datafile records
              for (i=0; i<numOfrecords ; i++) {
      	
                 fread(&rec, sizeof(rec), 1, fpb);
                 recc=create_record(rec.phone,rec.lastname,rec.firstname,rec.town,rec.amount); 
                 insert(hashtable,townList,recc);
              }
   
        memset(datafile,'\0',32*sizeof(char));
        fclose (fpb);
   }
   
   // (fpb2 == NULL) there is no valid datafile
   else
   {
    //create HashTable
   hashtable=(HashTable *)malloc(sizeof(HashTable));
   create_ht(hashtable,100); // fixed HashTable size
   
   //create Index
   townList=(TownList*)malloc(sizeof(TownList));
   init_TownList(townList);
             
   }
   
   
   //start reading the operationsfile
   
   while(fscanf(fpb2,"%s",option)>0){
        
       // insert 
       if(strcmp("i",option)==0)
       {       
                  fscanf(fpb2,"%s",recop.phone);
                  fscanf(fpb2,"%s",recop.lastname);
                  fscanf(fpb2,"%s",recop.firstname);
                  fscanf(fpb2,"%s",recop.town);
                  fscanf(fpb2,"%f",&recop.amount);
 
                  recc=create_record(recop.phone,recop.lastname,recop.firstname,recop.town,recop.amount); 
                  insert(hashtable,townList,recc);
                  memset(&recop,'\0',sizeof(Record));
                  printf("\n\n");
       }
       
       //delete
       else if(strcmp("d",option)==0)
       {
              
                 fscanf(fpb2,"%s",phone);
                 delete(hashtable,townList,phone);
                 memset(phone,'\0',11*sizeof(char));
                 printf("\n\n");
       }          
       
       // find a record
       else if(strcmp("q",option)==0)
       {
           
                  fscanf(fpb2,"%s",phone);
                  query(hashtable ,phone);
                  memset(phone,'\0',11*sizeof(char));
                  printf("\n\n");
       }
        
           
       //town's population
       else if(strcmp("p",option)==0)
       {
           
                  fscanf(fpb2,"%s",town);
                  population(townList,town);
                  memset(town,'\0',32*sizeof(char));
                  printf("\n\n");
       }  
       
       // l most populated towns
       else if(strcmp("t",option)==0)
       {
                  fscanf(fpb2,"%d",&l);
                  top_population(townList,l);
                  printf("\n\n"); 
       }
       
       
       // town's total dept
       else if(strcmp("s",option)==0)
       {
                  fscanf(fpb2,"%s",town);
                  sum(townList,town);
                  printf("\n\n");
       }
       
      // town's l biggest depts  
       else if(strcmp("ft",option)==0)
      {
           
                fscanf(fpb2,"%s",town);
                fscanf(fpb2,"%d",&l);
                top_deptors(townList ,town,l);
                printf("\n\n");
      }
          
       
       
       else if(strcmp("fts",option)==0)
       {
          top_spender(townList);
          printf("\n\n");
       }
       
       //min number
       else if(strcmp("min",option)==0)
       {
                  min(hashtable);
                  printf("\n\n");
       }
       
       //max number
       else if(strcmp("max",option)==0)
       {
                  max(hashtable);
                  printf("\n\n");
       }
          
       //load a datafile
       else if(strcmp("l",option)==0)
       {
            fscanf(fpb2,"%s",datafile);
            fpb3 = fopen (datafile,"rb");
                if (fpb3==NULL) {
      	            printf("Data file %s not found.\n\n",datafile);  
                }
                     
                else{   
                         
                         fseek (fpb3 , 0 , SEEK_END);
                         lSize = ftell (fpb3);
                         rewind (fpb3);
                         numOfrecords = (int) lSize/sizeof(rec);

                               for (i=0; i<numOfrecords ; i++) {
      	
                                      fread(&rec, sizeof(rec), 1, fpb3);
                                      recc=create_record(rec.phone,rec.lastname,rec.firstname,rec.town,rec.amount); 
                                      insert(hashtable,townList,recc);
                                }
                        
                        memset(datafile,'\0',32*sizeof(char));
                        fclose (fpb3);
                            
                }
       }
       
       // free memory - exit programm
       else if(strcmp("e",option)==0)
       {
                  exit_pro(hashtable,townList);
                  end=1;
                  printf("\n\n");
                  break;
       }
        
       else
        {
           
           printf("Unknown command\n");
          
        }
          
          
          memset(option,'\0',3*sizeof(char));
   
   }
   
  fclose (fpb2);
  
  
  
  //start the prompt
  
  while(end==0){
      
      memset(option,'\0',3*sizeof(char));
      printf("Enter your option:");
      scanf("%s",option);
      
      if(strcmp("i",option)==0)
       {       
                  scanf("%s",recop.phone);
                  scanf("%s",recop.lastname);
                  scanf("%s",recop.firstname);
                  scanf("%s",recop.town);
                  scanf("%f",&recop.amount);
              
                  recc=create_record(recop.phone,recop.lastname,recop.firstname,recop.town,recop.amount); 
                  insert(hashtable,townList,recc);
                  memset(&recop,'\0',sizeof(Record));
                  printf("\n\n");
       }
       
       else if(strcmp("d",option)==0)
       {
              
                 scanf("%s",phone);
                 delete(hashtable,townList,phone);
                 memset(phone,'\0',11*sizeof(char));
                 printf("\n\n");
       }          
        
       else if(strcmp("q",option)==0)
       {
           
                  scanf("%s",phone);
                  query(hashtable ,phone);
                  memset(phone,'\0',11*sizeof(char));
                  printf("\n\n");
       }
        
           
      
       else if(strcmp("p",option)==0)
       {
           
                  scanf("%s",town);
                  population(townList,town);
                  memset(town,'\0',32*sizeof(char));
                  printf("\n\n");
       }  
       
       
       else if(strcmp("t",option)==0)
       {
                  scanf("%d",&l);
                  top_population(townList,l);
                  printf("\n\n"); 
       }
       
       
       else if(strcmp("s",option)==0)
       {
                  scanf("%s",town);
                  sum(townList,town);
                  printf("\n\n");
       }
       
      
       else if(strcmp("ft",option)==0)
      {
           
                scanf("%s",town);
                scanf("%d",&l);
                top_deptors(townList ,town,l);
                printf("\n\n");
      }
          
       
       else if(strcmp("fts",option)==0)
       {
          top_spender(townList);
          printf("\n\n");
       }
       
       
       else if(strcmp("min",option)==0)
       {
                  min(hashtable);
                  printf("\n\n");
       }
       
       else if(strcmp("max",option)==0)
       {
                  max(hashtable);
                  printf("\n\n");
       }
          
       else if(strcmp("l",option)==0)
       {
                 scanf("%s",datafile);
                  
                 fpb3 = fopen (datafile,"rb");
                     if (fpb3==NULL) {
      	                printf("Data file %s not found.\n",datafile);  
                     }
                     
                     else{   
                         
                         fseek (fpb3 , 0 , SEEK_END);
                         lSize = ftell (fpb3);
                         rewind (fpb3);
                         numOfrecords = (int) lSize/sizeof(rec);

                            for (i=0; i<numOfrecords ; i++) {
      	
                                      fread(&rec, sizeof(rec), 1, fpb3);
                                      recc=create_record(rec.phone,rec.lastname,rec.firstname,rec.town,rec.amount); 
                                      insert(hashtable,townList,recc);
   
                                           
                            }
                         memset(datafile,'\0',32*sizeof(char));
                         fclose (fpb3);
                            
                        }
           
            }
       
       else if(strcmp("e",option)==0)
       {
                  exit_pro(hashtable,townList);
                  printf("\n\n");
                  break;
       }
      
       //print the Hash Table content
       else if(strcmp("ht",option)==0)
       {
                printHT(hashtable);
                printf("\n\n");
                 
       }
       
      
      //print the Index content 
       else if(strcmp("rp",option)==0)
       {
                print_RPList(townList);
                printf("\n\n");
                 
       }
          
        else
        {
           
           printf("Unknown command\n");
          
        }
 
  }
   
  
     
}// end main
