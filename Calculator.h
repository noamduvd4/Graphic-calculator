#ifndef CALCULATION_H
#define CALCULATION_H
#include "Graph.h"
#include "fstream"
class Calculator
{
    private:
        std::map<std::string,Graph> graphs;
        int temperary_counter;
        void WorksOnNewGraphInExpretion(std::string &data );
        void WorksOnNotInExpretion(std::string &data);
        void WorksOnOperatinInExpretion(std::string &data);
        void WorksOnCyrcleParenthesisInExpretion(std::string &data);
        void WorksOnFullExpretion(std::string &data);
        void GetEqualSign(std::string &data);
        bool GetInput(std::string&data,std::ostream &os);
        bool GetCommand(std::string&data,std::ostream &os);
        void Who(std::ostream &os) const ;
        void SaveGraph(std::string &data);
        void PrintGraph(std::string &data,std::ostream &os);
        void Reset();
        void DeleteGraph(std::string &data);
        void CleanTemperaryParams();
        void DealingWithLoad(std::string &data);


    public:
        Calculator(std::map<std::string,Graph> given_graph=std::map<std::string,Graph>(),int x=0);
        ~Calculator()=default;
        void Manual_Running();
        void Auto_Running(std::ifstream &input, std::ofstream &output);
        bool IfGraphIsInCalculator(const std::string &Graph_name )const;

};
#endif