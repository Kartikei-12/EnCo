namespace My_namespace
{
    class RSA
    {
        int32_t prime_1, prime_2, totient, pu_K, modulas_n, pr_K;
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
        RSA() {;}
        RSA(string KEY) {
            RSA_Generator( KEY.at(0) , KEY.at(1) );
        }
        auto charEncrypt(auto data) {
            return mod_Exp(data,pu_K, modulas_n);
        }
        auto charDecrypt(auto enMsge) {
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

    class Vigenere_Cypher
    {
        string Key;
    public:
        Vigenere_Cypher() {;}
        Vigenere_Cypher(string a) 
        {
            Key = a;
            a.clear();
            for(char i:Key)
                if(isalpha(i))
                    if(isupper(i))
                        a += i;
                    else
                        a += toupper(i);
            Key.clear();
            Key = a;
        }
        string Encrypt(string msg)
        {
            size_t mLength = msg.length();
            string encryptedMsg="";
            for(uint32_t i=0; i<mLength; ++i)
                if(isalpha(msg.at(i)))
                    if(isupper(msg.at(i)))
                        encryptedMsg += (char )(( msg.at(i) + Key.at(i%mLength) ) % 26) + 'A' ;
                    else
                        encryptedMsg += (char )(( msg.at(i) + Key.at(i%mLength) + 'A' - 'a' ) % 26) + 'a';
                else
                    encryptedMsg += msg.at(i);
            return encryptedMsg;
        }
        string Decrypt(string encryptedMsg)
        {
            size_t mLength = encryptedMsg.length();
            string decryptedMsg="";
            for(uint32_t i = 0; i<mLength; ++i)
                if(isalpha(encryptedMsg.at(i)))
                    if(isupper(encryptedMsg.at(i)))
                        decryptedMsg += (char )(( encryptedMsg.at(i) - Key.at(i%mLength) + 'a' - 'A' - 6 ) % 26) + 'A';
                    else
                        decryptedMsg += (char )(( encryptedMsg.at(i) - Key.at(i%mLength) - 6 ) % 26) + 'a';
                else
                    decryptedMsg += encryptedMsg.at(i);
            return decryptedMsg;
        }
    };
}