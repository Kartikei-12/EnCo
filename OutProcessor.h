string VinC_Dy(string encryptedMsg,string newKey)
{
    string decryptedMsg="";
    for(uint16_t i = 0; i < encryptedMsg.length(); ++i)
        if(isalpha(encryptedMsg.at(i)))
            if(isupper(encryptedMsg.at(i)))
                decryptedMsg += (char )(( encryptedMsg.at(i) - newKey.at(i) + 'a' - 'A' - 6 ) % 26) + 'A';
            else
                decryptedMsg += (char )(( encryptedMsg.at(i) - newKey.at(i) - 6 ) % 26) + 'a';
        else
            decryptedMsg += encryptedMsg.at(i);
    return decryptedMsg;
}

string RSA_Dy(string enMsg,string key)
{
    My_namespace::RSA R(key);
    string decryptedMsg = "";
    for(char i:enMsg)
        decryptedMsg += R.Decrypt(i);
    return decryptedMsg;
}

string DyProcess(string msg,string key)
{   
    string Output = VinC_Dy( RSA_Dy(msg,key) ,My_namespace::V_KeyG(key,max_buffer_size));
    return Output;
}