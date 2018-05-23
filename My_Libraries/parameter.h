namespace My_namespace
{
    //Class to manage project parameter
    class Project_Parameter
    {
    public:
        bool isEncrypt=false, isDecrypt=false, isCompress=false, isDecompress=false, isFileFound=false, isKeyFound=false;
        size_t no_Argument;
        uint64_t workFileSize;
        string workFile,key;
       
        Project_Parameter() {;}
        Project_Parameter(auto command[],size_t a)
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
                !isKeyFound                                            ||
                !isFileFound                                           ||
                (isEncrypt && isDecrypt)                               ||
                (isEncrypt && isDecompress)                            ||
                (isCompress && isDecompress)                           ||
                (isDecrypt && (isCompress || isDecompress))            ||
                (isDecrypt && isDecompress && isEncrypt && isCompress) || 
                (!isEncrypt && !isDecrypt)                             ||
                false
            )
                throw Invalid_Arguments;
        }
    };
}