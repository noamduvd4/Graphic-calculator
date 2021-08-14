%module graph
%{
    #include "PythonGraph.h"
%}

Graph* create();
void destroy(Graph* graph_to_destroy);
Graph* addVertex(Graph* graph, const char* vertix_name);
Graph* addEdge(Graph* graph,const char* source, const char* destenion );
void disp(Graph* graph );
Graph* graphUnion(Graph* graph_in1, Graph*  graph_in2,Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphComplement(Graph* graph_in, Graph* graph_out);