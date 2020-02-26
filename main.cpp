#include <iostream>
#include <fstream>
#include <string>

#include "parse.h"
#include "lex.h"

using namespace std;
int main(int argc, char* argv[])
{
    istream *in = &cin;
    ifstream infile;
    int linenum = 0;
    if(argc > 2)
    {
        cout << "TOO MANY FILENAMES" << endl;
        return 1;
    }
    if(argc == 2)
    {
        infile.open(argv[1]);
        if(infile.is_open() == false)
        {
            cout << "COULD NOT OPEN " << argv[1] << endl;
            return 1;
        }
        in = &infile;
    }
    if (in == NULL) return linenum;
    ParseTree *prog = Prog(*in, linenum);
    if( prog == 0 )return 0;    
    map<string,bool> declaredId;  
    map<string,Val> symbolTable;
    prog->CheckLetBeforeUse(declaredId);
    try {
        prog->Eval(symbolTable);
    }
    catch (string& e) {
        cout << "RUNTIME ERROR" << e << endl;
    }
    return 0;
}    