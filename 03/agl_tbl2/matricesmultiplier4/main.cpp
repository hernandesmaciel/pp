#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;

vector<int**> matrices;

void multiplyMatrices(int** matrix1, int** matrix2)
{
    int product[3][3];
    int sum = 0;

    for (int i = 0 ; i < 3; i++) {
        for (int j = 0 ; j < 3 ; j++) {
            for (int k = 0 ; k < 3 ; k++ )
                sum = sum + matrix1[i][k]*matrix2[k][j];

            product[i][j] = sum;
            sum = 0;
        }
    }
}

int** allocateMatrix()
{
    int** matrix = new int*[3];
    for (int i = 0; i < 3; i++)
        matrix[i] = new int[3];

    return matrix;
}

void getMatrices(const string& filePath)
{
    string line;
    ifstream matricesFile(filePath.c_str());
    if (matricesFile.is_open()) {
        int index = 0;
        int** currentMatrix = nullptr;
        while (getline(matricesFile, line)) {
            if (line.empty()) {
                index = 0;
                if (currentMatrix)
                    matrices.push_back(currentMatrix);

                currentMatrix = nullptr;
            } else {
                if (!currentMatrix)
                    currentMatrix = allocateMatrix();
                istringstream iss(line);
                string temp;
                while (iss >> temp) {
                    currentMatrix[index / 3][index % 3] = atoi(temp.c_str());
                    index++;
                }
            }
        }
        if (currentMatrix)
            matrices.push_back(currentMatrix);

        matricesFile.close();
    } else {
        cout << "Unable to open file " << filePath << endl;
        exit(1);
    }
}

void multiply() {
    vector<thread> threads;
    for (int i = 0; i < matrices.size(); i = i + 2) {
        threads.push_back(thread(multiplyMatrices, matrices[i], matrices[i + 1]));
    }

    for (thread& t : threads)
        t.join();
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Error executing matricesmultiplier. Use as follows:" << endl;
        cout << "./matricesmultiplier <matrices_file>" << endl;
        return 1;
    }

    string matricesFile(argv[1]);
    getMatrices(argv[1]);
    multiply();

    return 0;
}
