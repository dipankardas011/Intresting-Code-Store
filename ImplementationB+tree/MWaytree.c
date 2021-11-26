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

// first insert a M-way tree
tree* insertion(tree* root, int ikey){
  // if the node is NULL
  if(!root){
    return createNode(ikey);
  }
  // if not NULL check if the avilable space is there or not
  if(root->availableKeys < M){
    // avilable
    root->keys[(root->availableKeys) + 1] = ikey;
    (root->availableKeys)++;
    return root;
  }

  // not available then search for the place
  if(root->keys[1] > ikey){
    // leftmost key
    root->childrens[0] = insertion(root->childrens[0], ikey);
    return root;
  }

  // now moving L <- R
  int ptr;
  for (ptr = root->availableKeys; ptr > 1 && root->keys[ptr] > ikey; ptr--)
    ;
  if(root->keys[ptr] == ikey){
    printf("Duplication not allowed!!!\n");
    return root;
  }
  // right child
  root->childrens[ptr] = insertion(root->childrens[ptr], ikey);
  return root;
}


void inorderTrav(tree* root){
  if(!root)
    return;

  int i = 0;
  while(i<root->availableKeys){

    inorderTrav(root->childrens[i]);
    printf("%d ", root->keys[i+1]);
    i++;
  }
  inorderTrav(root->childrens[i]);
}

int search(tree* root, int skey){
  if(!root){
    return 0;
  }

  if(root->keys[1] > skey){
    // leftmost key
    return search(root->childrens[0], skey);
  }

  // now moving L <- R
  int ptr;
  for (ptr = root->availableKeys; ptr > 1 && root->keys[ptr] > skey; ptr--)
    ;
  if(root->keys[ptr] == skey){
    return 1;
  }
  // right child
  return search(root->childrens[ptr], skey);
}


tree* deletion(tree* root, int dkey){
  if(!root){
    return root;
  }

  if(root->keys[1] > dkey){
    // leftmost key
    root->childrens[0] = insertion(root->childrens[0], dkey);
    return root;
  }

  // now moving L <- R
  int ptr;
  for (ptr = root->availableKeys; ptr > 1 && root->keys[ptr] > dkey; ptr--)
    ;
  if(root->keys[ptr] == dkey){
    printf("Found\n");
    
    return root;
  }
  // right child
  root->childrens[ptr] = insertion(root->childrens[ptr], dkey);
  return root;
}


int main(int argc, char const *argv[]){
  tree *root = NULL;
  int ch;
  do{
    printf("1 > insert\n");
    printf("2 > display\n");
    printf("3 > search\n");
    printf("4 > delete\n");
    printf("0 > exit\n> ");
    scanf("%d", &ch);
    int kk;
    switch(ch){
      case 1:
        printf("Enter the keyy to be inserted: ");
        scanf("%d", &kk);
        root = insertion(root, kk);
        break;

      case 2:
        inorderTrav(root);
        printf("\n");
        break;
      case 3:
        printf("Enter the keyy to be inserted: ");
        scanf("%d", &kk);
        (search(root, kk)) ? printf("Found\n") : printf("not Found\n");
        break;
    }
  } while (ch);
  return 0;
}
