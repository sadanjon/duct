#ifndef QUEUE_H

#define QUEUE_H
#include "util.h"

/*
 * Fixed sized queue with O(1) operations.
 * Holds node_p pointers
 */

typedef struct queue* queue_p;
typedef const struct queue* const_queue_p;
struct node;

/**
 * Initialize queue
 * @param size the size of the queue
 *
 * @return the populated queue struct
 */
queue_p queue_init(int size);

/**
 * Deallocate the queue
 * @param queue the queue struct
 */
void queue_free(queue_p queue);

/**
 * Clear the queue.
 * @param queue the queue struct
 */
void queue_clear(queue_p queue);

/**
 * Print the queue.
 * @param queue the queue struct
 */
void queue_print(const_queue_p queue);

/**
 * Check if the queue is empty.
 * @param queue the queue struct
 *
 * @return TRUE if the queue is empty FALSE otherwise
 */
boolean queue_is_empty(const_queue_p queue);

/**
 * Check if the queue is empty.
 * @param queue the queue struct
 *
 * @return TRUE if the queue is empty FALSE otherwise
 */
boolean queue_is_full(const_queue_p queue);

/**
 * Enqueue a new node pointer
 * @param queue the queue struct
 * @param node a pointer to a node
 *
 */
void queue_enqueue(queue_p queue, struct node *node);

/**
 * Dequeue a node pointer
 * @param queue the queue struct
 *
 * @return the dequeued node
 */
struct node* queue_dequeue(queue_p queue);

#endif /* end of include guard: QUEUE_H */
