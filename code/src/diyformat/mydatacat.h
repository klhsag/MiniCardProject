#pragma once

/****************************************
**提供link_str函数
**拼接字符串和序号生成唯一字符串索引
**附加解析函数
****************************************/

#include <string>
#include <utility>

#include "mystrsplit.h"

template<typename T>
std::string link_str(T arg){
    return diytostr(arg);
}

template<typename T, typename ... Args>
std::string link_str(T arg0, Args... args){
    return diytostr(arg0)+"."+link_str(args...);
}

inline auto break_str(std::string src)->decltype(split(src,".")) {
    return split(src, ".");
}

inline int str_to_int(std::string src){
    std::stringstream stream;
    int result;
    stream << src;
    stream >> result;
    return result;
}

inline std::string str_with_int(std::string arg1, int arg2){
    return link_str(arg1, arg2);
}

inline std::pair<std::string, int> str_split_int(std::string src){
    auto strv = break_str(src);
    int length = strv.size();
    switch (length){
    case 0:{
        return {"", 0};
    }
    case 1:{
        return {strv[0], 0};
    }
    default:
        std::string first = strv[0];
        for (int i=1; i<length-1; ++i) first += strv[i];
        return {first, str_to_int(strv[length-1])};
    }
}
