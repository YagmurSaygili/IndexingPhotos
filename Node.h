/* Creator : Yagmur Saygili / School Assigment

 	Self created library file to use modular approach
	and make it easier to read or inspect the code later on.
	
	Here Node (Like a node in Tree) consepts, functions and their declarations 
	are defined.

    Node structure is defined here as well.
*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char Name[100];
    char Dimension[100];
    char Size[100];
    char City[100];
    char Country[100];
    int year;

    struct Node* next;
};


int Max(int,int);


int Max(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}


