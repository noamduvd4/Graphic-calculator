#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>
    class Exception : public std::exception {
        private:

        protected:
            const std::string  name_error;
            Exception(std::string error):name_error( "Error: "+ error){}
        public:
            const char* what() const noexcept override{
                return(name_error.c_str());
            } 
    };
            
    class IllegalGraphArgument: public Exception
    {
        public:
            IllegalGraphArgument():Exception("Illegal Graph Argument"){}

    };
    class IllegalGraphnName: public Exception
    {
        public:
            IllegalGraphnName():Exception("Illegal Graphn Name"){}
    };
    class GraphIsNotExists: public Exception
    {
        public:
            GraphIsNotExists():Exception("Graph Is Not Exists"){}  
    };
    class InvalidExpretion: public Exception
    {
        public:
            InvalidExpretion():Exception("Invalid Expretion"){}  
    };
    class InvalidCommand: public Exception
    {
        public:
            InvalidCommand():Exception("Invalid Command"){}  
    };
    class UnknownExceptoion: public Exception
    {
        public:
            UnknownExceptoion():Exception("Unknown Exceptoion"){}  
    };
    class InvalidVerticisName: public Exception
    {
        public:
            InvalidVerticisName():Exception("Invalid Verticis Name"){}  
    };
    class VerticisAllreadyExist: public Exception
    {
        public:
            VerticisAllreadyExist():Exception("Verticis Allready Exists In Graph"){}  
    };
    class EdgeisAllreadyExist: public Exception
    {
        public:
            EdgeisAllreadyExist():Exception("Edge Allready Exists In Graph"){}  
    };
    class VerticisisNotExists: public Exception
    {
        public:
            VerticisisNotExists():Exception("Verticis is not Exists In Graph"){}  
    };
    class CannotOpenFile: public Exception
    {
        public:
            CannotOpenFile():Exception("Cannot Open File"){}  
    };
    class FileFormatUnrecocnize: public Exception
    {
        public:
            FileFormatUnrecocnize():Exception("File Format Unrecognize"){}  
    };
    class InvlaidEdgeName: public Exception
    {
        public:
        InvlaidEdgeName():Exception("Invalid Edge Name"){} 
    };


    
    
#endif //EXCEPTION_H
