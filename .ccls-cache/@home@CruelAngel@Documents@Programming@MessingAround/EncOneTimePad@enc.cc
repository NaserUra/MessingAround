#include <iostream>
#include <string>
#include <fstream>

void encrypt(std::fstream& file2enc, std::fstream& encFile, std::fstream& key_file){
    char ch;
    while(file2enc.get(ch)) {
        char c = ch;
        int key = rand();
        int encrypted_char = c ^ key; 

        encFile << encrypted_char;
        key_file << key;
        //std::cout << "1\n";
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "No file encluded for encryption!" << std::endl;
        return -1;
    }
    else{
        std::string file2EncName = argv[1];
        std::fstream file2enc, encFile, key_file;
        file2enc.open(file2EncName, std::ios::in);
        encFile.open("crypt.out", std::ios::out);
        key_file.open("key.out", std::ios::out);

        encrypt(file2enc, encFile, key_file);

        key_file.close();
        encFile.close();
        file2enc.close();
    }
    return 0;
}
