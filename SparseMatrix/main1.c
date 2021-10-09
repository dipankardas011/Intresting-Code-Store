#include <stdio.h>
#include <stdlib.h>
#define createMemory (struct Matrix *)malloc(sizeof(struct Matrix))
/***
 * @diagram
 * header needed so 
 * header circular linklist used
 * header 0 -> header 1 -> header 2
 * node 0 -> node 1 -> node 2 ↺ 
 *   ↓        ↓           ↓
 * node r0 -> node r1 -> node r2 ↺ 
 * ↻          ↺           ↺
 * 
 * header
 * right and down
 * element
 * right nd down and element(row, col, value)
 */
enum TYPE{
  header,
  element
};

struct Element {
  int row;
  int col;
  int data;
};

struct Matrix{
  struct Matrix *down;
  struct Matrix *right;
  enum TYPE type;
  // if type is header and element
  union {
    struct Element ele;
    struct Matrix *next;
  }u;
};

// first create the headers required in a array down pointing to it self and right back to start

struct Matrix *createSpareseMatrix();
void displaySpareseMatrix(struct Matrix *);

int main(int argc, char **argv) {
  struct Matrix *head = createSpareseMatrix();
  displaySpareseMatrix(head);
  remove(argv[0]);
  return EXIT_SUCCESS;
}

struct Matrix *createSpareseMatrix() {
  int M,N;
  int totalValid;
  printf("Enter M and N: ");
  scanf("%d %d",&M, &N);
  printf("Enter the number of valid elements: ");
  scanf("%d",&totalValid);

  struct Matrix *colHeader = (struct Matrix*)malloc(sizeof(struct Matrix)*N);
  struct Matrix *rowHeader = (struct Matrix*)malloc(sizeof(struct Matrix)*M);

  struct Matrix *matrixStart = NULL;
  if (!matrixStart) {
    matrixStart = createMemory;
    matrixStart->down = rowHeader;
    matrixStart->right = colHeader;
    matrixStart->type = element;//so that we can store the total row, total col, total valid in data
    {
      matrixStart->u.ele.col = N;
      matrixStart->u.ele.row = M;
      matrixStart->u.ele.data = totalValid;
    }
  }

  /***
   * column header are initialized
   */
  int col;
  // making the headers pointing to itself
  for (col = 0; col<matrixStart->u.ele.col-1 ; col++) {
    colHeader[col].down = &colHeader[col];// pointing to itself
    // here the right will not be used
    colHeader[col].type = header;
    colHeader[col].right = NULL;
    colHeader[col].u.next = &colHeader[col+1];
  }
  // last element will point to the beginning
  // i.e. to the matrstart
  colHeader[col].down = &colHeader[col];// pointing to itself
  colHeader[col].type = header;
  colHeader[col].right = NULL;
  colHeader[col].u.next = matrixStart;

  /***
   * row header are initialized
   */
  int row;
  for (row=0; row<matrixStart->u.ele.row-1;row++) {
    // here the next will not be used
    rowHeader[row].type = header;
    rowHeader[row].u.next = NULL;
    rowHeader[row].down = &rowHeader[row+1];
    rowHeader[row].right = &rowHeader[row];
  }
  // last row will point back to the MAtrixStart
  rowHeader[row].type = header;
  rowHeader[row].u.next = NULL;
  rowHeader[row].down = matrixStart;
  rowHeader[row].right = &rowHeader[row];

  /***
   * elements to be entered
   */
  struct Matrix *temp = 0;
  struct Matrix *rowTraversal = 0, *colTraversal = 0;
  for (int valid = 0; valid<matrixStart->u.ele.data; valid++) {
    temp = rowTraversal = colTraversal = 0;
    int r, c, val;
    printf("Enter the row, col, data to be entered: ");
    scanf("%d %d %d",&r, &c, &val);
    if(r>=M || c>=N)
    {
      fprintf(stderr, "Error invalid row index or column index!!\n");
      valid--;
      continue;
    }
    temp = createMemory;
    temp->down = temp->right = 0;
    temp->type = element;
    temp->u.ele.col = c;
    temp->u.ele.row = r;
    temp->u.ele.data = val;
    // now find the place to enter
    // find the row
    // input is row major wise
    temp->right = &rowHeader[r];
    temp->down = &colHeader[c];
    rowTraversal = temp->right;
    colTraversal = temp->down;
    while(rowTraversal->right!=temp->right){
      rowTraversal = rowTraversal->right;
    }

    while(colTraversal->down!=temp->down){
      colTraversal = colTraversal->down;
    }
    // found the place 
    rowTraversal->right = temp;
    colTraversal->down = temp;
  }

  return matrixStart;
}

void displaySpareseMatrix(struct Matrix *matrix) {
  // using the rowHeader
  printf("Rows: %d\nCols: %d\nValidCount: %d\n",matrix->u.ele.row, matrix->u.ele.col, matrix->u.ele.data);
  struct Matrix *row = matrix->down;
  while(row != matrix) {
    struct Matrix *temp = row;
    while(temp->right != row) {
      printf("%5d | %5d | %5d\n",temp->u.ele.row,temp->u.ele.col,temp->u.ele.data);
      temp = temp->right;
    }
    row = row->down;
  }
}