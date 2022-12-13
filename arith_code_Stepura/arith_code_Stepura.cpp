#include <string>
#include <iostream>
#include "arith_Stepura.h"
using namespace std;

string arithmetic::get_encode()
{
	return encode;
}

void arithmetic::input_string(string input)
{
	text = input;
	text.push_back(symbol_break);
}

void arithmetic::get_abc()
{
	bool exit_flag = 0; // добавить символ - в начало
	abc.push_back(EOF_symbol);
	for (int i = 0; i < text.size(); i++)
	{
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++)
		{
			if (abc[j] == text[i])			//если в алфавите уже есть такая буква
			{
				exit_flag = 1;				//выходим, если нашли такую букву
				break;
			}
		}
		if (exit_flag == 1)					//если мы находили букву ранее
		{
			continue;						//переход на следующую итерацию для след. буквы
		}
		else								//если буква найдена не была
		{
			abc.push_back(text[i]);
			continue;
		}
	}
}

void arithmetic::get_frequency()
{
	freq = new int[abc.size()];
	for (int i = 0; i < abc.size(); i++)
	{
		freq[i] = 0;
	}
	for (int j = 0; j < abc.size(); j++)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (abc[j] == text[i])
			{
				freq[j]++;
			}
		}
		if (j > 0)
		{
			freq[j] += freq[j - 1];
		}
	}
}

void arithmetic::get_next_symbol(int i, int* current)
{
	// индекс символа из текста в алфавите
	bool exit = false;
	for (i; i < text.size() && !exit; i++)
	{
		char temp_text = text[i];
		for (int j = 0; j < abc.size(); j++)
		{
			char temp_abc = abc[j];
			if (temp_text == temp_abc)
			{
				*current = j;
				exit = true;
				break;
			}
		}
	}
}

string arithmetic::write_bits(bool bit, int bits_to_foll)
{
	string temp;
	temp += to_string(bit);
	while (bits_to_foll > 0)
	{
		temp += to_string(!bit);
		bits_to_foll -= 1;
	}
	return temp;
}

void arithmetic::encode_text()
{
	int mass_size = text.length();
	unsigned short int* _low = new unsigned short int[mass_size];
	unsigned short int* _high = new unsigned short int[mass_size];
	_low[0] = _low_edge;
	_high[0] = _high_edge;
	int current = 1;	// какой элемент берём 
	int i = 0;			// где находимся 
	unsigned int range = 0;
	int del = freq[abc.size() - 1]; // del - последняя накопленная частота
	int bits_to_foll = 0;
	string code = "";
	while (i < text.length())
	{
		get_next_symbol(i, &current);
		i += 1;
		range = _high[i - 1] - _low[i - 1] + 1;
		_low[i] = _low[i - 1] + (range * freq[current - 1]) / del;
		_high[i] = _low[i - 1] + (range * freq[current]) / del - 1;
		for (;;)
		{
			if (_high[i] < half)
			{
				code += write_bits(0, bits_to_foll);
				bits_to_foll = 0;
			}
			else if (_low[i] >= half)
			{
				code += write_bits(1, bits_to_foll);
				bits_to_foll = 0;
				_low[i] -= half;
				_high[i] -= half;
			}
			else if (_low[i] >= first_qtr && _high[i] < third_qtr)
			{
				bits_to_foll += 1;
				_low[i] -= first_qtr;
				_high[i] -= first_qtr;
			}
			else break;
			_low[i] = 2 * _low[i];
			_high[i] = 2 * _high[i] + 1;
		}
	}
	encode = code;
}
