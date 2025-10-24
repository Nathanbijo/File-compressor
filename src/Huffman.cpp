// Write header: number of unique chars and their frequencies.
// This header is used during decompression to rebuild the same tree.
#include "../include/Huffman.hpp"

// Constructor initializes root pointer
Huffman::Huffman() : root(nullptr) {}

// Destructor cleans up the tree memory
Huffman::~Huffman() {
    freeTree(root);
}

// Recursively delete all nodes in Huffman Tree
void Huffman::freeTree(Node* node) {
    if (!node) return;
    // bit '0' -> traverse left child, bit '1' -> traverse right child
// when leaf encountered, append the character and reset to root

    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// Step 1️⃣: Build frequency table for all characters
void Huffman::buildFrequencyTable(const string& text) {
    freq.clear();
    for (char ch : text)
        freq[ch]++;
}

// Step 2️⃣: Build Huffman Tree using a min-heap
void Huffman::buildTree() {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and push into the queue
    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));
// pop two smallest frequency nodes and merge them into a parent node
    // Merge nodes until only one root node remains
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* combined = new Node('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        pq.push(combined);
    }

    root = pq.top();  // Root of Huffman tree
}

// Step 3️⃣: Traverse tree recursively to generate binary codes
void Huffman::generateCodes(Node* node, string code) {
    // If this node is a leaf (has a character), store its code.
// Otherwise, go left with '0' and right with '1'.

    if (!node) return;

    // If it's a leaf node (contains a character)
    // node->ch == '\0' indicates an internal node (no char), leaves hold actual characters

    if (node->ch != '\0')
        codes[node->ch] = code;

    // Traverse left (append '0') and right (append '1')
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

// Step 4️⃣: Encode text using the Huffman codes
string Huffman::encode(const string& text) {
    string encoded;
    for (char ch : text)
        encoded += codes[ch];
    return encoded;
}

// Step 5️⃣: Decode encoded string using the Huffman tree
string Huffman::decode(const string& encoded) {
    string decoded;
    Node* curr = root;

    for (char bit : encoded) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (curr->ch != '\0') { // reached leaf
            decoded += curr->ch;
            curr = root;
        }
    }

    return decoded;
}

// Step 6️⃣: Compress a file (text → encoded binary)
void Huffman::compressFile(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    if (!in) {
        cerr << "Error: Cannot open input file.\n";
        return;
    }

    // Read full file into string
    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    buildFrequencyTable(text);
    buildTree();
    generateCodes(root, "");

    string encoded = encode(text);

    // Save encoded string to output file
    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Error: Cannot open output file.\n";
        return;
    }

    // Write a simple header first (number of entries)
    out << freq.size() << "\n";
    for (auto &p : freq)
        out << (int)p.first << " " << p.second << "\n";
    // The '====' separator marks the end of the header and the beginning of encoded bits.
out << "====\n";

    // Then the encoded text (as '0' and '1' for simplicity)
    out << encoded;
    out.close();

    cout << "✅ File compressed successfully → " << outputFile << endl;
}

// Step 7️⃣: Decompress file (encoded → text)
void Huffman::decompressFile(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Error: Cannot open compressed file.\n";
        return;
    }

    // Read header
    int mapSize;
    in >> mapSize;
    freq.clear();

    for (int i = 0; i < mapSize; i++) {
        int chVal, frequency;
        in >> chVal >> frequency;
        freq[(char)chVal] = frequency;
    }

    string line;
    getline(in, line); // consume newline
    getline(in, line); // should read "===="

    // Read rest of file (encoded content)
    string encoded((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    // Rebuild tree and decode
    buildTree();
    string decoded = decode(encoded);

    ofstream out(outputFile);
    if (!out) {
        cerr << "Error: Cannot create output file.\n";
        return;
    }

    out << decoded;
    out.close();

    cout << "✅ File decompressed successfully → " << outputFile << endl;
}
