<<<<<<< HEAD

//////////////////////////////////////////////////////////////
// THINGS TO FIX :                                         ///
// 1. WHAT IS REQUIRED FOR READ()                          ///
// 2. ***MAKE DELETE()                                     ///
// 3. !!!!!MAKE GETFILESIZE() needed to loop each          ///
//     file array by its size to allocate                  ///               ///
// 4. DIRECTORY HOW MANY BLOCKS?                           ///
// 5. freeBlockIndex[60]; fileName[60]; fileIndex[60];     ///
//     fileSize[60]; THE SIZE 60? BEST SCALABLE SIZE       ///
//     DEPENDING ON THE BLOCK SIZE.                        ///
// 6. FREE SPACE MANAGEMENT                                ///                     ///
// 7.                                                      ///
// 8.                                                      ///
// 9.                                                      ///
//                                                         ///
//////////////////////////////////////////////////////////////



#include<stdio.h>
#include<stdlib.h>

int blockArray[121];
int fileArray[2] = {100, 101};
int fileArrayTwo[3] ={102, 103, 104};
int fileArrayThree[4] = {105, 106, 107, 108};
int fileArrayFour[5] = {109, 110, 111, 112, 113};
size_t n = sizeof(fileArray) / sizeof(fileArray[0]);

struct VCB
{
    int totalBlocks;
    int numberOfFreeBlocks;
    int blockSize;
    int freeBlockIndex[60];
};

struct Directory
{
    int fileName[60];
    int fileIndex[60];
    int fileSize[60];
};

struct VCB vcb;
struct Directory directory;


void setFreeBlockIndex();
unsigned setFileSize();
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
        //printf("\ni is:%d\n", i);
        //for the very first blockArray[0]
        /*if (blockArray[1] == 0)
        {
            printf("pos 1");
            vcb.freeBlockIndex[i/vcb.blockSize] = 1;
        }*/
        //for when blockArray[?] have no file -- update freeblockindex[] to the index of blockArray[]
        if (blockArray[i+1] == 0)
        {    
            //printf("pos 2");
            vcb.freeBlockIndex[i/vcb.blockSize] = i+1;
            //printf("here1");
            directory.fileName[i/vcb.blockSize] = blockArray[i+1];
            //printf("here2");
            directory.fileIndex[i/vcb.blockSize] = 0;
            //printf("here3");
        }
        //for when blockArray[?] have a file -- update freeblockindex to 0
        else if (blockArray[i+1] !=0 )
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

unsigned setFileSize(int file[])
{
    n = 3;
    //size_t n = sizeof(file) / sizeof(file[0]);
    //directory.fileSize[0] = n;


}

void add(int file[])
{
    int i;
    int j = 0;
    int endBlockIndex, nextIndex;
    for (i = 0; i<n ; i++)
    {   
        
        if( (i+1+j) % vcb.blockSize == 0 )
        {
            endBlockIndex = (i + 1 + j);
            j++;
            nextIndex = (i +j + 1);
            blockArray[endBlockIndex] = nextIndex;
            
            printf("\nj=%d\n", j);
                
        } 
        //allocating
        if (blockArray[i+1+j] == 0 && (i+1+j) % vcb.blockSize != 0)
        {
            if (blockArray[((i*vcb.blockSize) +1)] == 0)
            {
                nextIndex = (i + 1 + j);
            
                blockArray[i+1+j] = file[i];
            }
            
        }

    }
}

