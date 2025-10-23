#include "../include/Huffman.hpp"

// ================================
// Main menu-driven program
// ================================
int main() {
    Huffman huff;
    int choice;
    string input, output;

    do {
        cout << "\n======= FILE COMPRESSION TOOL =======\n";
        cout << "1. Compress File\n";
        cout << "2. Decompress File\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter input text file path: ";
                cin >> input;
                cout << "Enter output compressed file path: ";
                cin >> output;
                huff.compressFile(input, output);
                break;

            case 2:
                cout << "Enter compressed file path: ";
                cin >> input;
                cout << "Enter output decompressed file path: ";
                cin >> output;
                huff.decompressFile(input, output);
                break;

            case 3:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
