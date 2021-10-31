#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Classes.h"

/*
 * Error codes:
 * 4: Could not reach input file
 * -4: Could not reach output file
 */

std::vector<Die> dice;
constexpr int iterations = 100000;

bool getDice(const std::string& file);
void fillResult(std::vector<std::vector<double>>& r);

int main(int argc, char* argv[]) {
	std::string file = "wuerfel0.txt";
	if (argc == 2) {
		file = (std::string)argv[1];
	}
	if (!getDice(file)) {
		return 4;
	}

	std::vector<std::vector<double>> result;
	fillResult(result);

	Player ply1;
	Player ply2;

	for (int i = 0; i < dice.size(); i++) {
		ply1.giveDie(&dice.at(i));
		for (int j = 0; j < i; j++) {
			ply2.giveDie(&dice.at(j));

			// TODO: Spielablauf
		}
	}

	return 0;
}

bool getDice(const std::string& file) {
	std::string path = "../examples/" + file;
	std::ifstream inFile(path);
	if (!inFile) {
		return false;
	}

	std::string holder;
	inFile >> holder;
	int diceAmount = std::stoi(holder);

	for (int i = 0; i < diceAmount; i++) {
		std::vector<int> temp;

		inFile >> holder;
		int sideAmount = std::stoi(holder);
		for (int j = 0; j < sideAmount; j++) {
			inFile >> holder;
			temp.push_back(std::stoi(holder));
		}

		dice.emplace_back(temp);
	}

	return true;
}

void fillResult(std::vector<std::vector<double>>& r) {
	for (int i = 0; i < dice.size(); i++) {
		std::vector<double> temp;
		for (int j = 0; j < i; j++) {
			temp.push_back(-1.0);
		}
		r.push_back(temp);
	}
}
