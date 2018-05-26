namespace My_namespace
{
    //Class to manage project parameter
    class Project_Parameter
    {
    public:
        bool isEncrypt=false, isDecrypt=false, isCompress=false, isDecompress=false, isFileFound=false, isKeyFound=false;
        size_t no_Argument;
        string workFile,key;
       
        void setParameter(auto command[],size_t a)
        {
            string i;
            no_Argument = a;
            for(size_t j=1; j<a; ++j)
            {
                i = command[j];
                if(i == "-e")
                    isEncrypt = true;
                if(i == "-d")
                    isDecrypt = true;
                if(i == "-com")
                    isCompress = true;
                if(i == "-decom")
                    isDecompress = true;
                if(i == "-file")
                {
                    isFileFound = true;
                    workFile = command[j+1];
                }
                if(i == "-key")
                {
                    isKeyFound = true;
                    key = command[j+1];
                }
            }
        }

        void isValidCommand()
        {
            if(
                !isKeyFound                                                ||
                !isFileFound                                               ||
                (isEncrypt && isDecrypt)                                   ||
                (isEncrypt && isDecompress)                                ||
                (isCompress && isDecompress)                               ||
                (isCompress && isDecrypt)                                  ||
                (!isEncrypt && !isDecrypt && !isCompress && !isDecompress) ||
                false
            )
            {
                cerr<<"\n\tValid Flags:"
                    <<"\n";
                throw Invalid_Arguments;
            }
        }
    };
}