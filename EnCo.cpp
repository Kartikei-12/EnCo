//Standard command template
//./EnCo.exe --file FILE_NAME --key KEY -e -c
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
#include<windows.h>
#include<time.h>
    using namespace std;
//Project lbraries
#include"My_Libraries/Utility_Definations.h"
#include"My_Libraries/parameter.h"
#include"My_Libraries/Crypto.h"
#include"My_Libraries/huffman.h"
class Programm
{
    string inputName,outputName,tempName,fileExtension,Out_nameExtended;
public:
    My_namespace::Project_Parameter WorkP;
    void DoIt()//Function doing main work
    {
        //Preparing I/O file names and such
        fileExtension = WorkP.workFile.substr(WorkP.workFile.rfind('.'));
        tempName = "temp" + fileExtension;
        inputName.assign( WorkP.workFile.begin(), WorkP.workFile.begin()+WorkP.workFile.rfind('.') );
        
        //Preparing extended file name for Output file
        Out_nameExtended.clear();
        if(WorkP.isEncrypt)
            Out_nameExtended += "_e";
        else
            Out_nameExtended += "_d";
        if(WorkP.isCompress)
            Out_nameExtended += "_com";
        if(WorkP.isDecompress)
            Out_nameExtended += "_decom";
        outputName = inputName + Out_nameExtended + fileExtension;
        
        //Resetting original Input file name
        inputName = WorkP.workFile;
        
        //Doing work
        //When Only file encryption is asked
        if(WorkP.isEncrypt && !WorkP.isCompress)
            My_namespace::Cryptografhy_function(inputName,outputName,WorkP.key,!WorkP.isEncrypt);
        //When only file compression is asked
        else if(!WorkP.isEncrypt && WorkP.isCompress)
            My_namespace::Huffman_Compression::encoder(inputName,outputName);
        //When both file encryption and compression is asked
        else if(WorkP.isEncrypt && WorkP.isCompress)
        {
            My_namespace::Cryptografhy_function(inputName,tempName,WorkP.key,!WorkP.isEncrypt);
            My_namespace::Huffman_Compression::encoder(tempName,outputName);
        }
        //When only file decryption is required
        else if(WorkP.isDecrypt && !WorkP.isDecompress)
            My_namespace::Cryptografhy_function(inputName,outputName,WorkP.key,WorkP.isDecrypt);
        //When only file decompresin is asked
        else if(!WorkP.isDecrypt && WorkP.isDecompress)
            My_namespace::Huffman_Compression::decoder(inputName,outputName);
        //When both file decompression and decryption is required
        else if(WorkP.isDecrypt && WorkP.isDecompress)
        {
            My_namespace::Huffman_Compression::decoder(inputName,tempName);
            My_namespace::Cryptografhy_function(tempName,outputName,WorkP.key,WorkP.isDecrypt);
        }
        //Unknown case
        else
            throw Cannot_Process_Request;
        //Removing temporary file if any
        remove(tempName.c_str());
    }
};

int main(int argc, char *argv[])
try
{
    uint64_t start_s = clock(), stop_s=0;
    time_t t = time(0);
    struct tm *now = localtime(&t);

    setlocale(LC_ALL, "en_Us.utf8");
    string right_now = asctime(now);
    My_namespace::keepLog("-------------------------------------------------\n"+
                          right_now);
    
    //Defineing project object and checking validity of command
    Programm P;
    P.WorkP.setParameter(argv,argc);
    P.WorkP.isValidCommand();
    
    //Calling method to perform task asked
    P.DoIt();
    
    //Ending time counter and calculating efficiency factors 
    stop_s = clock();
    auto duration = ((stop_s-start_s)/double(CLOCKS_PER_SEC)) + 0.5;
    auto speed = (double )My_namespace::FileSize(P.WorkP.workFile)/( 1024.0 * duration);
    My_namespace::keepLog("Run time: "+to_string(duration)+
                          " sec Speed(KB/s):"+to_string(speed)+
                          "\n-------------------------------------------------\n\n\n");
    My_namespace::keepLog("Clean Up");
    return 0;
}
catch(My_ERROR E)
{//For exception thrown by user-defined class,method and function
    switch(E)
    {
        case Cannot_Open_File:
            cerr<<"Cannot_Open_File";
            break;
        case Invalid_Choice:
            cerr<<"Invalid_Choice";
            break;
        case Insufficient_Argument:
            cerr<<"Insufficient Argument";
            break;
        case Excess_Argument:
            cerr<<"Excess Argument";
            break;
        case Insufficient_Argument_Length:
            cerr<<"Insufficient_Argument_Length";
            break;
        case Invalid_Arguments:
            cerr<<"Invalid_Aguments";
            break;
        case Output_File_Exist:
            cerr<<"Output_File_Exist";
            break;
        case Cannot_Process_Request:
            cerr<<"Cannot process request due to unknown reason.";
            break;
        default:
            cerr<<"Unknown Exception by me.";
    }
    cerr<<"\n";
    My_namespace::provideValidFlags();
    cerr<<"\n";
}
catch(exception& e)
{//For exception thrown by predefined library function, class and methods
    cerr<<endl<<e.what();
    My_namespace::provideValidFlags();
}
catch(...)
{//Exception not caught by both user-defined exceptions and exception library
    cerr<<"Unknown Exception.\n";
    My_namespace::provideValidFlags();
}