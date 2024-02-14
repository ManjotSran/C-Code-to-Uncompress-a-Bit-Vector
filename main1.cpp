#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

std::vector<bool> decompressRun(const std::string &s, size_t &index) {
    // Find the position of the first '0' which gives us the value j-1
    size_t count_1s = 0;
    while (index < s.size() && s[index] == '1') {
        count_1s++;
        index++;
    }

    
    index++;

    
    size_t j = count_1s + 1;

    // Now reading the next j bits to get b1(i)
    if (index + j > s.size()) {
        throw std::runtime_error("Malformed compressed bit vector.");
    }

    size_t runLength = 0;
    for (size_t k = 0; k < j; k++, index++) {
        runLength = (runLength << 1) | (s[index] == '1');
    }

    // Construct the run of '0's followed by a '1'
    std::vector<bool> run(runLength, false);
    run.push_back(true);

    return run;
}

std::vector<bool> decompress(const std::string &compressed) {
    std::vector<bool> decompressed;
    size_t index = 0;

    while (index < compressed.size()) {
        std::vector<bool> run = decompressRun(compressed, index);
        decompressed.insert(decompressed.end(), run.begin(), run.end());
    }

    return decompressed;
}

std::string boolVectorToString(const std::vector<bool>& boolVec) {
    std::string s;
    for (bool bit : boolVec) {
        s.push_back(bit ? '1' : '0');
    }
    return s;
}

int main() {
    std::string compressed;
    std::cout << "Enter the compressed bit vector: ";
    std::cin >> compressed;

    try {
        std::vector<bool> decompressed = decompress(compressed);
        std::string decompressedStr = boolVectorToString(decompressed);
        std::cout << "Decompressed bit vector: " << decompressedStr << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}