#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::find
#include <unordered_map>

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

// have a map that will store card id's and how many times they need to be repeated, can get id from find : - 1

void calculateDupe(std::unordered_map<int, int>& playMap, int score, int ID) {
	for (int i = 1; i < score+1; i++) {
		if (ID + i > 216) {
			return;
		}
		else {
			if (playMap.find(ID+i) == playMap.end()) {
				// 1 original + the added dupe
				playMap[ID + i] = 2;
			}
			else {
				playMap[ID + i] += 1;
			}
		}
	}
}


void problem2() {
	std::ifstream codeFile("input.txt");
	std::string card;
	int cardScore, plays, result = 0;
	std::vector<int> cardNums, winningNums;
	std::unordered_map<int, int> playValues;
	while (std::getline(codeFile, card)) {
		int cardID = stoi(card.substr(card.find(" "), (card.find(":") - card.find(" "))));
		if (playValues.find(cardID) == playValues.end()) {
			playValues[cardID] = 1;
		}
		plays = 0;
		cardNums.clear();
		winningNums.clear();
		card = card.substr(card.find(":") + 2, std::string::npos);
		cardSplit(cardNums, card.substr(0, card.find("|")));
		cardSplit(winningNums, card.substr(card.find("|") + 2));
		cardScore = 0;
		for (int num : winningNums) {
			if (std::find(cardNums.begin(), cardNums.end(), num) != cardNums.end()) {
				cardScore++;
			}
		}
		do {
			calculateDupe(playValues, cardScore, cardID);
			plays++;
		} while (plays < playValues[cardID]);
	}
	for (auto const& x : playValues) {
		result += x.second;
	}
	std::cout << "Part 2 Result: " << result << "\n";
}


int main() {
	problem1();
	problem2();
}