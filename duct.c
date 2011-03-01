#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "duct.h"
#include "node.h"
#include "queue.h"

queue_p QUEUE = NULL;

int main(int argc, char **argv) {
    grid_p g = NULL;
    node_p start_node = NULL;
    int solutions = 0;

    // init grid and global queue
    g = grid_init(stdin);
    QUEUE = queue_init(grid_get_max_rooms(g));

    // the start room.
    start_node = grid_get_start_node(g);

    // start running!
    DFS(start_node, g, &solutions);

    // feeeewww... how much?
    printf("%d\n", solutions);

    return 0;
}

/**
 * My main...
int main(int argc, char **argv) {
    grid_p g = NULL;
    node_p start_node = NULL;

    time_t start_time, end_time;
    time_t diff;

    int solutions = 0;

    // init grid and global queue
    g = grid_init(stdin);
    QUEUE = queue_init(grid_get_max_rooms(g));

    // the start room.
    start_node = grid_get_start_node(g);

    // start running!
    start_time = time(NULL);
    DFS(start_node, g, &solutions);
    end_time = time(NULL);

    // feeeewww... how was that?
    diff = end_time - start_time;
    printf("time: %ld:%ld:%ld\n", diff/3600, diff/60, diff%60);
    printf("%d ways to run the duct.\n", solutions);

    grid_free(g);
    queue_free(QUEUE);

    return 0;
}
*/

void DFS(node_p node, grid_p grid, int *solutions) {
    assert(node != NULL);
    node_p next = NULL;
    int i;
    int possible = 0;

    grid_count_inc(grid);

    if (grid_get_count(grid) == grid_get_max_rooms(grid)) {
        if (node_get_type(node) == END) {
            ++(*solutions);
            //printf("solution no. %d:\n", (*solutions));
            //grid_print(grid);
            grid_count_dec(grid);
            return;
        }
    } else if (node_get_type(node) == END) {
        grid_count_dec(grid);
        return;
    }

    possible = count_possible(node, grid);
    if (possible < 0) {
        grid_count_dec(grid);
        return;
    }

    if (possible + grid_get_count(grid) < grid_get_max_rooms(grid)) {
        grid_count_dec(grid);
        return;
    }

    for (i = 0; i < 4; i++) {
        next = node_set_to(node, i);
        if (next == NULL) {
            node_delete_to(node);
            continue;
        }
        DFS(next, grid, solutions);
        node_delete_to(node);
    }

    grid_count_dec(grid);
}

int count_possible(node_p node, grid_p grid) {
    static int mark = 0;
    ++mark;
    int x, y;
    int k;
    int count = 0;
    node_p cur_node = NULL, other_node = NULL;
    int count_blocked = 0;

    queue_enqueue(QUEUE, node);

    while (!queue_is_empty(QUEUE)) {
        cur_node = queue_dequeue(QUEUE);
        ++count;

        x = node_get_x(cur_node);
        y = node_get_y(cur_node);
        count_blocked = 0;
        for (k = 0; k < 4; k++) {
            switch (k) {
            case UP:
                other_node = grid_get(grid, x, y-1);
                break;
            case DOWN:
                other_node = grid_get(grid, x, y+1);
                break;
            case LEFT:
                other_node = grid_get(grid, x-1, y);
                break;
            case RIGHT:
                other_node = grid_get(grid, x+1, y);
                break;
            }
            if (node_get_type(cur_node) == END || cur_node == node || other_node == node) {
                count_blocked = -3;
            }
            if (other_node == NULL || node_get_type(other_node) == NOT_OURS ||
                node_get_to(other_node) != NULL) {
                ++count_blocked;
                continue;
            }

            if (other_node == node || node_is_marked(other_node, mark) || node_get_from(other_node) != NULL) {
                continue;
            }
            queue_enqueue(QUEUE, other_node);
            node_mark(other_node, mark);
        }
        if (count_blocked == 3) {
            return -1;
        }
    }
    queue_clear(QUEUE);
    return count;
}
