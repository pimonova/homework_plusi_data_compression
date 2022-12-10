#include <iostream>
#include <map>
#include <string>

#define SIZE_DICTIONARY_BUFFER 9
#define SIZE_LOOK_AHEAD_BUFFER 5

using namespace std;

char dictionary_buffer[SIZE_DICTIONARY_BUFFER];
char look_ahead_buffer[SIZE_LOOK_AHEAD_BUFFER];
char d[1];

map<int, char> code;

void Init(string text) 
{
	if (text.size() > SIZE_LOOK_AHEAD_BUFFER) {
		for (int i = 0; i < 5; i++) {
			look_ahead_buffer[i] = text[i];
		}
	}
}

void Move(char sym)
{
	for (int i_look_ahead_buffer = 0; i_look_ahead_buffer <= SIZE_LOOK_AHEAD_BUFFER; i_look_ahead_buffer++) {
		
		if (i_look_ahead_buffer == 0) {
			
			for (int i = 7; i > 0; i--) {
				dictionary_buffer[i] = dictionary_buffer[i + 1];
			}
			dictionary_buffer[8] = look_ahead_buffer[0];
			
		}
		else {
			look_ahead_buffer[i_look_ahead_buffer - 1] = look_ahead_buffer[i_look_ahead_buffer];
			
		}
		
	}
	look_ahead_buffer[4] = sym;
	
}

void Encode(string text) 
{
	Init(text);
	for (int i = 5; i < text.size(); i++) {
		
		for (int i_dictionary_buffer = 0; i_dictionary_buffer < SIZE_DICTIONARY_BUFFER; i_dictionary_buffer++) {
			if (dictionary_buffer[i_dictionary_buffer] == text[i]) {
				code.insert(make_pair(i_dictionary_buffer, text[i]));
				break;
			}
				
		}
		if (look_ahead_buffer[0] == text[i]) {
			code.insert(make_pair(0, text[i]));
			break;
		}

		Move(text[i]);
	}

}


int main() {

	Encode("qwerty12345");
	
	cout << "qwerty12345" << endl;
	cout << look_ahead_buffer;
	return 0;
}