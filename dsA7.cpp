#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

// Huffman Tree Node
class Node {
public:
    char symbol;
    int freq;
    Node *left, *right;

    Node(char symbol, int freq) :
		symbol(symbol), freq(freq),
		left(nullptr), right(nullptr) {}

    bool operator <(const Node &other) const {
        return this->freq < other.freq;
    }

	void printHuffmanTree() {
        if (this->left == nullptr && this->right == nullptr) {
            std::cout << "Character: " << symbol << ", Frequency: " << freq << std::endl;
        }

        // 遞迴打印左子樹
        if (left != nullptr) {
            left->printHuffmanTree();
        }

        // 遞迴打印右子樹
        if (right != nullptr) {
            right->printHuffmanTree();
        }
    }
};

// Custom Priority Queue using Min-Heap
template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (compare(heap[index], heap[parentIndex])) {
            std::swap(heap[index], heap[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && compare(heap[leftChild], heap[smallest])) { smallest = leftChild; }
        if (rightChild < heap.size() && compare(heap[rightChild], heap[smallest])) { smallest = rightChild; }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    bool compare(const T& a, const T& b) {
        return a < b; // sort by freq
    }

public:
    void push(const T &value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    T top() const {
        if (heap.empty()) {
            throw std::out_of_range("Error");
        }
        return heap[0];
    }

    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
};

// Calculate frequency of each character in the input file
void calculateFrequency(
	const std::string &filePath,
	std::unordered_map<char, int> &frequency) {

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(EXIT_FAILURE);
    }

    char ch;
    while (file.get(ch)) {
        frequency[ch]++;
    }
    file.close();
}

// Build Huffman tree from character frequencies
Node* buildHuffmanTree(const std::unordered_map<char, int> &frequency) {
    PriorityQueue<Node*> pq;
    for (const auto &pair : frequency) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
	pq.top()->printHuffmanTree();
    return pq.top();
}

// Generate Huffman codes from the Huffman tree
void generateHuffmanCodes(
	Node* root,
	const std::string &currentCode,
	std::unordered_map<char, std::string> &codes) {
    if (!root) return;
    if (root->symbol != '\0') {
        codes[root->symbol] = currentCode;
        std::cout << "Char: " << root->symbol << ", code: " << currentCode << std::endl;
    }
    generateHuffmanCodes(root->left, currentCode + "0", codes);
    generateHuffmanCodes(root->right, currentCode + "1", codes);
}

// Compress the input file using the generated Huffman codes
void compressFile(
	const std::string &inputFilePath,
	const std::string &outputFilePath,
	const std::unordered_map<char,std::string> &codes) {

    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);

    std::string encodedString;
    char ch;
    while (inputFile.get(ch)) {
        encodedString += codes.at(ch);
    }
    outputFile << encodedString;

    inputFile.close();
    outputFile.close();
}

// Decompress the compressed file using the Huffman tree
void decompressFile(
	const std::string &inputFilePath,
	const std::string &outputFilePath,
	Node* root) {

    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);

    std::string bitString;
    char ch;
    while (inputFile.get(ch)) {
        bitString += ch;
    }

    Node* current = root;
    for (char bit : bitString) {
        if (bit == '0') { current = current->left; }
        else { current = current->right; }

        if (current->left == nullptr && current->right == nullptr) {
            outputFile.put(current->symbol);
            current = root;
        }
    }

    inputFile.close();
    outputFile.close();
}

using std::string;

int main() {
	std::cout << "hello, world!\n";
    string inputFilePath = "dsA7.txt";
    string compressedTextFilePath = "dsA7_comp.txt";
    string decompressedFilePath = "dsA7_decomp.txt";

    std::unordered_map<char, int> frequency;
    calculateFrequency(inputFilePath, frequency);

    Node* root = buildHuffmanTree(frequency);
    std::unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);
    compressFile(inputFilePath, compressedTextFilePath, codes);
    decompressFile(compressedTextFilePath, decompressedFilePath, root);

    return 0;
}