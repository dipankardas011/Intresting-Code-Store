#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**
 * @param M the degree of tree i.e. maximum no. of children
 * @param Ml the minimum no of keys allowed
 **/
#define M 3 
#define Ml M/2


typedef enum KeyStatus{
    Duplicate,
    SearchFailure,
    Success,
    InsertIt,
    LessKeys,
} KeyStatus;


typedef struct nodes{
    int keys[M-1];  /*Keys are 0,1,.., M-2*/
    struct nodes *childrens[M]; /*Childrens are 0,1,..,M-1*/
    int availableKeys;  /*Present no. of keys*/
}BTree;

void insertNode(BTree**, int);
int searchPosition(BTree *, int);
KeyStatus Insertion(BTree *, int, int*, BTree**);
void displayBTree(BTree *);

int searchPosition(BTree *node, int skey){
    int pos = 0;
    while(pos<node->availableKeys && skey > node->keys[pos])
        pos++;
    return pos;
}

KeyStatus Insertion(BTree *root, int ikey, int *upkey, BTree **newNode)
{
    BTree *newPtr = NULL;
    BTree *lastPtr = NULL;
    int splitPos, newKey, lastKey;
    int pos;
    KeyStatus status;

    if(!root){
        (*newNode) = NULL;
        (*upkey) = ikey;
        return InsertIt;
    }
    int NoOfKeys = root->availableKeys;
    pos = searchPosition(root, ikey);
    if (pos < NoOfKeys && root->keys[pos] == ikey)
        return Duplicate;
    status = Insertion(root->childrens[pos], ikey, &newKey, &newPtr);
    if (status != InsertIt)
        return status;

    if(NoOfKeys < M-1){
        /*Space is left*/
        pos = searchPosition(root, newKey);
        for (int iter = NoOfKeys; iter > pos;iter--){
            root->keys[iter] = root->keys[iter - 1];
            root->childrens[iter + 1] = root->childrens[iter];
        }
        root->keys[pos] = newKey;
        root->childrens[pos + 1] = newPtr;
        (root->availableKeys)+=1;
        return Success;
    }
    else {
        /*Space is not available so splitting*/
        // so store the last node somewhere
        if(pos==M-1){
            /*Last node where to place the extra key*/
            lastKey = newKey;
            lastPtr = newPtr;
        } else {
            /*place the extra key between*/
            lastKey = root->keys[M - 2];
            lastPtr = root->childrens[M - 1];

            for (int iter = M - 2; iter > pos;iter--){
                root->keys[iter] = root->keys[iter - 1];
                root->childrens[iter + 1] = root->childrens[iter];
            }
            root->keys[pos] = newKey;
            root->childrens[pos + 1] = newPtr;
        }

        // so after storing the lastNode as we dont have space
        // splitting
        int splitPos = (M - 1) >> 1;
        *upkey = root->keys[splitPos];
        /**
         * @param{newNode} has the right subtree and the @param{root} will 
         * have the left subtree and the @param{upkey} the root of the split
         */
        *newNode = (BTree *)malloc(sizeof(BTree));
        for (int i = 0; i < M;i++)
            (*newNode)->childrens[i] = NULL;    /*Default value*/
        root->availableKeys = splitPos;

        (*newNode)->availableKeys = M - 1 - splitPos;

        for (int iter = 0; iter < (*newNode)->availableKeys;iter++){
            (*newNode)->childrens[iter] = root->childrens[iter + splitPos + 1];
            root->childrens[iter + splitPos + 1] = NULL;

            if(iter<(*newNode)->availableKeys-1){
                (*newNode)->keys[iter] = root->keys[iter + splitPos + 1];
                root->keys[iter + splitPos + 1] = -99;
            }
            else
                (*newNode)->keys[iter] = lastKey;
        }
        (*newNode)->childrens[(*newNode)->availableKeys] = lastPtr;
        return InsertIt;
    }
}

void insertNode(BTree** root, int ikey)
{
    BTree *rightNewNode = NULL;
    int upkey = 0;
    KeyStatus status = Insertion(*root, ikey, &upkey, &rightNewNode);
    if(status==Duplicate)
        fprintf(stderr, "Duplicates are not allowed (%s:%d)\n", __FILE__, __LINE__);
    else if(status==InsertIt) {
        BTree *oldRoot = *root;
        *root = (BTree *)malloc(sizeof(BTree));
        (*root)->availableKeys = 1;
        (*root)->keys[0] = upkey;
        (*root)->childrens[0] = oldRoot;
        (*root)->childrens[1] = rightNewNode;
    } else {
        if(status==Success)
            return;
        fprintf(stderr, "Other kind of error (%s : Line %d)\n", __FILE__, __LINE__);
        return;
    }
}

void inorderTrav(BTree *root)
{
    if (!root)
        return;

    int i = 0;
    while (i < root->availableKeys)
    {

        inorderTrav(root->childrens[i]);
        printf("%d ", root->keys[i]);
        i++;
    }
    inorderTrav(root->childrens[i]);
}

void nodeLevelDis(BTree *root)
{
    if (!root)
        return;
    printf("\t{ ");

    for (int i = 0; i < root->availableKeys; i++)
        printf("%d ", root->keys[i]);
    printf("}\n");
    for (int i = 0; i <= root->availableKeys; i++)
        nodeLevelDis(root->childrens[i]);
}

void displayBTree(BTree *root)
{
    fprintf(stdout, "Inorder Trav [ ");
    inorderTrav(root);
    fprintf(stdout, "]\n");

    fprintf(stdout, "Every Node {\n");
    nodeLevelDis(root);
    fprintf(stdout, "}\n");
}

int main(int argc, char **argv)
{
    BTree *root = NULL;
    int ch;
    do{
        printf("[ 1 ] Insert\n[ 2 ] Display\n[ 0 ] EXIT\n> ");
        scanf("%d", &ch);
        int ikey;
        switch(ch){
            case 1:{
                printf("Enter the key to insert: ");
                scanf("%d", &ikey);
                insertNode(&root, ikey);
                break;
            }
            case 2:{
                displayBTree(root);
                break;
            }
        }
    } while (ch);
    return EXIT_SUCCESS;
}