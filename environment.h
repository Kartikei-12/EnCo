namespace My_namespace
{
    size_t LCM(size_t a,size_t b) {
        return ( (a*b) / __gcd(a,b) );  }
        
    //Generates vector of prime numbers upto provided argument

    vector<int>  getSieveOfEratosthenes ( int max )
    {
        vector<bool> primes(max, true);
        int sz = primes.size();

        for ( int i = 3; i < sz ; i+=2 )
            if ( primes[i] ) 
                for ( int j = i * i; j < sz; j+=i)
                    primes[j] = false;

        vector<int> ret;
        ret.reserve(primes.size());
        //ret.push_back(2);
        
        for (int i=17; i<sz; i+=2)
            if ( primes[i] )
                ret.push_back(i);

        return ret;
    }

    class RSA
    {
        uint32_t prime_1, prime_2, totient, pu_K, modulas_n, pr_K;

        void Parameter_Generator()
        {            
            modulas_n = prime_1 * prime_2;
            totient = LCM((prime_1-1) , (prime_2-1)) ;
            pu_K = 3;
            while(__gcd(pu_K,totient)!=1)
                ++pu_K;
            float o = 2.0,temp=0;
            do{
                temp = (1.0 + o*totient)/(pu_K*1.0);
                ++o;
            }
            while(floor(temp)!=ceil(temp));
            pr_K = (size_t)temp;
        }

        int mod_Exp(int b, int e)
        {
            int remainder, x = 1,m = modulas_n;
            while (e != 0)
            {
                remainder = e % 2;
                e /= 2;
                if(remainder == 1)
                    x = (x * b) % m;
                b = (b * b) % m; // New base equal b^2 % m
            }
            return x;
        }

        void RSA_Generator(int a,int b)
        {
            bool satisfied = false;
            size_t failure = 0;
            vector<int > SE = getSieveOfEratosthenes(a+b);
            for(int j=0; (j<(SE.size()-2)) && !satisfied; ++j)
                for(int k=j+1; (k<(SE.size()-1)) && !satisfied; ++k)
                {    
                    prime_1 = *(SE.begin() + j);
                    prime_2 = *(SE.begin() + k);
                    Parameter_Generator();
                    size_t failure = 0;
                    string msg="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789~`!@#$^&*()_+=-{}|:<>?[];',./" ;
                    for(char i:msg)
                        if(i != (char)mod_Exp( mod_Exp(i,pu_K) , pr_K) )
                            ++failure;
                    if(failure==0 && modulas_n<1000)
                        satisfied = true;
                }
        }
        
    public:
        RSA(string KEY)
        {
            RSA_Generator( tolower(KEY.at(0)) , tolower(KEY.at(1)) );
        }
        auto Encrypt(int msg)
        {
            return mod_Exp(msg,pu_K);
        }
        auto Decrypt(int enMsg)
        {
            return mod_Exp(enMsg,pr_K);
        }
    };

    string V_KeyG(string key,size_t len)
    {
        string newKey ="",temp = "";
        for(char i:key)
            if(isalpha(i))
                temp += toupper(i);
        size_t keyLen = temp.length();
        for(int i=0; i<((len/keyLen)+1); ++i)
            newKey += temp;
        return newKey;
    }
}
    
/*

            
            //char ch='G';
            //cout<<"\n"<<":"<<ch<<"\t"<<(char )mod_Exp( mod_Exp(ch,pu_K) , pr_K);
            //cout<<"\nHere:"<<prime_1<<"\t"<<prime_2<<"\nFailure"<<failure<<"\n:A"<<modulas_n;
            cerr<<"\n-------------";




            int failure = 0;
            string msg="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789~`!@#$^&*()_+=-{}|:<>?[];',./" ;
            for(char i:msg)
                if(i != (char )mod_Exp( mod_Exp(i,pu_K) , pr_K) )
                    ++failure;
            cout<<"\nFailure:"<<failure;
            //cout<<"\nSize:"<<Prime_List.size();
            //cout<<"\n"<<MM_i->first<<"\t"<<MM_i->second<<":";



















*/