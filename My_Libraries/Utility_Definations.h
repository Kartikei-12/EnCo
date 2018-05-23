#define max_buffer_size 160
enum My_ERROR{
        Cannot_Open_File,
        Invalid_Choice,
        Insufficient_Argument,
        Excess_Argument,
        Insufficient_Argument_Length,
        Invalid_Arguments,
        Output_File_Exist,
        Unknown_Error = 20  
    };
namespace My_namespace
{   
    //Returns size of file, name supplied
    uint64_t FileSize(string name)
    {
        fstream my(name.c_str(),ios::in);
        auto a = my.tellg();
        my.seekg(0,ios::end);
        auto b = my.tellg() - a;
        my.close();
        return b-a;
    }
    
    //Largest Common Multiple
    inline int32_t LCM(int32_t a,int32_t b) {
        return ( (a*b)/__gcd(a,b) );  }

    //Fast Modular Exponentiation
    inline int32_t mod_Exp(int32_t b, int32_t e,int32_t m)
    {
        int32_t remainder=0, x = 1;
        while (e!=0)
        {
            remainder = e%2;
            e /= 2;
            if(remainder == 1)
                x = (x*b) % m;
            b = (b * b) % m; // New base equal b^2 % m
        }
        return x;
    }

    //Sieve Of Eratosthenes
    inline vector<int> getSieveOfEratosthenes(int32_t max)
    {
        vector<bool> primes(max, true);
        int32_t sz = primes.size();

        for (int32_t i = 3; i < sz ; i+=2)
            if (primes[i]) 
                for(int j = i*i; j<sz; j+=i)
                    primes[j] = false;
        vector<int> ret;
        ret.reserve(primes.size());//Make sure there is space for "max" number of elements.
        //We do not want 2 in out list of prime numbers.
        //ret.push_back(2);
        for (int i=3; i<sz; i+=2)
            if ( primes[i] )
                ret.push_back(i);
        return ret;
    }
}