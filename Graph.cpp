#include "Graph.h"
#include "Exception.h"
#include "Utilitis.h"
#include <vector>
#include <cctype>
#include <bitset>
using namespace std;


static Graph HelperOperetor(const Graph& graph1, const Graph& graph2,const char loigical);
static string GetVerticesNameFromFile(ifstream& file);
Graph::Graph(const map<string,set<string>>&vetrics_to_enter):vertices(vetrics_to_enter){}
const map<string,set<string>>& Graph::GetVertices() const
{
    return(this->vertices);
}
Graph operator+(const Graph& graph1, const Graph& graph2 )
{
    return(HelperOperetor(graph1,graph2,PLUS));
}
Graph& Graph::operator=(const Graph& graph_to_copy)
{
    this->vertices=graph_to_copy.GetVertices();
    return(*this);
}

Graph operator^(const Graph& graph1, const Graph& graph2 )
{
    return(HelperOperetor(graph1,graph2,INTERSECTION));
}
static Graph HelperOperetor(const Graph& graph1, const Graph& graph2,const char loigical)
{
    map<string,set<string>> union_graph;
    auto graph1_vertices_iterator=graph1.GetVertices().begin();
    auto graph2_vertices_iterator=graph2.GetVertices().begin();
    while ((graph1_vertices_iterator!=graph1.GetVertices().end())&&(graph2_vertices_iterator!=graph2.GetVertices().end()))
    {
        if((graph2_vertices_iterator->first) >(graph1_vertices_iterator->first))
        {
            if(loigical==PLUS)
            {
                union_graph.insert(*graph1_vertices_iterator);
            }
            graph1_vertices_iterator++;
            continue;
        }
        if((graph2_vertices_iterator->first) < (graph1_vertices_iterator->first))
        {
            if(loigical==PLUS)
            {
                union_graph.insert(*graph2_vertices_iterator);
            }
            graph2_vertices_iterator++;
            continue;
        }
        if((graph2_vertices_iterator->first) == (graph1_vertices_iterator->first))
        {
            set<string> new_edge_set;
            auto graph1_edges_iterator=graph1_vertices_iterator->second.begin();
            auto graph2_edges_iterator=graph2_vertices_iterator->second.begin();
            while ((graph1_edges_iterator!=graph1_vertices_iterator->second.end())&&(graph2_edges_iterator!=graph2_vertices_iterator->second.end()))
            {
                if(*graph2_edges_iterator>*graph1_edges_iterator)
                {
                    if(loigical==PLUS)
                    {
                        new_edge_set.insert(*graph1_edges_iterator);
                    }
                    graph1_edges_iterator++;
                    continue;
                }
                if(*graph2_edges_iterator<*graph1_edges_iterator)
                {
                    if(loigical==PLUS)
                    {
                        new_edge_set.insert(*graph2_edges_iterator);
                    }
                    graph2_edges_iterator++;
                    continue;
                }
                if(*graph2_edges_iterator==*graph1_edges_iterator)
                {
                    if(loigical==INTERSECTION||loigical==PLUS)
                    {
                        new_edge_set.insert(*graph2_edges_iterator);
                    }
                    graph2_edges_iterator++;
                    graph1_edges_iterator++; 
                    continue;   
                }

            }
            while(graph1_edges_iterator!=graph1_vertices_iterator->second.end())
            {
                if(loigical==PLUS)
                {
                    new_edge_set.insert(*graph1_edges_iterator);
                }
                graph1_edges_iterator++;
            }
            while(graph2_edges_iterator!=graph2_vertices_iterator->second.end())
            {
                if(loigical==PLUS)
                {
                    new_edge_set.insert(*graph2_edges_iterator);
                }
                graph2_edges_iterator++;
            }

            union_graph.insert({graph2_vertices_iterator->first,new_edge_set});
            graph1_vertices_iterator++;
            graph2_vertices_iterator++;

        }

    }
    while (graph1_vertices_iterator!=graph1.GetVertices().end())
    {
        if(loigical==PLUS)
        {
            union_graph.insert(*graph1_vertices_iterator);
        }
        graph1_vertices_iterator++;
    }
    while (graph2_vertices_iterator!=graph2.GetVertices().end())
    {
        if(loigical==PLUS)
        {
            union_graph.insert(*graph2_vertices_iterator);
        }
        graph2_vertices_iterator++;
    }
    return(union_graph);

}
Graph operator-(const Graph& graph1, const Graph& graph2 )
{
    map<string,set<string>> new_graph;
    auto graph1_vertices_iterator=graph1.GetVertices().begin();
    auto graph2_vertices_iterator=graph2.GetVertices().begin();
    while ((graph1_vertices_iterator!=graph1.GetVertices().end())&&(graph2_vertices_iterator!=graph2.GetVertices().end()))
    {
        if((graph2_vertices_iterator->first) >(graph1_vertices_iterator->first))
        {
            set<string> new_edge_set;
            auto graph1_edges_iterator=graph1_vertices_iterator->second.begin();
            while(graph1_edges_iterator!=graph1_vertices_iterator->second.end())
            {
                if(graph2.GetVertices().count(*graph1_edges_iterator)==0)
                {
                    new_edge_set.insert(*graph1_edges_iterator);
                }                
                graph1_edges_iterator++;
            }
            new_graph.insert({graph1_vertices_iterator->first,new_edge_set});
            graph1_vertices_iterator++;
            continue;
        }
        if((graph2_vertices_iterator->first) < (graph1_vertices_iterator->first))
        {
            graph2_vertices_iterator++;
            continue;
        }
        if((graph2_vertices_iterator->first) == (graph1_vertices_iterator->first))
        {
            graph1_vertices_iterator++;
            graph2_vertices_iterator++;
        }

    }
    while (graph1_vertices_iterator!=graph1.GetVertices().end())
    {
        set<string> new_edge_set;
        auto graph1_edges_iterator=graph1_vertices_iterator->second.begin();
        while(graph1_edges_iterator!=graph1_vertices_iterator->second.end())
            {
                if(graph2.GetVertices().count(*graph1_edges_iterator)==0)
                {
                    new_edge_set.insert(*graph1_edges_iterator);
                }
                graph1_edges_iterator++;
            }
        new_graph.insert({graph1_vertices_iterator->first,new_edge_set});
        graph1_vertices_iterator++;
    }
    return(new_graph);
}
Graph Graph::operator!() const
{
    map<string,set<string>> new_graph;
    auto iterator_vertices_1=vertices.begin();
    while (iterator_vertices_1!=vertices.end())
    {
        set<string> new_edge_set;
        auto iterator_vertices_2=vertices.begin();
        while(iterator_vertices_2!=vertices.end())
        {
            if((iterator_vertices_1->second.count(iterator_vertices_2->first)==0)&&(iterator_vertices_1!=iterator_vertices_2))
            {
                new_edge_set.insert(iterator_vertices_2->first);
            }
            iterator_vertices_2++;
        }
        new_graph.insert({iterator_vertices_1->first,new_edge_set});
        iterator_vertices_1++;
    }
    return(new_graph);
}
Graph operator*(const Graph& graph1,const Graph& graph2)
{
    map<string,set<string>> new_graph;
    auto graph1_vertices_iterator=graph1.GetVertices().begin();
    while(graph1_vertices_iterator!=graph1.GetVertices().end())
    {
        auto graph2_vertices_iterator=graph2.GetVertices().begin();
        while (graph2_vertices_iterator!=graph2.GetVertices().end())
        {
            string name_of_vertic= OPEN_PARENTHESIS + graph1_vertices_iterator->first + COMMA + graph2_vertices_iterator->first + CLOSE_PARENTHESIS;
            set<string> new_edge_set;
            auto graph1_edges_iterator=graph1_vertices_iterator->second.begin();
            while(graph1_edges_iterator!=graph1_vertices_iterator->second.end())
            {
                auto graph2_edges_iterator=graph2_vertices_iterator->second.begin();
                while (graph2_edges_iterator!=graph2_vertices_iterator->second.end())
                {
                    string name_of_edge=OPEN_PARENTHESIS + *graph1_edges_iterator + COMMA 
                    + *graph2_edges_iterator + CLOSE_PARENTHESIS;
                    new_edge_set.insert(name_of_edge);
                    graph2_edges_iterator++;
                }
            graph1_edges_iterator++;
                
            }
            new_graph.insert({name_of_vertic,new_edge_set});
            graph2_vertices_iterator++;

        
        }
        graph1_vertices_iterator++;
    }
    return(new_graph);
}
std::ostream& operator<< (std::ostream &os,const Graph& graph)
{
    string out_string;
    auto graph_iterator=graph.GetVertices().begin();
    if(graph.GetVertices().begin()==graph.GetVertices().end())
    {
        os<<"$"<<endl;
        return(os);
    }
    while(graph_iterator!=graph.GetVertices().end())
    {
        os<<graph_iterator->first<<endl;
        graph_iterator++;
    }
    os<<'$'<<endl;
    graph_iterator=graph.GetVertices().begin();
    while ((graph_iterator!=graph.GetVertices().end()))
    {
        auto edges_iterator=graph_iterator->second.begin();
        while (edges_iterator!=graph_iterator->second.end())
        {
            os<<graph_iterator->first<<" "<<*edges_iterator<<endl;
            edges_iterator++;
        }
        graph_iterator++;
    }
    return(os);
    
}
bool CheckVericesName(const string &name)
{

    int count_comma=0;
    if(name=="")
    {
        return(false);
    }
    for(char letter:name)
    {
        if(isalpha(letter)|| isdigit(letter))
        {
            continue;
        }
        if((letter==OPEN_PARENTHESIS)||(letter==CLOSE_PARENTHESIS)||(letter==COMMA))
        {
            if(letter==OPEN_PARENTHESIS)
            {
                count_comma++;
            }
            if(letter==CLOSE_PARENTHESIS)
            {
                count_comma--;
                if(count_comma<0)
                {
                    
                    return(false);
                }
            }
            if((letter==COMMA)&&(count_comma<1))
            {
                return(false);
            }

        }
        else
        {
            return(false);
        }
        
    }
    if(count_comma==0)
    {
        return(true);
    }
    return(false);
}
bool Graph::IsVericesExistsInGraph(const std::string &verices_name) const
{

    if(this->vertices.count(verices_name)==1)
    {
        return(true);
    }
    return(false);
}

