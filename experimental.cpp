#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<conio.h>
#include<locale.h>
#include<algorithm>
#include<windows.h>
#include<vector>
    using namespace std;
#include"My_general.h"
#include"environment.h"
#include"InProcessor.h"
#include"OutProcessor.h"

int main(int argc, char *argv[])
try {
    cout<<"\nHiiii";
    string key=argv[1];
    
    string msg="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789~`!@#$^&*()_+=-{}|:<>?[];',./" ;
    My_namespace::RSA R(key);
    //string Output = RSA_En( VinC_En(msg,My_namespace::V_KeyG(key,max_buffer_size)) ,key);
    //string Output1 = VinC_Dy( RSA_Dy(Output,key) ,My_namespace::V_KeyG(key,max_buffer_size));
    
    string Output = RSA_Dy(RSA_En(msg,key),key);
    int j=0;
    for(int i=0; i<msg.length(); ++i)
        if(msg.at(i) != Output.at(i) )
            ++j;
    cout<<"\n\nasd:"<<j;
    cout<<"\n:"<< (char )R.Decrypt(R.Encrypt('b')); 
    
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