#pragma once

#include <iostream> 
#include <string> 

using namespace std;

struct node {
    string codw = "";
    char sym = {};
    int pro = 0;
    int top = 0;
};

void shannon(int, int, node);

void sort_by_probability(int, node);

string shennon_fano(string&);