/***
 */
#include <stdio.h>
#include <stdlib.h>
// #define MALLOC(t, n) { \
//     malloc(n)\
//   }\

#define MAX_SIZE 50
typedef enum {head, entry} tagfield;

typedef struct y{
  int row;
  int col;
  int value;
}entryNode;

typedef struct x{
  struct x* down;
  struct x* right;
  tagfield tag;
  union {
    struct x* next;
    entryNode entry;
  }u;
}matrixNode;
matrixNode* hdnode[MAX_SIZE];

matrixNode* newNode() {
  matrixNode* tmp = (matrixNode*)malloc(sizeof(matrixNode));
  tmp->tag = entry;
  return tmp;
}

matrixNode* mread() {
  int numRows, numCols, numTerms, numHeads, i;
  int row, col, value, currRow;
  matrixNode *temp, *last, *node;
  printf("Enter the number of rows, colums and the number of nonzeroterms: ");
  scanf("%d %d %d",&numRows,&numCols, &numTerms);
  numHeads = (numCols > numRows) ? numCols : numRows;
  // setup header node for the list of header nodes
  node = newNode();
  node->tag = entry;
  node->u.entry.row = numRows;
  node->u.entry.col = numCols;

  if(!numHeads)
    node->right = node;
  else {
    // initialize the header node
    
    for (i = 0; i<numHeads; i++) {
      /***
       * @bug temp pointing to same hdnode[i] and u.next as well
       */
      temp = newNode();
      node->right = hdnode[0];
      hdnode[i] = temp;
      hdnode[i]->tag = head;
      hdnode[i]->right = node;
      hdnode[i]->u.next = temp;
    }
    currRow = 0;
    last= hdnode[0];  // last node in currNode
    for (i = 0; i<numTerms; i++) {
      printf("Enter row, column, value: ");
      scanf("%d%d%d",&row, &col,&value);
      
      if(row>currRow) {
        //close current row
        last->right = hdnode[currRow];
        currRow = row;
        last = hdnode[row];
      }
      // MALLOC(temp, sizeof(*temp));
      temp = newNode();
      temp->tag = entry;
      temp->u.entry.row = row;
      temp->u.entry.col = col;
      temp->u.entry.value = value;
      last->right = temp;
      last = temp;

      hdnode[col]->u.next->down = temp;
      hdnode[col]->u.next = temp;
    }

    // close last row;
    last->right = hdnode[currRow];
    // close all column lists
    for (i=0; i<numCols;i++) 
      hdnode[i]->u.next->down = hdnode[i];
    //link all header nodes together
    for(i=0;i<numHeads-1;i++)
      hdnode[i]->u.next = hdnode[i+1];
    hdnode[numHeads-1]->u.next = node;
    node->right = hdnode[0];

  }
  return node;
}

void mwrite(matrixNode* node){
  int i;
  matrixNode *temp,*head = node->right;
  printf("\n numRows = %d, numCols = %d\n",
        node->u.entry.row, node->u.entry.col);
  printf("the matrix by row, column, and value: \n");
  for(i=0;i<node->u.entry.row;i++) {
    for(temp =head->right; temp!=head;temp = temp->right) {
      printf("%5d %5d %5d\n",temp->u.entry.row,temp->u.entry.col,temp->u.entry.value);
      head = head->u.next;
    }
  }
}

int main(int argc, char **argv) {
  matrixNode* header = NULL;
  header = mread();
  mwrite(header);
  remove(argv[0]);
  return EXIT_SUCCESS;
}