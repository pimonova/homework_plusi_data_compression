// Homework_Data_compression.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Datasets.h"
#include "Utils.h"
#include <chrono>
#include <string>
#include <vector>
#include "zhurinova_shannon_fanoo.h"
#include "arith_Stepura.h"
#include "arith_code_function_Stepura.h"


using namespace std;

string binary(uint32_t x)
{
    string s;
    do
    {
        s.push_back('0' + (x & 1));
    } while (x >>= 1);
    reverse(s.begin(), s.end());
    return s;
}

vector<string> toASCII(string data)
{
    vector<string> codesASCII;
    for (uint32_t i = 0; i < data.length() - 1; i++)
    {
        codesASCII.resize(i + 1);
        codesASCII[i] = binary(int(data[i]));
    }

    return codesASCII;
}

using participant = string(*)(string&);

void run(string methodName, participant p, string data)
{
    auto start = chrono::system_clock::now();
    string result = p(data);
    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    vector<string> ASCIIstr = toASCII(data);
    
    cout << "Method: " << methodName << endl
        << "Source string: " << data << endl
        <<   "String in ASCII code:\n";
    string strASCII{};
    for (uint32_t i = 0; i < ASCIIstr.size(); i++)
    {
        cout << ASCIIstr[i];
        strASCII += ASCIIstr[i];
    }
    cout << endl;
    double_t compression = 100 - (double(result.length()) / double(strASCII.length()) *100);
    cout << "String in shannon_fano code: " << result << endl
         << "Time: " << time << endl
         << "Compression: " << compression << "%" << endl;
}

int main()
{
    cout << "Hello!\n"
         << "This is our team homework - data compression algorithms\n"
         << "Our team: Kate Borushko, Farid Mystafaev, Maria Zhurinova, Maria Stepura, Julius Tokar', Stepan Lavrentev and Antonina Pimonova\n";
    
    cout << "Enter dataset size:" << endl;
    uint32_t datasetSize;
    getCorrect(datasetSize);
    string stringData = createDatatset(datasetSize);

    run("Shannon - Fano", shennon_fano, stringData);

    run("Arith", arith_cod, stringData);
}

 