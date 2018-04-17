#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<cctype>
#include<algorithm>
#include<locale>
#include<windows.h>
#include<vector>
    using namespace std;
#include"My_general.h"
#include"environment.h"
#include"InProcessor.h"
#include"OutProcessor.h"

class Programm
{
	char temporary_Char;
    uint32_t coun,track;
    string nameF_In,nameF_Out,buffer,buffer1;
    fstream tF1,tF3;
public:
    int64_t O_size;
    Programm()
    {
        buffer = "";
        temporary_Char = 'A';
        coun = track = O_size = 0;
    }
    void Pro(string FileName,string KEY,bool WhatToDo)
    {
        nameF_In = FileName;
        //Opening required files
        tF1.open(nameF_In.c_str(),ios::in | ios::binary);
        
        //Checking success of opening file
        if(!tF1.is_open())
            throw Cannot_Open_File;
        
        //Checking number of lines
        O_size = My_namespace::FileSize(nameF_In.c_str());
        
        //Preparing file names
        nameF_In.erase( nameF_In.find(".") , ( nameF_In.length() - nameF_In.find(".") ) );

        if(!WhatToDo)
            nameF_Out = nameF_In + "_e.txt";
        else
            nameF_Out = nameF_In + "_d.txt";
        tF3.open(nameF_Out.c_str(),ios::out | ios::trunc | ios::binary);
//-------------------------------------Doing Actual Work----------------------------------------
        do
        {
            coun = max_buffer_size;
            if( (O_size - track) < max_buffer_size )
                coun = O_size - track;
        
            //Emptying buffer of residue data
            buffer.clear();
            buffer1.clear();
            //Reading file
            for(int i=0; i<coun; ++i)
            {
                tF1.get(temporary_Char);
                buffer += temporary_Char;
            }
            
            if(!WhatToDo)
                buffer1 = EnProcess(buffer,KEY);
            else
                buffer1 = DyProcess(buffer,KEY);
            //Writting file
            for(char i:buffer1)
            {
                temporary_Char = i;
                tF3.put(temporary_Char);
            }
            track += coun;
            if(track >= O_size) break;
        }while(!tF1.eof());
        
        tF1.close();
        tF3.close();

    }
}P;

int main(int argc, char *argv[])
try
{
    if(argc<4)
        throw Insufficient_Argument;
    if(argc>4)
        throw Excess_Argument;
    
    setlocale(LC_ALL,"en_Us.utf8");
    system("cls");

//Actual Program
    P.Pro(argv[1],argv[2],My_namespace::Converter(argv[3]));

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