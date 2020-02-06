///////////////////////////////////////////////////////////////
//***********************************************************//
//* THINGS TO FIX :                                         *//
//* 1. directory.fileIndex  IS 0. FIX IT ###DONE###         *//
//* 2. WHAT IS REQUIRED FOR READ()                          *//
//* 3. MAKE DELETE()                                        *//
//* 4. DOES NOT WORK FOR BLOCKSIZE = 2                      *//
//* 5. MAKE GETFILESIZE()                                   *//
//* 6. UPGRADE ADD() SO THAT BLOCKARRAY[POINTER] IS         *//
//*    WORKING... (NEED directory.fileIndex)                *//
//***********************************************************//
///////////////////////////////////////////////////////////////


#include<stdio.h>
#include<stdlib.h>

int blockArray[121];
int fileArray[7] = {100, 101, 102, 103, 104, 105, 106};
size_t n = sizeof(fileArray) / sizeof(fileArray[0]);

struct VCB
{
    int totalBlocks;
    int numberOfFreeBlocks;
    int blockSize;
    int freeBlockIndex[24];
};

struct Directory
{
    int fileName[24];
    int fileIndex[24];
    int fileSize[24];
};

struct VCB vcb;
struct Directory directory;


void setFreeBlockIndex();
void setFileSize();
void setFileIndex();
void add();
void allocate();
void read();
void delete();

void setFreeBlockIndex()
{
    //initial all is free block

    int i;
    for (i = 0; i<121; i += (vcb.blockSize))
    {
        //for the very first blockArray[0]
        if (blockArray[1] == 0)
        {
            vcb.freeBlockIndex[i/vcb.blockSize] = 1;
        }
        //for when blockArray[?] have no file -- update freeblockindex[] to the index of blockArray[]
        if (blockArray[i+1] == 0)
        {    
            vcb.freeBlockIndex[i/vcb.blockSize] = i+1;
            directory.fileName[i/vcb.blockSize] = blockArray[i+1];
            directory.fileIndex[i/vcb.blockSize] = 0;
        }
        //for when blockArray[?] have a file -- update freeblockindex to 0
        if (blockArray[i+1] !=0 )
        {
            vcb.freeBlockIndex[i/vcb.blockSize] = 0;
            directory.fileName[i/vcb.blockSize] = blockArray[i+1];
            directory.fileIndex[i/vcb.blockSize] = (i+1);


        }
    }
}

void setFileIndex()
{
    int i;
    for (i = 0; i<n; i += (vcb.blockSize))
    {
        if (blockArray[i+1] == 0)
        {    
            directory.fileIndex[i/vcb.blockSize] = 0;
        }

        if (blockArray[i+1] !=0 )
        {
            directory.fileIndex[i/vcb.blockSize] = (i+1);
        }
    }

}


void setFileSize()
{
size_t n = sizeof(fileArray) / sizeof(fileArray[0]);
directory.fileSize[0] = n;

}

void add()
{
    int i;
    int j = 0;
    for (i = 0; i<n ; i++)
    {   
        
        if( (i+1+j) % vcb.blockSize == 0 )
            {
                j++;
                printf("\nj=%d\n", j);
                //blockArray[i+1+j] = fileArray[i];
                //continue;
                //break;
            } 
        if (blockArray[i+1+j] == 0 && (i+1+j) % vcb.blockSize != 0)
        {
            
            blockArray[i+1+j] = fileArray[i];

        }

    }
}

void allocate()
{
    /// if user select allocation //
    add();
    setFreeBlockIndex();
    setFileIndex();
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
    printf("\nblockArray[16]: %d\n", blockArray[16]);
    printf("\nvcb.freeBlockIndex[0]: %d\n", vcb.freeBlockIndex[0]);
    printf("\nvcb.freeBlockIndex[1]: %d\n", vcb.freeBlockIndex[1]);
    printf("\nvcb.freeBlockIndex[2]: %d\n", vcb.freeBlockIndex[2]);
    printf("\nvcb.freeBlockIndex[3]: %d\n", vcb.freeBlockIndex[3]);
    printf("\nvcb.freeBlockIndex[4]: %d\n", vcb.freeBlockIndex[4]);
    printf("\ndirectory.fileIndex[0]: %d\n", directory.fileIndex[0]);
    printf("\ndirectory.fileIndex[1]: %d\n", directory.fileIndex[1]);
    printf("\nfilearray: %d", n);
    //////////////////////////////////
    return;
}

void read()
{
    int readfile;
    int i;
    printf("Read what file?");
    scanf("%d", &readfile);
    
    for (i=0; i<24; i++)
    {
        if (readfile == directory.fileName[i])
    {
        printf("\ndirectory.fileName: %d\n", directory.fileName[i]);
        printf("\ndirectory.fileIndex: %d\n", directory.fileIndex[i]);
        // bug : directory.fileIndex[i] = 0/// suppose to be = 1
    }
    
    }
    
}

void delete()
{

}

int main(){
    vcb.blockSize = 3; //does not work for 2
    setFreeBlockIndex();
    setFileIndex();

    ///prompt user////
    int choose;
    printf("\nPress 1 to allocate\n");
    printf("\nPress 2 to read\n");
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

    main();
    




    

}