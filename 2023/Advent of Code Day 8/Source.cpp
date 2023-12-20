#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair


void problem1() {
	std::ifstream codeFile("input.txt");
	std::string line, directions;
	std::unordered_map<std::string, std::pair<std::string, std::string>> paths;
	if (codeFile.is_open()) {
		std::getline(codeFile, directions);
		codeFile.ignore(); // ignores empty line so as to not need an if for every while iteration
		while (std::getline(codeFile, line)) {
			std::string key, dest1, dest2;
			key = line.substr(0, 3);
			dest1 = line.substr(line.find("(")+1, 3);
			dest2 = line.substr(line.find(")") - 3, 3);
			paths[key] = std::make_pair(dest1, dest2);
		}
		codeFile.close();
	}
	else {
		std::cout << "Error: File not found\n";
	}
	std::string location = "AAA";
	int index = 0, steps=  0;
	while (location != "ZZZ") {
		if (index > directions.length()-1) {
			index = 0;
		}
		char direction = directions[index];
		if (direction == 'L') {
			location = paths[location].first;
		}
		else {
			location = paths[location].second;
		}
		steps++;
		index++;
	}
	std::cout << "Part 1 Result: " << steps << "\n";
}


int main() {
	problem1();
}