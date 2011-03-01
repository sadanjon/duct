#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include "util.h"
struct node;

/**
 * The grid of node/rooms.
 */
typedef struct grid* grid_p;
typedef const struct grid* const_grid_p;

/**
 * Initialize a new grid struct according to a file.
 *
 * @param input a FILE struct pointer to the file descriptor of the grid.
 *
 * @return a new grid struct.
 */
grid_p grid_init(FILE *input);

/**
 * Free a grid struct.
 *
 * @param grid the grid struct.
 */
void grid_free(grid_p grid);

/**
 * Get a node/room on the grid.
 *
 * @param grid the grid struct
 * @param x the x coordinate
 * @param y the y coordinate
 *
 * @return the node/room or NULL if x and y is invalid
 */
struct node *grid_get(const_grid_p grid, int x, int y);

/**
 * Set a node/room's type on the grid. (not actually used)
 *
 * @param grid the grid struct.
 * @param x the x coordinate
 * @param y the y coordinate
 * @param value the new type
 */
void grid_set(const_grid_p grid, int x, int y, int value);

/**
 * Get the grid's width
 * @param grid the grid struct.
 *
 * @return the grid's width
 */
int grid_get_width(const_grid_p grid);

/**
 * Get the grid's height
 * @param grid the grid struct.
 *
 * @return the grid's height
 */
int grid_get_height(const_grid_p grid);

/**
 * Print the grid along with all the connections between rooms/nodes.
 *
 * @param the grid struct.
 */
void grid_print(const_grid_p grid);

/**
 * Get the grid's maximum number of rooms/nodes that the duct
 * can run through.
 *
 * @param grid the grid struct.
 *
 * @return the maximum rooms/nodes
 */
int grid_get_max_rooms(const_grid_p grid);

/**
 * Get the grid's number of rooms the duct passed through.
 *
 * @param grid the grid struct.
 *
 * @return the grid's number of rooms the duct passed through.
 */
int grid_get_count(const_grid_p grid);

/**
 * Increment the grid's 'count' (number of rooms the duct passed
 * through)
 * 
 * @param grid the grid struct.
 */
void grid_count_inc(grid_p grid);

/**
 * Decrement the grid's 'count' (number of rooms the duct passed
 * through)
 * 
 * @param grid the grid struct.
 */
void grid_count_dec(grid_p grid);

/**
 * Get the grid's start node/room.
 *
 * @param grid the grid struct.
 *
 * @return the grid's start node/room.
 */
struct node *grid_get_start_node(const_grid_p grid);

#endif /* GRID_H */

