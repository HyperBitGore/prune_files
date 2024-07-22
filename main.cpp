#include <ios>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>


void pruneFiles (unsigned char c, std::string dir_path) {
    for (const auto & entry : std::filesystem::directory_iterator(dir_path)){
        std::string s = entry.path().string();
        if (s.find(c) != std::string::npos) {
            std::cout << entry.path() << "\n";
            std::remove(s.c_str());
        }
    }
}


int main () {


    /* std::ofstream file("chars.txt", std::ios_base::out | std::ios_base::binary);
    for (unsigned char i = 128; i < 255; i++) {
        file << i;
    }
    file.close();

    
    std::ofstream file;
    for (unsigned char i = 128; i < 255; i++) {
        std::string ss = "../stupid_files/";
        ss.push_back(i);
        file.open(ss, std::ios_base::binary | std::ios_base::out);
        file << "goonga\n";
        file.close();
    }*/

    std::string s;
    std::cout << "Input the dir path to prune!\n";
    std::cin >> s;

    std::cout <<"opening files\n";
    std::ifstream r_file("chars.txt", std::ios::binary);
    if (!r_file) {
        std::cout << "Failed to read file!\n";
        return -1;
    }
    r_file.seekg(0, std::ios::end);
    std::streamsize size = r_file.tellg();
    r_file.seekg(0, std::ios::beg);
    std::cout << "File size: " << size << "\n";
    //read each character and process
    std::vector<char> buffer(size);
    r_file.read(buffer.data(), size);
    r_file.close();
    for (char i : buffer) {
        unsigned char c = (unsigned char)i;
        pruneFiles(c, s);
    }
    return 0;
}