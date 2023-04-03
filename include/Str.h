//
// Created by User on 2023/3/29.
//

#ifndef STUDYCXX_STR_H
#define STUDYCXX_STR_H

#include "Vec.h"
#include <cstring>

class Str {
public:
    typedef Vec<char>::size_type size_type;

    Str() {}

    Str(size_type n, char c) : data(n, c) {}

    Str(const char *cp) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }

    template<class In>
    Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }

    size_type size() const { return data.size(); }

//    std::ostream &operator<<(std::ostream &os, const Str &s);
//    需要访问Str内部私有成员,定义为友元函数
    friend std::istream &operator>>(std::istream &is, Str &s);

//    += 运算符左值+右值，并把结果赋值给左值，所以可把+=重载函数作为成员函数
    Str &operator+=(const Str &s) {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }

    char &operator[](size_type i) { return data[i]; }

    const char &operator[](size_type i) const { return data[i]; }

private:
    Vec<char> data;
};

std::istream &operator>>(std::istream &is, Str &s) {
    s.data.clear();
    char c;
    while (is.get(c) && isspace(c));//空字符忽略
    if (is) {
        do {
            s.data.push_back(c);//重复读取字符，直到遇到空格字符
        } while (is.get(c) && !isspace(c));
    }
    return is;
}

//操作符左值需要作为参数传入，方法不能定义在类内部
std::ostream &operator<<(std::ostream &os, const Str &s) {
    for (Str::size_type i = 0; i < s.size(); ++i) {
        os << s[i];
    }
    return os;
}

//operator+ 需要生成新的对象，不改变参数原来的值
Str operator+(const Str &s, const Str &t) {
    //复制s赋值给r
    Str r = s;
    r += t;
    return r;
}

#endif //STUDYCXX_STR_H
