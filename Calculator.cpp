#include "Calculator.h"
#include "Utilitis.h"
#include "Exception.h"
#include <fstream>
using namespace std;


static bool CheckGraphName(string &name);
static vector<string> OrgnizeEdges(string data);
static Graph CreateNewGraph (const string &data);
static bool CheckOpenerAndCloser(const string &data);
static void ReplaceNewGraphWithLigalName(string &data);
static bool LocationOfLoad(string &data , int& begin, int& end, int& cyrcle_begin);
static void ReplaceLoad(string &data);
static void RemoveAllSpaces(string &data);
static bool CheckNotLocation(const string& data);
static bool CheckOpenAndCloserCyrcleLocation(const string& data);
static void ChangeMultiSpaceToOneSpace(string &data);
static void RemoveSpaceBetweenOperators(string &data);
static void ReplaceOperatorsWithSpace(string &data);
static bool CheckIfThereIsSpace(const string &data );
static bool CheckOperatorExpretion(const string &data);

Calculator::Calculator(map<string,Graph> given_graph,int x):graphs(given_graph),temperary_counter(x){}

void Calculator::CleanTemperaryParams()
{
    for(int i=1;i<=this->temperary_counter;i++)
    {
        this->graphs.erase(to_string(i)+"G");
    }
    this->temperary_counter=0;
}

void Calculator::Manual_Running()
{
    bool not_exit=true;
    while (not_exit)
    {
        std::cout<<"Gcalc> ";
        string data;
        std::getline(cin,data);
        if(cin.eof())
        {
            break;
        }
        try {not_exit=GetInput(data,cout);}
            catch(Exception & exception)
            {
                cout<<exception.what()<<endl;
                not_exit=true;
                CleanTemperaryParams();
            }
        CleanTemperaryParams();

    }
}
    void Calculator::Auto_Running(ifstream &input, ofstream &output)
    {
    bool not_exit=true;
    while (!input.eof())
    {
        string data;
        std::getline(input,data);
        try {not_exit=GetInput(data,output);}
            catch(Exception & exception)
            {
                output<<exception.what()<<endl;
                CleanTemperaryParams();
            }
        CleanTemperaryParams();
        if(!not_exit)
        {
            break;

        }
    }


}
static bool CheckGraphName(string &name)
{
    bool firt_time=true;
    RemoveSpacesFromBeginAndEnd(name);
    if(SAVED_WORD.count(name)==1)
    {
        return(false);
    }
    if(name==LOAD_COMMAND)
    {
        return(false);
    }
    if(name=="")
    {
        return(true);
    }
    for(char letter:name)
    {
        if(isalpha(letter)|| isdigit(letter))        
        {   
            if(firt_time)
            {
                firt_time=false;
                if(isdigit(letter))
                {
                    return(false);
                }
                continue;
            }
            continue;

        }
        return(false);
    }
    return(true);
}

