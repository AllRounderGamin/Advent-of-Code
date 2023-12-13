#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>


bool isValid(std::string cubeSelection) {
	std::unordered_map<std::string, int> cubeAmount = { {"red", 12}, {"green", 13}, {"blue", 14} };
	if (cubeSelection.find_first_not_of(" ") != 0) {
		cubeSelection = cubeSelection.substr(cubeSelection.find_first_not_of(" "), cubeSelection.length() - 1);
	}
	std::string number = cubeSelection.substr(0, cubeSelection.find(" "));
	std::string colour = cubeSelection.substr(cubeSelection.find(" ") + 1, cubeSelection.find_last_not_of(" "));
	std::unordered_map<std::string, int>::const_iterator found = cubeAmount.find(colour);
	if (found == cubeAmount.end()) {
		std::cout << "ERROR";
	}
	if (found->second < stoi(number)) {
		//std::cout << colour << number << "\n";
		return false;
	}
	return true;
}


bool roundCheck(std::string roundSelection) {
	size_t cubeEndPos;
	while ((cubeEndPos = roundSelection.find(",")) != std::string::npos) {
		bool checked = isValid(roundSelection.substr(0, cubeEndPos));
		if (!checked) {
			return false;
		}
		roundSelection.erase(0, cubeEndPos + 1);
	}
	bool checked = isValid(roundSelection);
	if (!checked) {
		return false;
	}
	return true;
}

void prob1() {
	std::ifstream codeFile("input.txt");
	std::string round, number, colour, roundSelection, cubeSelection;
	std::size_t endPos;
	int roundID = 1;
	int result = 0;
	bool validRound;
	if (codeFile.is_open()) {
		while (std::getline(codeFile, round)) {
			// trim off round name, roundID will keep track of what game it is
			round.erase(0, round.find(":") + 1);
			// Find position of end of the selection
			while ((endPos = round.find(";")) != std::string::npos) {
				validRound = true;
				// Strip preceeding whitespace
				roundSelection = round.substr(round.find_first_not_of(" "), endPos-1);
				bool valid = roundCheck(roundSelection);
				if (!valid) {
					validRound = false;
					break;
				}
				round.erase(0, endPos + 1);
			}
			// runs one more time as final "selection" doesnt have a semi colon at the end
			if (validRound){
				bool valid = roundCheck(round);
				if (!valid) {
					validRound = false;
				}
			}
			if (validRound) {
				result += roundID;
			}
			roundID += 1;
		}
	}
	else {
		std::cout << "Error: File Not Opened";
	}
	std::cout << result;
	codeFile.close();
}


int main() {
	prob1();
}