bool Graph::IsEdgeExistsExistsInGraph(const std::string &source, const std::string &destinaion) 
{
    if(this->vertices[source].count(destinaion)==1)
    {
        return(true);
    }
    return(false);
}

Graph& Graph::AddVerticesToGraph(const std::string &vertices_name)
{
    if(!CheckVericesName(vertices_name))
    {
        throw(InvalidVerticisName());
    }
    if(IsVericesExistsInGraph(vertices_name))
    {
        throw(VerticisAllreadyExist());
    }
    set<string> edges_of_vertices;
    this->vertices.insert({vertices_name,edges_of_vertices});
    return(*this);
}
Graph& Graph::AddEdgesToGraph(const std::string &source, const std::string &destinaion)
{
    if(!IsVericesExistsInGraph(source))
    {
        throw(VerticisisNotExists());
    }
    if(!IsVericesExistsInGraph(destinaion))
    {
        throw(VerticisisNotExists());
    }
    if(source==destinaion)
    {
        throw(InvlaidEdgeName());
    }
    if(IsEdgeExistsExistsInGraph(source,destinaion))
    {
        throw(EdgeisAllreadyExist());
    }
    this->vertices[source].insert(destinaion);
    return(*this);
}
unsigned int Graph::NumberOfVerticesInGraph() const
{
    return(this->vertices.size());
}
unsigned int Graph::NumberOfEdgesInGraph() const
{
    unsigned int count_edges=0;
    auto iterator=this->vertices.begin();
    while (iterator!=this->vertices.end())
    {
        count_edges=count_edges + iterator->second.size();
        iterator++;
    }
    return(count_edges);
}
void Graph::SaveGraphToFile(std::string file_name) const
{
    ofstream outfile(file_name,std::ios_base::binary);
    if(!outfile)
    {
        throw(CannotOpenFile());
    }
    unsigned int number_of_vertices=this->NumberOfVerticesInGraph();
    unsigned int number_of_edges=this->NumberOfEdgesInGraph();
    outfile.write((const char*)&number_of_vertices,sizeof(unsigned int));
    outfile.write((const char*)&number_of_edges,sizeof(unsigned int));
    auto iterator=this->vertices.begin();
    while (iterator!=this->vertices.end())
    {
        unsigned int  vertices_size=iterator->first.size();
        outfile.write((const char*)&vertices_size,sizeof(unsigned int));
        for(char letter:iterator->first)
        {
            outfile.write((const char*)&letter,sizeof(char));
        }
        iterator++;
    }
    iterator=this->vertices.begin();
    while (iterator!=this->vertices.end())
    {
        auto edge_iterator=iterator->second.begin();
        while (edge_iterator!=iterator->second.end())
        {
            unsigned int  vertices_size=iterator->first.size();
            outfile.write((const char*)&vertices_size,sizeof(unsigned int));
            for(char letter:iterator->first)
            {
                outfile.write((const char*)&letter,sizeof(char));
            }
            unsigned int size_of_edge=edge_iterator->size();
            outfile.write((const char*)&size_of_edge,sizeof(unsigned int));
            for(char letter:*edge_iterator)
            {
                outfile.write((const char*)&letter,sizeof(char));
            }
            edge_iterator++;
        }
        iterator++;
    }
}
void Graph::LoadGraphFromFile(std::string file_name)
{
    RemoveSpacesFromBeginAndEnd(file_name);
    ifstream infile(file_name,std::ios_base::binary);
    if(!infile)
    {
        throw(CannotOpenFile());
    }
    unsigned int number_of_vertices=0;
    unsigned int number_of_edges=0;
    infile.read((char*)&number_of_vertices,sizeof(unsigned int));
    if(!infile)
    {
        throw(FileFormatUnrecocnize());
    }
    infile.read((char*)&number_of_edges,sizeof(unsigned int));
    if(!infile)
    {
        throw(FileFormatUnrecocnize());
    }
    unsigned int count_vertices=1;
    while (count_vertices<=number_of_vertices)
    {   
        string vertix_name=GetVerticesNameFromFile(infile);
        this->AddVerticesToGraph(vertix_name);
        count_vertices++;
    }
    unsigned int count_edges=1;
    while (count_edges<=number_of_edges)
    {   
        string source=GetVerticesNameFromFile(infile);
        string dest=GetVerticesNameFromFile(infile);
        this->AddEdgesToGraph(source,dest);
        count_edges++;
    }

    if((infile.get()!=EOF))
    {

        throw(FileFormatUnrecocnize());
    }
    
}
static string GetVerticesNameFromFile(ifstream& infile)
{
    string name_of_vertix="";
    unsigned int vertices_length=0;
    infile.read((char*)&vertices_length,sizeof(unsigned int));
    if(!infile)
    {
        throw(FileFormatUnrecocnize());
    }
    char letter;
    for(unsigned int i=0;i<vertices_length;i++)
    {
        infile.read((char*)&letter,sizeof(char));
        if(!infile)
        {
            throw(FileFormatUnrecocnize());
        }
        name_of_vertix=name_of_vertix + letter;
    }
    return(name_of_vertix);
}