static vector<string> OrgnizeEdges(string data)
{
    vector<string> edges;
    int less_pos=-1,more_pos=-1;
    for(unsigned int i=0;i<data.size();i++)
    {
        char letter=data[i];
        switch (letter)
        {
        case WHITE_SPACE:
            break;
        case LESS_THAN_SIGN:
            if(less_pos!=-1)
            {
                throw(InvlaidEdgeName());
            }
            less_pos=i;
            break;
        case MORE_THAN_SIGN:
            if((less_pos==-1)||(more_pos!=-1))
            {
                throw(InvlaidEdgeName());


            }
            more_pos=i;
            edges.push_back(data.substr(less_pos+1, more_pos-less_pos-1));
            break;
        case SPLITER:
            if((less_pos!=-1)&&(more_pos==-1))
            {
                break;
            }
            if((less_pos!=-1)&&(more_pos!=-1))
            {
                less_pos=-1;
                more_pos=-1;
                break;
            }
            throw(InvlaidEdgeName());
        default:
            if((less_pos!=-1)&&(more_pos==-1))
            {
                break;
            }
            throw(InvlaidEdgeName());
        }
  
        
    }
    if((less_pos!=-1)&&(more_pos!=-1));
    {
        return(edges);
    }
    throw(InvlaidEdgeName());
    return(edges);
} 
static Graph CreateNewGraph (const string &data)
{
        if(data=="")
        {
            Graph new_graph;
            return(new_graph);
        }
        const char SPLIT_V_FROM_E ='|';
        vector<string>split_v_from_e_vector=SplitToArry(data,SPLIT_V_FROM_E);
        map<string,set<string>> vertices;
        if(split_v_from_e_vector.size()>2)
        {

            throw(IllegalGraphArgument());
        }
        vector<string> names_of_vertices=SplitToArry(split_v_from_e_vector[0],SPLITER);
        int location_not_space_first=split_v_from_e_vector[0].find_first_not_of(WHITE_SPACE);
        if(location_not_space_first!=-1)
        {
            for(string name :names_of_vertices)
            {
                RemoveSpacesFromBeginAndEnd(name);
                if(CheckVericesName(name)==false)
                {
                    throw(InvalidVerticisName());
                }
                if(vertices.count(name)==1)
                {
                    throw(VerticisAllreadyExist());
                }
                set<string> new_set;
                vertices.insert({name,new_set});
            }
        }
        if(split_v_from_e_vector.size()==2)
        {
            RemoveSpacesFromBeginAndEnd(split_v_from_e_vector[1]);
            if(split_v_from_e_vector[1]!="")
            {
                if(split_v_from_e_vector[1].find_last_of(SPLITER)==split_v_from_e_vector[1].size()-1)
                {
                    throw(InvlaidEdgeName());   
                }             
                vector<string> edges_vector=OrgnizeEdges(split_v_from_e_vector[1]);
                for(string edge: edges_vector)
                {
                    vector<string> vertics_in_edges=SplitToArry(edge,SPLITER);
                    if(vertics_in_edges.size()!=2)
                    {
                        throw(InvlaidEdgeName());
                    }
                    RemoveSpacesFromBeginAndEnd(vertics_in_edges[0]);
                    RemoveSpacesFromBeginAndEnd(vertics_in_edges[1]);
                    if((vertices.count(vertics_in_edges[0])==0)||(vertices.count(vertics_in_edges[1])==0))
                    {
                        throw(VerticisisNotExists());
                    }
                    if(vertices.find(vertics_in_edges[0])->second.count(vertics_in_edges[1])==1)
                    {
                        throw(EdgeisAllreadyExist());
                    }
                    if(vertics_in_edges[0]==vertics_in_edges[1])
                    {
                        throw(InvlaidEdgeName());
                    }
                    vertices.find(vertics_in_edges[0])->second.insert(vertics_in_edges[1]);
                }

            }
        }
        Graph new_graph(vertices);
        return(new_graph);

}
static bool CheckOpenerAndCloser(const string &data)
{
    int count_cyrcle=0;
    int count_new_graph=0;
    for(char letter:data)
    {
        switch (letter)
        {
        case OPEN_CYRCLE_PARENTHESIS:
            count_cyrcle++;
            break;
        case CLOSE_CYRCLE_PARENTHESIS: 
            count_cyrcle--;
            if(count_cyrcle<0)
            {
                return(false);
            }
            break;
        case OPEN_NEW_GRAPH:
            count_new_graph++;
            if(count_new_graph>1)
            {
                return(false);
            }
            break;
        case CLOSE_NEW_GRAPH:
            count_new_graph--;
            if (count_new_graph<0)
            {
                return(false);
            }
            
            break;
        default:
            break;
        }


    }
    if((count_new_graph==0)&&(count_cyrcle==0))
    {
        return(true);
    }
    return(false);
}
static void ReplaceNewGraphWithLigalName(string &data)
{
    bool not_finish=true;
    while (not_finish==true)
    {
        not_finish=false;
        int count=0,index_begin=0,index_end=0;
        for(unsigned int i=0;i<data.size();i++)
        {
            if(data[i]==OPEN_NEW_GRAPH)
            {
                index_begin=i;
                count++;
            }
            if(data[i]==CLOSE_NEW_GRAPH)
            {
                index_end=i;
                count++;
            }
            if(count==2)
            {
                data.replace(index_begin,index_end-index_begin+1,VALID_GRAPH_NAME);
                not_finish=true;
                break;
            }

        }
        
    }

}
static bool LocationOfLoad(string &data , int& begin, int& end, int& cyrcle_begin)
{
    begin=data.find(LOAD_COMMAND,begin);
    while (begin!=-1)
    {
        int data_size=data.size();
        for(int i=begin+LOAD_COMMAND.size();i<data_size;i++)
        {
            if(data[i]==WHITE_SPACE)
            {
                continue;
            }
            else if (data[i]!=OPEN_CYRCLE_PARENTHESIS)
            {

                break;
            }
            cyrcle_begin=i;
            end=data.find(CLOSE_CYRCLE_PARENTHESIS,cyrcle_begin);
            return(true);
        }
        begin=data.find(LOAD_COMMAND,begin+1);

    }
    return(false);
         
}


