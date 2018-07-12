namespace My_namespace
{
    //Clas managing RSA cryptografhy
    class RSA
    {
        int32_t prime_1, prime_2, totient, pu_K, modulas_n, pr_K;
        //Keys generator
        void Parameter_Generator()
        {            
            modulas_n = prime_1 * prime_2;
            totient = LCM((prime_1-1) , (prime_2-1)) ;
            pu_K = 2;
            while(__gcd(pu_K,totient)!=1)
                ++pu_K;
            float o=2.0, temp=0;
            do{
                temp = (1.0 + o*totient*1.0)/(pu_K*1.0);
                ++o;
            }
            while(floor(temp)!=ceil(temp));
            pr_K = (int)temp;
        }

        //Generates valid keys
        void RSA_Generator(int a,int b)
        {
            bool satisfied = false;
            size_t failure = 10;//Random integer greater than 0
            vector<int > SE = getSieveOfEratosthenes(2*(a+b));
            for(int j=0; (j<(SE.size()-2)) && !satisfied; ++j)
                for(int k=j+2; (k<(SE.size()-1)) && !satisfied; ++k)
                {
                    failure = 0;    
                    prime_1 = *(SE.begin() + j);
                    prime_2 = *(SE.begin() + k);
                    Parameter_Generator();
                    string msg1="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789~`!@#$^&*()_+=-{}|:<>?[];',./" ;
                    for(char i:msg1)
                        if(i != mod_Exp( mod_Exp(i,pu_K, modulas_n) , pr_K, modulas_n) )
                            ++failure;
                    if(failure==0 && modulas_n<256 && modulas_n>100)
                        satisfied = true;
                }
        }
        
    public:
        RSA() {
            ;
        }
        RSA(string KEY) {
            RSA_Generator( KEY.at(0) , KEY.at(1) );
        }
        char charEncrypt(size_t data) {
            return mod_Exp(data,pu_K, modulas_n);
        }
        char charDecrypt(size_t enMsge) {
            return mod_Exp(enMsge,pr_K, modulas_n);
        }
        string stringEncrypt(string msg)
        {
            string encryptedMsg = "";
            for(char i:msg)
                encryptedMsg += mod_Exp(i,pu_K, modulas_n);
            return encryptedMsg;
        }
        string stringDecrypt(string enMsg)
        {
            string decryptedMsg = "";
            for(char i:enMsg)
                decryptedMsg += mod_Exp(i,pr_K, modulas_n);
            return decryptedMsg;
        }
    };

    //Class to manage Vigenere Cypher
    class Vigenere_Cypher
    {
        string Key;
    public:
        Vigenere_Cypher() {
            ;
        }
        //Setting strickly Capital alfhabatic key
        Vigenere_Cypher(string a) 
        {
            for(int i=0; i<a.length(); ++i)
                if(isalpha(a.at(i)))
                    Key += toupper(a.at(i));
        }
        string Encrypt(string msg)
        {
            size_t kLength = Key.length();
            string encryptedMsg;
            for(int i=0; i<msg.length(); ++i)
                if(isalpha(msg.at(i)))
                    if(isupper(msg.at(i)))
                        encryptedMsg += (char )(( msg.at(i) + Key.at(i%kLength) ) % 26) + 'A' ;
                    else
                        encryptedMsg += (char )(( msg.at(i) + Key.at(i%kLength) + 'A' - 'a' ) % 26) + 'a';
                else
                    encryptedMsg += msg.at(i);
            return encryptedMsg;
        }
        string Decrypt(string encryptedMsg)
        {
            size_t kLength = Key.length();
            string decryptedMsg;
            for(int i = 0; i<encryptedMsg.length(); ++i)
                if(isalpha(encryptedMsg.at(i)))
                    if(isupper(encryptedMsg.at(i)))
                        decryptedMsg += (char )(( encryptedMsg.at(i) - Key.at(i%kLength) + 'a' - 'A' - 6 ) % 26) + 'A';
                    else
                        decryptedMsg += (char )(( encryptedMsg.at(i) - Key.at(i%kLength) - 6 ) % 26) + 'a';
                else
                    decryptedMsg += encryptedMsg.at(i);
            return decryptedMsg;
        }
    };

    //Method to perform encryption and decryption
    void Cryptografhy_function(string& inputName,string& outputName,string& key, bool WhatToDo)
    {
        //Defining required variables and objects
        char temporary_Char='.';
        uint64_t fileSize = FileSize(inputName),coun=0,track=0;
        string buffer, buffer1;
        fstream iFile,oFile;
        RSA R(key);
        Vigenere_Cypher V(key);
        
        //Opening required files
        iFile.open(inputName.c_str(), ios::in | ios::binary);
        if(!iFile.is_open())
            throw Cannot_Open_File;
        if(ifstream(outputName.c_str()))
            throw Output_File_Exist;
        oFile.open(outputName.c_str(), ios::out | ios::binary);
        

        do
        {
            //Emptying buffer
            buffer.clear();
            buffer1.clear();
            coun = max_buffer_size;
            if( (fileSize - track) < max_buffer_size )
                coun = fileSize - track;
            //Reading file
            for(int i=0; i<coun; ++i)
            {
                iFile.get(temporary_Char);
                buffer += temporary_Char;
            }
            //Calling cryptografhy functions
            if(!WhatToDo)
                buffer1 = R.stringEncrypt(V.Encrypt(buffer));
            else
                buffer1 = V.Decrypt(R.stringDecrypt(buffer));
            //Writting file
            for(char i:buffer1)
            {
                temporary_Char = i;
                oFile.put(temporary_Char);
            }
            track += coun;
        }while(track != fileSize && !iFile.eof());
        
        //Closing file
        iFile.close();
        oFile.close();
    }
}