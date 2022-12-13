#pragma once
#include <string>
#include <iostream>
#define symbol_break '\0'
#define _low_edge 0
#define _high_edge 65535
#define EOF_symbol '-'
using namespace std;

class arithmetic
{
private:
	// определение половины, четверти и 3/4 
	const int first_qtr = _high_edge / 4 + 1;
	const int half = 2 * first_qtr;
	const int third_qtr = 3 * first_qtr;
	// объекты для работы с текстом */
	string text;
	string abc;
	string encode;
	int* freq; // массив частот
public:
	string get_encode(); // закодированная строка
	void input_string(string); // string text
	void get_abc(); // алфавит
	void get_frequency(); // массив частот
	void get_next_symbol(int, int*); // получение индекса следующего символа
	string write_bits(bool, int); // записать биты
	void encode_text(); // метод кодирования текста
};