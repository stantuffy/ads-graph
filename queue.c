#include <stdlib.h>

#include "queue.h"

nodeq *new_queue() {
    nodeq *q = (nodeq *)calloc(1, sizeof(nodeq));
    return q;
}

void enqueue(nodeq *q, node *info) {
    node_list *new_node = (node_list *)calloc(1, sizeof(node_list));
    new_node->info = info;
    new_node->next = q->head;
    
    if(q->head != NULL)
        q->head->prev = new_node;
        
    q->head = new_node;
        
    if(q->tail == NULL)
        q->tail = new_node;
        
    q->num_nodes ++;
}

node dequeue(nodeq *q) {
    if(q == NULL || q->tail == NULL)
        return;
    
    node result = *(q->tail->info);
    
    node_list *tmp = q->tail->prev;
    
    if(tmp != NULL)
        tmp->next = NULL;
    
    free(q->tail);
    
    q->tail = tmp;
    
    if(q->tail == NULL)
        q->head = NULL;
    
    q->num_nodes --;
    
    return result;
}

_Bool is_empty(nodeq *q) {
    return q->num_nodes == 0;
}