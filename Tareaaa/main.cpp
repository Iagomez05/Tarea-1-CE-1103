#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "PagedArray.h"
#include "SortingAlgorithm.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"

using namespace std;
using namespace std::chrono;

void printUsage() {
    cout << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << endl;
    cout << "ALGORITMO puede ser QS (Quick Sort), IS (Insertion Sort), o BS (Bubble Sort)" << endl;
}

SortingAlgorithm* getSortingAlgorithm(const string& algorithm) {
    if (algorithm == "QS") {
        return new QuickSort();
    } else if (algorithm == "IS") {
        return new InsertionSort();
    } else if (algorithm == "BS") {
        return new BubbleSort();
    } else {
        return nullptr;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printUsage();
        return 1;
    }

    string inputFile, outputFile, algorithm;

    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-input") {
            inputFile = argv[i + 1];
        } else if (arg == "-output") {
            outputFile = argv[i + 1];
        } else if (arg == "-alg") {
            algorithm = argv[i + 1];
        } else {
            printUsage();
            return 1;
        }
    }

    ifstream inFile(inputFile, ios::binary | ios::ate);
    if (!inFile) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return 1;
    }
    streamsize size = inFile.tellg();
    inFile.seekg(0, ios::beg);

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    vector<char> buffer(size);
    if (!inFile.read(buffer.data(), size)) {
        cerr << "Error al leer el archivo de entrada." << endl;
        return 1;
    }

    if (!outFile.write(buffer.data(), size)) {
        cerr << "Error al escribir el archivo de salida." << endl;
        return 1;
    }

    PagedArray arr(outputFile, size / sizeof(int));
    int numElements = size / sizeof(int);

    SortingAlgorithm* sortingAlgorithm = getSortingAlgorithm(algorithm);
    if (!sortingAlgorithm) {
        printUsage();
        return 1;
    }

    auto start = high_resolution_clock::now();
    sortingAlgorithm->sort(arr, numElements);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Tiempo durado: " << duration << " ms" << endl;
    cout << "Algoritmo utilizado: " << algorithm << endl;
    cout << "Cantidad de page faults: " << arr.getPageFaults() << endl;
    cout << "Cantidad de page hits: " << arr.getPageHits() << endl;

    delete sortingAlgorithm;

    return 0;
}
