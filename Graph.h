#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <fstream>
class Graph
{
    private:
       std::map<std::string,std::set<std::string>> vertices;

    public:
        Graph(const std::map<std::string,std::set<std::string>>& vetrics_to_enter=std::map<std::string,std::set<std::string>>());
        ~Graph()=default;
        const std::map<std::string,std::set<std::string>>& GetVertices() const;
        Graph& operator=(const Graph& graph_to_copy);
        Graph operator!() const;
        Graph& AddVerticesToGraph(const std::string &vertix_name);
        Graph& AddEdgesToGraph(const std::string &source,const std::string &destinaion);
        bool IsVericesExistsInGraph(const std::string &verices_name) const;
        bool IsEdgeExistsExistsInGraph(const std::string &source, const std::string &destinaion) ;
        unsigned int NumberOfVerticesInGraph() const; 
        unsigned int NumberOfEdgesInGraph() const;
        void SaveGraphToFile(std::string file_name) const;
        void LoadGraphFromFile(std::string file_name);

        

        
};
std::ostream& operator<< (std::ostream &os,const Graph& graph);
Graph operator+(const Graph& graph1, const Graph& graph2 );
Graph operator^(const Graph& graph1, const Graph& graph2 );
Graph operator-(const Graph& graph1, const Graph& graph2);
Graph operator*(const Graph& graph1, const Graph& graph2);
bool CheckVericesName(const std::string &name);





 
#endif