#ifndef ARRAY_H
#define	ARRAY_H

typedef struct TopPop TopPop;
typedef struct TopSpend TopSpend;


struct TopPop{
    
    char * town;
    int population;    
};

struct TopSpend{
 
    char * town;
    char * phone;
    float dept;
};

/*TopPop functions*/

void insert_array(TownList * townList,TopPop * array);
void quickSort( TopPop * array, int l, int r);
int partition( TopPop * array, int l, int r);
void print_array(TopPop * array , int l);
void free_array(TopPop  * array, int size);


/*TopSped functions*/

void insert_TopSpend(TownList * townList,TopSpend * array);
void quickSortTS( TopSpend * array, int l, int r);
int partitionTS( TopSpend * array, int l, int r);
void print_TopSpend(TopSpend * array , int l);
void free_TS(TopSpend * array , int size);














#endif

