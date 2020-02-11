/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"


int main(int argc, char* argv[])
{
    if ((argc !=3 && argc != 4) || (argv[1][0] != 's' && argv[1][0] != 'v'))
        std::cout << "wrong format! should be \"a.exe s filename\"";
    else {
      std::string filename = argv[2];


      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file

      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();

      std::string copyOFfile = filename+".Copy";
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();

      //std::cout<<memblock;

      if (argv[1][0]=='s') {
         std::cout << "\n"<<"Need to sign the doc.\n";
         // generate a SHA-256 hash of the content of the file to be signed (e.g., "file.txt", ìfile.exeî)
        std::string shaHash = sha256(memblock);
        std::ofstream file;
        file.open("file.txt");
        file << shaHash;
        file.close();

        // sign / "decrypt" this hash value using the private key stored in d_n.txt;
        std::string dTemp, nTemp;
        std::ifstream DN;
        DN.open("d_n.txt");
        DN >> dTemp >> nTemp;
        BigUnsigned D, N;
        D = stringToBigUnsigned(dTemp);
        N = stringToBigUnsigned(nTemp);
        std::cout << "MDD: " << D << std::endl;
        std::cout << "MDN: " << N << std::endl;

        BigUnsignedInABase hashMessage = BigUnsignedInABase(shaHash, 16);
        BigUnsigned message = hashMessage;
        BigUnsigned signature = modexp(message, D, N);

        // Store signature in the file
        std::ofstream signatureLog;
        signatureLog.open("file.txt.signature");
        signatureLog << signature;
      }
      else {
        std::cout << "\n"<<"Need to verify the doc.\n";
        // generate a SHA-256 hash of the content of the file to be signed (e.g., "file.txt", ìfile.exeî)
        std::string shaHash = sha256(memblock);
        std::ofstream file;
        file.open("file.txt");
        file << shaHash;
        file.close();

        BigUnsignedInABase originMessage = BigUnsignedInABase(shaHash, 16);
        std::cout << "shahash: " << shaHash << std::endl;
        std::cout << "originalMessg: " << originMessage << std::endl;
        BigUnsigned originMes = originMessage; // convert to BigUnsigned

        std::string signatureFile = argv[3];
        std::ifstream signatureF;
        signatureF.open("file.txt.signature");

        std::string signatureString;
        signatureF >> signatureString;

        BigUnsigned signature = stringToBigUnsigned(signatureString);

        // "encrypt" saved hash value (signature) using the public key
        BigUnsigned E, N;

        std::ifstream PublicKeyFile;
        PublicKeyFile.open("e_n.txt");

        std::string eTemp, nTemp;
        PublicKeyFile >> eTemp >> nTemp;
        E = stringToBigUnsigned(eTemp);
        N = stringToBigUnsigned(nTemp);

        BigUnsigned encrypt = modexp(signature, E, N);

        std::cout << "Encrypt: " << encrypt << std::endl;

        if (originMes == encrypt)
                std::cout << "Document is authentic" << std::endl;
            else
                std::cout << "Document is modified" << std::endl;

      }
      delete[] memblock;
    }
    return 0;
}
