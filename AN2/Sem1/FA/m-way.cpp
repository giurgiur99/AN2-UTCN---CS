#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct _Node2{
    int info = 0;
    int nrChildren = 0;
    _Node2 **child = NULL;
}Node2;

typedef struct _Node3{
    int info = 0;
    _Node3 *child = NULL, *brother = NULL;
}Node3;

void initR2(Node2 **r2, int n)
{
    for(int i=1;i<=n;i++)
    {
        r2[i] = (Node2*)malloc(sizeof(Node2));
        r2[i]->child = (Node2**)malloc(n * sizeof(Node2*));
        r2[i]->nrChildren = 0;
        r2[i]->info = i;
    }
}

void newNode2(int *r1, Node2 ** r2, int i)
{
    Node2 *x = r2[r1[i]];
    x->child[x->nrChildren] = r2[i];
    x->nrChildren++;
}


Node2* trans1(int *r1, int n, Node2** r2)
{
    Node2 *root;
    root = NULL;
    initR2(r2,n);
    for(int i=1; i<=n; i++)
    {
        if(r1[i]==-1)
            root = r2[i];
        else
            newNode2(r1,r2,i);

    }
    return root;
}

void prettyPrint2(Node2* root, int level)
{


    if(level > 0)
        printf(" ");

    for (int i = 0; i < level + 1; i++)
        printf("  ");

    printf("%d",root->info);
    printf("\n");

    for (int j = 0; j < root->nrChildren; j++)
    {
        prettyPrint2(root->child[j], level + 1);
    }
}

void initR3(Node3** r3, int n)
{
    for (int i = 1; i <= n; i++)
    {
        r3[i] = (Node3*)malloc(sizeof(Node3));
        r3[i]->info = i;
        r3[i]->child = NULL;
        r3[i]->brother = NULL;
    }
}
void trans2(Node3 **r3, Node2 * p, Node2 * child, int count)
{
    if(p != NULL)
    {
        if(count < p->nrChildren)
            r3[child->info]->brother = r3[p->child[count]->info];
        else
            r3[child->info]->brother = NULL;
    }
    else
        r3[child->info]->brother = NULL;
    if(child->nrChildren > 0)
        r3[child->info]->child = r3[child->child[0]->info];
    
    for(int i=0 ; i < child->nrChildren ; i++)
    {
        trans2(r3, child, child->child[i], i + 1);
    }
}

void prettyPrint3(Node3* r, int level)
{
    if(level > 0)
        printf(" ");

    for (int i = 0; i < level + 1; i++)
        printf("  ");

    printf("%d\n",r->info);

    if (r->child != NULL)
        prettyPrint3(r->child, level + 1);

    if (r->brother != NULL)
        prettyPrint3(r->brother, level);
}



int main() {
    int n = 9;
    int r1[] = {0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
    Node2 *r2Array[100],*r2;
    Node3 *r3Array[100],*r3;

    r2 = trans1(r1, n, r2Array);

   // prettyPrint2(r2, 0);
   // printf("\n");

    initR3(r3Array, n);
    r3 = r3Array[r2->info];

    trans2(r3Array, NULL, r2, 0);
    prettyPrint3(r3,0);

    return 0;
}