void Calculator::DealingWithLoad(string &data)
{

    int begin_load=0,end_load=0,being_cyrcle=0;
    while (LocationOfLoad(data,begin_load,end_load,being_cyrcle))
    {
        int graph_name_begin=being_cyrcle+1;
        int graph_name_end=end_load-1;
        if(graph_name_begin==graph_name_end)
        {
            throw(CannotOpenFile());
        }
        Graph new_graph;
        string file_name=data.substr(graph_name_begin,graph_name_end-graph_name_begin+1);
        new_graph.LoadGraphFromFile(file_name);
        this->temperary_counter++;
        string graph_name=to_string(this->temperary_counter)+"G";
        this->graphs.insert({graph_name,new_graph});
        data.replace(begin_load,end_load-begin_load+1,graph_name);
        begin_load=0;
        end_load=0;
        being_cyrcle=0;  
    } 
    
}
static void ReplaceLoad(string &data)
{
    int begin_load=0,end_load=0,being_cyrcle=0;
    while (LocationOfLoad(data,begin_load,end_load,being_cyrcle))
    {
        data.replace(begin_load,end_load-begin_load+1,VALID_GRAPH_NAME);
        begin_load=0;
        end_load=0;
        being_cyrcle=0;  
    } 
}

static void ChangeMultiSpaceToOneSpace(string &data)
{
    string new_data="";
    int count=0;
    for(char letter:data)
    {
        if(letter!=WHITE_SPACE)
        {
            count=0;
            new_data=new_data + letter;

        }
        else
        {
            if(count==0)
            {
                count=1;
                new_data=new_data+WHITE_SPACE;
            }
        }
        

    }
    data=new_data;
}
static void RemoveSpaceBetweenOperators(string &data)
{

   string new_data="";
   for(unsigned int i=0;i<data.size();i++)
   {
       if(data[i]!=WHITE_SPACE)
       {
           new_data=new_data+data[i];
       }
       else
       {
           if((VALID_OPERATORS_SET.count(data[i-1])==1)||(VALID_OPERATORS_SET.count(data[i+1])==1)||(data[i-1]==NOT)||(data[i+1]==NOT))
           {
               continue;
           }

           if((data[i+1]==OPEN_CYRCLE_PARENTHESIS)||(data[i+1]==CLOSE_CYRCLE_PARENTHESIS)||(data[i-1]==OPEN_CYRCLE_PARENTHESIS)||(data[i-1]==CLOSE_CYRCLE_PARENTHESIS))
           {
               continue;
           }
           new_data=new_data+WHITE_SPACE;

       }
 
   }
   data=new_data;


}
static void ReplaceOperatorsWithSpace(string &data)
{

   string new_data;
   for(unsigned int i=0;i<data.size();i++)
   {
       char letter=data[i];
       if((letter==PLUS)||(letter==INTERSECTION)||(letter==SUBTRACTION)||(letter==ASTERISK))
       {

           new_data=new_data+WHITE_SPACE;
       }
       else if ((letter==OPEN_CYRCLE_PARENTHESIS)||(letter==CLOSE_CYRCLE_PARENTHESIS)||(letter==NOT))
       {
           continue;
       }
       else
       {
           new_data=new_data+letter;
       }  
   }
   data=new_data;
}

