#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"

struct queue {
    int size;
    node_p *arr;

    int head;
    int tail;
};

queue_p queue_init(int size) {
    queue_p queue = malloc(sizeof(struct queue));

    queue->size = size;
    queue->arr = (node_p*)calloc(size, sizeof(node_p));
    queue->head = 0;
    queue->tail = 0;

    return queue;
}
void queue_free(queue_p queue) {
    if (queue != NULL) {
        free(queue->arr);
    }
    free(queue);
}

boolean queue_is_empty(const_queue_p queue) {
    assert(queue != NULL);

    if (queue->tail % queue->size == queue->head % queue->size) {
        return TRUE;
    }

    return FALSE;
}

boolean queue_is_full(const_queue_p queue) {
    assert(queue != NULL);

    if (queue->tail % queue->size == (queue->head - 1) % queue->size) {
        return TRUE;
    }
    return FALSE;
}

void queue_clear(queue_p queue) {
    assert(queue != NULL);
    queue->head = 0;
    queue->tail = 0;
}

void queue_enqueue(queue_p queue, node_p node) {
    assert(queue != NULL);

    if (queue_is_full(queue)) {
        return;
    }

    queue->arr[queue->tail] = node;
    queue->tail = (queue->tail + 1) % queue->size;
}

node_p queue_dequeue(queue_p queue) {
    assert(queue != NULL);
    node_p value = NULL;

    if (queue_is_empty(queue)) {
        return NULL;
    }

    value = queue->arr[queue->head];
    queue->head = (queue->head + 1) % queue->size;

    return value;
}

void queue_print(const_queue_p queue) {
    assert(queue != NULL);
    int i;

    for (i = 0; i < queue->size; i++) {
        if (queue->arr[i] == NULL) {
            printf("NUL, ");
        } else {
            printf("%dx%d, ", node_get_x(queue->arr[i]), node_get_y(queue->arr[i]));
        }
    }
    printf("\n");
    for (i = 0; i < queue->size; i++) {
        if (i == queue->head) {
            printf(" ^   ");
        } else if (i == queue->tail) {
            printf(" |   ");
        } else {
            printf("     ");
        }
    }
    printf("\n");
}





