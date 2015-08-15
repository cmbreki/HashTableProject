#
# In order to execute this "Makefile" just type "make"
#
#

OBJS 	= main.o Record.o RecordList.o Operations.o Index.o HashTable.o Array.o
SOURCE	= main.c Record.c RecordList.c Operations.c Index.c HashTable.c Array.c 
HEADER  = Record.h RecordList.h Operations.h Index.h HashTable.h Array.h
OUT  	= myphones
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

Record.o: Record.c
	$(CC) $(FLAGS) Record.c

RecordList.o: RecordList.c
	$(CC) $(FLAGS) RecordList.c

Operations.o: Operations.c
	$(CC) $(FLAGS) Operations.c

Index.o: Index.c
	$(CC) $(FLAGS) Index.c

HashTable.o: HashTable.c
	$(CC) $(FLAGS) HashTable.c

Array.o: Array.c
	$(CC) $(FLAGS) Array.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