static bool CheckIfThereIsSpace(const string& data )
{
    if(data.find(' ')!=string::npos)
    {
        return(true);
    }
    return(false);
}
static bool CheckOperatorExpretion(const string &data)
{
    string copy_of_data=data;
    if(CheckOpenerAndCloser(copy_of_data)!=true)
    {
        return(false);
    }
    ReplaceNewGraphWithLigalName(copy_of_data);
    ReplaceLoad(copy_of_data);
    ChangeMultiSpaceToOneSpace(copy_of_data);
    RemoveSpacesFromBeginAndEnd(copy_of_data);
    RemoveSpaceBetweenOperators(copy_of_data);
    if(copy_of_data=="")
    {
        return(false);
    }
    if(CheckIfThereIsSpace(copy_of_data))
    {
        throw(InvalidExpretion());
    }
    if(!CheckNotLocation(copy_of_data))
    {
        throw(InvalidExpretion());
    }
    if(!CheckOpenAndCloserCyrcleLocation(copy_of_data))
    {
        throw(InvalidExpretion());
    }
    ReplaceOperatorsWithSpace(copy_of_data);
    int count_space=0;
    for(unsigned int i=0;i<copy_of_data.size();i++)
    {
        char letter=copy_of_data[i];
        if(letter==' ')
        {
            if((i==0)||(i==copy_of_data.size()-1))
            {
                return(false);
            }
            count_space++;
            if(count_space>1)
            {
                return(false);
            }
        }
        else
        {
            count_space=0;
        }
        
    }
    vector<string> names_arry=SplitToArry(copy_of_data,' ');
    for(string name: names_arry)
    {
        if(CheckGraphName(name)==false)
        {
            return(false);
        }
    }
    return(true);    
}
static void  RemoveAllSpaces(string &data)
{
    string new_data="";
    for(char letter: data)
    {
        if(letter!=WHITE_SPACE)
        {
            new_data=new_data+letter;
        }
    }
    data=new_data;
}
static bool CheckNotLocation(const string &data)
{
    for(unsigned int i=0;i<data.size();i++)
    {
        if(data[i]==NOT)
        {
            if((i==data.size()-1)||(VALID_OPERATORS_SET.count(data[i+1])==1)||(data[i+1]==CLOSE_CYRCLE_PARENTHESIS))
            {
                return(false);
            }
            if((i!=0)&&(VALID_OPERATORS_SET.count(data[i-1])==0)&&(data[i-1]!=OPEN_CYRCLE_PARENTHESIS)&&(data[i-1]!=NOT))
            {
                return(false);
            }

        }
    }
    return(true);
}
static bool CheckOpenAndCloserCyrcleLocation(const string& data)
{
    for(unsigned int i=0; i<data.size();i++)
    {
        if(data[i]==OPEN_CYRCLE_PARENTHESIS)
        {

            if((i!=0)&&(VALID_OPERATORS_SET.count(data[i-1])==0)&&(data[i-1]!=NOT)&&(data[i-1]!=OPEN_CYRCLE_PARENTHESIS))
            {
                return(false);
            }
            if((VALID_OPERATORS_SET.count(data[i+1])==1)||(data[i+1]==CLOSE_CYRCLE_PARENTHESIS))
            {
                return(false);
            }

        }
        if(data[i]==CLOSE_CYRCLE_PARENTHESIS)
        {
            if(i==data.size()-1)
            {
                return(true);
            }
            if((VALID_OPERATORS_SET.count(data[i-1])==1)||(data[i-1]==NOT)||(data[i-1]==OPEN_CYRCLE_PARENTHESIS))
            {
                return(false);
            }
            if((VALID_OPERATORS_SET.count(data[i+1])==0)&&(data[i+1]!=CLOSE_CYRCLE_PARENTHESIS))
            {
                return(false);
            }



        }
    }
    return(true);
}

