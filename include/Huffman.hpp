// Huffman.hpp
// Author: <Your Name>
// Created: 2025-10-24
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// =========================
// Node Structure for Huffman Tree
// =========================
struct Node {
    char ch;           // Character stored in this node
    int freq;          // Frequency of the character
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// =========================
// Comparator for priority queue (min-heap)
// =========================
// Compare functor for priority_queue to build a min-heap based on frequency.
// priority_queue in C++ is a max-heap by default; we invert comparison.
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// =========================
// Huffman class encapsulates the entire compression logic
// =========================
class Huffman {
private:
    unordered_map<char, string> codes;     // Character → binary code
    unordered_map<char, int> freq;         // Character → frequency
    Node* root;                            // Root node of Huffman tree

    // Helper methods (private)
    void buildFrequencyTable(const string& text);
    void buildTree();
    void generateCodes(Node* node, string code);
    string encode(const string& text);
    string decode(const string& encoded);

public:
    Huffman();  // Constructor
    ~Huffman(); // Destructor to free memory
    // Compresses inputFile into outputFile using Huffman coding.
// - reads the entire input file, builds frequency table,
// - creates Huffman tree and codes, then writes a header and encoded data.

    void compressFile(const string& inputFile, const string& outputFile);
    // Decompresses a file created by compressFile()
// - reads frequency header, rebuilds Huffman tree
// - decodes the encoded bitstream and writes original text.

    void decompressFile(const string& inputFile, const string& outputFile);

    void freeTree(Node* node);  // Recursively delete tree
};

#endif
