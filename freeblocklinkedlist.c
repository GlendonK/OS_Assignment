/*#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    int file;
    struct NODE *next;
};


int main(){


   struct NODE *head = NULL;
   head = (struct NODE*)malloc(sizeof(struct NODE));

   head ->file = 1;
   head ->next = NULL;

}*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int blockArray[121];
int fileArray[2] = {100, 101};
int fileArrayTwo[3] ={102, 103, 104};
int fileArrayThree[4] = {105, 106, 107, 108};
int fileArrayFour[5] = {109, 110, 111, 112, 113};
int n = sizeof(fileArrayFour) / sizeof(fileArrayFour[0]);
struct NODE *head = NULL;
int numNode;

struct NODE // one box of the linked list
{
    int file;
    struct NODE *next;  // pointer points to a strcut NODE 
}; 

struct VCB
{
    int totalBlocks;
    int numberOfFreeBlocks;
    int blockSize;
    int freeBlockIndex[60];
};

struct Directory /// make into a struct array. inside be start, end of file
{
    int fileName;
    int fileIndex;
    int fileSize;
    int fileEnd;
};

struct VCB vcb;
struct Directory directory [60];


void setFreeBlockIndex();
unsigned setFileSize();
void setFileIndex();
void add(int file[]);
void allocate();
void read();
void delete();
void createFreeBlockNode(int firstEmptyBlockIndex);
void addFreeBlockNode(struct NODE *head, int emptyBlockIndex);
int removeFreeBlockNode(struct NODE * head);
void freePointers(struct NODE *currentNode, struct NODE *head);
void getNextFreeBlock(struct NODE *head);

void createFreeBlockNode(int firstEmptyBlockIndex)
{
    
    //struct NODE *head = NULL;
    head = (struct NODE*)malloc(sizeof(struct NODE)); // creates node

    head ->file = firstEmptyBlockIndex; // set first empty index
    head ->next = NULL; // set null pointer

}

void addFreeBlockNode(struct NODE *head, int emptyBlockIndex)
{
    /*head->next = (struct NODE*)malloc(sizeof(struct NODE)); // create new node
    head->next->file = emptyBlockIndex;
    head->next->next =NULL;*/
    
    struct NODE *currentNode = head; // temp node to get to last node
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next; // go to the last node
    }

    currentNode -> next = (struct NODE*)malloc(sizeof(struct NODE));// create new node
    currentNode->file = emptyBlockIndex; // set index of empty block
    currentNode->next->next = NULL; // set null pointer for last node
}

int removeFreeBlockNode(struct NODE *head)
{
    int index = -1;
    struct NODE *nextNode = NULL;
    if(head ==NULL)
    {
        return -1;
    }

    nextNode = (head)->next;
    index = (head)->file;
    free(head);
    head = nextNode;

    return index;


}


/* 
!how to free all the pointers after programme end ?
*/
void freePointers(struct NODE *currentNode, struct NODE *head){
    free(currentNode);
    free(head);
}

void printList(struct NODE *head)
{
    struct NODE *thisNode = head;
    while(thisNode->next!=NULL)
    {
        printf("%d\n", thisNode->file);
        thisNode = thisNode->next;   
    }
}

int listCount(struct NODE *head)
{
    struct NODE *currentNode = head;
    while(currentNode->next != NULL)
    {
        numNode +=1;
    }
    return numNode;
}

void setFreeBlockIndex()
{
    //initial all is free block

    /*int i;
    int k = 0;
    for (i = 0; i<120; i += (vcb.blockSize))
    {
        //for when blockArray[?] have no file -- update freeblockindex[] to the index of blockArray[]
        if (blockArray[i] == 0)
        {    
            //printf("pos 2");
            vcb.freeBlockIndex[k] = i;
            k = k+1;
            //printf("here1");
            directory[i/vcb.blockSize].fileName = blockArray[i];
            //printf("here2");
            directory[i/vcb.blockSize].fileIndex = 0;
            //printf("here3");
        }
        //for when blockArray[?] have a file -- update freeblockindex to 0
        else if (blockArray[i] !=0 )
        {
            vcb.freeBlockIndex[k] = -1;
            k = k+1;
            directory[i/vcb.blockSize].fileName = blockArray[i];
            directory[i/vcb.blockSize].fileIndex = (i);
        }
    }*/

    int i;
    for(i=0;i<121;i+=vcb.blockSize)
    {
        if(blockArray[i] == 0)
        {
            if(head == NULL)
            {
                createFreeBlockNode(0);
            }

            if(head != NULL)
            {
                addFreeBlockNode(head, i);
            }

        }
        // remove in the add()
       /* if(blockArray[i] != 0)
        {
            removeFreeBlockNode(head);
        }*/ 
    }

    

}

