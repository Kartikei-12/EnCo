
//Project class
namespace My_namespace
{
    class Programm
    {
        string inputName, outputName,
            tempName, fileExtension, 
            Out_nameExtended;

        void set_names()
        {
            //Preparing I/O file names and such
            fileExtension = WorkP.workFile.substr(WorkP.workFile.rfind('.'));
            tempName = "temp" + fileExtension;
            inputName.assign( WorkP.workFile.begin(), WorkP.workFile.begin()+WorkP.workFile.rfind('.') );
            
            //Preparing extended file name for Output file
            Out_nameExtended.clear();
            if(WorkP.isEncrypt)
                Out_nameExtended += "-e";
            else
                Out_nameExtended += "-d";
            
            if(WorkP.isCompress)
                Out_nameExtended += "-com";
            if(WorkP.isDecompress)
                Out_nameExtended += "-decom";
            outputName = inputName + Out_nameExtended + fileExtension;
            
            //Resetting original Input file name
            inputName = WorkP.workFile;
        }

    public:
        Project_Parameter WorkP;

        void DoIt()//Function doing main work
        {
            set_names();
            
            keepLog("Input File: "+inputName);
            keepLog("Output File: "+outputName);

            //Doing work
            //When Only file encryption is asked
            if(WorkP.isEncrypt && !WorkP.isCompress)
            {
                keepLog("Encrypting.", __FILE__, __LINE__);
                Cryptografhy_function(inputName, outputName,
                                        WorkP.key, !WorkP.isEncrypt);
            }
            //When only file compression is asked
            else if(!WorkP.isEncrypt && WorkP.isCompress)
            {
                keepLog("Compressing.", __FILE__, __LINE__);
                Huffman_Compression::encoder(inputName,outputName);
            }
            //When both file encryption and compression is asked
            else if(WorkP.isEncrypt && WorkP.isCompress)
            {
                keepLog("Encryting.", __FILE__, __LINE__);
                Cryptografhy_function(inputName, tempName,
                                        WorkP.key, !WorkP.isEncrypt);
                keepLog("Compressing.", __FILE__, __LINE__);
                Huffman_Compression::encoder(tempName,outputName);
            }
            //When only file decryption is required
            else if(WorkP.isDecrypt && !WorkP.isDecompress)
            {
                keepLog("Decrypting", __FILE__, __LINE__);
                Cryptografhy_function(inputName, outputName,
                                        WorkP.key, WorkP.isDecrypt);
            }
            //When only file decompresin is asked
            else if(!WorkP.isDecrypt && WorkP.isDecompress)
            {
                keepLog("Decompressing", __FILE__, __LINE__);
                Huffman_Compression::decoder(inputName,outputName);
            }
            //When both file decompression and decryption is required
            else if(WorkP.isDecrypt && WorkP.isDecompress)
            {
                keepLog("Decompressing", __FILE__, __LINE__);
                Huffman_Compression::decoder(inputName,tempName);
                keepLog("Decrypting", __FILE__, __LINE__);
                Cryptografhy_function(tempName, outputName,
                                        WorkP.key, WorkP.isDecrypt);
            }
            //Unknown case
            else
                throw error.encountered("Cannot Process Request", __FILE__, __LINE__);
            
            //Removing temporary file if any
            remove(tempName.c_str());
        }
    };
}