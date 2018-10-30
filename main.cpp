#include <iostream>
#include <vector>
#include <memory>


#include "namespaces.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "datalogProgram.h"
#include "interpreter.h"

int main(int argc, char* argv[])
{
    // vector<string> fileNames
    // {
    //     "1.txt",
    //     "2.txt",
    //     "3.txt",
    //     "4.txt",
    //     "5.txt",
    //     "6.txt",
    //     "7.txt",
    //     "8.txt",
    //     "9.txt",
    //     "10.txt"
    // };
    
    // for (auto i : fileNames) 
    // {
    //     cout << "test: " << i << endl;
    //     Scanner scanner(i);
    //     vector<Token*> tokens = scanner.lexicalAnalyzer();
        
    //     Parser parser = Parser(tokens);
    //     DatalogProgram* program = parser.datalogParsing();
        
    //     //cout << "calling program.toString()" << endl;
    //     cout << program->toString() << endl;
        
    //     delete program;
    // }

    Scanner scanner(argv[1]);
    std::vector<shared_ptr<Token>> tokens = scanner.lexicalAnalyzer();
    
    Parser parser = Parser(tokens);
    shared_ptr<DatalogProgram> program = parser.datalogParsing();
    
    Interpreter interpreter = Interpreter(program);
    interpreter.createDatabase();
    
    std::cout << interpreter.runQueries();
    
    //delete program;
    
    return 0;
}