void setFileIndex()
{
    int i;
    for (i = 0; i<n; i += (vcb.blockSize))
    {
        if (blockArray[i] == 0)
        {    
            directory[i/vcb.blockSize].fileIndex = 0;
        }

        if (blockArray[i] !=0 )
        {
            directory[i/vcb.blockSize].fileIndex = (i);
        }
    }

}

unsigned setFileSize(int file[])
{
    //n = 3;
    //size_t n = sizeof(file) / sizeof(file[0]);
    //directory.fileSize[0] = n;


}


/*void add(int file[])
{
    int i;
    int j;
    
    int blockAvail = 0;
    double blockReq;
    double block;
    int *freeBlockIndex;
    int currentFreeBlock = 0;
    int w=0;

    block = n/(vcb.blockSize-1);
    blockReq = ceill(block); // blocks required
    printf("BLOCKREQ: %lf\n", blockReq);
    
    for (j = 0; j<(60); j++)
    {
        if (vcb.freeBlockIndex[j] != -1)
        {
            blockAvail = blockAvail + 1; // get number of free blocks
        }
    }
    printf("BLOCKAVAIL: %d\n", blockAvail);

    freeBlockIndex = (int*)malloc(blockAvail*sizeof(int)); // create array to store the index of free blocks of blockArray[]

    for (i = 0; i<60; i++)
    {
        if (vcb.freeBlockIndex[i] != -1)
        {
            freeBlockIndex[w] = vcb.freeBlockIndex[i];
            w++;
        }
    }
    printf("vcb.freeBlockIndex: %d\n", vcb.freeBlockIndex[1]);
    printf("FREEBLOCKINDEX: %d\n", freeBlockIndex[0]);

    if (blockReq > blockAvail) // error if not enuf blocks
    {
        printf("Not enuf blocks");
        
    }
    
    if ( blockReq < blockAvail || blockReq == blockAvail)
    {   
        int k = 0;
        int l =0;
        for (i = 0; i<n ; i++) // allocating
        {     
            if (blockArray[0] == 0)
            {
                blockArray[freeBlockIndex[currentFreeBlock]+k] = file[i];
                l = l+1;
            }

            if ( l != vcb.blockSize-1 && blockArray[freeBlockIndex[currentFreeBlock]+k] == 0 ) // assign the first empty block
            {
                blockArray[freeBlockIndex[currentFreeBlock]+k] = file[i];
                //k += 1;
                l = l+1;
            }

            
            if ( l == vcb.blockSize-1 && blockArray[freeBlockIndex[currentFreeBlock]+k] == 0) // when need more than 1 block. assign to the next block
            {
                currentFreeBlock += 1;
                //blockArray[freeBlockIndex[currentFreeBlock-1]+(vcb.blockSize-1)] = freeBlockIndex[currentFreeBlock]; // set the pointer index to the start of next empty block
                if ( blockArray[freeBlockIndex[currentFreeBlock]] == 0)
                {
                    blockArray[freeBlockIndex[currentFreeBlock-1]+(vcb.blockSize-1)] = freeBlockIndex[currentFreeBlock]; // set the pointer index to the start of next empty block
                    blockArray[freeBlockIndex[currentFreeBlock]] = file[i]; // allocate from the next empty block
                }
                if (blockArray[freeBlockIndex[currentFreeBlock]] != 0)
                {
                    //currentFreeBlock +=1;
                    blockArray[freeBlockIndex[currentFreeBlock]] = file[i];
                    //blockArray[freeBlockIndex[currentFreeBlock-1]+(vcb.blockSize-1)] = freeBlockIndex[currentFreeBlock];
                }
                k = 0;
                l=1;
                //freeBlockIndex[currentFreeBlock] += 1;
            }
            k += 1;    
        }
    }
    
    
    free(freeBlockIndex);
    
        
}*/

