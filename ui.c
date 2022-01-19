#include "ui.h"
#include <string.h>
// #include <assert.h>
#include <ncurses.h>
#include <unistd.h>


WINDOW *uiwindow = NULL;

int color_map[MAX_INTENSITY + 1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 3, 6};

void set_colors();

bool init_ui(int fg) 
{
    uiwindow = initscr();
    if (!uiwindow) 
        return false;
    
    start_color();
    if(!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
        fprintf(stderr, "Warning! your terminal can't handle this program!\n");
        return false;
    }

    set_colors(fg);

    return true;
}

void cleanup_ui() 
{
    delwin(uiwindow);
    endwin();
    refresh();
}

void show_matrix() 
{
    for (int x = 0; x<MAXX; x++) {
        for (int y = 0; y< MAXY; y++) {
            int intensity = matrix[x][y].intensity;
            color_set(color_map[intensity], NULL);
            // wcolor_set(color_map[intensity],3, NULL);

            mvaddch(y,x,matrix[x][y].char_value);
        }
    }
    refresh();
}

void set_colors(int foreground)
{
    for (int i = 0; i < 8; i++) 
        init_pair(i+1, i, COLOR_BLACK);
    
    //set shades of green
    int R = 0, G = 0, B = 0;
    switch (foreground) {
        case 1: G = 1;
        break;
        case 2: R = 1;
        break;
        case 3: B = 1;
        break;
    }
    for (int i=0;i<=5;i++) 
        // init_color(i, 0, i*200, 0);
        init_color(i, i*200*R, i*200*G, i*200*B);
    
    init_color(6, 1000, 1000, 1000);
}