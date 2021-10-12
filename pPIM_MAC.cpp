// pPIM_MAC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

float* BUFF = new float[3 * 3 * 3];
float* BUFF_sort = new float[3 * 3 * 3];


int MAC(int A, int B) {
    int R; 
    R = A * B;
    return R;
}

/*///////////////////////////////////////////////////////////////////////////
/
/     |A11  A12  A13|   |B11  B12  B13|   |C11  C12  C13|
/     |A21  A22  A23| x |B21  B22  B23| = |C21  C22  C23|
/     |A31  A32  A33|   |B31  B32  B33|   |C31  C32  C33|
/
/Matrice saved in R/W Buffer like this:
/   
/     [A11, A12, ..., A33, B11, B12, ..., B33, C11, C12, ..., C33]
/
/MatrixMultiplication_PIM represent the matrix multiplication operation with 
in one PIM cluster. A 3x3 matrix will needs 3 clusters work at the same time. 
/float* BUFF : R/W BUffer shared 3 PIM clusters.
/int size : size of one side of square matrix, if 3x3, then size = 3
///////////////////////////////////////////////////////////////////////////*/

void MatrixMultiplication_PIM(float* BUFF, int size) { //float not possible 
    
    int MatrixSize = size * size;

    for (int j = 0; j < size; j++) {
        float TempResult = 0;
        for (int i = 0; i < size; i++) {
            TempResult += MAC(BUFF[i + (j * size)], BUFF[MatrixSize + (i * size)]);
        }
        BUFF[(j * size) + (MatrixSize * 2)] = TempResult;
    }
    
}

/*///////////////////////////////////////////////////////////////////////////
/
/     |A11  A12  A13|   |B11  B12  B13|   |C11  C12  C13|
/     |A21  A22  A23| x |B21  B22  B23| = |C21  C22  C23|
/     |A31  A32  A33|   |B31  B32  B33|   |C31  C32  C33|
/
/Matrice saved in R/W Buffer like this:
/
/     [A11, A12, ..., A33, B11, B21, B31, B12, B22, B32, B13, B23, B33, C11,
C11, C21, C31, C12, C22, C32, C13, C23, C33,]
/
/MatrixMultiplication_PIM represent the matrix multiplication operation with
in one PIM cluster. A 3x3 matrix will needs 3 clusters work at the same time.
/float* BUFF : R/W BUffer shared 3 PIM clusters.
/int size : size of one side of square matrix, if 3x3, then size = 3
///////////////////////////////////////////////////////////////////////////*/

void MatrixMultiplication_PIM_sorted(float* BUFF, int size) {
    
    int MatrixSize = size * size;

    for (int j = 0; j < size; j++) {
        float TempResult = 0;
        for (int i = 0; i < size; i++) {
            TempResult += MAC(BUFF_sort[i + (j * size)], BUFF_sort[MatrixSize + i]); //MAC(A, B, Result)
        }
        BUFF[j + (MatrixSize * 2)] = TempResult;
    }

}



int main()
{
    std::cout << "Hello World!\n";

    for (int i = 0; i < 18; i++) {
        BUFF[i] = i + 1;
    }

    for (int i = 0; i < 18; i++) {
        BUFF_sort[i] = i + 1;
    }

    MatrixMultiplication_PIM(BUFF, 3);

    for (int i = 0; i < 27; i++) {
        std::cout << (BUFF)[i] << "\n";
    }
    
    MatrixMultiplication_PIM_sorted(BUFF_sort, 3);

    for (int i = 0; i < 27; i++) {
        std::cout << (BUFF_sort)[i] << " ";
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
