#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;
using std::cout;
using std::cin;

// 非零元素節點結構
struct Node {
    int col;     // 行號
    int value;   // 值
    Node* next;  // 下一個節點
    
    Node(int c, int v) : col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;          // 矩陣維度
    vector<Node*> rowHeads;  // 每列的表頭
    
    // 釋放記憶體的輔助函數
    void clear() {
        for (Node* head : rowHeads) {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        rowHeads.clear();
    }

public:
    // 建構子
    SparseMatrix(int m, int n) : rows(m), cols(n) {
        rowHeads.resize(m, nullptr);
    }
    
    // 解構子
    ~SparseMatrix() {
        clear();
    }
    
    // 讀入矩陣資料
    void input() {
        for (int i = 0; i < rows; i++) {
            while (true) {
                int c, v;
                cin >> c;
                if (c == 0) break;
                cin >> v;
                
                // 建立新節點
                Node* newNode = new Node(c-1, v);  // 轉換為0-based索引
                
                // 插入節點（保持行號順序）
                if (!rowHeads[i] || rowHeads[i]->col > c-1) {
                    newNode->next = rowHeads[i];
                    rowHeads[i] = newNode;
                } else {
                    Node* curr = rowHeads[i];
                    while (curr->next && curr->next->col < c-1) {
                        curr = curr->next;
                    }
                    newNode->next = curr->next;
                    curr->next = newNode;
                }
            }
        }
    }
    
    // 矩陣加法
    SparseMatrix operator+(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions do not match for addition");
        }
        
        SparseMatrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            Node* p1 = rowHeads[i];
            Node* p2 = other.rowHeads[i];
            
            while (p1 || p2) {
                if (!p2 || (p1 && p1->col < p2->col)) {
                    result.insert(i, p1->col, p1->value);
                    p1 = p1->next;
                } else if (!p1 || (p2 && p2->col < p1->col)) {
                    result.insert(i, p2->col, p2->value);
                    p2 = p2->next;
                } else {  // p1->col == p2->col
                    int sum = p1->value + p2->value;
                    if (sum != 0) {
                        result.insert(i, p1->col, sum);
                    }
                    p1 = p1->next;
                    p2 = p2->next;
                }
            }
        }
        
        return result;
    }
    
    // 矩陣乘法
    SparseMatrix operator*(const SparseMatrix& other) const {
        if (cols != other.rows) {
            throw std::runtime_error("Matrix dimensions do not match for multiplication");
        }
        
        SparseMatrix result(rows, other.cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                Node* row = rowHeads[i];
                
                while (row) {
                    Node* col = other.rowHeads[row->col];
                    while (col) {
                        if (col->col == j) {
                            sum += row->value * col->value;
                            break;
                        }
                        col = col->next;
                    }
                    row = row->next;
                }
                
                if (sum != 0) {
                    result.insert(i, j, sum);
                }
            }
        }
        
        return result;
    }
    
    // 矩陣轉置
    SparseMatrix transpose() const {
        SparseMatrix result(cols, rows);
        
        for (int i = 0; i < rows; i++) {
            Node* curr = rowHeads[i];
            while (curr) {
                result.insert(curr->col, i, curr->value);
                curr = curr->next;
            }
        }
        
        return result;
    }
    
    // 插入元素的輔助函數
    void insert(int row, int col, int value) {
        Node* newNode = new Node(col, value);
        
        if (!rowHeads[row] || rowHeads[row]->col > col) {
            newNode->next = rowHeads[row];
            rowHeads[row] = newNode;
        } else {
            Node* curr = rowHeads[row];
            while (curr->next && curr->next->col < col) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
    
    // 一般格式輸出
    void printRegular() const {
        for (int i = 0; i < rows; i++) {
            Node* curr = rowHeads[i];
            for (int j = 0; j < cols; j++) {
                if (curr && curr->col == j) {
                    cout << std::setw(4) << curr->value;
                    curr = curr->next;
                } else {
                    cout << std::setw(4) << "0";
                }
            }
            cout << "\n";
        }
    }
    
    // 列表格式輸出（包含記憶體使用量）
    void printList() const {
        cout << "Dimensions: " << rows << " x " << cols << "\n";
        int memoryUnits = 0;
        
        for (int i = 0; i < rows; i++) {
            cout << "Row " << i+1 << ": ";
            Node* curr = rowHeads[i];
            while (curr) {
                cout << "(" << curr->col+1 << "," << curr->value << ") ";
                memoryUnits += 3;  // col + value + pointer
                curr = curr->next;
            }
            cout << "\n";
            memoryUnits += 1;  // row head pointer
        }
        memoryUnits += 2;  // rows and cols
        
        cout << "Memory units used: " << memoryUnits << "\n";
    }
};

int main() {
    int rows = 5, cols = 6;
    
    // 1. 配置指標陣列（第一維）
    int** mtrx = new int*[rows];
    
    // 2. 配置每一列的空間（第二維）
    for(int i = 0; i < rows; i++) {
        mtrx[i] = new int[cols];
    }
    
    // 3. 填入資料
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            mtrx[i][j] = 2*j + i;
        }
    }
    
    // 4. 輸出資料
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << mtrx[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 5. 釋放記憶體（注意順序！）
    for(int i = 0; i < rows; i++) {
        delete[] mtrx[i];  // 先釋放每一列
    }
    delete[] mtrx;        // 再釋放指標陣列
    
    return 0;
}