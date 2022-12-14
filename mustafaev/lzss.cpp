#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "lzss.h"

#define SIZE_DICTIONARY 9
#define SIZE_BUFFER 5

struct code {
	std::vector<std::vector<char>> keys;
	int offset;
	int length;
	int prefix;
};

char dictionary[SIZE_DICTIONARY];
char buffer[SIZE_BUFFER];

std::vector<code> codes;

void lzss_move(std::string text, int offset, int position)
{
	if (text == "")
	{
		for (int i = 0; i < SIZE_DICTIONARY - 1; i++)
		{
			dictionary[i] = dictionary[i + 1];
		}
		dictionary[SIZE_DICTIONARY - 1] = buffer[0];
		for (int i = 0; i < SIZE_BUFFER - 1; i++)
		{
				buffer[i] = buffer[i + 1];
			
		}
		buffer[SIZE_BUFFER - 1] = 0;
	}
	else {
		for (int k = 0; k < offset; k++) {
			for (int i = 0; i < SIZE_DICTIONARY - 1; i++)
			{
				dictionary[i] = dictionary[i + 1];
			}
			dictionary[SIZE_DICTIONARY - 1] = buffer[0];
			for (int i = 0; i < SIZE_BUFFER - 1; i++)
			{
				
				buffer[i] = buffer[i + 1];
			
			}

			

			if (text != "" && position + k < text.size())
				buffer[SIZE_BUFFER - 1] = text[position + k];
			else
				buffer[SIZE_BUFFER - 1] = 0;
		}
		
	}
	
	
}

void lzss_init(std::string text)
{
	for (int i = 0; i < 5; i++)
	{
		buffer[i] = text[i];
	}
}

void add_codes(std::vector<char> keys, int offset, int length, int prefix)
{
	code code;
	code.keys.push_back(keys);
	code.offset = offset;
	code.length = length;
	code.prefix = prefix;
	codes.push_back(code);
}

std::string Mustafaev_lzss_encode(std::string text)
{
	lzss_init(text);
	int i = 5;
	bool f = true;
	while (f)
	{
		if (buffer[0] != 0 && buffer[1] == 0 && buffer[2] == 0)
			f = false;

		int check = 0;
		int jq;
		for (jq = 0; jq < SIZE_DICTIONARY - 3; jq++) {
			if (dictionary[jq] == buffer[0]) {
				check++;
				if (dictionary[jq + 1] == buffer[1]) {
					check++;
					if (dictionary[jq + 2] == buffer[2]) {
						check++;
						if (dictionary[jq + 3] == buffer[3]) {
							check++;
							break;
						}
						
					}
				}
			}
		}
		if (check == 0) {
			check = 1;
			std::vector<char> key;
			key.push_back(buffer[0]);
			add_codes(key, jq, 0, 0);
		}
		else {
			
			std::vector<char> key;
			key.push_back('0');
			add_codes(key, jq + 1, check, 1);
		}


		if (i > text.size())
			lzss_move("", check, i);
		else
		{
			lzss_move(text, check, i);
			i = i + check - 1;
		}
			

		i++;
		/*if (i > 300) {
			break;
		}*/
	}
	std::string result = "";
	for (auto& code : codes) {
		if (code.prefix == 0) {
			char ch = code.keys[0][0];
			std::string key(1, ch);
			result +=  key;
		}
		if (code.prefix == 1) {
			result += "(" + std::to_string(code.offset) + "," + std::to_string(code.length) + ")";
		}
	}
	
	return result;
}

//std::string Mustafaev_lzss_decode(std::string text)
//{
//	codes.clear();
//	int i = 0;
//	while (i < text.size() - 3) {
//		if (text[i] == '(') {
//			if (text[i + 1] == '0') {
//				std::vector<char> key;
//				key.push_back(text[i + 3]);
//				add_codes(key, 0, 0, 0);
//			}
//			if (text[i + 1] != '0') {
//				std::vector<char> key;
//				key.push_back(' ');
//				add_codes(key, text[i + 1] - 49, text[i + 3] - 48, 1);
//			}
//		}
//
//		i++;
//	}
//	std::string result = "";
//	for (int k = 0; k < SIZE_DICTIONARY; k++) 
//	{
//		dictionary[k] = 0;
//	}
//	i = 0;
//	for (auto& c : codes) {
//		
//		if (c.prefix == 0) {
//			result += c.keys[0][0];
//			for (int k = 0; k < SIZE_DICTIONARY - 1; k++) {
//				dictionary[k] = dictionary[k + 1];
//			}
//			dictionary[8] = c.keys[0][0];
//		}
//		if (c.prefix == 1) {
//			std::vector<char> bu;
//			for (int j = c.offset; j < c.length; j++) {
//				result += dictionary[j];
//				bu.push_back(dictionary[j]);
//		
//			}
//			for (int q = 0; q < bu.size(); q++) {
//				for (int k = 0; k < SIZE_DICTIONARY - 1; k++) {
//					dictionary[k] = dictionary[k + 1];
//				}
//				dictionary[8] = bu[q];
//			}
//			bu.clear();
//		}
//		
//		/*dictionary[8] = '0';*/
//		i++;
//	}
//	return result;
//}

