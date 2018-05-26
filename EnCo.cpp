//Standard command template
//./EnCo.exe -file FILE_NAME -key KEY -e -c
#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<iomanip>
#include<algorithm>
#include<locale>
#include<vector>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
    using namespace std;
#include"My_Libraries/Utility_Definations.h"
#include"My_Libraries/parameter.h"
#include"My_Libraries/Crypto.h"
#include"My_Libraries/huffman.h"
class Programm
{
    string inputName,outputName,tempName,fileExtension,Out_nameExtended;
public:
    My_namespace::Project_Parameter WorkP;
    void DoIt()
    {
        //Preparing I/O file names and such
        fileExtension = WorkP.workFile.substr(WorkP.workFile.rfind('.'));
        inputName.assign( WorkP.workFile.begin(), WorkP.workFile.begin()+WorkP.workFile.rfind('.') );
        
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
        inputName = WorkP.workFile;
        tempName = "temp" + fileExtension;
        //I/O files names done//Files opened
        //Doing work
        if(WorkP.isEncrypt && !WorkP.isCompress)
            My_namespace::Cryptografhy_function(inputName,outputName,WorkP.key,!WorkP.isEncrypt);
        else if(!WorkP.isEncrypt && WorkP.isCompress)
            My_namespace::Huffman_Compression::encoder(inputName,outputName);
        else if(WorkP.isEncrypt && WorkP.isCompress)
        {
            My_namespace::Cryptografhy_function(inputName,tempName,WorkP.key,!WorkP.isEncrypt);
            My_namespace::Huffman_Compression::encoder(tempName,outputName);
        }
        else if(WorkP.isDecrypt && !WorkP.isDecompress)
            My_namespace::Cryptografhy_function(inputName,outputName,WorkP.key,WorkP.isDecrypt);
        else if(!WorkP.isDecrypt && WorkP.isDecompress)
            My_namespace::Huffman_Compression::decoder(inputName,outputName);
        else 
            if(WorkP.isDecrypt && WorkP.isDecompress)
        {
            My_namespace::Huffman_Compression::decoder(inputName,tempName);
            My_namespace::Cryptografhy_function(tempName,outputName,WorkP.key,WorkP.isDecrypt);
        }
        remove(tempName.c_str());
    }
};

int main(int argc, char *argv[])
try
{
    uint64_t start_s = clock(), stop_s=0;
    time_t t = time(0);
    struct tm *now = localtime(&t);
    ofstream Hist( "History.txt" , ios::out |ios::app);
    Programm P;
    setlocale(LC_ALL,"en_Us.utf8");
    P.WorkP.setParameter(argv,argc);
    P.WorkP.isValidCommand();

    P.DoIt();
    
    Hist<<now->tm_mday<<"/"
        <<(now->tm_mon + 1)<<"/"
        <<(now->tm_year + 1900)<<" "
        <<"Time: "
        <<"";
    stop_s = clock();
    Hist<<(((stop_s-start_s)/double(CLOCKS_PER_SEC)) + 1)
        <<" sec Speed:"
        <<(double )(My_namespace::FileSize(P.WorkP.workFile)/( 1024 * (((stop_s-start_s)/double(CLOCKS_PER_SEC)) + 1)))<<"\n";
    Hist.close();
    return 0;
}
catch(My_ERROR E)
{
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
        default:
            cerr<<"Unknown Exception by me.";
    }
    cerr<<"\nTry:\n./EnCo.exe -file FILE_NAME -key KEY -e -c";
}
catch(exception& e)
{
    cerr<<endl<<e.what();
}
catch(...)
{
    cerr<<"Unknown Exception.\n";
    cerr<<"\nTry:\n./EnCo.exe -file FILE_NAME -key KEY -e -com";
}