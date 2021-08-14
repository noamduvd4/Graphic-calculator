#include <iostream>
#include "Utilitis.h"
#include "Exception.h"
#include "Calculator.h"
using namespace std;
int main(int argc, char const *argv[])
{ 
    if(argc==1)
    {
        
        Calculator new_calculator;
        new_calculator.Manual_Running();

    }
    else if(argc==3)
    {
        Calculator new_calculator;
        ifstream input_file (argv[1]);
        if(!input_file)
        {
            cerr<<"Error: Cannot Open File "<< argv[1]<<std::endl;
            return(0);
        }
        ofstream out_file (argv[2]);
        if(!out_file)
        {
            cerr<<"Error: Cannot Open File "  <<argv[2]<<std::endl;
            return(0);

        }
        if((out_file)&&(input_file))
        {
            Calculator calculator;
            calculator.Auto_Running(input_file,out_file);

        }

    }
    else
    {
        cerr<<"Error: Incurect Number Of File";
    }
    
    return 0;
}


