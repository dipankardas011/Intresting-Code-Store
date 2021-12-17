#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**
 * @param M the degree of tree i.e. maximum no. of children
 * @param Ml the minimum no of keys allowed
 **/
#define M 3 
#define Ml (M-1)/2


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
void search(BTree *, int);
void nodeLevelDis(BTree *);
void inorderTrav(BTree *);
void deleteNode(BTree **, int);
KeyStatus Deletion(BTree *, BTree *, int);

int searchPosition(BTree *node, int skey)
{
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


KeyStatus Deletion(BTree* orgRoot, BTree* root, int dkey)
{
    KeyStatus status;
    int pos, pivot;
    BTree *leftPtr = NULL, *rightPtr = NULL;

    if(!root)
        return SearchFailure;

    int NoofKeys = root->availableKeys;
    int min = Ml;
    pos = searchPosition(root, dkey);

    /*is it is leaf(any child is NULL)*/
    if(!root->childrens[0]){
        if(pos ==NoofKeys || dkey<root->keys[pos])
            return SearchFailure;

        for (int iter = pos + 1; iter < NoofKeys; iter++){
            root->keys[iter - 1] = root->keys[iter];
            root->childrens[iter] = root->childrens[iter + 1];
        }
        return --(root->availableKeys) >= (root == orgRoot ? 1 : min) ? Success : LessKeys;
    }

    /*Found the key but not in leaf node*/
    if(pos<NoofKeys && dkey==root->keys[pos]){
        /*inorder predessor*/
        BTree *leftRightMost = root->childrens[pos];/*Left subtree of key[pos]*/
        while(leftRightMost->childrens[leftRightMost->availableKeys])
            leftRightMost = leftRightMost->childrens[leftRightMost->availableKeys];

        root->keys[pos] = leftRightMost->keys[leftRightMost->availableKeys - 1];
        leftRightMost->keys[leftRightMost->availableKeys - 1] = dkey;
    }
    status = Deletion(orgRoot, root->childrens[pos], dkey);
    if(status!=LessKeys)
        return status;
    
    
    /**
     * Borrow from left sibling [pos - 1] of child [pos]
     *  . B  {X}..(root)
     *  /   |   \
     * A(L) b(R)  C  (child)
     *  \  /
     *  ~ ~
     * childrens[pos-1] = A
     * childrens[pos] = b
     * childrens[pos+1] = C
     * 
     * b(~) <== B
     * B(~).child <== A(~).child
     * B <== A(~)
     **/
    if (pos > 0 && root->childrens[pos - 1]->availableKeys > min){
        pivot = pos - 1;
        leftPtr = root->childrens[pos - 1];
        rightPtr = root->childrens[pos];

        rightPtr->childrens[rightPtr->availableKeys + 1] = 
                rightPtr->childrens[rightPtr->availableKeys];

        for (int iter = rightPtr->availableKeys; iter > 0;iter--){
            rightPtr->keys[iter] = rightPtr->keys[iter - 1];
            rightPtr->childrens[iter] = rightPtr->childrens[iter - 1];
        }
        (rightPtr->availableKeys)++;
        rightPtr->keys[0] = root->keys[pivot];
        rightPtr->childrens[0] = leftPtr->childrens[leftPtr->availableKeys];
        root->keys[pivot] = leftPtr->keys[leftPtr->availableKeys - 1];
        leftPtr->childrens[leftPtr->availableKeys] = NULL;
        leftPtr->keys[leftPtr->availableKeys - 1] = -99;
        (leftPtr->availableKeys)--;
        return Success;
    }

    /**
     * Borrow from right sibling [pos + 1] of child [pos]
     * ... {X}..(root)
     *    /   \  
     *   A(L)  b(R)  (child)
     *    \   /  
     *    ~  ~
     * childrens[pos] = A
     * childrens[pos+1] = b
     * childrens[pos+2] = C
     * 
     * A(~) <== X
     * A(~).child <== b(~).child
     * X <== b(~)
     **/
    if (pos < NoofKeys && root->childrens[pos + 1]->availableKeys > min){
        pivot = pos;
        leftPtr = root->childrens[pivot];
        rightPtr = root->childrens[pivot+1];

        leftPtr->keys[leftPtr->availableKeys] = root->keys[pivot];
        leftPtr->childrens[leftPtr->availableKeys + 1] = rightPtr->childrens[0];
        (leftPtr->availableKeys)++;
        root->keys[pivot] = rightPtr->keys[0];
        (rightPtr->availableKeys)--;
        for (int iter = 0; iter < rightPtr->availableKeys;iter++){
            rightPtr->keys[iter] = rightPtr->keys[iter + 1];
            rightPtr->childrens[iter] = rightPtr->childrens[iter + 1];
        }
        rightPtr->childrens[rightPtr->availableKeys] = rightPtr->childrens[rightPtr->availableKeys + 1];
        rightPtr->childrens[rightPtr->availableKeys + 1] = NULL;
        rightPtr->keys[rightPtr->availableKeys] = -99;
        return Success;
    }

    /*Merge right node with left node*/
    pivot = pos == NoofKeys ? pos - 1 : pos;

    leftPtr = root->childrens[pivot];
    rightPtr = root->childrens[pivot + 1];
    leftPtr->keys[leftPtr->availableKeys] = root->keys[pivot];
    leftPtr->childrens[leftPtr->availableKeys + 1] = rightPtr->childrens[0];

    for (int iter = 0; iter < rightPtr->availableKeys;iter++){
        leftPtr->keys[leftPtr->availableKeys + 1 + iter] = rightPtr->keys[iter];
        leftPtr->childrens[leftPtr->availableKeys + 2 + iter] = rightPtr->childrens[iter + 1];
    }
    leftPtr->availableKeys = leftPtr->availableKeys + rightPtr->availableKeys + 1;
    free(rightPtr);
    for (int iter = pos + 1; iter < NoofKeys;iter++){
        root->keys[iter - 1] = root->keys[iter];
        root->childrens[iter] = root->childrens[iter + 1];
    }
    return --(root->availableKeys) >= (root == orgRoot ? 1 : min) ? Success : LessKeys;
}

void deleteNode(BTree** root, int dkey)
{
    BTree *delRoot = NULL;
    KeyStatus status = Deletion(*root, *root, dkey);

    switch(status){
        case SearchFailure:{
            fprintf(stderr, "^~~~ Key not present(Line:%d)", __LINE__);
            break;
        }
        case LessKeys:{
            delRoot = *root;
            *root = (*root)->childrens[0];
            free(delRoot);
            break;
        }
        default:{
            return;
        }
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

void search(BTree* root, int skey)
{
    int pos, i, n;
    BTree *ptr = root;
    printf("Search path:\n");
    while (ptr) {
        n = ptr->availableKeys;
        for (i = 0; i < ptr->availableKeys; i++)
            printf(" %d", ptr->keys[i]);
        printf("\n");
        pos = searchPosition(ptr, skey);
        if (pos < n && skey == ptr->keys[pos]){
            printf("Key %d found in position %d of last dispalyed node\n", skey, i);
            return;
        }
        ptr = ptr->childrens[pos];
    }
    printf("Key %d is not available\n", skey);
}

int main(int argc, char **argv)
{
    BTree *root = NULL;
    int ch;
    do{
        printf("[ 1 ] Insert\n[ 2 ] Display\n[ 3 ] Delete\n[ 4 ] Search\n[ 0 ] EXIT\n> ");
        scanf("%d", &ch);
        int key;
        switch(ch){
            case 1:{
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insertNode(&root, key);
                break;
            }
            case 2:{
                displayBTree(root);
                break;
            }
            case 3:{
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                deleteNode(&root, key);
                break;
            }
            case 4:{
                printf("Enter the key to search: ");
                scanf("%d", &key);
                search(root, key);
                break;
            }
        }
    } while (ch);
    return EXIT_SUCCESS;
}