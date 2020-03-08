//! MUST INITIALISE THE LINKED LIST FIRST "111". AS LINKED LIST CAN ONLY BE BUILDT ONCE.
//! LINKED LIST WILL APPEND TO TAIL TO ITSELF IF MULTIPLE RUNS

//! DO NOT STORE FILE NAME IN MAIN BLOCKARRAY. ONLY STORE IN DIRECTORY

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int blockArray[121];
int fileArray[2] = {100, 101};
int fileArrayTwo[3] ={102, 103, 104};
int fileArrayThree[4] = {105, 106, 107, 108};
int fileArrayFour[5] = {109, 110, 111, 112, 113};
int n = sizeof(fileArrayFour) / sizeof(fileArrayFour[0]); //! NEED TO CHANGE THIS TO CHANGE ARRAY.
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
void setFileIndex(int fileName, int fileNameTwo);
void add(int file[]);
void allocate();
void read();
void delete();
void createFreeBlockNode(int firstEmptyBlockIndex);
void addFreeBlockNode(struct NODE *head, int emptyBlockIndex);
void removeFreeBlockNode(struct NODE * head);
void freePointers(struct NODE *currentNode, struct NODE *head);
void getNextFreeBlock(struct NODE *head);
void setBlockStart();

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

void removeFreeBlockNode(struct NODE *head) 
{   
    if (head != NULL)
    {
        struct NODE *currentNode = head->next;
        //free(head->next);
        head->file = 0;
        head->next = NULL;
        head->file = currentNode->file;
        head->next = currentNode->next;
        
    }
    

}


