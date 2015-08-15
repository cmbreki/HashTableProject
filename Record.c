#include "Record.h"
#include <stdlib.h>
#include <string.h>



Record * create_record (const char * phone, const char * lastname, const char * firstname,const char * town, float amount) 
{

  Record *record = (Record *) malloc(sizeof(Record));

  if(record == NULL)
      return NULL ;
        
        memset(record->phone,'\0',strlen(phone) + 1);
        memset(record->lastname,'\0',strlen(lastname) + 1);
        memset(record->firstname,'\0',strlen(firstname) + 1);
        memset(record->town,'\0',strlen(town) + 1);
        
         strcpy(record->phone, phone);
         strcpy(record->lastname, lastname);
         strcpy(record->firstname, firstname);
         strcpy(record->town,town);
         record->amount =amount;
         
         return record;
}


void delete_record(Record * record){
 
    free(record);
}




