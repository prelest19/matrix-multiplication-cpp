import numpy as np

def read_matrix(filename):
    return np.loadtxt(filename)

A = read_matrix("../data/matrixA.txt")
B = read_matrix("../data/matrixB.txt")
C_cpp = read_matrix("../data/resultMatrix.txt")

C_python = np.dot(A, B)

if np.allclose(C_cpp, C_python):
    print("Verification SUCCESS: Results match.")
else:
    print("Verification FAILED: Results do not match.")
