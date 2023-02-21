
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


