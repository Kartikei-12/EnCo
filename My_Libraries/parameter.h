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
                if(i == "-h")
                    throw Help;
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
                !isKeyFound                                                || //Key not found
                !isFileFound                                               || //Input file not found
                (isEncrypt && isDecrypt)                                   || //Both encryption and decryption
                (isEncrypt && isDecompress)                                || //Both encryption and decompression
                (isCompress && isDecompress)                               || ////Both compression and decompression
                (isCompress && isDecrypt)                                  || //Both compression and decryption
                (!isEncrypt && !isDecrypt && !isCompress && !isDecompress) || //None operational parameter found
                false
            )
                throw Invalid_Arguments;
        }
    };
}