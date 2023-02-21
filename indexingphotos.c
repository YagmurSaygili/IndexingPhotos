/* Creator : Yagmur Saygili / School Assigment

 	Main file where the program runs from
	
	Here taken from Node and AVLTree libraries( self created ), 
    functions are used to manage more complex operations.

    The program should be executed from the command line by giving
    photos.txt like file given as a parameter

    Example --> C:\Desktop > indexingphotos.exe photos.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Node.h"

#include "AVLTree.h"


AVLTree readData(char *);
AVLTree InsertPhoto(char *,char *,char *,char *,char *,int ,AVLTree);
void displayIndex(AVLTree);
void popularYear(AVLTree);
void popularCountry(AVLTree);
void displayIndex(AVLTree);

AVLTree readData(char str[])
{

    char name[50],dimension[100],size[50],city[50],country[50];
    int year;

    AVLTree root=Iniitialisetree();//Creating a tree and making it null


    char line[200],val[100];// val here reads the values in terms of strings

    FILE *fp;


    fp=fopen(str,"r");

     if (fp==NULL)
        printf("\nCould not open file");


   while( fgets(line,sizeof(line),fp) )
   {


       fflush(stdin);
       strcpy (name,strtok(line,","));
      //Storing name

       strcpy (dimension,strtok(NULL,","));
       //Storing dimension

       strcpy (size,strtok(NULL,","));
       //Storing size

       strcpy (city,strtok(NULL,","));
       //Storing city

       strcpy (country,strtok(NULL,","));
       //Storing country

       strcpy (val,strtok(NULL,"\n"));
       year=atoi(val);
       //Storing year


       root=InsertPhoto(name,dimension,size,city,country,year,root);

         fflush(stdin);
   }
    fclose(fp);


    return root;//Returning tree created with linked lists
}

AVLTree InsertPhoto(char name[50],char dimension[50],char size[50],
                    char city[50],char country[50],int year,AVLTree t)
{
    if (t==NULL)
    {

       t=(AVLTree)malloc(sizeof(struct AVLTreeNode*));
        if (t==NULL)
        {
            printf("Error creating tree!!!!!");
            exit(1);
        }
        else
        {
            MakeEmptyTree(t);

            struct Node* newnode=Newnode(name,dimension,size,city,country,year);

            t->tail->next = newnode;//Adding tree node to end of the list

            t->tail = t->tail->next;//Updating tail


            t->height=0;
             t->size++;
             t->left = t->right = NULL;

        }
    }
    else if ( strcmp(country,t->tail->Country)<0 )
	{

		t->left = InsertPhoto(name,dimension,size,city,country,year, t->left);

        if ( ( AVLTreeHeight(t->left) ) - ( AVLTreeHeight(t->right) ) == 2)

		if ( strcmp(country,t->left->tail->Country)<0 )
			t = SingleRotateWithLeft(t);
		else
			t = DoubleRotateWithLeft(t);

	}
    else if (strcmp(country,t->tail->Country)>0)
    {
        t->right= InsertPhoto(name,dimension,size,city,country,year,t->right);

        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        {
                if (    strcmp(country,t->right->tail->Country)>0 )

                    t = SingleRotateWithRight(t);
                else
                    t = DoubleRotateWithRight(t);
        }

    }
    else if ( strcmp(country,t->tail->Country)==0 )//The same country name
    {
        struct Node* newnode=Newnode(name,dimension,size,city,country,year);

        t->size++;//Increasing tree node's size since we are adding one more node to the same tree
        t->tail->next = newnode;
        t->tail = t->tail->next;

    }

    t->height=Max(AVLTreeHeight(t->left),AVLTreeHeight(t->right))+1;

    return t;
}


void popularYear(AVLTree root)//In this function first I find the total number of tree nodes in the three with FindNumberOfTreeNodes then
                            //I create an array with size of tree nodes and load every node's year in this array
                            //without looking they are equal or not with StoreYears function then
                            //I find the max repeated year in CountYears function finally I print those with
                            //PrintpopularYear function which is also recursive three traversal


                            //Complexity:I again use two tree traversal function and their complexity is O(n) since they process equal time
                            //with the number of nodes. But since in CountYears function and it includes nested for loop, the complexity of this
                            //function is O(n2) and I think I can improve this by improving my CountYears function to o(nlogn) maybe

{
    int no_tree_nodes=0;//This represents the number of tree nodes in the tree including their next or next s(same country with few photos)

    FindNumberOfTreeNodes(root,&no_tree_nodes);//Finding number of nodes recursively(pre order)

    int years[no_tree_nodes];//this year index will hold the years in different indexes no matter they are equal or not

    int i=-1;//This will count the indexes in array

    StoreYears(root,years,&i);//Here I just store the years one by one into the array(pre order)

    int max_year=CountYears(years,no_tree_nodes);//Counting the number of each year and determining the most repeated one

    printf("\nPhotos of  popular year:\n");

    PrintpopularYear(root,max_year);//Printing array recursively (post order)
    printf("\n");
}
void popularCountry(AVLTree root)//In this function I only used two recursive tree traversal functions
                                //One for finding max repeated country and one for printing those countries
                                //Because I only use recursive tree traversal this function's time complexity is O(n)
                                //I cannot think of a way that will be more efficient than this recursive implementation
                                //because it visits every node for once and that s all for both FinMax and PrintMax
{
    int max=1;//Minimum photo number that one country can have

    FindMaxforCountry(root,&max);//Finding maximum size(the photo number that each country has)(In order)

    printf("\nPhotos of popular country:\n");
    PrintMaxCountry(root,max);//Printing with in order tree traversal
    printf("\n");
}

void displayIndex(AVLTree t)
{
    printf("Photo Index:\n");
    DisplayTree(t);//This In order traversal left,parent,right will show in alphabetical order
                   //since left will be smaller than parent and parent will be smaller than right
    printf("\n");
}

int main(int count,char *string[])
{

    if (count<=1)
    {
         printf("Error taking commands!");
         exit(1);
    }
    char filename[30];
    strcpy(filename,string[1]);

    int option;//Menu option

    AVLTree root;
    root=readData(filename);


    printf("\n\n>>>Welcome to Photo Indexing<<<\n\n");
    do
    {
        printf("-Menu-\n");
        printf("1. Display the full index of photos\n2. Display the photos of popular country\n3. Display the photos of popular year\n4. Exit\n");
        printf("\nOption:");
        scanf(" %d",&option);
        if (option==1)
            displayIndex(root);
        else if (option==2)
            popularCountry(root);
        else if (option==3)
            popularYear(root);
        else if (option!=4)
            printf("\nInvalid option!!!\nPlease try one of 1 or 2 or 3 or 4\n\n");
    }while (option!=4);

    //free(root);//I tried to free the array but it crashes

    return 0;
}



