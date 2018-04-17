#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<conio.h>
#include<list>
#include<locale.h>
#include<algorithm>
#include<windows.h>
#include<math.h>
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
    /*
    string enMsg="";
    
    for(int i=0; i<msg.length(); ++i)
        enMsg += (char )R.Encrypt(msg.at(i));

    string deMsg="";
    for(int i=0; i<enMsg.length(); ++i)
        deMsg += (char )R.Decrypt(enMsg.at(i));
    size_t ghj=0;
    for(int i=0; i<msg.length(); ++i)
        if(msg.at(i) != deMsg.at(i))
            //cerr<<"\n"<<msg.at(i)<<" "<<(int )msg.at(i)<<" "<<deMsg.at(i)<<" KK";
            ghj++;
    cout<<"\n"<<ghj;*/
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