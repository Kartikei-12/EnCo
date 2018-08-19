namespace My_namespace
{
    //Class to manage project parameter
    class Project_Parameter
    {
    public:
        bool isEncrypt=false, isDecrypt=false,
             isCompress=false, isDecompress=false,
             isFileFound=false, isKeyFound=false;
        size_t no_Argument;
        string workFile,key;

        void isValidCommand()
        {
            if(!isKeyFound                                                || //Key not found
               !isFileFound                                               || //Input file not found
               (isEncrypt && isDecrypt)                                   || //Both encryption and decryption
               (isEncrypt && isDecompress)                                || //Both encryption and decompression
               (isCompress && isDecompress)                               || //Both compression and decompression
               (isCompress && isDecrypt)                                  || //Both compression and decryption
               (!isEncrypt && !isDecrypt && !isCompress && !isDecompress) || //None operational parameter found
               false
            )
                throw error.encountered("Invalid Arguments.", __FILE__, __LINE__);
        }

        void parameter_parser(auto command[],size_t a)
        {
            string i;
            no_Argument = a;
            for(size_t j=1; j<a; ++j)
            {
                i = command[j];
                if(i == "-h" || i == "--help")
                    throw error.encountered("Help.");
                if(i == "-e" || i == "--encrypt")
                    isEncrypt = true;
                if(i == "-d" || i == "--decrypt")
                    isDecrypt = true;
                if(i == "-com" || i == "--compress")
                    isCompress = true;
                if(i == "-decom" || i == "--decompress")
                    isDecompress = true;
                if(i == "-f" || i == "--file")
                {
                    isFileFound = true;
                    workFile = command[j+1];
                }
                if(i == "-k" || i == "--key")
                {
                    isKeyFound = true;
                    key = command[j+1];
                }
            }
            isValidCommand();
        }
    };
}