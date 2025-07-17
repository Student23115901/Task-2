#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <zlib.h>

const size_t CHUNK_SIZE = 1024 * 1024; // 1 MB
std::mutex io_mutex;

void compressChunk(const std::vector<unsigned char>& inputChunk, std::ofstream& outFile) {
    uLongf compressedSize = compressBound(inputChunk.size());
    std::vector<unsigned char> compressedData(compressedSize);

    if (compress(compressedData.data(), &compressedSize, inputChunk.data(), inputChunk.size()) != Z_OK) {
        std::lock_guard<std::mutex> lock(io_mutex);
        std::cerr << "Compression failed for a chunk.\n";
        return;
    }

    {
        std::lock_guard<std::mutex> lock(io_mutex);
        outFile.write(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));
        outFile.write(reinterpret_cast<char*>(compressedData.data()), compressedSize);
    }
}

void decompressChunk(std::ifstream& inFile, std::ofstream& outFile) {
    while (true) {
        uLongf compressedSize;
        {
            std::lock_guard<std::mutex> lock(io_mutex);
            if (!inFile.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize)))
                break;
        }

        std::vector<unsigned char> compressedData(compressedSize);
        {
            std::lock_guard<std::mutex> lock(io_mutex);
            inFile.read(reinterpret_cast<char*>(compressedData.data()), compressedSize);
        }

        std::vector<unsigned char> decompressedData(CHUNK_SIZE);
        uLongf decompressedSize = decompressedData.size();

        if (uncompress(decompressedData.data(), &decompressedSize, compressedData.data(), compressedSize) != Z_OK) {
            std::lock_guard<std::mutex> lock(io_mutex);
            std::cerr << "Decompression failed for a chunk.\n";
            return;
        }

        {
            std::lock_guard<std::mutex> lock(io_mutex);
            outFile.write(reinterpret_cast<char*>(decompressedData.data()), decompressedSize);
        }
    }
}

void compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening input file.\n";
        return;
    }
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening output file.\n";
        return;
    }

    std::vector<std::thread> threads;

    while (!in.eof()) {
        std::vector<unsigned char> buffer(CHUNK_SIZE);
        in.read(reinterpret_cast<char*>(buffer.data()), CHUNK_SIZE);
        std::streamsize bytesRead = in.gcount();

        if (bytesRead <= 0) break;
        buffer.resize(bytesRead);

        threads.emplace_back(compressChunk, buffer, std::ref(out));

        if (threads.size() >= std::thread::hardware_concurrency()) {
            for (auto& t : threads) t.join();
            threads.clear();
        }
    }

    for (auto& t : threads) t.join();

    std::cout << "File compressed successfully.\n";
}

void decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening input file.\n";
        return;
    }
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening output file.\n";
        return;
    }

    std::vector<std::thread> threads;

    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(decompressChunk, std::ref(in), std::ref(out));
    }

    for (auto& t : threads) t.join();

    std::cout << "File decompressed successfully.\n";
}

int main() {
    int choice;
    std::string inputFile, outputFile;

    std::cout << "==== Multithreaded File Compressor/Decompressor ====\n";
    std::cout << "1. Compress a file\n2. Decompress a file\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::cout << "Enter input file path: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter output file path: ";
    std::getline(std::cin, outputFile);

    if (choice == 1)
        compressFile(inputFile, outputFile);
    else if (choice == 2)
        decompressFile(inputFile, outputFile);
    else
        std::cerr << "Invalid choice.\n";

    return 0;
}
