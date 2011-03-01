#ifndef DUCT_H

#define DUCT_H

#include "node.h"
#include "grid.h"
#include "util.h"

/**
 * DFS graph traversal that counts legal duct
 * paths on the grid, with two heuristics.
 *
 * @param node current node/room to traverse from.
 * @param grid the grid the node in on
 * @param solutions number of solutions so far
 *
 */
void DFS(node_p node, grid_p grid, int *solutions);

/**
 * BFS traversal that count reachable nodes/rooms from the 
 * given node. If the BFS found a node that has a 
 * degree of one and it's not the end node/room and it's 
 * not reachable from the current node then a negative 
 * value will be returned indicating that the path so far 
 * is invalid.
 *
 * @param node the node to BFS from
 * @param grid the grid the node is on
 *
 * @return the number of reachable nodes, or a negative value
 *          iff no possible path is available from this point forth.
 */
int count_possible(node_p node, grid_p grid);

#endif /* end of include guard: DUCT_H */
