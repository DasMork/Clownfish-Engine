#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace clownfish {

	static std::vector<std::string> split_string(const std::string &string, char delimiter) {
		std::vector<std::string> elems;
		std::stringstream ss(string);
		std::string item;
		while(std::getline(ss,item,delimiter))
		{
			elems.push_back(item);
		}
		return elems;
	
	}

}