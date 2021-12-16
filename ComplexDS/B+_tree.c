#include <stdio.h>
#include <stdlib.h>
#define M 2
/*
0 1 2 3 (4)


 1 2 3(KEY)

0 1 2 3 (CHILD)
*/

typedef struct node{
  int keys[M + 1];
  struct node* childrens[M + 1];
  int availableKeys;
} tree;

tree* createNode(int key){
  tree *temp = (tree *)malloc(sizeof(tree));
  temp->keys[1] = key;
  for (int i = 0; i <= M;i++){
    temp->childrens[i] = NULL;
  }
  temp->availableKeys = 1;
  return temp;
}

int main(int argc, char **argv) {
  
  remove(argv[0]);
  return EXIT_SUCCESS;
}