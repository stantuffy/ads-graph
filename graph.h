#ifndef GRAPH_H
#define GRAPH_H

// Definizione della struttura "grafo".
// E' rappresentato con 2 liste, una per i nodi ed una per gli archi.
// In ogni nodo c'è una lista dei suoi archi(ovvero gli archi di cui è from/to).
// Le liste in questione sono doppiamente concatenate.

typedef struct node_list node_list;
typedef struct node node;
typedef struct edge_list edge_list;
typedef struct edge edge;
typedef struct graph graph;

graph *new_graph();
void add_edge_to_graph(graph *g, node *from, node *to, int id, _Bool is_directed);
void add_node_to_graph(graph *g, int id);
node *graph_get_node_by_id(graph *g, int id);
node *node_opposite(edge *e, node *n);
void BFS(graph *g);

struct node_list {
    struct node_list *prev;
    struct node_list *next;
    node *info;
};

struct node {
    int id;
    node_list *ref_list;
    edge_list *edges;
    int color;
};

struct edge_list {
    struct edge_list *prev;
    struct edge_list *next;
    edge *info;
};

struct edge {
    int id;
    node *from;
    node *to;
    edge_list *ref_list;
    edge_list *ref_list_from;
    edge_list *ref_list_to;
};

struct graph {
    node_list *nodes;
    edge_list *edges;
    int num_nodes;
    int num_edges;
};

#endif