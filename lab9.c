#include <stdio.h>
#include <stdlib.h>

//RecordType
struct RecordType
{
int id;
char name;
int order;
struct RecordType *next;//create a next pointer ( for a linkedlist structure )
};

// Fill out this structure
struct HashType
{
struct RecordType *data;// create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize)
{
return x % tableSize;//hash function is x % tablesize
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
FILE *inFile = fopen(inputFileName, "r");
int dataSz = 0;
int i, n;
char c;
struct RecordType *pRecord;
*ppData = NULL;

if (inFile)
{
fscanf(inFile, "%d\n", &dataSz);
*ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
// Implement parse data block
if (*ppData == NULL)
{
printf("Cannot allocate memory\n");
exit(-1);
}
for (i = 0; i < dataSz; ++i)
{
pRecord = *ppData + i;
fscanf(inFile, "%d ", &n);
pRecord->id = n;
fscanf(inFile, "%c ", &c);
pRecord->name = c;
fscanf(inFile, "%d ", &n);
pRecord->order = n;
pRecord->next = NULL;
}

fclose(inFile);
}

return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
int i;
printf("\nRecords:\n");
for (i = 0; i < dataSz; ++i)
{
printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
}
printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
int index = hash(record->id, tableSize);
if(hashTable[index].data == NULL){
hashTable[index].data = record;
}
else{
struct RecordType *pRecord = hashTable[index].data;
while(pRecord -> next != NULL){
pRecord = pRecord -> next;
}
pRecord -> next = record;
}

}


void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
int i;
for(i=0; i<tableSize; i++){
if(hashTable[i].data == NULL){
continue;
}
struct RecordType *pRecord = hashTable[i].data;
printf("Index %d -> ", i);
while(pRecord != NULL){
printf("%d %c %d -> ", pRecord -> id, pRecord -> name, pRecord -> order);
pRecord = pRecord -> next;
}
printf("NULL\n");
}

}

int main(void)
{
struct RecordType *pRecords;
int recordSz = 0;
int i;

recordSz = parseData("input.txt", &pRecords);
printRecords(pRecords, recordSz);

int hashTableSize = 11;
struct HashType *hashTable = (struct HashType *)calloc(hashTableSize, sizeof(struct HashType));
for(i = 0; i < recordSz; i++){
insertRecord(hashTable, pRecords + i, hashTableSize);
}

displayRecordsInHash(hashTable, hashTableSize);
free(pRecords);
free(hashTable);

return 0;
}
