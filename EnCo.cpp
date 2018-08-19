//Standard command template
//./EnCo.exe --file FILE_NAME --key KEY -e -com
#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<iomanip>
#include<algorithm>
#include<locale>
#include<vector>
#include<map>
#include<cctype>
#include<time.h>
    using namespace std;

//Project libraries and classes
#include"My_Libraries/error-handler.h"
#include"My_Libraries/utility-definations.h"
#include"My_Libraries/parameter.h"
#include"My_Libraries/crypto.h"
#include"My_Libraries/huffman.h"
#include"My_Libraries/project-class.h"

int main(int argc, char *argv[])
try
{
    //Start writing .log file
    My_namespace::keepLog("start-log");
    
    setlocale(LC_ALL, "en_Us.utf8");
    
    //Defineing project object and parsing argumenrs
    My_namespace::Programm P;
    P.WorkP.parameter_parser(argv, argc);
    
    //Calling method to perform task asked
    P.DoIt();
    
    //Ending log file
    My_namespace::keepLog("end-log", "", 0, 
                          My_namespace::FileSize(P.WorkP.workFile));
    return 0;
}
catch(My_namespace::my_Error &e) {
//For exception thrown by user-defined class,method and function
    My_namespace::error_clean_up(e.what());
}
catch(exception &e)
{
//For exception thrown by predefined library function, class and methods    
    cerr<<e.what()<<endl;
    My_namespace::error_clean_up("");
}
catch(...) {
//Exception not caught by both user-defined exceptions and exception library
    My_namespace::error_clean_up("Unknown Exception");
}