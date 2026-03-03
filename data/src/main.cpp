#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

typedef vector<vector<double>> Matrix;

// Чтение квадратной матрицы
bool readMatrix(const string& filename, Matrix& mat) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open file " << filename << endl;
        return false;
    }

    string line;
    size_t expectedSize = 0;

    while (getline(fin, line)) {
        istringstream iss(line);
        vector<double> row;
        double value;

        while (iss >> value)
            row.push_back(value);

        if (!row.empty()) {
            if (expectedSize == 0)
                expectedSize = row.size();
            else if (row.size() != expectedSize) {
                cerr << "Error: matrix is not rectangular." << endl;
                return false;
            }
            mat.push_back(row);
        }
    }

    if (mat.empty() || mat.size() != mat[0].size()) {
        cerr << "Error: matrix must be square." << endl;
        return false;
    }

    return true;
}

// Запись матрицы
void writeMatrix(const string& filename, const Matrix& mat) {
    ofstream fout(filename);
    for (const auto& row : mat) {
        for (double val : row)
            fout << val << " ";
        fout << "\n";
    }
}

// Умножение матриц
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, vector<double>(n, 0.0));

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            for (size_t k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

int main() {
    Matrix A, B, C;

    const string fileA = "data/matrixA.txt";
    const string fileB = "data/matrixB.txt";
    const string fileResult = "data/resultMatrix.txt";

    if (!readMatrix(fileA, A)) return 1;
    if (!readMatrix(fileB, B)) return 1;

    if (A.size() != B.size()) {
        cerr << "Error: matrices must have the same size." << endl;
        return 1;
    }

    size_t n = A.size();

    auto start = high_resolution_clock::now();
    C = multiplyMatrices(A, B);
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    writeMatrix(fileResult, C);

    unsigned long long operations = 2ULL * n * n * n;

    cout << "Matrix size: " << n << "x" << n << endl;
    cout << "Execution time: " << elapsed.count() << " seconds" << endl;
    cout << "Task volume (operations): " << operations << endl;

    return 0;
}
