#ifndef RECORD_H
#define RECORD_H

#define SIZEofBUFF 20

#include <stdlib.h>

typedef struct{
        char  	phone[SIZEofBUFF];
	char    lastname[SIZEofBUFF];
	char    firstname[SIZEofBUFF];
	char	town[SIZEofBUFF];
	float  	amount;
}Record;


Record *create_record(const char * , const char *, const char *,const char *,float);
void delete_record(Record * record);



#endif