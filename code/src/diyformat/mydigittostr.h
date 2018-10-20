#pragma once

/****************************************
**提供diytostr函数, 把任意类型变量转换为字符串
**以便参与string拼接运算
**该类型必须已有相应的运算符重载
****************************************/

#include <sstream>
#include <string>

inline std::string trim(std::string s) {
	if (s.empty()) {
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

template<typename T>
std::string diytostr(T &&src){
    std::stringstream stream;
    std::string result;
    stream << src;
    stream >> result;
    return result;
}
