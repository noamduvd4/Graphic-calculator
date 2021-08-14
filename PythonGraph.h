#ifndef PythonGraph_H
#define PythonGraph_H
#include "Graph.h"
 

typedef  Graph* grpah_pointer;

Graph* create();
void destroy(grpah_pointer graph_to_destroy);
Graph* addEdge(grpah_pointer graph,const char* source, const char* destenion );
Graph* addVertex(grpah_pointer graph,const char* vertix_name);
void disp(grpah_pointer graph );
Graph* graphUnion(grpah_pointer graph_in1, grpah_pointer  graph_in2,grpah_pointer graph_out);
Graph* graphIntersection(grpah_pointer graph_in1, grpah_pointer graph_in2, grpah_pointer graph_out);
Graph* graphDifference(grpah_pointer graph_in1, grpah_pointer graph_in2, grpah_pointer graph_out);
Graph* graphProduct(grpah_pointer graph_in1, grpah_pointer graph_in2, grpah_pointer graph_out);
Graph* graphComplement(grpah_pointer graph_in, grpah_pointer graph_out);





#endif