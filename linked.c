#include<stdio.h>
#include<stdlib.h>

int blockArray[121];
int fileArray[7] = {100, 101, 102, 103, 104, 105, 106};

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
void add();
void allocate();
void read();
void delete();

void setFreeBlockIndex()
{
    //initial all is free block

    int i;
    for (i = 0; i<(120+1); i += (vcb.blockSize))
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
        if (blockArray[i+1] != 0)
        {
            vcb.freeBlockIndex[i/vcb.blockSize] = 0;
            directory.fileName[i/vcb.blockSize] = blockArray[i+1];
            directory.fileIndex[i/vcb.blockSize] = (i+1);


        }
    }
}


void setFileSize()
{
    directory.fileSize[0] = sizeof(fileArray);
}

void add()
{
    int i;
    for (i = 0; i<(120+1); i++)
    {
        if (blockArray[i+1] == 0 && (i+1) % vcb.blockSize != 0)
        {
            blockArray[i+1] = fileArray[i];

        }

    }
}

void allocate()
{
    /// if user select allocation //
    add();
    setFreeBlockIndex();
    printf("\nblockArray[1]: %d\n", blockArray[5]);
    printf("\nvcb.freeBlockIndex[0]: %d\n", vcb.freeBlockIndex[0]);
    printf("\nvcb.freeBlockIndex[1]: %d\n", vcb.freeBlockIndex[1]);
    printf("\nvcb.freeBlockIndex[2]: %d\n", vcb.freeBlockIndex[2]);
    printf("\nvcb.freeBlockIndex[3]: %d\n", vcb.freeBlockIndex[3]);
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
    vcb.blockSize = 5;
    setFreeBlockIndex();

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