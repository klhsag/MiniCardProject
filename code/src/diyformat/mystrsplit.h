#pragma once

/****************************************
**提供split函数, 把string分割为vector<string>
**可自定义分隔符集合，只支持单字符分割
**内置trim函数移除每个子串前后空格
****************************************/

#include <string>
#include <vector>

#include "mydigittostr.h"

inline std::vector<std::string> split(const std::string &s, const std::string &seperator) {
	std::vector<std::string> result;
	using string_size = std::string::size_type;
	string_size i = 0;
	while (i != s.size()) {
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0) ++j;
		}
		if (i != j) {
		    std::string str = trim(s.substr(i, j - i));
            if (str.size()>0) result.push_back(std::move(str));
			i = j;
		}
	}
	return result;
}
