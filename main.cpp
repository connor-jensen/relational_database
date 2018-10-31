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
    vector<string> inputFileNames
    {
        "in1.txt",
        "in2.txt",
        "in3.txt"
        // "in4.txt",
        // "in5.txt",
        // "in6.txt",
        // "in7.txt",
        // "in8.txt",
        // "in9.txt",
        // "in10.txt"
    };

    vector<string> expectedOutputFileNames
    {
        "out1.txt",
        "out2.txt",
        "out3.txt"
        // "out4.txt",
        // "out1.txt",
        // "out5.txt",
        // "out6.txt",
        // "out7.txt",
        // "out8.txt",
        // "out9.txt",
        // "out10.txt"
    };

    for(int i = 0; i < inputFileNames.size(); i++) {
        Scanner scanner("tests/" + inputFileNames[i]);
        vector<shared_ptr<Token>> tokens = scanner.lexicalAnalyzer();

        Parser parser = Parser(tokens);
        shared_ptr<DatalogProgram> program = parser.datalogParsing();

        Interpreter interpreter = Interpreter(program);
        interpreter.createDatabase();

        string output = interpreter.runQueries();

        ifstream expectedOutputFile("expectedOutputs/" + expectedOutputFileNames[i]);

        stringstream ss;
        ss << expectedOutputFile.rdbuf();
        string expectedOutput = ss.str();

        cout << "Test " << i << ": ";
        if (expectedOutput == output) {
            cout << "PASS" << endl;
        }
        else cout << "FAIL" << endl;

        cout << "Expected output:" << endl;
        cout << expectedOutput << endl << endl;

        cout << "Actual output:" << endl;
        cout << output;
    }

    // Scanner scanner(argv[1]);
    // std::vector<shared_ptr<Token>> tokens = scanner.lexicalAnalyzer();
    
    // Parser parser = Parser(tokens);
    // shared_ptr<DatalogProgram> program = parser.datalogParsing();
    
    // Interpreter interpreter = Interpreter(program);
    // interpreter.createDatabase();
    
    // std::cout << interpreter.runQueries();
    
    //delete program;
    
    return 0;
}