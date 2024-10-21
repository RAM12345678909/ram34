#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

// Function to read the plain text file and store data in a map
std::unordered_map<std::string, std::string> readWordFile(const std::string& filename) {
    std::ifstream file(filename);
    std::unordered_map<std::string, std::string> data;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string original, md5hash, sha1hash, sha256hash;
        if (std::getline(ss, original, '\t') &&
            std::getline(ss, md5hash, '\t') &&
            std::getline(ss, sha1hash, '\t') &&
            std::getline(ss, sha256hash, '\t')) {
            data[md5hash] = original;
            data[sha1hash] = original;
            data[sha256hash] = original;
        }
    }

    file.close();
    return data;
}

int main() {
    std::string filename = "rainbow.docx"; // Plain text file converted from word file
    std::unordered_map<std::string, std::string> hashData = readWordFile(filename);

    if (hashData.empty()) {
        std::cerr << "No data found in the word file." << std::endl;
        return 1;
    }

    std::string hashInput;
    std::cout << "Enter hash string: ";
    std::cin >> hashInput;

    // Match hashInput with hashData
    if (hashData.find(hashInput) != hashData.end()) {
        std::cout << "Original text: " << hashData[hashInput] << std::endl;
    } else {
        std::cout << "No matching hash found." << std::endl;
    }

    return 0;
}
