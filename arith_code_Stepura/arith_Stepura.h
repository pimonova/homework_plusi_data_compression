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
	// ����������� ��������, �������� � 3/4 
	const int first_qtr = _high_edge / 4 + 1;
	const int half = 2 * first_qtr;
	const int third_qtr = 3 * first_qtr;
	// ������� ��� ������ � ������� */
	string text;
	string abc;
	string encode;
	int* freq; // ������ ������
public:
	string get_encode(); // �������������� ������
	void input_string(string); // string text
	void get_abc(); // �������
	void get_frequency(); // ������ ������
	void get_next_symbol(int, int*); // ��������� ������� ���������� �������
	string write_bits(bool, int); // �������� ����
	void encode_text(); // ����� ����������� ������
};