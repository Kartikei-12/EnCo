
#define max_buffer_size 320

namespace My_namespace
{
    //Method to write .log file
    inline void keepLog(const string message, 
                        const string f="", const size_t l=0,
                        const uint64_t fsize=0) 
    {
        static ofstream Log("EnCo.log", ios::out |ios::app);
        static uint64_t start_s = 0, stop_s=0;
        if(message == "start-log")
        {
            start_s = clock();
            time_t t = time(0);
            struct tm *now = localtime(&t);
            Log<<"-------------------------------------------------"<<endl
               <<asctime(now)<<endl;
        }
        else if(message == "end-log")
        {
            //Ending time counter and calculating efficiency factors 
            stop_s = clock();
            auto duration = ((stop_s-start_s)/double(CLOCKS_PER_SEC)) + 0.5;
            auto speed = (double )fsize/( 1024.0 * duration);
            Log<<"Run time: "<<duration<<" sec\n"
               <<"Speed: "<<speed<<" KB/s\n"        
               <<"-------------------------------------------------\n"<<endl;
            Log.close();
        }
        else
            if(f != "" && l!=0)
                Log<<message<<" file: "<<f<<" line: "<<l<<endl;
            else
                Log<<message<<endl;
        cout<<message<<" file: "<<f<<" line: "<<l<<endl;
    }

    //Returns size of file when file name supplied
    inline uint64_t FileSize(string name)
    {
        fstream my(name.c_str(),ios::in);
        auto a = my.tellg();
        my.seekg(0,ios::end);
        auto b = my.tellg() - a;
        my.close();
        return (b-a);
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
        //Reserving space for "max" number of elements.
        ret.reserve(primes.size());
        
        //We do not want 2 in out list of prime numbers.
        //ret.push_back(2);
        for(int i=3; i<sz; i+=2)
            if(primes[i])
                ret.push_back(i);
        return ret;
    }

    //Valid flags
    void provideValidFlags()
    {
        cerr<<"Usage:"
            <<"\n./EnCo.exe [-h] [-file FILE_NAME] [-key KEY] [-e] [-c] [-d] [-com] [-decom]"
            <<"\nFlag details"
            <<"\n\tCompulsary flags:"
            <<"\n\t\t-f, --file : Need to be followed by input file name"
            <<"\n\t\t-k, --key  : Need to be followed by string of chracters containning atleast one alfhabet."
            <<"\n\t\t-h, --help : To view all usage commands."
            <<"\n\tOther flags"
            <<"\n\t\t-e, --encrypt        : For encryption"
            <<"\n\t\t-d, --decrypt        : For decryption"
            <<"\n\t\t-com, --compress     : For compression"
            <<"\n\t\t-decom, --decompress : For decompression"
            <<"\n\tInvalid flag combination:-"
            <<"\n\t\t-e -d"
            <<"\n\t\t-com -decom"
            <<"\n\t\t-e -decom"
            <<"\n\t\t-d -com"
            <<"\n\t\t-e -d -com -decom"
            <<endl;
    }

    //Method to clean up after encountering an error or exception
    void error_clean_up(string s)
    {
        provideValidFlags();
        keepLog(s);
        keepLog("end-log");
    }
}