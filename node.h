#ifndef NODE_H
#define NODE_H

#include "util.h"
struct grid;

/**
 * Node of a graph. Represents a room in on the grid.
 *
 * Supports the operations of setting the duct through him.
 * Such as a 'to' value and a 'from' value. Where the duct is going to
 * and where the duct is coming from.
 *
 * A room/node can also be of a type: ours, not ours, start and end.
 *
 * All node/room structs should be on a grid struct.
 */

#define OURS 0
#define NOT_OURS 1
#define START 2
#define END 3

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NOWHERE 4

typedef struct node* node_p;
typedef const struct node* const_node_p;

/**
 * Initialize a node
 * @param x x coordinate
 * @param y y coordinate
 * @param type can be one of {OURS, NOT_OURS, START, END}
 * @param grid the grid the node is one
 *
 * @return a new node structure
 */
node_p node_init(int x, int y, int type, struct grid *grid);

/**
 * Frees a node structure
 *
 * @param node the node structure
 */
void node_free(node_p node);

/**
 * Set the to field of the node.
 * Can be one of the four directions
 * @param node the node structure
 * @param direction can be one of {UP, RIGHT, DOWN, LEFT}
 *
 * @return NULL if neighbor is out of the grid or has from/to already set
 *          (has the duct go through it already), the neighbor otherwise
 */
node_p node_set_to(node_p node, int direction);

/**
 * Delete the to field of the node, and also the from field of the
 * connected node.
 *
 * @param node the node structure
 */
void node_delete_to(node_p node);

/**
 * Delete the from field of the node.
 *
 * @param node the node structure
 */
void node_delete_from(node_p node);

/**
 * Set the type {OURS, NOT_OURS, END, START} of the node.
 *
 * @param node the node structure
 * @param type the new type
 */
void node_set_type(node_p node, int type);

/**
 * Return the type of the node.
 *
 * @return the type of the node
 */
int node_get_type(node_p node);

/**
 * Return the x field of the node.
 *
 * @return the x field of the node.
 */
int node_get_x(node_p node);

/**
 * Return the y field of the node.
 *
 * @return the node field of the node.
 */
int node_get_y(node_p node);

/**
 * Return the to field of the node.
 *
 * @return the to field of the node.
 */
node_p node_get_to(node_p node);

/**
 * Return the from field of the node.
 *
 * @return the from field of the node.
 */
node_p node_get_from(node_p node);

/**
 * Return the node's grid field.
 *
 * @return the node's grid field.
 */
struct grid *node_get_grid(node_p node);

/**
 * Mark the node with a value.
 *
 * @param the node structure
 * @param value the value to mark the node.
 */
void node_mark(node_p node, int value);

/**
 * Unmark the node (sets the mark to 0)
 * 
 * @param node the node structure
 */
void node_demark(node_p node);

/**
 * Check if node is marked (compare it to mark_value)
 * @param node the node structure
 * @param mark_value mark value to compare to
 *
 * @return TRUE if marked, FALSE otherwise
 */
boolean node_is_marked(node_p node, int mark_value);


#endif /* end of include guard: NODE_H */
