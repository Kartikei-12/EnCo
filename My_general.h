//Vigenere Cypher
#define max_buffer_size 160
enum My_ERROR{
        Cannot_Open_File,
        Invalid_Choice,
        Insufficient_Argument,
        Excess_Argument,
        Insufficient_Argument_Length,
        Unknown_Error = 10  
    };
namespace My_namespace{
    uint64_t FileSize(string name)
    {
        fstream my(name.c_str(),ios::in);
        auto a = my.tellg();
        my.seekg(0,ios::end);
        auto b = my.tellg() - a;
        my.close();
        return b-a;
    }
    bool Converter(string a)
    {
        if(a.at(0) == '0')
            return false;
        else
            return true;
    }
}