#pragma once

// 2023/7/18
// 用户自定义字面量：尾缀
unsigned long long operator "" _w1(unsigned long long n) {
	return n;
}

const char* operator "" _w2(const char* str) {
	return str;
}

long double operator "" _w3(long double d) {
	return d;
}

#include <string>
std::string operator "" _w4(const char* str, size_t len) {
	return str;
}

char operator "" _w5(char n) {
	return n;
}

template <char...c> std::string operator "" _w6() {
	std::string str;
	(str.push_back(c), ...);
	return str;
}