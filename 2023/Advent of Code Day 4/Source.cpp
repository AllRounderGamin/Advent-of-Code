#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::find

void cardSplit(std::vector<int>& vec, std::string string) {
	std::string input;
	while (string.length() > 3) {
		input = string.substr(0, 2);
		vec.push_back(stoi(input));
		string = string.substr(3, std::string::npos);
	}
	// Run once more to get final number (string.length() is 2, which would cause the substr to be out of range, but a space will be found if its single digit hence using length not .find(" ") for condition)
	vec.push_back(stoi(string));
	return;
}

void problem1() {
	std::ifstream codeFile("input.txt");
	std::string card;
	int cardScore = 0, result = 0;
	std::vector<int> cardNums, winningNums;
	while (std::getline(codeFile, card)) {
		cardNums.clear();
		winningNums.clear();
		cardScore = 0;
		card = card.substr(card.find(":") + 2, std::string::npos);
		cardSplit(cardNums, card.substr(0, card.find("|")));
		cardSplit(winningNums, card.substr(card.find("|") + 2));
		for (int num : winningNums) {
			if (std::find(cardNums.begin(), cardNums.end(), num) != cardNums.end()) {
				if (cardScore > 1) {
					cardScore *= 2;
				}
				else {
					cardScore++;
				}
			}
		}
		result += cardScore;
	}
	std::cout << "Part 1 Result: " << result << "\n";
}

int main() {
	problem1();
}