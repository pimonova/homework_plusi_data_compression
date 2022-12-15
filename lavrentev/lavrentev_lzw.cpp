#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> table_c;
std::unordered_map<int, std::string> table_d;

std::string first_input_char, next_input_char,translation,
			char_to_str, output_str, encoded_str;
std::vector<int> output_code;

int code = 256;
int count = 256;

std::string Lavrentev_LZW(std::string input_data)
{
	//		Encoding

	for (int i = 0; i <= 255; i++) {
		char_to_str = "";
		char_to_str += char(i);
		table_c[char_to_str] = i;
	}

	first_input_char = "";
	next_input_char = "";
	encoded_str = "";

	first_input_char += input_data[0];
	
	//		Character combination
	for (int i = 0; i < input_data.length(); i++) {
		if (i != input_data.length() - 1)
			next_input_char += input_data[i + 1];
		if (table_c.find(first_input_char + next_input_char) != table_c.end()) {
			first_input_char += next_input_char;
		}
		else {
			//output_code.push_back(table_c[first_input_char]);
			encoded_str += std::to_string(table_c[first_input_char]);
			table_c[first_input_char + next_input_char] = code;
			code++;
			first_input_char = next_input_char;
		}
		next_input_char = "";
	}

	//output_code.push_back(table_c[first_input_char]);
	encoded_str += std::to_string(table_c[first_input_char]);

	//		Decoding

	// for (int i = 0; i <= 255; i++) {
	// 	char_to_str = "";
	// 	char_to_str += char(i);
	// 	table_d[i] = char_to_str;
	// }
	// int old = output_code[0], n;

	// translation = table_d[old];

	// next_input_char = "";
	// next_input_char += translation[0];
	// output_str += translation;
	
	// for (int i = 0; i < output_code.size() - 1; i++) {
	// 	n = output_code[i + 1];
	// 	if (table_d.find(n) == table_d.end()) {
	// 		translation = table_d[old];
	// 		translation += next_input_char;
	// 	}
	// 	else {
	// 		translation = table_d[n];
	// 	}
	// 	output_str += translation;
	// 	next_input_char = "";
	// 	next_input_char += translation[0];
	// 	table_d[count] += next_input_char;
	// 	count++;
	// 	old = n;
	// }

	// return (input_data == output_str);
	return encoded_str;
}