/* 
!need to free all the pointers after allocate ?
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
        currentNode = currentNode->next;
    }
    return numNode;
}

void setFreeBlockIndex() // build the linked list
{
    int i;
    for(i=0;i<60;i+=vcb.blockSize)
    {
        if(blockArray[i] == -1)
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
    }

    

}

void setFileIndex(int fileName, int fileNameTwo)
{
    int i;
    int blockCounter = 0;
    int pointerCounter;
    for (i = 0; i<60; i++)
    {
        if (blockArray[blockCounter] == -1) // if block entry is empty
        {    
            directory[i].fileIndex = -1;
            directory[i].fileName = blockArray[blockCounter];
            blockCounter = blockCounter + vcb.blockSize; // go next starting entry block
        }

        if (blockArray[blockCounter] != -1 && blockArray[blockCounter] == fileNameTwo ) // if block entry is occupied and entry is the filename + 1
        {
            directory[i].fileIndex = (blockCounter); // save file start
            directory[i].fileName = fileName; // save file name
            pointerCounter = blockCounter; // clone counter
            //printf("109");
            if (blockArray[pointerCounter + vcb.blockSize -1] == -1) // if file ends in the start block make the fileEnd = fileStart
            {
                directory[i].fileEnd = blockCounter;
            }

            while (blockArray[pointerCounter + vcb.blockSize -1] != -1) // while pointer entry not empty. 
                                                                        //to find the file end which is when the poitner entry is -1
                                                                        // operate within a block at a time.
            {
                //pointerCounter = pointerCounter +vcb.blockSize; // go next block
                directory[i].fileEnd = blockArray[pointerCounter + vcb.blockSize -1]; // save file end as the element of pointer index/entry
                pointerCounter = blockArray[pointerCounter + vcb.blockSize -1]; //  jump to next block the file using.
            }
            //directory[i].fileEnd = pointerCounter; // save file end
            blockCounter = blockCounter + vcb.blockSize; // go next block
        }
        if (blockArray[blockCounter] != -1 && blockArray[blockCounter] != fileNameTwo)
        {
            //printf("%d", i);
            blockCounter = blockCounter + vcb.blockSize;
        }
    }

}

unsigned setFileSize(int file[])
{
    //n = 3;
    //size_t n = sizeof(file) / sizeof(file[0]);
    //directory.fileSize[0] = n;


}

void setBlockStart() // make all empty entry = -1
{
    for (int i = 0; i<60; i++)
    {
        if (blockArray[i] == 0)
        {
            blockArray[i] = -1;
        }
       
    }
}


void add(int file[])
{
    blockArray[0] = 500; //test 
    removeFreeBlockNode(head); // test
    //check block req
    double block = (n-1)/(vcb.blockSize-1);
    double blockReq = ceill(block); // blocks required
    printf("BLOCKREQ: %lf\n", blockReq);

    //// get count of free block
    int numberOfFreeBlocks = listCount(head);
    int count = 0;
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
        count = arrayOfFreeIndex[0];
        for(int i=0;i<(n); i++)
        {
            if ( i == 0 )
            {
                continue;
            }
            else if (count == arrayOfFreeIndex[track] && blockArray[count] == -1) // at start of block
            {
                removeFreeBlockNode(head);
                blockArray[count] = file[i];
                track +=1;
                count +=1;
            }
            else if (blockArray[count] == -1 && (count + 1) % vcb.blockSize != 0) // not start. not pointer 
            {
                blockArray[count] = file[i];
                count +=1;
            }
            
            else if (count == arrayOfFreeIndex[track] && blockArray[count] !=-1) // when a starting block entry is occupied
            {
                track +=1;
                count = arrayOfFreeIndex[track];
                i -=1;
            }
            
            else if ((count+1) % vcb.blockSize == 0 )// at pointer
            {
                blockArray[count] = arrayOfFreeIndex[track];
                count +=1;
                //track +=1;
                i -=1;
            } 
            
        }
    }
    else if(blockReq > numberOfFreeBlocks) //! BUG: does not run for some reason
    {
        printf("\nNot Enough Blocks\n");
    }
    
    free(arrayOfFreeIndex);
    setFileIndex(file[0], file[1]);

}

void allocate()
{
    /// if user select allocation //
    //printList(head);
    //add(fileArrayFour);
    add(fileArrayFour);
    //removeFreeBlockNode(head);
    //removeFreeBlockNode(head);
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
    for (int i = 0; i<61; i++)
    {
        printf("\nblockArray[%d]: %d",i,blockArray[i]);
    }
    printf("\nLinked List: %d", head->next->file); //// 2nd block index
    //printf("\nfilearray: %d", n);
    //////////////////////////////////
    return;
}

void read()
{
    int readfile;
    int i, j;
    //int thisFileIndex;
    printf("Read what file?");
    scanf("%d", &readfile);
    
    for (i=0; i<60; i++)
    {
        if (readfile == directory[i].fileName)
        {
            printf("\ndirectory.fileName: %d\n", directory[i].fileName);
            printf("\ndirectory.fileIndex: %d\n", directory[i].fileIndex);
            printf("\ndirectory.fileEnd: %d\n", directory[i].fileEnd);
            //thisFileIndex = directory[i].fileIndex;
        }
        
    }
}

void delete() 
{
    int delete;
    printf("\nWhat file to delete: \n");
    scanf("%d", &delete);
    //Find the filename to delete
    int i, j, delName, delStart, delEnd;
    int count = 0;
    
        /*
        //// get the file name and start index and fileEnd. 
        //// directory[i].fileName == delete:
        //// directory[i].fileIndex , directory[i].fileEnd is the start and end.
        //// for i=fileIndex i<filesize(n)+fileIndex i++:
        //// blockArray[i] = -1
        //// if index entry != -1:
        //// blockArray[index entry] = -1
        */
       for (i = 0; i<60; i++)
       {
           if (delete == directory[i].fileName) // when find the filename to del
           {
               delName = directory[i].fileName; // save for later use
               delStart = directory[i].fileIndex;
               addFreeBlockNode(head, delStart);
               //delEnd = directory[i].fileEnd;
               directory[i].fileName = 0; // set to 0
               directory[i].fileIndex = 0;
               directory[i].fileEnd = 0;

           }
       }
       for (j = 0; j<n-1; j++)
       {
           if ( ((delStart + count)+1) % vcb.blockSize == 0 && blockArray[delStart+count] != -1) // delete when at pointer and jump to next block
           {
               int temp = delStart; // save for later use
               delStart = blockArray[delStart + count];
               blockArray[temp + count] = -2;
               //blockArray[temp + count + 1] = -2;
               addFreeBlockNode(head, delStart); // release nodes
               count = 0; // reset counter before going next block              
           }
           blockArray[delStart + count] = -2; // delete
           count++;
       }
       printList(head);

       for (int i = 0; i<61; i++)
    {
        printf("\nblockArray[%d]: %d",i,blockArray[i]);
    }
    
    
    return;

    
}

int main(){
    vcb.blockSize = 10; 
    //setFileSize(fileArrayTwo);
    setBlockStart(); // make all block entry -1
    //setFreeBlockIndex(); // must only run once
    //setFreeBlockIndex();

    ///prompt user
    int choose;
    printf("\nPress 111 to initialise linked list\n");
    printf("\nPress 1 to allocate\n");
    printf("\nPress 2 to read\n");
    printf("\nPress 3 to delete\n");
    printf("\nPress 0 to end\n");
    scanf("%d", &choose);
    if ( choose == 1)
    {
        allocate();
        
    }
    else if ( choose == 2)
    {
        read();
    }
    else if ( choose == 0 )
    {
        exit(0);
    }
    else if ( choose == 3)
    {
        delete();
    }
    else if ( choose == 111)
    {
        setFreeBlockIndex(); // must only run once
    }
    

    main();
    
}
