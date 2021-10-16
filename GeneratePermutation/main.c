#include <stdio.h>
#include <string.h>
#define MAXLEN 50

void swap (char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void toString (char *str) {
    printf("[");
    int i = 0;
    while (str[i + 1]) {
        printf("%c, ",str[i]);
        i++;
    }
    printf("%c]\n",str[i]);
}

void perm (char *str, int i, int n) {
    if (i == n - 1) {
        // printf("%s\n",str);
        toString(str);
    } else {
        for (int iter = i; iter < n; iter++) {
            swap(str+i, str+iter);
            perm (str, i + 1, n);
            swap(str+i, str+iter);
        }
    }
}

int main (int argc, char **argv) {
    char a[MAXLEN];
    scanf("%s",a);
    printf("\nPermutations..\n");
    perm(a, 0, strlen(a));
    remove(argv[0]);
    return 0;
}