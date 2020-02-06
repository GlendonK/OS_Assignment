////// ***DUE 22/3/2020 23:59*** ///////
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>



//make directory.. use 2 blocks 
struct Directory {
    int file;
    int *pointerhead;


};
//vol control block
struct VCB {
    int totalblock;
    int freeblock;
    int blocksize;
    int *freeblockpointer; // linked list

};

struct file{
    char letter[100];
    char numba[100];
} fileofopen;

struct arrayfile{
    char ch[20];
} afile[20];

//make the block
int block[120];
int blocksize;
int choose;
struct VCB vcb;
int sample[3] = {100,101,102};
int i =0 ;



void addfile();

int main(){ 
    FILE *fp = fopen("CSC1007-SampleCSV.csv","r");
    char buf[1024];

    if (!fp) {
        printf("cant open file");
        return 1;
    }

    char arr[20][20];
    int k;
    

    while (fgets(buf, 1024, fp)){
        //printf("%s\n",buf);
        for ( i = 0; i < sizeof(buf); i++)
        {
            for ( k = 0; k< i; k++)
            {
                arr[i][k] = buf[i];
                //store each instance of buf into 2D array
                // 1st row is ADD, 2nd onwards is number
                //atoi() to cast char to int
            
            }
               
        }
        
        //***check 'a' for allocate ***//
       /* fileofopen.letter[i] = buf[0];
        if (fileofopen.letter[i] == 'a'){
            addfile();
        }
        i=i+1;*/
           
    }
    printf("\n%s",arr);
    
  
    fclose(fp);
    
    //determine block size
    /*printf("what the block size: ");
    scanf("%d",&vcb.blocksize);

    vcb.totalblock = 130 / vcb.blocksize;*/
    vcb.blocksize = 5;
    int i= 0;

    /*while (buf[i] != 0){
        i = i +1 ;
        if ("add"){
            addfile();
        }
        
    }*/

    


}

void addfile(){
    printf("\n1");
    

}


























/*#define blockSize 5

int *ptrNext;

///this will contain the pointers to the next block////
struct Node
{
    int *nextPointer;
    int *currentPointer;

};

///this is the block skeleton/////
struct Block
{
    
    int file[blockSize - 1];
    struct Node node;
    
    
};

///this will contain the filename, start and end pointer?////
//will be a array... takes up 1 block???////
struct Directory
{
    int filename[blockSize - 1];
    int *start;
    int *end;

};
struct Block block[10];
//file to add 123 111 222 333 . last element for pointer to next
void addfile(){
    
    int i,e;

    for (i=0; i<sizeof(block)-1; i++){ ////loop number of blocks /////

        if (block[i].file != 0) //check empty block
        {
            
               
        }

    }
    int inputn;

    
    //***must have user input block length or number of files, need to loop to that limit.///
    int *ptr = (int *)malloc(inputn * sizeof(int));
        

        ////if file more den 4 input, use more blocks. malloc///
        ////make a dynamic array storing the file data////
        ////loop asssign the data to block entry... if full go fill next block///

        //if there need use more den 1 block den need increase e//
        for (e = 0; e < sizeof(block)-1; e++){
            
            for (i = 0; i<blockSize - 1; i++){
                //////////input files/////////////
                printf("input: ");
                scanf("%d", &block[e].file[i]);
                printf("%d\n", block[e].file[i]);
                //////////////////////////////////

                ///directory///////////////////////////
                struct Directory directory;
                directory.filename[i] = block[e].file[i];
                directory.start = &block[e].file[0];
                directory.end = &block[e].file[blockSize - 1];
                //////////////////////////////////////
            }

        }
        
    

    ////the pointer pointint to the next block///////
    ptrNext = &block[1].file[0];
    block[0].file[blockSize] = *ptrNext;
    block[0].node.nextPointer = ptrNext;
    printf("%x", ptrNext);
    ////////////////////////////////////////////////
    


}


int main(){
    addfile();

}*/


