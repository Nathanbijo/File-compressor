#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
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

    void compressFile(const string& inputFile, const string& outputFile);
    void decompressFile(const string& inputFile, const string& outputFile);

    void freeTree(Node* node);  // Recursively delete tree
};

#endif
