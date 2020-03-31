#pragma once
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

std::string read_large_file(int index);
std::vector<int> get_multiples(int x);
void consume_multiples(std::map<int, std::vector<int>> m);
void moving_into_containers();
void moving_containers_instead_of_copying();