/*#include<stdio.h>
#define TB 100
#include<string.h>
#include<stdlib.h>
void allocate();
void deallocate();
void display();
int BFull();
struct Link
{
    char n[30];
    int len;
    int st;
    struct node
    {
        int index;
        struct node *next;
    }*Start,*current,*newnode,*temp;
}F[30];
int Table[TB+1],pos=0,r,i,j,ch,B=0;
char fn[30];
int main()
{
     printf("\n Linked File Allocation \n\n");
     do{
     printf("\n\n1.Allocate\n2.Deallocate\n3.Display\n4.Exit");
     printf("\n\nEnter Your choice : ");
     scanf("%d",&ch);


     switch(ch)
     {
                case 1:
                    pos++;
                    allocate();
                    break;

                case 2:
                    deallocate();
                    break;

                case 3:
                    display();
                    break;

                case 4:
                    exit(0);

                default:
                    printf("\nInvalid Choice ");
        }
     }while(ch!=4);

}
void allocate()
{
   printf("\nEnter File Name : ");
   scanf("%s",&(F[pos].n));
   printf("\nEnter File Length : ");
   scanf("%d",&(F[pos].len));
   F[pos].Start=NULL;
   if(BFull())
   {
        pos--;
       printf("\n\nNo Enough Free Space Available \n");
       return;
   }

   for(i=1;i<=F[pos].len;i++)
   {
        F[pos].newnode=(struct node *)malloc(sizeof(struct node));

        while(1)
        {

            r=rand()%TB+1;
            if(Table[r]==0)
            {
                    F[pos].newnode->index =r;
                    F[pos].newnode->next=NULL;
                    if(F[pos].Start==NULL)
                    {
                        F[pos].Start=F[pos].newnode;
                        F[pos].current=F[pos].newnode;
                    }
                    else
                    {
                        F[pos].current->next=F[pos].newnode;
                        F[pos].current=F[pos].newnode;
                    }

                    Table[r]=1;
                    break;
            }
        }
    }
    F[pos].st=F[pos].Start->index;
    for(i=r;i<r+F[pos].len;i++)
        Table[i]=1;
    printf("\n\tFile Allocation Table\n");
    printf("\nFileName\tStart\tEnd\tLength\n");
    for(i=1;i<=pos;i++)
    {
        printf("\n%s\t\t%d\t%d\t%d",F[i].n,F[i].st,F[pos].current->index,F[i].len);
        printf("\n");
    }

}
void deallocate()
{
   printf("\nEnter The File Name : ");
   scanf("%s",&fn);
   for(i=1;i<=pos;i++)
   {
            if(strcmp(F[i].n,fn)==0)
            {
                F[i].current=F[i].Start;
                while(F[i].current)
                {
                    Table[F[i].current->index]=0;
                    F[i].temp=F[i].current;
                    F[i].current=F[i].current->next;
                    free(F[i].temp);
                }

                strcpy(F[i].n,"NULL");
                F[i].st=0;
                F[i].len=0;
                printf("\nFile (%s) Deleted Successfully \n",fn);
                break;
            }
            else
                printf("\nDeletion Unsuccessful\n");
    }
    printf("\n\t\tFile Allocation Table\n");
    printf("\nFileName\tStart\tLength\n");
    for(i=1;i<=pos;i++)
    {
        printf("\n%s\t\t%d\t%d",F[i].n,F[i].st,F[i].len);
        printf("\n");
    }
}
void display()
{
    printf("\nEnter The File Name : ");
    scanf("%s",fn);
    printf("\nBlocks Allocated Are : ");
    for(i=1;i<=pos;i++)
    {
        if(strcmp(F[i].n,fn)==0)
        {
            F[i].current=F[i].Start;
            while(F[i].current)
            {
               printf(">--%d-->",F[i].current->index);
               F[i].current=F[i].current->next;
            }
            break;
        }
    }
    if(i==pos+1)
    {
        printf("\n\nNo File Found\n");
    }
}
int BFull()
{
    for(i=1,B=0;i<=pos;i++)
        B=B+F[i].len;
    if(B>TB)
        return 1;
    else
        return 0;
}*/

/*#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void main()
{
int f[50], i, st, len, j, c, k, count = 0;
clrscr();
for(i=0;i<50;i++)
f[i]=0;
printf("Files Allocated are : \n");
x: count=0;
printf("Enter starting block and length of files: ");
scanf("%d%d", &st,&len);
for(k=st;k<(st+len);k++)
if(f[k]==0)
count++;
if(len==count)
{
for(j=st;j<(st+len);j++)
if(f[j]==0)
{
f[j]=1;
printf("%d\t%d\n",j,f[j]);
}
if(j!=(st+len-1))
printf("The file is allocated to disk\n");
}
else
printf("The file is not allocated \n");
printf("Do you want to enter more file(Yes - 1/No - 0)");
scanf("%d", &c);
if(c==1)
goto x;
else
exit();
getch();
}*/