void add(int file[])
{
    //check block req
    double block = n/(vcb.blockSize-1);
    double blockReq = ceill(block); // blocks required
    printf("BLOCKREQ: %lf\n", blockReq);

    //// get count of free block
    int numberOfFreeBlocks = listCount(head);
    printf("WORKS BELOW WHILE LOOP");
   /* int count = 0;
    int track = 0;
    int freeIndex = 0;
    struct NODE *currentNode = head;
    int *arrayOfFreeIndex = (int*)malloc(sizeof(int)*numberOfFreeBlocks);
    while (currentNode->next != NULL)
    {
        arrayOfFreeIndex[freeIndex] = currentNode->file; // put all free index into a array
        freeIndex +=1;
        currentNode = currentNode->next;
    }

    
    

    if (blockReq < numberOfFreeBlocks || blockReq == numberOfFreeBlocks) // if enuogh blocks
    {
        for(int i=0;i<n; i++)
        {
            if (count == arrayOfFreeIndex[track]) // at start of block
            {
                removeFreeBlockNode(head);
                blockArray[count] = file[i];
                track +=1;
                count +=1;
            }
            else if (blockArray[count] == 0 && (count + 1) % vcb.blockSize != 0) // not start. not pointer 
            {
                blockArray[count] = file[i];
                count +=1;
            }
            else if ((count+1) % vcb.blockSize == 0 )// at pointer
            {
                blockArray[count] = arrayOfFreeIndex[track];
                count +=1;
            } 
        }
    }
    free(arrayOfFreeIndex);*/

}

void allocate()
{
    /// if user select allocation //
    //printList(head);
    add(fileArrayFour);
    printList(head);
    //setFileSize(fileArrayTwo);
    //blockArray[3] = 123;
    //setFreeBlockIndex();
    //add(fileArrayFour);
    //setFreeBlockIndex();
    //setFileIndex();
    /*printf("\nblockArray[0]: %d\n", blockArray[0]);
    printf("\nblockArray[1]: %d\n", blockArray[1]);
    printf("\nblockArray[2]: %d\n", blockArray[2]);
    printf("\nblockArray[3]: %d\n", blockArray[3]);
    printf("\nblockArray[4]: %d\n", blockArray[4]);
    printf("\nblockArray[5]: %d\n", blockArray[5]);
    printf("\nblockArray[6]: %d\n", blockArray[6]);
    printf("\nblockArray[7]: %d\n", blockArray[7]);
    printf("\nblockArray[8]: %d\n", blockArray[8]);
    printf("\nblockArray[9]: %d\n", blockArray[9]);
    printf("\nblockArray[10]: %d\n", blockArray[10]);
    printf("\nblockArray[11]: %d\n", blockArray[11]);
    printf("\nblockArray[16]: %d\n", blockArray[16]);*/
    printf("Linked List: %d", head->next->file); //// 2nd block index
    //printf("\nfilearray: %d", n);
    //////////////////////////////////
    return;
}

void read()
{
    int readfile;
    int i, j;
    int thisFileIndex;
    printf("Read what file?");
    scanf("%d", &readfile);
    
    for (i=0; i<60; i++)
    {
        if (readfile == directory[i].fileName)
    {
        printf("\ndirectory.fileName: %d\n", directory[i].fileName);
        printf("\ndirectory.fileIndex: %d\n", directory[i].fileIndex);
        thisFileIndex = directory[i].fileIndex;
        
    
    }
    
    }

   /* printf("\nFiles: \n");
    
    for (j = 0; j<20; j++)
    {

        if ((j + 1) % vcb.blockSize == 0)
        {
            thisFileIndex = blockArray[j + 1];
        }
        if ((j + 1) % vcb.blockSize != 0)
        {
            printf("\n%d\n", blockArray[thisFileIndex]);

        }
    }*/
}

void delete()
{
    int delete;
    printf("\nWhat file to delete: \n");
    scanf("%d", &delete);
    //Find the filename to delete
    int i, j;
    for (i = 0; i<121; i =+ (vcb.blockSize))
    {
        if (delete == blockArray[i])
        {
            for ( j = 0; j<vcb.blockSize-1; j++)
            {
                blockArray[i +j] = 0;
            }
        }
        else
        {
            printf("\nNo such file\n");
        }
    }
    return;

    
}

int main(){
    vcb.blockSize = 3; 
    //setFileSize(fileArrayTwo);
    setFreeBlockIndex();
    setFileIndex();

    ///prompt user
    int choose;
    printf("\nPress 1 to allocate\n");
    printf("\nPress 2 to read\n");
    printf("\nPress 3 to delete\n");
    printf("\nPress 0 to end\n");
    scanf("%d", &choose);
    if ( choose == 1)
    {
        allocate();
        
    }
    if ( choose == 2)
    {
        read();
    }
    if ( choose == 0 )
    {
        exit(0);
    }
    if ( choose == 3)
    {
        delete();
    }

    main();
    
}
