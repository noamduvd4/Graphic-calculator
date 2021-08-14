#include "PythonGraph.h"
#include "Exception.h"
Graph* create()
{
    Graph* new_graph= new Graph;
    return new_graph;
}

void destroy(grpah_pointer graph_to_destroy)
{
    delete(graph_to_destroy);
}

grpah_pointer addVertex(grpah_pointer graph, const char* vertix_name)
{
    std::string vertix_name_string (vertix_name);
    if(graph==nullptr)
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
    }
    else
    {
        try
        {
            graph->AddVerticesToGraph(vertix_name_string);
        }
        catch(const Exception& exception)
        {
            std::cout << exception.what() << '\n';
            return(nullptr);
        }
        return(graph);
    }
    return(nullptr);

}
grpah_pointer addEdge(grpah_pointer graph,const char* source, const char* destenion )
{
    std::string source_string (source);
    std::string destenion_string(destenion);

    if(graph==nullptr)
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
    }
    else
    {
        try
        {
            graph->AddEdgesToGraph(source_string,destenion_string);
        }
        catch(const Exception& exception)
        {
            std::cout << exception.what() << '\n';
            return(nullptr);
        }
        return(graph);
    }
    return(nullptr);
    
}
void disp(const grpah_pointer graph )
{
    if(graph==nullptr)
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
    }
    else
    {
        std::cout<<*graph;
    }
    
}
grpah_pointer graphUnion(const grpah_pointer graph_in1, const grpah_pointer graph_in2,grpah_pointer graph_out)
{
    if((graph_in1==nullptr)||(graph_in2==nullptr)||(graph_out==nullptr))
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
        return(nullptr);
    }
    *graph_out=*graph_in1 + *graph_in2;
    return(graph_out);
}
grpah_pointer graphIntersection(const grpah_pointer graph_in1, const grpah_pointer graph_in2, grpah_pointer graph_out)
{
    if((graph_in1==nullptr)||(graph_in2==nullptr)||(graph_out==nullptr))
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
        return(nullptr);
    }
    *graph_out=*graph_in1 ^ *graph_in2;
    return(graph_out);
}
grpah_pointer graphDifference(const grpah_pointer graph_in1, const grpah_pointer graph_in2, grpah_pointer graph_out)
{
    if((graph_in1==nullptr)||(graph_in2==nullptr)||(graph_out==nullptr))
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
        return(nullptr);
    }
    *graph_out=*graph_in1 - *graph_in2;
    return(graph_out);
}
grpah_pointer graphProduct(const grpah_pointer graph_in1, const grpah_pointer graph_in2, grpah_pointer graph_out)
{
    if((graph_in1==nullptr)||(graph_in2==nullptr)||(graph_out==nullptr))
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
        return(nullptr);
    }
    *graph_out=*graph_in1 * *graph_in2;
    return(graph_out);
}
grpah_pointer graphComplement(const grpah_pointer graph_in, grpah_pointer graph_out)
{
    if((graph_in==nullptr)||(graph_out==nullptr))
    {
        std::cout<<"Error: Pointer Value Is nullptr "<<std::endl;
        return(nullptr);
    }
    *graph_out=!*graph_in;
    return(graph_out);
}
