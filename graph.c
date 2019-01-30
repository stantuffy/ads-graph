#include "graph.h"
#include "queue.h"

#include <stdlib.h>

graph *new_graph() {
    graph *g = (graph *)calloc(1, sizeof(graph));
    g->nodes = NULL;
    g->edges = NULL;
    
    return g;
}

void add_edge_to_graph(graph *g, node *from, node *to, int id, _Bool is_directed) {
    if(g == NULL || from == NULL || to == NULL)
        return;
    
    
    // Alloco un nuovo nodo della lista di archi(lista DEL GRAFO).
    // Alloco anche un nuovo arco.
    edge_list *new_edge = (edge_list *)calloc(1, sizeof(edge_list));
    new_edge->info = (edge *)calloc(1, sizeof(edge));
    new_edge->info->id = id;
    new_edge->info->from = from;
    new_edge->info->to = to;
    new_edge->info->ref_list = new_edge;
    
    
    // Alloco un nuovo nodo della lista di archi.
    // Verrà collegato alla lista di archi del nodo etichettato come "from".
    edge_list *from_edge = (edge_list *)calloc(1, sizeof(edge_list));
    from_edge->next = from->edges;
    from_edge->prev = NULL;
    from_edge->info = new_edge->info;
    
    if(from->edges != NULL)
        from->edges->prev = from_edge;
    
    from->edges = from_edge;
    
    // Salvo la posizione dell'arco rispetto agli elementi della lista di archi del nodo "from".
    new_edge->info->ref_list_from = from->edges;
    
    
    if(!is_directed) {
        // Alloco un nuovo nodo della lista di archi.
        // Verrà collegato alla lista di archi del nodo etichettato come "to".
        edge_list *to_edge = (edge_list *)calloc(1, sizeof(edge_list));
        to_edge->next = to->edges;
        to_edge->prev = NULL;
        to_edge->info = new_edge->info;
        
        if(to->edges != NULL)
            to->edges->prev = to_edge;
        
        to->edges = to_edge;
    }
    
    // Salvo la posizione dell'arco rispetto agli elementi della lista di archi del nodo "to".
    new_edge->info->ref_list_to = to->edges;
    
    
    // Attacco il nuovo puntatore ad arco in cima alla lista degli archi.
    // (Parlo della lista degli archi DEL GRAFO).
    new_edge->next = g->edges;
    
    if(g->edges != NULL)
        g->edges->prev = new_edge;
        
    g->edges = new_edge;
    g->num_edges ++;
    
    // Ora il nuovo arco è in testa alla lista di archi del grafo.
}

void add_node_to_graph(graph *g, int id) {
    if(g == NULL)
        return;
        
    node_list *new_node = (node_list *)calloc(1, sizeof(node_list));
    new_node->info = (node *)calloc(1, sizeof(node));
    new_node->info->id = id;
    new_node->info->ref_list = new_node;
    
    new_node->next = g->nodes;
    
    if(g->nodes != NULL)
        g->nodes->prev = new_node;
        
    g->nodes = new_node;
    g->num_nodes ++;
}

node *graph_get_node_by_id(graph *g, int id) {
    node_list *nodes = g->nodes;

    while(nodes != NULL) {
        if(nodes->info->id == id)
            return nodes->info;
            
        nodes = nodes->next;
    }
    
    return NULL;
}

node *node_opposite(edge *e, node *n) {
    if(e->from->id == n->id)
        return e->to;
    return e->from;
}

void BFS(graph *g) {
    
    if(g == NULL || g->num_nodes == 0)
        return;
    
    node_list *nodes = g->nodes;
    
    
    while(nodes != NULL) {
        nodes->info->color = 0;
        nodes = nodes->next;
    }
    
    
    nodeq *q = new_queue();
    g->nodes->info->color = 1;
    enqueue(q, g->nodes->info);


    while (!is_empty(q)) {
        node n = dequeue(q);
        edge_list *edges = n.edges;
        
        while(edges != NULL) {
            node *to_visit = node_opposite(edges->info, &n);
            if(to_visit->color == 0) {
                to_visit->color = 1;
                enqueue(q, to_visit);
            }
            
            edges = edges->next;
        }
    }
}