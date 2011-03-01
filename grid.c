#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "grid.h"
#include "node.h"
#include "util.h"

struct grid {
    int width;
    int height;
    node_p *arr;
    int max_rooms;
    int count;
    node_p start_node;
};

/**
 * See if a character is a digit.
 *
 * @param c the character
 *
 * @return TRUE if c is a digit, FALSE otherwise
 */
static boolean is_digit(char c);

/**
 * Convert a character digit to an int
 *
 * @param c the character
 *
 * @return the int representation of that character.
 */
static int char_to_digit(char c);

/**
 * Convert an integer to a character digit.
 *
 * @param n the integer
 * @return the  
 */
static char int_to_char(int n);

/**
 * Read an integer of the stream.
 *
 * @param stream a FILE pointer to the stream.
 * @param c the first character of the integer.
 *
 * @return the entire integer, leaving the stream pointer
 *      on the character right after.
 */
static int read_int(FILE *stream, char c);

static boolean is_digit(char c) {
    if (c >= 48 && c <= 57) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static int char_to_digit(char c) {
    assert(is_digit(c));
    return (c - 48);
}
static char int_to_char(int n) {
    assert(n >= 0 && n <= 9);
    return (n + 48);
}

static int read_int(FILE *stream, char c) {
    int num = 0;

    while (!feof(stream) && is_digit(c)) {
        num = num*10 + char_to_digit(c);
        c = getc(stream);
    }

    return num;
}

grid_p grid_init(FILE *input) {
    char c = 0;
    int state = 0;
    int i = 0;

    grid_p grid = (grid_p)malloc(sizeof(struct grid));
    memset(grid, 0, sizeof(struct grid));

    while (!feof(input)) {
        c = getc(input);
        switch (state) {
        case 0:
            if (is_digit(c)) {
                grid->width = read_int(input, c);
                state = 1;
            }
            break;
        case 1:
            if (is_digit(c)) {
                grid->height = read_int(input, c);
                grid->arr = (node_p*)calloc(grid->height * grid->width, sizeof(node_p));
                state = 2;
            }
            break;
        case 2:
            if (is_digit(c)) {
                int type = read_int(input, c);
                if (type != NOT_OURS) {
                    ++grid->max_rooms;
                }
                grid->arr[i] = node_init(i%grid->width, i/grid->width, type, grid);

                if (type == START) {
                    grid->start_node = grid->arr[i];
                }

                ++i;
            }
            break;
        }
    }

    return grid;
}

void grid_free(grid_p grid) {
    int i;

    if (grid != NULL) {
        if (grid->arr != NULL) {
            for (i = 0; i < grid->width * grid->height; i++) {
                if (grid->arr[i] != NULL) {
                    node_free(grid->arr[i]);
                }
            }
        }
        free(grid->arr);
    }
    free(grid);
}

node_p grid_get(const_grid_p grid, int x, int y) {
    assert(grid != NULL);

    if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return NULL;
    }

    return grid->arr[y*grid->width + x];
}

void grid_set(const_grid_p grid, int x, int y, int value) {
    assert(grid != NULL);

    if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return;
    }

    node_set_type(grid->arr[y*grid->width + x], value);
}

int grid_get_width(const_grid_p grid) {
    assert(grid != NULL);
    return grid->width;
}

int grid_get_height(const_grid_p grid) {
    assert(grid != NULL);
    return grid->height;
}

int grid_get_max_rooms(const_grid_p grid) {
    assert(grid != NULL);
    return grid->max_rooms;
}

int grid_get_count(const_grid_p grid) {
    assert(grid != NULL);
    return grid->count;
}

void grid_count_inc(grid_p grid) {
    assert(grid != NULL);
    ++grid->count;
}

void grid_count_dec(grid_p grid) {
    assert(grid != NULL);
    --grid->count;
}

void grid_print(const_grid_p grid) {
    int i = 0, j = 0;
    node_p to_node = NULL, from_node = NULL;

    for (i = 0; i < grid->width*3 - 2; i++) {
        putchar('=');
    }
    putchar('\n');
    for (i = 0; i < grid->height*grid->width; i++) {
        if (i > 0 && i % grid->width == 0) {
            putchar('\n');
            for (j = 0; j < grid->width && i+j < grid->width*grid->height; j++) {
                from_node = node_get_from(grid->arr[i + j]);
                to_node = node_get_to(grid->arr[i + j]);
                if (from_node != NULL &&
                    node_get_y(from_node) < node_get_y(grid->arr[i+j])) {
                    putchar('|');
                    putchar(' ');
                    putchar(' ');
                } else if (to_node != NULL &&
                           node_get_y(to_node) < node_get_y(grid->arr[i+j])) {
                    putchar('|');
                    putchar(' ');
                    putchar(' ');
                } else {
                    putchar(' ');
                    putchar(' ');
                    putchar(' ');
                }
            }
            putchar('\n');
        }

        to_node = node_get_to(grid->arr[i]);
        from_node = node_get_from(grid->arr[i]);
        putchar(int_to_char(node_get_type(grid->arr[i])));
        if (from_node != NULL &&
            node_get_x(from_node) > node_get_x(grid->arr[i])) {
            putchar('-');
            putchar('-');
        } else if (to_node != NULL &&
                   node_get_x(to_node) > node_get_x(grid->arr[i])) {
            putchar('-');
            putchar('-');
        } else {
            putchar(' ');
            putchar(' ');
        }
    }
    putchar('\n');
}

node_p grid_get_start_node(const_grid_p grid) {
    assert(grid != NULL);
    return grid->start_node;
}

