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
	int type;
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

void add_codes(char key, int offset, int length, int type)
{
	code code;
	code.key = key;
	code.offset = offset;
	code.length = length;
	code.type = type;
	codes.push_back(code);
}

void print_codes()
{
	std::set<char> word;
	bool f = false;
	std::cout << "CODES: ";
	for (auto& k : codes)
	{
		if(k.key != ' ')
			word.insert(k.key);
	}
	for (char w : word) {
		if(w != 0)
			std::cout << w << ", ";
	}
	
	
}

void search_in_dictionary()
{
	int check = 0;
	for (int i = SIZE_DICTIONARY; i > 0; i--) {
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

void lzss_encode(std::string text)
{
	std::cout << "ENCODE" << std::endl;
	std::cout << "TEXT: " << text << std::endl;
	std::string::size_type sz = sizeof(text);
	std::cout << "SIZE: " << sz << std::endl;
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
	
}

void lzss_decode()
{
	for (int k = 0; k < SIZE_DICTIONARY; k++) 
	{
		dictionary[k] = 0;
	}
	int i = 0;
	std::cout << std::endl;
	for (auto& c : codes) {
		
		if (c.type == 0) {
			std::cout << c.key;
			dictionary[8] = c.key;
		}
		if (c.type == 1) {
			std::cout << dictionary[c.offset - 1];
			dictionary[8] = dictionary[c.offset - 1];
		}
		for (int k = 0; k < SIZE_DICTIONARY - 1; k++) {
			dictionary[k] = dictionary[k + 1];
		}
		i++;
	}
}

int main() 
{
	std::string text = "rustam huesos i ebal ego rot";
	
	lzss_encode(text);	
	print_codes();
	lzss_decode();
	return 0;
}