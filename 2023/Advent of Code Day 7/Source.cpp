#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>


void problem1() {
	std::ifstream codeFile("input.txt");
	std::unordered_map<std::string, int> handWorth;
	std::string hand;
	if (codeFile.is_open()) {
		while (std::getline(codeFile, hand)) {
			std::string card;
			int bet;
			card = hand.substr(0, hand.find(" "));
			bet = stoi(hand.substr(hand.find(" ") + 1, std::string::npos));
		}
	}
	else {
		std::cout << "Error: File not found \n";
	}
}


int main() {

}