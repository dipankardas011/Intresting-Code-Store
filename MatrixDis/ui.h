#ifndef _UI_H_
#define _UI_H_

#define MAXX 200
#define MAXY 50
#include <wchar.h>
#define MAX_INTENSITY 13
#define MIN_INTENSITY 2
#include <stdbool.h>
typedef struct {
    wchar_t char_value;
    int intensity;
}cell;

extern cell matrix[MAXX][MAXY];


bool init_ui();
void cleanup_ui();
void show_matrix();

#endif