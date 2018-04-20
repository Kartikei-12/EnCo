string VinC_En(string msg,string newKey)
{
    string encryptedMsg="";
    for(int i = 0; i < msg.length(); ++i)
        if(isalpha(msg.at(i)))
            if(isupper(msg.at(i)))
                encryptedMsg += (char )((msg.at(i) + newKey.at(i)) % 26) + 'A' ;
            else
                encryptedMsg += (char )((msg.at(i) + newKey.at(i) + 'A' - 'a' ) % 26) + 'a';
        else
            encryptedMsg += msg.at(i);
    return encryptedMsg;
}

string RSA_En(string msg,string key)
{
    My_namespace::RSA R(key);
    string encryptedMsg;
    for(char i:msg)
        encryptedMsg += R.Encrypt(i);
    return encryptedMsg;
}

string EnProcess(string msg,string key)
{
    string Output = RSA_En( VinC_En(msg,My_namespace::V_KeyG(key,max_buffer_size)) ,key);
    return Output;
}