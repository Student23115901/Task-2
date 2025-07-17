# Multithreaded File Compression & Decompression Tool  
### Author: Anushk Singh  
### Internship ID: CT06DF1877  
### Company: CodeTech IT Solutions Pvt Ltd  
### Internship Duration: 30/05/2025 – 15/07/2025  

---

## Project Overview  

This project is a **Multithreaded File Compression and Decompression Tool** developed as part of my second internship assignment. The core objective of this project was to design a professional-grade utility capable of compressing and decompressing large files efficiently using multithreading for performance optimization.  

Compression algorithms can often be CPU-intensive. By utilizing C++ multithreading along with the zlib compression library, this tool aims to demonstrate how parallel processing can reduce time consumption when handling sizable files — a concept widely adopted in industry-grade compression utilities.  

---

## Key Features  

- ✅ **File Compression using zlib’s Deflate Algorithm**  
- ✅ **File Decompression using zlib’s Inflate Algorithm**  
- ✅ **Chunk-based Multithreaded Processing** — Processes file chunks in parallel threads for better CPU utilization  
- ✅ **Thread Synchronization & Safety**  
- ✅ **Error Handling & Validation of Compressed Data**  
- ✅ **Command-Line Interface for User-Friendly Operations**  

---

## Technologies & Libraries Used  

- **Language:** C++17  
- **Libraries:**  
  - `zlib` for compression/decompression  
  - `thread` and `mutex` from `<thread>` & `<mutex>` for multithreading  
- **Compiler:** GCC with `-pthread` and `-lz` flags  

---

## How to Compile & Run  

1️⃣ Compile with multithreading and zlib support:  
```bash
g++ -std=c++17 -pthread -lz -o file_compressor file_compressor.cpp
```  

2️⃣ Run the compression tool:  
```bash
./file_compressor compress input.txt output_compressed.txt
```  

3️⃣ Run the decompression tool:  
```bash
./file_compressor decompress output_compressed.txt decompressed_output.txt
```  

---

## Project Description (Task Summary)  

The **Multithreaded File Compression and Decompression Tool** is designed to handle large file sizes by dividing the input file into manageable chunks and assigning them to multiple threads for simultaneous compression or decompression.  

During compression:  
- The file is split into fixed-size blocks.  
- Each block is compressed in a separate thread.  
- The compressed blocks are then written sequentially to the output file.  

During decompression:  
- The compressed file is read block by block.  
- Each block is decompressed in its thread.  
- The decompressed output is reassembled in the correct order.  

The project not only demonstrates technical concepts like buffer management, thread synchronization, and stream operations but also emphasizes real-world application challenges such as ensuring thread safety, maintaining data integrity, and optimizing read/write speeds.  

Throughout development, particular attention was given to exception handling to avoid race conditions, crashes, or data corruption — especially when handling I/O operations concurrently.  

This task simulates a lightweight version of industry-used utilities like ZIP or GZIP and serves as a strong practical implementation of concurrency and file handling techniques in C++.  

---

## Key Learnings from this Task  

- Practical implementation of multithreading concepts in C++  
- Hands-on experience with the zlib compression library  
- Understanding thread-safe I/O operations and synchronization  
- Learning chunked data processing for scalable file handling  
- Importance of error handling in multithreaded environments  

---

## Conclusion  

The successful completion of this **Multithreaded Compression/Decompression Tool** marked a signific
