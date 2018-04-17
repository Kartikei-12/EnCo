#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<locale.h>
#include<algorithm>
#include<time.h>
#include<windows.h>
    using namespace std;
#include"My_general.h"

int main(int argc, char *argv[])
try {
    
    if(argc<4)
        throw Insufficient_Argument;
    if(argc>4)
        throw Excess_Argument;

    uint64_t start_s,stop_s;
    double timE=0.0;
    setlocale(LC_ALL,"en_Us.utf8");

    if(My_namespace::Converter(argv[3]))
    {
        ifstream Rec( "rec.txt",ios::in);
        Rec>>start_s;
        //Accessing time functionality for project efficiency log and analysis
        ofstream Hist( "History.txt" , ios::out |ios::app);
        time_t t = time(0);
        struct tm *now = localtime(&t);
        //Writing log file
        Hist<<now->tm_mday<<"/"
            <<(now->tm_mon + 1)<<"/"
            <<(now->tm_year + 1900)<<" "
            <<"C Ratio:"<<( (My_namespace::FileSize(argv[2]) * 1.0) / My_namespace::FileSize(argv[1]) ) * 100.0
            <<"\nMode:"<<argv[3];
        //Writing log file
        Hist<<" Time:";
        Rec.close();
        //cout<<"\n"<<argv[2]<<"\t"<<argv[1];
        //getch();
        stop_s=clock();
        timE = ((stop_s-start_s)/double(CLOCKS_PER_SEC)) + 0.5;
        Hist<<timE<<" sec "<<endl;
        Hist.close();
    }
    else
    {
        start_s = clock();
        ofstream Rec( "rec.txt",ios::out | ios::trunc );
        Rec<<clock();
        Rec.close();
    }
    system("cls");
    return 0;
}
catch( My_ERROR E )
{
    switch(E)
    {
        case Cannot_Open_File:
            cout<<"Cannot_Open_File";
            break;
        case Invalid_Choice:
            cout<<"Invalid_Choice";
            break;
        case Insufficient_Argument:
            cout<<"Insufficient Argument";
            break;
        case Excess_Argument:
            cout<<"Excess Argument";
            break;
        case Insufficient_Argument_Length:
            cout<<"Insufficient_Argument_Length";
            break;
        default:
            cerr<<"Unknown Exception.";
    }
}
catch(...)
{
    cerr<<"Unknown Exception.";
}