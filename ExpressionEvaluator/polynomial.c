#include <stdio.h>
#include <stdlib.h>

#define DEF_TERM printf("\033[0m\n")

typedef struct node
{
    int coeff;
    int power;
    struct node *next;
} Node;

Node *insertData(Node *p, int c, int po)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->coeff = c;
    t->power = po;
    t->next = NULL;

    if (!p)
    {
        p = t;
        return p;
    }

    Node *tmp = p;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = t;
    return p;
}

void displayPoly(Node *poly)
{
    if (!poly)
    {
        printf("Empty!\n");
        return;
    }
    do
    {
        if (poly->power > 1)
        {
            if (poly->coeff > 0)
            {
                printf("+%dX^%d ", poly->coeff, poly->power);
            }
            else
            {
                printf("%dX^%d ", poly->coeff, poly->power);
            }
        }
        else
        {
            if (poly->power == 1)
            {
                if (poly->coeff > 0)
                {
                    printf("+%dX ", poly->coeff);
                }
                else
                {
                    printf("%dX ", poly->coeff);
                }
            }
            else if (poly->power == 0)
            {
                if (poly->coeff > 0)
                {
                    printf("+%d ", poly->coeff);
                }
                else
                {
                    printf("%d ", poly->coeff);
                }
            }
            else
            {
                printf("%dX^%d ", poly->coeff, poly->power);
            }
        }
        poly = poly->next;
    } while (poly);
    // printf("\n");
}

void deletePoly(Node *p)
{
    Node *t = 0;
    while (p)
    {
        t = p;
        p = p->next;
        free(t);
    }
}

Node *addPoly(Node *poly1, Node *poly2)
{
    Node *res = 0;
    while (poly1 && poly2)
    {
        if (poly1->power > poly2->power)
        {
            res = insertData(res, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        }

        else if (poly1->power < poly2->power)
        {
            res = insertData(res, poly2->coeff, poly2->power);
            poly2 = poly2->next;
        }

        else
        {
            res = insertData(res, (poly1->coeff + poly2->coeff), poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1)
    {
        res = insertData(res, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }

    while (poly2)
    {
        res = insertData(res, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return res;
}

Node *subPoly(Node *poly1, Node *poly2)
{
    // poly2 - poly1
    Node *res = 0;
    while (poly1 && poly2)
    {
        if (poly1->power > poly2->power)
        {
            res = insertData(res, -poly1->coeff, poly1->power);
            poly1 = poly1->next;
        }

        else if (poly1->power < poly2->power)
        {
            res = insertData(res, poly2->coeff, poly2->power);
            poly2 = poly2->next;
        }

        else
        {
            res = insertData(res, (poly2->coeff - poly1->coeff), poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1)
    {
        res = insertData(res, -poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }

    while (poly2)
    {
        res = insertData(res, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return res;
}

Node *insertMul(Node *p ,int co, int po)
{
    Node *t = (Node*)malloc(sizeof(Node));
    t->coeff = co;
    t->power = po;
    t->next = 0;
    
    if(!p){
        p = t;
        return p;
    }
    // maintain the descending order
    Node *tmp = p;
    while(tmp->next && tmp->next->power > po)
        tmp = tmp->next;

    // stop before the desired position
    if(!tmp->next){
        // last node is
        tmp->next = t;
        return p; 
    }
    if(tmp->next->power < po){
        t->next = tmp->next;
        tmp->next = t;
        return p;
    }
    if(tmp->next->power == po){
        // edit it
        tmp->next->coeff += co;
        free(t);
        return p;
    }
}

Node *mulPoly(Node *poly1, Node *poly2){
    Node *res=0;

    Node *ptr2 = NULL;
    Node *ptr1 = poly1;

    while(ptr1)
    {
        ptr2 = poly2;
        
        while(ptr2){
            res = insertMul(res,
                    (ptr1->coeff * ptr2->coeff),
                    (ptr1->power + ptr2->power));

            ptr2 = ptr2->next;
            // printf("###  ");
            // displayPoly(res);
        }

        ptr1 = ptr1->next;
    }

    return res;
}


int main(int argc, char const *argv[])
{
    Node *poly1 = 0,
         *poly2 = 0;

    poly1 = insertData(poly1, 2, 3);
    poly1 = insertData(poly1, 5, 2);
    poly1 = insertData(poly1, 3, 0);

    poly2 = insertData(poly2, 2, 4);
    poly2 = insertData(poly2, 5, 1);
    poly2 = insertData(poly2, 2, 0);
    
    printf("\033[33;44mPoly1 : ");
    displayPoly(poly1);DEF_TERM;

    printf("\033[33;44mPoly2 : ");
    displayPoly(poly2);DEF_TERM;

    ////Addition////

    Node *poly3 = addPoly(poly1, poly2);
    printf("\033[33;44mAdd : ");
    displayPoly(poly3);DEF_TERM;

    ////SUbtraction////

    Node *poly4 = subPoly(poly1, poly2);
    printf("\033[33;44mSub{2-1} : ");
    displayPoly(poly4);DEF_TERM;


    ////Multiplication////

    Node *poly5 = mulPoly(poly1, poly2);
    printf("\033[33;44mMultiplication : ");
    displayPoly(poly5);DEF_TERM;
    printf("\n");

    deletePoly(poly1);
    deletePoly(poly2);
    deletePoly(poly3);
    deletePoly(poly4);
    deletePoly(poly5);

    return 0;
}
