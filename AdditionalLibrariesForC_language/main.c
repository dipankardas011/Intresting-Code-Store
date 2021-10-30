#include <stdio.h>
#include <stdlib.h>


/**
 * @def to convert the given number to its equalalent binary format
 * @param N number to get converted to binary
 * @return void
 */
void toBinary(int N) {
    if (N > 0) {
        toBinary(N >> 1);
        printf("%d ", N&1);
    }
}


int main(int argc, char **argv) {
    for (int i=0;i<10;i++)
    {
        toBinary(i);
        printf("\n");
    }
    remove(argv[0]);
    return EXIT_SUCCESS;
}