void allocate()
{
    /// if user select allocation //
    //setFileSize(fileArrayTwo);
    add(fileArray);
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
    int i, j;
    int thisFileIndex;
    printf("Read what file?");
    scanf("%d", &readfile);
    
    for (i=0; i<60; i++)
    {
        if (readfile == directory.fileName[i])
    {
        printf("\ndirectory.fileName: %d\n", directory.fileName[i]);
        printf("\ndirectory.fileIndex: %d\n", directory.fileIndex[i]);
        thisFileIndex = directory.fileIndex[i];
        
    
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
    vcb.blockSize = 3; //does not work for 2
    setFileSize(fileArrayTwo);
    setFreeBlockIndex();
    setFileIndex();

    ///prompt user////
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

/*
                   ▄              ▄
                  ▌▒█           ▄▀▒▌
                  ▌▒▒█        ▄▀▒▒▒▐
                 ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
               ▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
             ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌
            ▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌
            ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
           ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌
           ▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌
          ▌▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐
          ▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌
          ▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐
           ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌
           ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐
            ▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌
              ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
                ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀
                   ▒▒▒▒▒▒▒▒▒▒▀▀

=======

/**************************************************************
***************************************************************
*** THINGS TO FIX :                                         ***
*** 1. directory.fileIndex  IS 0. FIX IT ###DONE###         ***
*** 2. WHAT IS REQUIRED FOR READ()                          ***
*** 3. MAKE DELETE()                                        ***
*** 4. DOES NOT WORK FOR BLOCKSIZE = 2  ###DONE###          ***
*** 5. !!!!!MAKE GETFILESIZE() needed to loop each          ***
***     file array by its size to allocate                  ***
*** 6. UPGRADE ADD() SO THAT BLOCKARRAY[POINTER] IS         ***
***    WORKING... (NEED directory.fileIndex)                ***
*** 7. DIRECTORY HOW MANY BLOCKS?                           ***
*** 8. freeBlockIndex[60]; fileName[60]; fileIndex[60];     ***
***     fileSize[60]; THE SIZE 60? BEST SCALABLE SIZE       ***
***     DEPENDING ON THE BLOCK SIZE.                        ***
*** 9. FREE SPACE MANAGEMENT                                ***
***                                                         ***
***************************************************************
**************************************************************/



#include<stdio.h>
#include<stdlib.h>

int blockArray[121];
int fileArray[2] = {100, 101};
int fileArrayTwo[3] ={102, 103, 104};
size_t n = sizeof(fileArray) / sizeof(fileArray[0]);

struct VCB
{
    int totalBlocks;
    int numberOfFreeBlocks;
    int blockSize;
    int freeBlockIndex[60];
};

struct Directory
{
    int fileName[60];
    int fileIndex[60];
    int fileSize[60];
};

struct VCB vcb;
struct Directory directory;


void setFreeBlockIndex();
unsigned setFileSize();
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
        //printf("\ni is:%d\n", i);
        //for the very first blockArray[0]
        /*if (blockArray[1] == 0)
        {
            printf("pos 1");
            vcb.freeBlockIndex[i/vcb.blockSize] = 1;
        }*/
        //for when blockArray[?] have no file -- update freeblockindex[] to the index of blockArray[]
        if (blockArray[i+1] == 0)
        {    
            //printf("pos 2");
            vcb.freeBlockIndex[i/vcb.blockSize] = i+1;
            //printf("here1");
            directory.fileName[i/vcb.blockSize] = blockArray[i+1];
            //printf("here2");
            directory.fileIndex[i/vcb.blockSize] = 0;
            //printf("here3");
        }
        //for when blockArray[?] have a file -- update freeblockindex to 0
        else if (blockArray[i+1] !=0 )
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

unsigned setFileSize(int file[])
{
    n = 3;
    //size_t n = sizeof(file) / sizeof(file[0]);
    //directory.fileSize[0] = n;


}

void add(int file[])
{
    int i;
    int j = 0;
    int endBlockIndex, nextIndex;
    for (i = 0; i<n ; i++)
    {   
        
        if( (i+1+j) % vcb.blockSize == 0 )
        {
            endBlockIndex = (i + 1 + j);
            j++;
            nextIndex = (i +j + 1);
            blockArray[endBlockIndex] = nextIndex;
            
            printf("\nj=%d\n", j);
                
        } 
        //allocating
        if (blockArray[i+1+j] == 0 && (i+1+j) % vcb.blockSize != 0)
        {
            if (blockArray[((i*vcb.blockSize) +1)] == 0)
            {
                nextIndex = (i + 1 + j);
            
                blockArray[i+1+j] = file[i];
            }
            
        }

    }
}

void allocate()
{
    /// if user select allocation //
    //setFileSize(fileArrayTwo);
    add(fileArrayTwo);
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
    int i, j;
    int thisFileIndex;
    printf("Read what file?");
    scanf("%d", &readfile);
    
    for (i=0; i<60; i++)
    {
        if (readfile == directory.fileName[i])
    {
        printf("\ndirectory.fileName: %d\n", directory.fileName[i]);
        printf("\ndirectory.fileIndex: %d\n", directory.fileIndex[i]);
        thisFileIndex = directory.fileIndex[i];
        
    
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

/*
                   ▄              ▄
                  ▌▒█           ▄▀▒▌
                  ▌▒▒█        ▄▀▒▒▒▐
                 ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
               ▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
             ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌
            ▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌
            ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
           ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌
           ▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌
          ▌▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐
          ▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌
          ▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐
           ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌
           ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐
            ▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌
              ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
                ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀
                   ▒▒▒▒▒▒▒▒▒▒▀▀

>>>>>>> a5a03422438a9f7d047a0a2b43ecd3cc16c47b69
*/