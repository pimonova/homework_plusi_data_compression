// Homework_Data_compression.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Datasets.h"
#include "Utils.h"

using namespace std;

int main()
{
    cout << "Hello!\n"
         << "This is our team homework - data compression algorithms\n"
         << "Our team: Kate Borushko, Farid Mystafaev, Maria Zhurinova, Maria Stepura, Julius Tokar', Stepan Lavrentev and Antonina Pimonova\n";
    
    cout << "Enter dataset size:" << endl;
    uint32_t datasetSize;
    getCorrect(datasetSize);
    string stringData = createDatatset(datasetSize);
    cout << stringData << endl;
}

