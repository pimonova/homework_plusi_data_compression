#include <iostream>
#include <string>
#include "mustafaev/lzss.h"
#include "lavrentev/lavrentev_lzw.h"

using namespace std;

int main() {
	string text = "12312312312";
	lzss_encode(text);
	lzw(text);
	return 0;
}