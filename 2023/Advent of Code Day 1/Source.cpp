#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>    // std::find_first_of

void prob1() {
	std::string code, num1, num2, value;
	int result = 0;
	std::ifstream codeFile ("input.txt");
	if (codeFile.is_open()) {
		while (std::getline(codeFile, code)) {
			for (int i = 0; i < code.length(); i++) {
				if (std::isdigit(code[i])) {
					num1 = code[i];
					break;
				}
			}
			for (int i = code.length()-1; i >= 0; i--) {
				if (std::isdigit(code[i])) {
					num2 = code[i];
					break;
				}
			}
			value = num1 + num2;
			result += std::stoi(value);
		}
	}
	codeFile.close();
	std::cout << "Part 1 Result: " << result << "\n";
}

void prob2() {
	std::string code, num1, num2, value, key;
	int index;
	int result = 0;
	std::unordered_map<std::string, std::string> numbers = { {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"} };
	std::vector<std::string> keys = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::ifstream codeFile("input.txt");
	if (codeFile.is_open()) {
		while (std::getline(codeFile, code)) {
			index = code.length();
			for (std::string x : keys) {
				std::size_t location = code.find(x);
				if (location != std::string::npos && location < index) {
					index = location;
					key = x;
				}
			}
			std::unordered_map<std::string, std::string>::iterator entry = numbers.find(key);
			if (entry != numbers.end()) {
				num1 = entry->second;
			}
			else {
				num1 = key;
			}
			index = 0;
			for (std::string x : keys) {
				std::size_t location = code.rfind(x);
				if (location != std::string::npos && location > index) {
					index = location;
					key = x;
				}
			}
			entry = numbers.find(key);
			if (entry != numbers.end()) {
				num2 = entry->second;
			}
			else {
				num2 = key;
			}
			value = num1 + num2;
			result += std::stoi(value);
		}
	}
	codeFile.close();
	std::cout << "Part 2 Result: " << result << "\n";
}


int main() {
	prob1();
	prob2();
	return 0;
}