void Calculator::WorksOnNewGraphInExpretion(string &data )
{
    bool find_new_graph_to_create=true;
    while (find_new_graph_to_create)
    {
        find_new_graph_to_create=false;
        int strat_new_graph_location=0;
        int end_new_graph_location=0;
        for(unsigned int i=0;i<data.size();i++)
        {
            char letter=data[i];
            if(letter==OPEN_NEW_GRAPH)
            {
                strat_new_graph_location=i;
            }
            if(letter==CLOSE_NEW_GRAPH)
            {
                end_new_graph_location=i;
                string new_graph_data=data.substr(strat_new_graph_location+1,end_new_graph_location-strat_new_graph_location-1);
                Graph new_temperary_graph=CreateNewGraph(new_graph_data);
                this->temperary_counter++;
                string new_graph_name= std::to_string(this->temperary_counter) + "G";
                data.replace(strat_new_graph_location,end_new_graph_location-strat_new_graph_location+1,new_graph_name);
                this->graphs.insert({new_graph_name,new_temperary_graph});
                find_new_graph_to_create=true;
                break;               
            }
        }
    }
    
}
void Calculator::WorksOnNotInExpretion(string &data)
{
    bool there_was_not=true;
    while(there_was_not==true)
    {
        int not_location=-1;
        int end_of_graph_location=-1;
        there_was_not=false;
        for (unsigned int i=0;i<data.size();i++)
        {

            if((data[i]==NOT)&&(data[i+1]!=NOT))
            {
                not_location=i;
            }
            if((not_location!=-1)&&((i==data.size()-1)||(VALID_OPERATORS_SET.count(data[i+1])==1)))
            {
                end_of_graph_location=i;
                string graph_name=data.substr(not_location+1,end_of_graph_location-not_location);
                if(!(this->IfGraphIsInCalculator(graph_name)))
                {
                    throw(GraphIsNotExists());
                }
                this->temperary_counter++;
                Graph new_graph=!(this->graphs[graph_name]);
                string new_graph_name=std::to_string(this->temperary_counter) +"G";
                this->graphs.insert({new_graph_name,new_graph});
                data=data.replace(not_location,end_of_graph_location-not_location+1,new_graph_name);
                there_was_not=true;
                break;


            }
        }
    }
}
bool Calculator::IfGraphIsInCalculator(const string &graph_name ) const
{
    if(this->graphs.count(graph_name)==1)
    {
        return(true);
    }
    return(false);
}
void Calculator::WorksOnOperatinInExpretion(string &data)
{
    bool there_is_operator=true;

    while (there_is_operator)
    {
        int pos_of_first_graph_begining=0;
        int pos_of_first_graph_ending=-1;
        int pos_of_second_graph_begining=-1;
        int pos_of_second_graph_ending=-1;
        int pos_of_operator;
        bool start_operation=false;
        there_is_operator=false;
        for(unsigned int i=0;i<data.size();i++)
        {

            string graph1_name, graph2_name;

            if(VALID_OPERATORS_SET.count(data[i])==1)
            {
                if((pos_of_first_graph_ending==-1))
                {
                    pos_of_first_graph_ending=i-1;
                    pos_of_operator=i;
                    pos_of_second_graph_begining=i+1;
                }
                else
                {
                    pos_of_second_graph_ending=i-1;
                    graph1_name=data.substr(pos_of_first_graph_begining,pos_of_first_graph_ending-pos_of_first_graph_begining+1);
                    graph2_name=data.substr(pos_of_second_graph_begining,pos_of_second_graph_ending-pos_of_second_graph_begining+1);
                    start_operation=true;
                }
                
            }
            if((pos_of_second_graph_begining!=-1)&&(i==data.size()-1))
            {
                pos_of_second_graph_ending=i;
                graph1_name=data.substr(pos_of_first_graph_begining,pos_of_first_graph_ending-pos_of_first_graph_begining+1);
                graph2_name=data.substr(pos_of_second_graph_begining,pos_of_second_graph_ending-pos_of_second_graph_begining+1);
                start_operation=true;
            }
            if(start_operation)
            {
                start_operation=false;
                if((!this->IfGraphIsInCalculator(graph1_name))||(!this->IfGraphIsInCalculator(graph2_name)))
                {
                    throw(GraphIsNotExists());
                }
                Graph graph_1=this->graphs[graph1_name];
                Graph graph_2=this->graphs[graph2_name];
                Graph new_graph;
                switch (data[pos_of_operator])
                {
                case (PLUS):
                    new_graph=graph_1+graph_2;
                    break;
                case (INTERSECTION):
                    new_graph=graph_1^graph_2;
                    break;
                case (SUBTRACTION):
                    new_graph=graph_1-graph_2;
                    break;
                case (ASTERISK):
                    new_graph=graph_1*graph_2;
                    break;
                default:
                    throw(UnknownExceptoion());
                    break;
                }
                this->temperary_counter++;
                string new_graph_name=std::to_string(this->temperary_counter) + "G";
                this->graphs.insert({new_graph_name,new_graph});
                data=data.replace(pos_of_first_graph_begining,pos_of_second_graph_ending-pos_of_first_graph_begining+1,new_graph_name);
                there_is_operator=true;
                break;
            }



        }
    }
    
    
}
void Calculator::WorksOnCyrcleParenthesisInExpretion(string &data)
{
    bool there_is_parenthesis=true;
    while (there_is_parenthesis)
    {
        int opener_pos=-1;
        int closer_ps=-1;
        there_is_parenthesis=false;
        for(unsigned int i=0;i<data.size();i++)
        {

            if(data[i]==OPEN_CYRCLE_PARENTHESIS)
            {
                opener_pos=i;
            }
            if(data[i]==CLOSE_CYRCLE_PARENTHESIS)
            {
                closer_ps=i;
                string new_graph_name=data.substr(opener_pos+1,closer_ps-opener_pos-1);
                WorksOnNotInExpretion(new_graph_name);
                WorksOnOperatinInExpretion(new_graph_name);
                data=data.replace(opener_pos,closer_ps-opener_pos+1,new_graph_name);
                there_is_parenthesis=true;
                break;
            }
        }
        
        
    }
    
}
void Calculator::WorksOnFullExpretion(string &data)
{
    if(CheckOperatorExpretion(data)==false)
    {
        throw(InvalidExpretion());
    }
    WorksOnNewGraphInExpretion(data);
    DealingWithLoad(data);
    RemoveAllSpaces(data);
    WorksOnCyrcleParenthesisInExpretion(data);
    WorksOnNotInExpretion(data);
    WorksOnOperatinInExpretion(data);

}


