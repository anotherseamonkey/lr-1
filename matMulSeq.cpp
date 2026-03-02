#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <format>

using namespace std;


// Matrix output
template <typename T> int matrixOutput(T* Mat, int size, string name)
{
    cout << "\"" << name << "\" matrix output:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << Mat[i * size + j] << " ";
        }
        cout << endl;
    }

    return 1;
}

void saveMatrix(const string name, float* mat, const int N) {
    ofstream fout(name);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fout << mat[i * N + j] << " ";
        }
        fout << endl;
    }
    fout.close();
}

void saveTime(const string name, double time, const int N) {
    ofstream fout(name);
    if (fout.is_open()) {
        fout << format("Size {}x{}", N, N) << endl;
        fout << format("time (s): {}", time) << endl;
    }
    fout.close();
}

int main() 
{


    clock_t start;

    int arr[10] = {10, 50, 100, 250, 500, 700, 1000, 1500, 2000, 2500};
    int l = 0;

    for (l; l < 10; l++) {
        const int N = arr[l];
        cout << N << endl;
        cout << "Begin initializing ..." << endl;

        float* A, * B;

        // Allocating memory for 2 initial matrices
        A = new float[N * N];
        B = new float[N * N];


        // initializing matrix A and B with random numbers
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                A[i * N + j] = (i + 1) * (j + 1);
                B[i * N + j] = (i + 1) + 2 * (j + 1);
            }

        //matrixOutput<float>(A, N, "A");
        //matrixOutput<float>(B, N, "B");
        saveMatrix(format("Matrix A if n = {}", N), A, N);
        saveMatrix(format("Matrix B if n = {}", N), B, N);
        float* C = new float[N * N];

        cout << "Begin calculating ..." << endl;

        start = clock();

        // Sequantial matrix multiplication
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                C[i * N + j] = 0;
                for (int k = 0; k < N; k++)
                {
                    C[i * N + j] += A[i * N + k] * B[k * N + j];
              
                   
                }
            }
        double time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << endl << "Calculation time: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

        //matrixOutput<float>(C, N, "resulting C");
        saveMatrix(format("Matrix C if n = {}", N), C, N);

        saveTime(format("Time for N = {}", N), time, N);

        // free memory
        delete[] A;
        delete[] B;
        delete[] C;

    }
    return 0;
}
