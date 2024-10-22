#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;

struct Node {
	int index; // in which col
	int value;
	Node* next;
	Node(int c, int v) : index(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols; // size of the matrix
    Node** rowHeads; // stores datas of the sparse matrix 
public:
    SparseMatrix(int m, int n) : rows(m), cols(n) {
        rowHeads = new Node*[m];  // Dynamically allocate array
        for(int i = 0; i < m; i++) {
            rowHeads[i] = nullptr;
        }
    }
    
    ~SparseMatrix() {
        for (int i = 0; i < rows; i++) {
            Node* head = rowHeads[i];
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        delete[] rowHeads;  // Delete the array
    }
    
    // register sparse matrix data 
    void input() {
        for (int i = 0; i < rows; i++) {
            while (1) {
                int col, value;
                cin >> col;
                if (!col || col > cols) break;
                cin >> value;
                if (!value) continue;
                // row <i> col <col - 1> is <value>
                insert(i, col - 1, value);
            }
        }
        return;
    }
    
    // addition of matrices
    SparseMatrix operator+(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "ERROR: Matrix dimensions do not match for multiplication\n";
            return SparseMatrix(0, 0);
        }
        
        SparseMatrix resultMatrix(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            Node* A = rowHeads[i];
            Node* B = other.rowHeads[i];
            Node* dummyNode = new Node(-1, 0);
            Node* C = dummyNode;
            
            while (A && B) {
                if (A->index == B->index) {
                    int sum = A->value + B->value;
                    C->next = new Node(A->index, sum);
                    A = A->next;
                    B = B->next;
                } else if (A->index < B->index) {
                    C->next = new Node(A->index, A->value);
                    A = A->next;
                } else {
                    C->next = new Node(B->index, B->value);
                    B = B->next;
                }
                C = C->next;
            }
            while (A) {
                C->next = new Node(A->index, A->value);
                A = A->next;
                C = C->next;
            }
            while (B) {
                C->next = new Node(B->index, B->value);
                B = B->next;
                C = C->next;
            }

            resultMatrix.rowHeads[i] = dummyNode->next;
            delete dummyNode;
        }
        
        return resultMatrix;
    }
    
    // multiplication of matrices
    SparseMatrix operator*(const SparseMatrix& other) const {
        if (cols != other.rows) {
            cout << "ERROR: Matrix dimensions do not match for multiplication\n";
            return SparseMatrix(0, 0);
        }
    
        SparseMatrix result(rows, other.cols);
        auto other_T = other.transpose();
    
        for (int i = 0; i < rows; i++) {
            Node* dummyPointer = new Node(-1, 0);
            Node* c = dummyPointer;
    
            for (int j = 0; j < other_T.rows; j++) {
                int sum = 0;
                Node* a = rowHeads[i];
                Node* b = other_T.rowHeads[j];
    
                while (a && b) {
                    if (a->index == b->index) {
                        sum += a->value * b->value;
                        a = a->next;
                        b = b->next;
                    } else if (a->index < b->index) {
                        a = a->next;
                    } else {
                        b = b->next;
                    }
                }
    
                if (sum) {
                    c->next = new Node(j, sum);
                    c = c->next;
                }
            }
            result.rowHeads[i] = dummyPointer->next;
            delete dummyPointer;
        }
        return result;
    }
    
    // operating transpose to a matrix
    SparseMatrix transpose() const {
        SparseMatrix result(cols, rows); // change row and col
        
        for (int i = 0; i < rows; i++) {
            Node* curr = rowHeads[i];
            while (curr) {
				// insert [row][col] to [col][row]
                result.insert(curr->index, i, curr->value);
                curr = curr->next;
            }
        }
        
        return result;
    }
    
    // insertion of input
    void insert(int row, int col, int value) {
        Node* newNode = new Node(col, value);

        if (!rowHeads[row] || rowHeads[row]->index > col) {
            // the new Node would be the head
            newNode->next = rowHeads[row];
            rowHeads[row] = newNode;
        }
        else {
            // else it would be somewhere else
            Node* curr = rowHeads[row];
            while (curr->next && curr->next->index < col) {
                // find where the new Node should belong
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        return;
    }
    
    // output as a rectangular form
    void printRegular() const {
        for (int i = 0; i < rows; i++) {
            Node* curr = rowHeads[i];
            for (int j = 0; j < cols; j++) {
                if (curr && curr->index == j) {
                    cout << std::setw(4) << curr->value;
                    curr = curr->next;
                } else {
                    cout << std::setw(4) << "0";
                }
            }
            cout << "\n";
        }
    }
    
    // output every elements in a row
    void printList() const {
        cout << "Dimensions: " << rows << " x " << cols << "\n";
        int memoryUnits = 0;
        
        for (int i = 0; i < rows; i++) {
            cout << i + 1 << ": ";
            Node* current = rowHeads[i];
            while (current) {
                cout << "(" << current->index + 1 << "," << current->value << ")";
                memoryUnits += 3; // col + value + pointer
                current = current->next;
                if (current) cout << " -> ";
            }
            cout << "\n";
            memoryUnits += 1; // row head pointer
        }
        memoryUnits += 2; // rows and cols
        
        cout << "Memory units used: " << memoryUnits << "\n";
    }
};

int main() {
	int rows = 3, cols = 3;
	cin >> rows >> cols;
	SparseMatrix A(rows, cols);
	A.input();
	
	cout << "A\n";
	A.printList();

	cin >> rows >> cols;
	SparseMatrix B(rows, cols);
	B.input();

	cout << "B\n";
	B.printList();

	auto C = A + B;
	cout << "summation:\nC\n";
	C.printList();

	auto D = A * B;
	cout << "multiplication\nD\n";
	D.printList();

	auto E = A.transpose();
	cout << "transpose\nE\n";
	E.printList();
	
	return 0;
}

/*
4 3
2 1 0 1 3 3 4 0 1 5 3 6 0 3 4 2 8 0

A
Dimensions: 4 x 3
1: (2,1)
2: (1,3) -> (3,4)
3: (1,5) -> (3,6)
4: (2,8) -> (3,4)
Memory units used: 27
3 4
2 8 0 2 1 3 2 0 1 4 3 7 4 6 0
*/