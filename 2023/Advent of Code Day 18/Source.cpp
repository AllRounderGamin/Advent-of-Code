#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>


void updateBounds(std::vector<int>& bounds, std::string line, std::vector<int>& coords, char direction, int distance) {
	switch (direction) {
	case 'U':
		coords[1] -= distance;
		if (-coords[1] > bounds[0]) {
			bounds[0] = -coords[1];
		}
		break;
	case 'D':
		coords[1] += distance;
		if (coords[1] > bounds[2]) {
			bounds[2] = coords[1];
		}
		break;
	case 'L':
		coords[0] -= distance;
		if (-coords[0] > bounds[3]) {
			bounds[3] = -coords[0];
		}
		break;
	case 'R':
		coords[0] += distance;
		if (coords[0] > bounds[1]) {
			bounds[1] = coords[0];
		}
		break;
	}

}


void digTrench (std::vector<std::vector<char>>& trench, std::string line, std::vector<int>& coords, char direction, int distance) {
	switch (direction) {
	case 'U':
		for (int i = 0; i <= distance; i++) {
			trench[coords[1] - i][coords[0]] = '#';
		}
		coords[1] -= distance;
		break;
	case 'D':
		for (int i = 0; i <= distance; i++) {
			trench[coords[1] + i][coords[0]] = '#';
		}
		coords[1] += distance;
		break;
	case 'L':
		for (int i = 0; i <= distance; i++) {
			trench[coords[1]][coords[0] - i] = '#';
		}
		coords[0] -= distance;
		break;
	case 'R':
		for (int i = 0; i <= distance; i++) {
			trench[coords[1]][coords[0] + i] = '#';
		}
		coords[0] += distance;
		break;
	}
}

void printMap(std::vector<std::vector<char>>& trench) {
	for (int i = 0; i < trench.size(); i++) {
		for (int j = 0; j < trench[i].size(); j++) {
			std::cout << trench[i][j];
		}
		std::cout << "\n";
	}
}


void problem1() {
	// For ease of understanding, bounds is to be read as a compass going clockwise starting at north
	std::vector<int> bounds = { 0, 0, 0, 0 }, coords = { 0, 0 };
	std::string line;
	std::ifstream codeFile("message.txt");
	if (codeFile.is_open()) {
		while (std::getline(codeFile, line)) {
			char direction = line[0];
			int distance = stoi(line.substr(line.find(" "), line.find(" ", line.find(" ") + 1)));
			updateBounds(bounds, line, coords, direction, distance);
		}
		int vecSize = bounds[0] + bounds[2] + 1;
		int rowSize = bounds[1] + bounds[3] + 1;
		std::vector<std::vector<char>> trench(vecSize, std::vector<char>(rowSize, '.'));
		// as indexing starts at 0, the point of starting is equal to the north bounding and west bounding
		std::vector<int> currentIndex = { bounds[3], bounds[0] };
		codeFile.clear();
		codeFile.seekg(0, codeFile.beg);
		
		while (std::getline(codeFile, line)) {
			char direction = line[0];
			int distance = stoi(line.substr(line.find(" "), line.find(" ", line.find(" ") + 1)));
			digTrench(trench, line, currentIndex, direction, distance);
		}
		codeFile.close();
		int result = 0, wallStart = 0;
		for (int i = 0; i < trench.size(); i++) {
			bool inside = false, wall = false;
			for (int j = 0; j < trench[i].size(); j++) {
				if (trench[i][j] == '#') {
					result++;
				}
				if (wall && trench[i][j] == '.') {
					wall = !wall;
					if (j - wallStart == 1) {
						inside = !inside;
					}
					else if (i > 0 && !(trench[i - 1][wallStart] == '#' && trench[i - 1][j - 1] == '#')) {
						if (i < trench.size() - 1 && !(trench[i + 1][wallStart] == '#' && trench[i + 1][j - 1] == '#')) {
							if (!inside) {
								trench[i][j] = ',';
								result++;
							}
							inside = !inside;
						}
					}
					if ((i > 0 && (trench[i - 1][wallStart] == '#' && trench[i - 1][j - 1] == '#')) || (i < trench.size() - 1 && (trench[i + 1][wallStart] == '#' && trench[i + 1][j - 1] == '#'))) {
						if (inside) {
							trench[i][j] = ',';
							result++;
						}
					}
				}
				else if (!wall && trench[i][j] == '#') {
					wall = !wall;
					wallStart = j;
				}
				else if (inside && trench[i][j] == '.') {
					result++;
					trench[i][j] = ',';
				}

			}
		}
		//printMap(trench);
		std::cout << "Part 1 Result: " << result << "\n";
	}
	else {
		std::cout << "File not found \n";
	}
}


void updateCoords(std::vector<long long>& coords, std::string line) {
	std::unordered_map<char, char> directionMap = { {'0', 'R'}, {'1', 'D'}, {'2', 'L'}, {'3', 'U'} };
	line = line.substr(line.find('#') + 1, std::string::npos);
	char direction = directionMap[line[5]];
	int distance{ std::stoi(line.substr(0,5), nullptr, 16) };
	switch (direction) {
	case 'U':
		coords[1] += distance;
		break;
	case 'D':
		coords[1] -= distance;
		break;
	case 'L':
		coords[0] -= distance;
		break;
	case 'R':
		coords[0] += distance;
		break;
	}
}


void problem2() {
	std::vector<long long> prevCoords = { 0, 0 }, currentCoords = { 0, 0 };
	std::unordered_map<char, char> directionMap = { {'0', 'R'}, {'1', 'D'}, {'2', 'L'}, {'3', 'U'} };
	std::string line;
	std::ifstream codeFile("input.txt");
	long long sum = 0;
	long long totDistance = 0;
	if (codeFile.is_open()) {
		std::getline(codeFile, line);
		do {
			prevCoords = currentCoords;
			updateCoords(currentCoords, line);
			sum += ((prevCoords[0] * currentCoords[1]) - (prevCoords[1] * currentCoords[0]));
			line = line.substr(line.find('#') + 1, std::string::npos);
			totDistance += std::stoi(line.substr(0, 5), nullptr, 16);
		}
		while (std::getline(codeFile, line));
		sum /= 2;
		if (sum < 0) {
			sum *= -1;
		}
		long long result = sum + totDistance / 2 + 1;
		// I do not understand why the perimeter must be halved, but this is how it works
		std::cout << "Part 2 Result: " << result << "\n";
	}
	else {
		std::cout << "File not found \n";
	}
}


int main() {
	problem1();
	problem2();
}
