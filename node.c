/*
 *  'duct' is an algorithm for a special case of the hamilton path problem.
 *  Copyright 2011 Joanthan Sadan
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  Contact me:
 *  sadanjon <at> gmail <dot> com
 */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"
#include "grid.h"
#include "util.h"

struct node {
    int x;
    int y;
    int type;

    node_p to;
    node_p from;

    grid_p grid;

    int mark;
};

node_p node_init(int x, int y, int type, grid_p grid) {
    node_p node = (node_p)malloc(sizeof(struct node));

    node->x = x;
    node->y = y;
    node->type = type;
    node->to = NULL;
    node->from = NULL;

    node->grid = grid;

    node->mark = FALSE;

    return node;
}

void node_free(node_p node) {
    if (node != NULL) {
        free(node->to);
        free(node->from);
    }
    free(node);
}

node_p node_set_to(node_p node, int direction) {
    assert(node != NULL);
    node_p other_node = NULL;

    switch (direction) {
    case UP:
        if (node->y == 0) {
            return NULL;
        }
        other_node = grid_get(node->grid, node->x, node->y-1);

        if (other_node->type == NOT_OURS) {
            return NULL;
        }

        if (other_node->to != NULL || other_node->from != NULL) {
            return NULL;
        }

        node->to = other_node;
        other_node->from = node;
        break;
    case DOWN:
        if (node->y == grid_get_height(node->grid) - 1) {
            return NULL;
        }
        other_node = grid_get(node->grid, node->x, node->y+1);

        if (other_node->type == NOT_OURS) {
            return NULL;
        }
        
        if (other_node->to != NULL || other_node->from != NULL) {
            return NULL;
        }

        node->to = other_node;
        other_node->from = node;
        break;
    case LEFT:
        if (node->x == 0) {
            return NULL;
        }
        other_node = grid_get(node->grid, node->x - 1, node->y);
        if (other_node->type == NOT_OURS) {
            return NULL;
        }

        if (other_node->to != NULL || other_node->from != NULL) {
            return NULL;
        }

        node->to = other_node;
        other_node->from = node;
        break;
    case RIGHT:
        if (node->x == grid_get_width(node->grid) - 1) {
            return NULL;
        }
        other_node = grid_get(node->grid, node->x + 1, node->y);

        if (other_node->type == NOT_OURS) {
            return NULL;
        }

        if (other_node->to != NULL || other_node->from != NULL) {
            return NULL;
        }

        node->to = other_node;
        other_node->from = node;
        break;
    default:
        assert(NULL);
    }

    return other_node;
}

void node_delete_to(node_p node) {
    assert(node != NULL);

    if (node->to != NULL) {
        node->to->from = NULL;
        node->to = NULL;
    }
}

void node_delete_from(node_p node) {
    assert(node != NULL);

    node->from = NULL;
}

void node_set_type(node_p node, int type) {
    assert(node != NULL);

    node->type = type;
}

int node_get_type(node_p node) {
    assert(node != NULL);

    return node->type;
}

int node_get_x(node_p node) {
    assert(node != NULL);
    return node->x;
}

int node_get_y(node_p node) {
    assert(node != NULL);
    return node->y;
}

node_p node_get_to(node_p node) {
    assert(node != NULL);
    return node->to;
}

node_p node_get_from(node_p node) {
    assert(node != NULL);
    return node->from;
}

grid_p node_get_grid(node_p node) {
    assert(node != NULL);
    return node->grid;
}

void node_mark(node_p node, int value) {
    assert(node != NULL);
    node->mark = value;
}

void node_demark(node_p node) {
    assert(node != NULL);
    node->mark = 0;
}

boolean node_is_marked(node_p node, int mark_value) {
    assert(node != NULL);
    return (node->mark == mark_value);
}