void Calculator::GetEqualSign (string &data)
{
    vector<string> names_of_graphs=SplitToArry(data,EQUAL);
    if(!CheckGraphName(names_of_graphs[0]))
    {
        throw(IllegalGraphnName());
    }
    if(names_of_graphs[0]=="")
    {
        throw(InvalidExpretion());
    }
    WorksOnFullExpretion(names_of_graphs[1]);
    if((CheckGraphName(names_of_graphs[1])==true)&&(!this->IfGraphIsInCalculator(names_of_graphs[1])))
    {
        throw(GraphIsNotExists());
    }
    Graph new_graph=this->graphs[names_of_graphs[1]];
    if(this->graphs.count(names_of_graphs[0])==0)
    {   
        this->graphs.insert({names_of_graphs[0],new_graph});
    }
    else
    {
        this->graphs[names_of_graphs[0]]=new_graph;
    }
    

}
bool Calculator::GetInput(string&data,std::ostream &os)

{
    int count_equal=0;
    for(char letter:data)
    {
        if(letter==EQUAL)
        {
            count_equal++;
            if(count_equal>1)
            {
                throw(InvalidExpretion());
            }
        }
    }
    if(count_equal==1)
    {
        GetEqualSign(data);
        return(true);
    }
    else
    {
        return(GetCommand(data,os));
    }
    
}
void Calculator::Who(std::ostream &os) const
{
    auto iterator=this->graphs.begin();
    while (iterator!=this->graphs.end())
    {
        string name_of_graph= iterator->first;
        if(CheckGraphName(name_of_graph))
        {
            os<<iterator->first<<std::endl;
        }
        iterator++;
    }
}
void Calculator::PrintGraph(string &data,std::ostream &os)
{
    WorksOnFullExpretion(data);
    if(this->graphs.count(data)==0)
    {
        throw(GraphIsNotExists());
    }
    os<<this->graphs[data];
}
void Calculator::Reset()
{
    while (!this->graphs.empty())
    {
        this->graphs.erase(this->graphs.begin());
    }
}
void Calculator::DeleteGraph(string &data)
{
    if(!CheckGraphName(data))
    {
        throw(IllegalGraphnName());
    }
    if(this->graphs.count(data)==0)
    {
        throw(GraphIsNotExists());
    }
    this->graphs.erase(data);
    
}
bool Calculator::GetCommand(string&data,std::ostream &os)
{
    RemoveSpacesFromBeginAndEnd(data);
    string copy_of_data=data;
    ChangeMultiSpaceToOneSpace(data);
    if(data=="")
    {
        return true;
    }
    for(string valid_operation_name:SAVED_WORD)
    {
        if((valid_operation_name==PRINT_COMMAND)||(valid_operation_name==DELETE_COMMAND)||(valid_operation_name==SAVE_COMMAND))
        {   
            int pos_begin_of_command=copy_of_data.find(valid_operation_name);
            if((pos_begin_of_command!=-1)&&(pos_begin_of_command==0))
            {
                int save_command_lenght=valid_operation_name.size();
                int copy_of_data_size=copy_of_data.size();
                for(int i=save_command_lenght;i<copy_of_data_size;i++)
                {
                    if(copy_of_data[i]==WHITE_SPACE)
                    {
                        continue;
                    }
                    if((copy_of_data[i]!=OPEN_CYRCLE_PARENTHESIS)||(!CheckOpenerAndCloser(copy_of_data)))
                    {
                        throw(InvalidCommand());
                    }
                    pos_begin_of_command=i;
                    int pos_end_of_command=copy_of_data.find_last_of(CLOSE_CYRCLE_PARENTHESIS);
                    if((pos_begin_of_command==copy_of_data_size-1)||(pos_begin_of_command==pos_end_of_command))
                    {
                        throw(InvalidCommand());
                    }
                    string expretion=copy_of_data.substr(pos_begin_of_command+1,pos_end_of_command-pos_begin_of_command-1);
                    if(valid_operation_name==PRINT_COMMAND)
                    {
                        PrintGraph(expretion,os);
                        return(true);
                    }
                    if(valid_operation_name==DELETE_COMMAND)
                    {
                        DeleteGraph(expretion);
                        return(true);
                    }
                    if(valid_operation_name==SAVE_COMMAND)
                    {
                        SaveGraph(expretion);
                        return(true);
                    }

                }
            }
            
        }
        else if ((valid_operation_name==QUIT_COMMAND)||(valid_operation_name==RESET_COMMAND)||(valid_operation_name==WHO_COMMAND))
        {
            int pos_begin_of_command=data.find(valid_operation_name);
            if((pos_begin_of_command!=-1)&&(pos_begin_of_command==0))
            {
                if((data.size()!=valid_operation_name.size()))
                {
                    throw(InvalidCommand());
                }
                if(valid_operation_name==WHO_COMMAND)
                {
                    Who(os);
                    return(true);
                }
                if(valid_operation_name==RESET_COMMAND)
                {
                    Reset();
                    return(true);
                }
                if(valid_operation_name==QUIT_COMMAND)
                {
                    return(false);
                }
            }
            
        }

    }
    throw(InvalidCommand());
    return(true);
}

void Calculator::SaveGraph(string &data)
{
    int location_of_seperator=data.find_last_of(SPLITER);
    int data_lenght=data.size();
    if((location_of_seperator==-1)||(location_of_seperator==0)||(location_of_seperator==data_lenght-1))
    {
        throw(InvalidExpretion());
    }
    string name_of_file=data.substr(location_of_seperator+1,data_lenght-location_of_seperator);
    string expretion=data.substr(0,location_of_seperator);
    this->WorksOnFullExpretion(expretion);
    RemoveSpacesFromBeginAndEnd(name_of_file);
    if(this->graphs.count(expretion)==0)
    {
        throw(GraphIsNotExists());
    }
    this->graphs[expretion].SaveGraphToFile(name_of_file);

}






    










