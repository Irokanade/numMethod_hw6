//
//  main.cpp
//  numMethod_hw6
//
//  Created by Michael Leong on 14/10/2022.
//

#include <iostream>
#include <cmath>

#define BUFFER 100

using namespace std;

void printMatrix(double myMatrix[][11], int row, int col) {
    for(int i = 1; i <= row; i++) {
        for(int j = 1; j <= col; j++) {
            cout << myMatrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

//naive matrix multiplication
//hardcode the size for now
void multMat(double mat1[11][11], double mat2[11][11], double result[11][11]) {
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            for(int k = 0; k < 11; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

//naive matrix vector multiplication
//hardcode the size for now
void multVecMat(double mat1[11][11], double vec[11], double result[11]) {
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            result[i] += mat1[i][j]*vec[j];
        }
    }
}

//naive matrix addition
//hardcode the size for now
void addMat(double mat1[11][11], double mat2[11][11], double result[11][11]) {
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            result[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
}

//hardcode size for now
void vectorSub(double vec1[11], double vec2[11], double result[11]) {
    for(int i = 0; i < 11; i++) {
        result[i] = vec1[i]-vec2[i];
    }
}

int main(int argc, const char * argv[]) {
    double myMatrix[11][11] = {0};
    double initVector[11] = {1}; //init vector for guessing value (set all as 1)
    double matrixDinv[11][11] = {0};
    double matrixL[11][11] = {0};
    double matrixU[11][11] = {0};
    double ansVector[11] = {0};
    
    //init myMatrix
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= 10; j++) {
            if(fabs(i-j) == 1) {
                myMatrix[i][j] = 2;
            } else if(fabs(i-j) >= 2 && j <= 10) {
                myMatrix[i][j] = 0;
            } else {
                myMatrix[i][j] = -4;
            }
        }
    }
    
    //init ansVector
    for(int i = 1; i <= 10; i++) {
        ansVector[i] = i+1;
    }
    
    //print ansVec
    cout << "ansVec\n";
    for(int i = 1; i <= 10; i++) {
        cout << ansVector[i] << '\n';
    }
    
    //print matrix
    cout << "myMatrix\n";
    printMatrix(myMatrix, 10, 10);
    
    
    //set matrixDinv
    for(int i = 1; i <= 10; i++) {
        matrixDinv[i][i] = 1/myMatrix[i][i];
    }
    
    //set matrixL
    for(int i = 1; i <= 10; i++) {
        for(int j = i+1; j <= 10; j++) {
            matrixL[i][j] = myMatrix[i][j];
        }
    }

    //set matrixU
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= i-1; j++) {
            matrixU[i][j] = myMatrix[i][j];
        }
    }
    
    cout << "matrixDinv\n";
    printMatrix(matrixDinv, 10, 10);
    cout << "matrixL\n";
    printMatrix(matrixL, 10, 10);
    cout << "matrixU\n";
    printMatrix(matrixU, 10, 10);
    
    
    double answer[11] = {0};
    
    int count = 0;
    while(count < 1000) {
        //L+U
        double matrixLplusU[11][11] = {0};
        addMat(matrixL, matrixU, matrixLplusU);
        
        //(L+U)*initVec
        double matrixLUMultVec[11] = {0};
        multVecMat(matrixLplusU, initVector, matrixLUMultVec);
        
        //ansVec - prevresult
        double almostResult[11] = {0};
        vectorSub(ansVector, matrixLUMultVec, almostResult);
        
        //Dinv * almost ans
        
        for(int i = 1; i <= 11; i++) {
            answer[i] = matrixDinv[i][i]*almostResult[i];
        }
        
        //update initVector
        for(int i = 0; i < 11; i++) {
            initVector[i] = answer[i];
        }
        
        count++;
    }
    
    //print answer
    for(int i = 1; i <= 10; i++) {
        cout << answer[i] << '\n';
    }
    
    
    return 0;
}
