#include <cstdio>
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

bool containsWords (std::vector<std::string>& words, std::string s) {
    for (auto& i : words) {
        if (s.find(i) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void pruneFilesWords (std::vector<std::string>& words, std::string dir_path) {
    for (const auto & entry : std::filesystem::directory_iterator(dir_path)) {
        std::string s = entry.path().string();
        if (!containsWords(words, s)) {
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

    std::string mode;
    std::cout << "Prune mode:\n 1. Prune based on chars.txt (characters found will prune files)\n 2. Prune files not containing words in words.txt\n";
    std::cin >> mode;

    std::string s;
    std::cout << "Input the dir path to prune!\n";
    std::cin >> s;
    if (mode.compare("1") == 0) {
        std::cout <<"opening file\n";
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
    } else if (mode.compare("2") == 0) {
        std::cout <<"opening file\n";
        std::ifstream r_file("words.txt");
        if (!r_file) {
            std::cout << "Failed to read file!\n";
            return -1;
        }
        std::vector<std::string> words;
        std::string line;
        std::cout << "Reading words\n";
        while(getline(r_file, line)) {
            words.push_back(line);
            std::cout << line << "\n";
        }
        std::cout << "Pruning files\n";
        r_file.close();
        pruneFilesWords(words, s);
    }

    return 0;
}