#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

// Function to read CSV file and store data in a map
std::unordered_map<std::string, std::string> readCSV(const std::string& filename) {
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
        if (std::getline(ss, original, ',') &&
            std::getline(ss, md5hash, ',') &&
            std::getline(ss, sha1hash, ',') &&
            std::getline(ss, sha256hash, ',')) {
            data[md5hash] = original;
            data[sha1hash] = original;
            data[sha256hash] = original;
        }
    }

    file.close();
    return data;
}

int main() {
    std::string filename = "Rainbow_Table.csv"; // CSV file containing hashed values
    std::unordered_map<std::string, std::string> hashData = readCSV(filename);

    if (hashData.empty()) {
        std::cerr << "No data found in CSV file." << std::endl;
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
