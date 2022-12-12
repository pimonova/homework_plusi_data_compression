#include <iostream>
#include <vector>
#include <string>
#include <set>

#define SIZE_DICTIONARY 9
#define SIZE_BUFFER 5

struct code {
	char key;
	int offset;
	int length;
	int prefix;
};

char dictionary[SIZE_DICTIONARY];
char buffer[SIZE_BUFFER];

std::vector<code> codes;

void lzss_move(char sym)
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

	buffer[SIZE_BUFFER - 1] = sym;
}

void lzss_init(std::string text)
{
	for (int i = 0; i < 5; i++)
	{
		buffer[i] = text[i];
	}
}

void add_codes(char key, int offset, int length, int prefix)
{
	code code;
	code.key = key;
	code.offset = offset;
	code.length = length;
	code.prefix = prefix;
	codes.push_back(code);
}



void search_in_dictionary()
{
	int check = 0;
	for (int i = SIZE_DICTIONARY - 1; i > 0; i--) {
		if (dictionary[i] == buffer[0])
		{
			add_codes(buffer[0], i, 1, 1);
			check++;
			break;
		}
	}
	if(check == 0)
		add_codes(buffer[0], 0, 0, 0);
}

std::string lzss_encode(std::string text)
{
	lzss_init(text);
	int i = 5;
	bool f = true;
	while (f)
	{
		if (buffer[0] != 0 && buffer[1] == 0 && buffer[2] == 0)
			f = false;
		search_in_dictionary();

		if(i > text.size())
			lzss_move(0);
		else 
			lzss_move(text[i]);	

		i++;
	}
	std::string result = "";
	for (auto& k : codes) {
		if (k.prefix == 0){
			char ch = k.key;
			std::string key(1, ch);
			result += "(" + std::to_string(k.prefix) + "," + key + ")";
		}
		if (k.prefix == 1) {
			result += "(" + std::to_string(k.offset) + "," + std::to_string(k.length) + ")";
		}
	}
	
	return result;
}

std::string lzss_decode(std::string text)
{
	codes.clear();
	int i = 0;
	while (i < text.size() - 3) {
		if (text[i] == '(') {
			if (text[i + 1] == '0') {
				add_codes(text[i + 3], 0, 0, 0);
			}
			if (text[i + 1] != '0') {
				add_codes('1', text[i + 1] - 48, text[i + 3] - 48, 1);
			}
		}

		i++;
	}
	std::string result = "";
	for (int k = 0; k < SIZE_DICTIONARY; k++) 
	{
		dictionary[k] = 0;
	}
	i = 0;
	for (auto& c : codes) {
		
		if (c.prefix == 0) {
			result += c.key;
			dictionary[8] = c.key;
		}
		if (c.prefix == 1) {
			result += dictionary[c.offset - 1];
			dictionary[8] = dictionary[c.offset - 1];
		}
		for (int k = 0; k < SIZE_DICTIONARY - 1; k++) {
			dictionary[k] = dictionary[k + 1];
		}
		i++;
	}
	return result;
}

int main() 
{
	std::string result_encode = lzss_encode("hfhejfkslkf");
	std::cout << "ENCODE: " << result_encode << std::endl;
	std::string reuslt_decode = lzss_decode(result_encode);
	std::cout << "DECODE: " << reuslt_decode << std::endl;
	return 0;
}