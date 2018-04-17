namespace My_namespace
{
    //Generates vector of prime numbers upto provided argument
    vector<size_t>  getSieveOfEratosthenes ( size_t max , size_t start )
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

        for (int i=start; i<sz; i+=2)
            if ( primes[i] )
                ret.push_back(i);

        return ret;
    }
    
    size_t LCM(size_t a,size_t b) {
        return ( (a*b) / __gcd(a,b) );  }

    class RSA
    {
        uint64_t prime_1,prime_2,totient,pu_K,modulas_n;
        long double pr_K;

        size_t mod_Exp(size_t b, size_t e)
        {
            int64_t remainder, x = 1,m = modulas_n;
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
            size_t failure = 4,p1=0,p2=0,preF=4;
            vector<int> SE = getSieveOfEratosthenes( (a*b+20),a+b );

            for(int j=0; j<(SE.size()-2) && failure>3; ++j)
                for(int k=1; k<(SE.size()-1) && failure>3; ++k)
                    if(j != k)
                    {    
                        prime_1 = *(SE.begin() + j);
                        prime_2 = *(SE.begin() + k);

                        modulas_n = prime_1 * prime_2;
                        totient = LCM((prime_1-1) , (prime_2-1)) ;
                        pu_K = 3;
                        while(__gcd(pu_K,totient)!=1)
                            ++pu_K;
                        float o = 2.0; 
                        do{
                            pr_K = (1.0 + o*totient)/(pu_K*1.0);
                            ++o;
                        }
                        while(floor(pr_K)!=ceil(pr_K));

                        failure = 0;
                        string msg="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789~`!@#$^&*()_+=-{}|:<>?[];',./" ;
                        for(int i=0; i<msg.length(); ++i)
                            if(msg.at(i) != (char )mod_Exp( mod_Exp(msg.at(i),pu_K) , pr_K) )
                                ++failure;
                        if(failure<preF)
                        {
                            p1 = prime_1;
                            p2 = prime_2;
                            preF = failure;
                        }
                    }
            if(preF<failure)
            {
                prime_1 = p1;
                prime_2 = p2;
                failure = preF;
            }
            //cout<<"\n"<<prime_1<<"\t"<<prime_2<<"\n"<<failure;
        }
        
    public:
        RSA(string KEY)
        {
            RSA_Generator( tolower(KEY.at(0)) , tolower(KEY.at(1)) );
        }
        char Encrypt(size_t msg)
        {
            return mod_Exp(msg,pu_K);
        }
        char Decrypt(size_t enMsg)
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