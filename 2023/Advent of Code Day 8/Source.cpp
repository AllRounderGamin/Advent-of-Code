#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair

long long lcm_of_array(std::vector<int>);

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


void problem2() {
	std::ifstream codeFile("input.txt");
	std::string line, directions;
	std::unordered_map<std::string, std::pair<std::string, std::string>> paths;
	std::vector<std::string> trackedNodes;
	if (codeFile.is_open()) {
		std::getline(codeFile, directions);
		codeFile.ignore(); // ignores empty line so as to not need an if for every while iteration
		while (std::getline(codeFile, line)) {
			std::string key, dest1, dest2;
			key = line.substr(0, 3);
			dest1 = line.substr(line.find("(") + 1, 3);
			dest2 = line.substr(line.find(")") - 3, 3);
			paths[key] = std::make_pair(dest1, dest2);
			if (key[2] == 'A') {
				trackedNodes.push_back(key);
			}
		}
		codeFile.close();
	}
	else {
		std::cout << "Error: File not found\n";
	}
	std::vector<int> minSteps;
	for (std::string node : trackedNodes) {
		std::string location = node;
		int index = 0, steps = 0;
		while (location[2] != 'Z') {
			if (index > directions.length() - 1) {
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
		minSteps.push_back(steps);
	}
	long long result2 = lcm_of_array(minSteps);

	std::cout << "Part 2 Result: " << result2 <<  "\n";
}

// Code below this point from: https://www.geeksforgeeks.org/lcm-of-given-array-elements/ Method 4 (Method 3 interestingly returned a significantly lower result?)

long long gcd(long long num1, long long num2)
{
	if (num2 == 0)
		return num1;
	return gcd(num2, num1 % num2);
}

long long lcm_of_array(std::vector<int> arr)
{
	long long lcm = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		long long num1 = lcm;
		long long num2 = arr[i];
		long long gcd_val = gcd(num1, num2);
		lcm = (lcm * arr[i]) / gcd_val;
	}
	return lcm;
}



int main() {
	problem1();
	problem2();
}