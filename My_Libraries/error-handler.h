//Erraor and exception handaling class
namespace My_namespace
{
    class my_Error
    {
        int found_in_line;
        string message, found_in_file;
    public:
        my_Error(string s="")
        {
            found_in_line = 0;
            found_in_file = "";
            message = s;
        }

        void at_line(int a) {
            found_in_line = a;
        }

        void in_file(string a) {
            found_in_file = a;
        }
        string what() 
        {
            string s = message+" File: "+
                       found_in_file+" Line: "+
                       to_string(found_in_line);
            return s;
        }

        my_Error encountered(string s="", string f="", int a=0)
        {
            message = s;
            found_in_file = f;
            found_in_line = a;
            return *this;
        }
    } error; 
}