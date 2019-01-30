#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

typedef struct nodeq nodeq;

nodeq *new_queue();
void enqueue(nodeq *q, node *info);
node dequeue(nodeq *q);
_Bool is_empty(nodeq *q);

struct nodeq {
    node_list *head;
    node_list *tail;
    int num_nodes;
};

#endif