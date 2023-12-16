#include <string>
#include <iostream>
#include <fstream>


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

void prob2() {
	std::ifstream codeFile("input.txt");
	std::string line;
	std::size_t endPos;
	if (codeFile.is_open()) {
		std::getline(codeFile, line);
	}
	else {
		std::cout << "Error: File Not Opened";
	}
}



int main() {
	prob1();
}