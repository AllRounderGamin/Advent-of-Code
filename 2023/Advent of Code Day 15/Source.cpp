#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>


void prob1() {
	std::ifstream codeFile("input.txt");
	std::string line;
	int value = 0, result = 0;
	if (codeFile.is_open()) {
		std::getline(codeFile, line);
		for (int i = 0; i < line.length(); i++) {
			char character = line[i];
			if (character != ',') {
				value += int(character);
				value *= 17;
				value %= 256;
			}
			else if (character == ',') {
				result += value;
				value = 0;
			}
		}
		result += value;
	}
	else {
		std::cout << "Error: File Not Opened";
	}
	std::cout << "Part 1 Result: " << result << "\n";
}

int hash_string(std::string string) {
	int value = 0;
	for (int i = 0; i < string.length(); i++) {
		char character = string[i];
		value += int(character);
		value *= 17;
		value %= 256;
	}
	return value;
}

void handle_code(std::string code, std::unordered_map<int, std::vector<std::string>>& boxes) {
	int hash;
	size_t codeEndPos;
	if ((codeEndPos = code.find("=")) != std::string::npos) {
		hash = hash_string(code.substr(0, codeEndPos));
		if (boxes.find(hash) != boxes.end()) {
			// Creates input as, values of code from 0 to the =/-, a space, and then the rest of the code string
			std::string input = (code.substr(0, codeEndPos).append(" ").append(code.substr(codeEndPos + 1, std::string::npos)));
			for (std::vector<std::string>::iterator it = boxes[hash].begin(); it != boxes[hash].end(); it++) {
				if ((*it).substr(0, (*it).find(" ")) == code.substr(0, codeEndPos)) {
					*it = input;
					return;
				}
			}
			boxes[hash].push_back(input);
		}
		else {
			std::vector<std::string> input;
			input.push_back(code.substr(0, codeEndPos).append(" ").append(code.substr(codeEndPos + 1, std::string::npos)));
			boxes[hash] = input;
		}
	}
	else if ((codeEndPos = code.find("-")) != std::string::npos) {
		hash = hash_string(code.substr(0, codeEndPos));
		if (boxes.find(hash) != boxes.end()) {
			for (std::vector<std::string>::iterator it = boxes[hash].begin(); it != boxes[hash].end(); it++) {
				if ((*it).substr(0, (*it).find(" ")) == code.substr(0, codeEndPos)) {
					boxes[hash].erase(it);
					return;
				}
			}
		}
	}
}

void prob2() {
	std::ifstream codeFile("input.txt");
	std::string line, code;
	std::size_t endPos;
	int result = 0;
	std::unordered_map<int, std::vector<std::string>> boxes;
	if (codeFile.is_open()) {
		std::getline(codeFile, line);
		while ((endPos = line.find(",")) != std::string::npos) {
			code = line.substr(0, endPos);
			handle_code(code, boxes);
			line.erase(0, endPos+1);
		}
		handle_code(line, boxes);
		for (std::unordered_map<int, std::vector<std::string>>::iterator boxit = boxes.begin(); boxit != boxes.end(); boxit++) {
			int boxNum = boxit->first + 1;
			int lensNum = 1;
			for (std::vector<std::string>::iterator vecit = boxit->second.begin(); vecit != boxit->second.end(); vecit++) {
				int focalStr = stoi((*vecit).substr((*vecit).find(" "), std::string::npos));
				result = result + (boxNum * lensNum * focalStr);
				lensNum++;
			}
		}
	}
	else {
		std::cout << "Error: File Not Opened";
	}
	std::cout << "Part 2 Result: " << result << "\n";
}



int main() {
	prob1();
	prob2();
}