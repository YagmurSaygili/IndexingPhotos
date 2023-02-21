/* Creator : Yagmur Saygili / School Assigment

 	Self created library file to use modular approach
	and make it easier to read or inspect the code later on.
	
	Here AVLTree consepts, functions and their declarations 
	are defined.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLTreeNode* AVLTree;
struct AVLTreeNode
{
	struct  Node *head;
	struct  Node *tail;
	AVLTree left;
    AVLTree right;//This is to link lists as tree
	int size;//This will help me counting photos that each country has
    int height;
};

AVLTree InitialiseList(void);
void MakeEmptyTree(AVLTree);
void DisplayTree(AVLTree );

struct Node* Newnode(char *,char *,char *,char *,char *,int );
int AVLTreeHeight(AVLTree );

AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);

void PrintMaxCountry(AVLTree ,int );
void FindMaxforCountry(AVLTree ,int *);
void FindNumberOfTreeNodes(AVLTree,int *);
int CountYears(int *,int);
void StoreYears(AVLTree,int *,int *);
void PrintpopularYear(AVLTree,int);

void PrintpopularYear(AVLTree t,int year)//Here year variable holds the most repeated year
                                        //Again, I basically traverse the array recursively and print the matched years ones
{
    if (t!=NULL)
    {

        PrintpopularYear(t->left,year);
        PrintpopularYear(t->right,year);
        t->tail=t->head->next;
        while (t->tail!=NULL)
        {
            if (  (t->tail->year)==year)
               printf("%s,%s,%s,%s,%s,%d\n",t->tail->Name,t->tail->Dimension,t->tail->Size,t->tail->City,t->tail->Country,t->tail->year);
            t->tail=t->tail->next;
        }
    }
}

void StoreYears(AVLTree t,int array[],int *i)//This will load the years one by one in to the array
{
    //array will hold the years

    if (t!=NULL)
    {
        t->tail=t->head->next;
        while (t->tail!=NULL)
        {
            *i=*i+1;//Updating count
            array[*i]=t->tail->year;
            t->tail=t->tail->next;
        }
        StoreYears(t->left,array,i);
        StoreYears(t->right,array,i);
    }
}

int CountYears(int *years_array,int number_of_nodes)//This function basically Count the years and return the max repeated one
{
    int temp,maximum_number=0,repetition,i,j;

    int max_year;//This will hold the most repeated year

    for (i=0;i<number_of_nodes;i++)
    {
        temp=years_array[i];
        repetition=0;
        for (j=0;j<number_of_nodes;j++)
        {
            if (temp==years_array[j])
                repetition++;
        }
        if (repetition>maximum_number)
        {
            maximum_number=repetition;
            max_year=years_array[i];
        }

    }

    return max_year;

}

void FindNumberOfTreeNodes(AVLTree t,int *number)//This function basically takes the tree root and count how many tree nodes the tree has
                                    //I will use this number to create array and store years
{
    if (t!=NULL)//Basic traversing tree
    {
        t->tail=t->head->next;
        while (t->tail!=NULL)
        {

             *number= *number+1;
             t->tail=t->tail->next;
        }

        FindNumberOfTreeNodes(t->left,number);
        FindNumberOfTreeNodes(t->right,number);

    }
}

void FindMaxforCountry(AVLTree t,int *max)//This basically finds the maximum size of tree nodes and pass by reference
{
    if (t!=NULL)
    {
        t->tail=t->head->next;
        if (t->size>*max)
        {
            *max=t->size;
        }
        FindMaxforCountry(t->left,max);
        FindMaxforCountry(t->right,max);
    }
}

void PrintMaxCountry(AVLTree t,int max)//After finding max number of photos(max),
                                        // this function basically finds the node with max size and prints that node
{
    if (t!=NULL)
    {


        if (max==t->size)
        {
            while (t->tail!=NULL)
        {
            printf("%s,%s,%s,%s,%s,%d\n",t->tail->Name,t->tail->Dimension,t->tail->Size,t->tail->City,t->tail->Country,t->tail->year);
            t->tail=t->tail->next;
        }
        }
        PrintMaxCountry(t->left,max);
        PrintMaxCountry(t->right,max);
    }

}

AVLTree SingleRotateWithLeft(AVLTree A)
{
    AVLTree B=A->left;// Left child of the root node//which will become root after rotation
    AVLTree T=B->right; // This is the subtree of B if there is one

    B->right=A;//B is the root now
    A->left=T;

    B->height=Max(AVLTreeHeight(B->left),AVLTreeHeight(B->right));
    A->height=Max(AVLTreeHeight(A->left),AVLTreeHeight(A->right))+1;

    return B;
}

AVLTree SingleRotateWithRight(AVLTree A)
{
    AVLTree B=A->right;// Right child of the root node// will become root after rotation
    AVLTree T=B->left;// This is the subtree of B if there is one

    B->left=A;//B is the root now;
    A->right=T;

    B->height=Max(AVLTreeHeight(B->left),AVLTreeHeight(B->right));
    A->height=Max(AVLTreeHeight(A->left),AVLTreeHeight(A->right))+1;

    return B;
}

AVLTree DoubleRotateWithLeft(AVLTree C)//Left-Right Rotation
{
    AVLTree A=C->left;//Left child of the root
    AVLTree B=A->right;//Right child of the B node

    AVLTree T=B->left;

    B->left=A;
    A->right=T;

    A->height=Max(AVLTreeHeight(A->left),AVLTreeHeight(B->right))+1;

    C->height=Max(AVLTreeHeight(C->left),AVLTreeHeight(C->right));

    C->left=B;
    //That was rotation to left

    C=SingleRotateWithLeft(C);//As last step right rotating the root and the left child of the root

    return C;
}

AVLTree DoubleRotateWithRight(AVLTree A)// A is the root initially
{
    AVLTree C=A->right;//Right Child of the root
    AVLTree B=C->left;//Left child of the right child of the root

    AVLTree T=B->left;

    B->right=C;
    C->left=T;

    C->height=Max(AVLTreeHeight(C->left),AVLTreeHeight(C->right))+1;
    B->height=Max(AVLTreeHeight(A->left),AVLTreeHeight(A->right));

    A->right=B;

    // That was rotation to right

    A=SingleRotateWithRight(A);//As last step left rotating the root and the left child of the root

    return A;
}



int AVLTreeHeight(AVLTree t)
{
	if (t== NULL)
		return -1;
	else
		return t->height;
}


void DisplayTree(AVLTree t)
{

	if (t != NULL)
	{

        DisplayTree(t->left);
        t->tail=t->head->next;
		while(t->tail!=NULL)
        {
		printf("%s,%s,%s,%s,%s,%d\n",t->tail->Name,t->tail->Dimension,t->tail->Size,t->tail->City,t->tail->Country,t->tail->year);
		t->tail = t->tail->next;
        }

        DisplayTree(t->right);

	}
}


struct Node* Newnode(char name[50],char dimension[50],char size[50],
                    char city[50],char country[50],int year)
{
    struct Node* newnode;
    newnode=(struct Node*)malloc(sizeof(struct Node));//Allocating tree node
    if (newnode==NULL)
    {
        printf("Error creating tree node\nALLAH ALLAH");
        exit(1);
    }

    //Storing data
    strcpy(newnode->Name,name);
    strcpy(newnode->Dimension,dimension);
    strcpy(newnode->Size,size);
    strcpy(newnode->City,city);
    strcpy(newnode->Country,country);
    newnode->year=year;

    newnode->next=NULL;

    return newnode;
}


void MakeEmptyTree(AVLTree t)//Takes a tree node and organize its head and tail
{

	t->head = (struct Node*)malloc(sizeof(struct Node));
	if (t->head == NULL)
		printf("Out of memory!\n");

	t->head->next = NULL;
	t->tail = t->head;

	t->size = 0;
}

AVLTree Iniitialisetree(void)
{
    return NULL;
}





