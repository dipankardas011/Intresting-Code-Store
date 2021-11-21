/**
 * implementation of B-tree
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

 // M degree so M-1 keys
#define M 3
typedef struct Node {
    int keys[M-1];
    struct Node* children[M];
}BTree;

BTree* allocateMemo() {
    BTree* new = (BTree*)malloc(sizeof(BTree));
    for (int i = 0; i < M; i++)
    {
        new->keys[i] = 0;
        new->children[i] = NULL;
    }
    new->children[M - 1] = NULL;
    return new;
}

/**
 * @return {nothing}
 * @def improve the display method
 */
void displayB_Tree(BTree* root) {
    if (!root) {
        return;
    }

    for (size_t i = 0; i < M; i++)
    {
        printf("%d ", root->keys[i]);
        displayB_Tree(root->children[i]);
    }
    displayB_Tree(root->children[M - 1]);
    
}

int main(int argc, char const *argv[])
{
    BTree* root = NULL;
    int ch = 0;
    do {
        printf("Enter your choice\n");
        printf("> 0. STOP\n");
        printf("> 1. Insert key\n");
        printf("> 2. Display\n");
        printf("> 3. Delete key\n");
        printf("-> ");
        scanf("%d", &ch);
        int kk;
        switch (ch) {
        case 1: {
            break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
        }
    } while (ch);
    return 0;
}
