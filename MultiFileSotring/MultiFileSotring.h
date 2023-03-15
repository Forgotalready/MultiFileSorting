#ifndef MULTIFILESOTRING_MULTIFILESOTRING_H
#define MULTIFILESOTRING_MULTIFILESOTRING_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <utility>

using std::cin, std::cout, std::fstream, std::string, std::vector;

void divide(const string& name, vector <string>& out_names);

vector<string> generate_file_names(int n);

void create_file(const string& name);

void gen_rand_file(const string& name, int n);

std::pair<bool, int> isSortAndCount(const string& name);

void name(vector<string> &name, int n);

void merge(vector<string> &names);

int Min(vector<int>&x, int n);

#endif //MULTIFILESOTRING_MULTIFILESOTRING_H
