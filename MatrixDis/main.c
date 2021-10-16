#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <wchar.h>

#include <locale.h>

#include "ui.h"
#include "matrix.h"
#define DEF_TERM printf("\033[0m")


#define ITERATIONS 300
#define REFRESH_DELAY 50000L

int main(int argc, char **argv) {
    // setlocale(LC_CTYPE,"C-UTF-8");
    setlocale(LC_ALL, "");
    printf("\033[43mWelcome to MATRIX\n");
    printf("Enter 1 for green 2 for red 3 for blue-> ");DEF_TERM;
    int ch;
    scanf("%d",&ch);
    if (!init_ui(ch)) {
        return EXIT_FAILURE;
    }

    matrix_init();
    size_t i = 0;
    do {
        matrix_update();
        show_matrix();

        usleep(REFRESH_DELAY);
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));DEF_TERM;
        printf("\033[31m%ld",(10101010&i));//DEF_TERM;
        i++;
    }while(1);//getchar_unlocked()!='Q'
    cleanup_ui();
    DEF_TERM;
    return EXIT_SUCCESS;
}