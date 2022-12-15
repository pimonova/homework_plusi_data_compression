#include <string>
#include <iostream>
#include "arith_Stepura.h"
#include "arith_code_function_Stepura.h"

std::string arith_cod(std::string& in)
{
	arithmetic coding;
	coding.input_string(in);
	coding.get_abc();
	coding.get_frequency();
	coding.encode_text();
	return coding.get_encode();
}