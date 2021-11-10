#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

#include "Classes.h"

/*
 * Error codes:
 * 4: Could not reach input file
 * 5: Could not reach output file
 */

std::vector<Die> dice;
constexpr int iterations = 10000;  // Just for testing purposes; Production value should be 10000

bool getDice(const std::string& file);
void fillResult(std::vector<std::vector<int>>& r, std::vector<int>& generalR);
bool output(const std::string& file, const std::vector<std::vector<int>>& result, const std::vector<int>& absoluteWins);
bool determineWinable(Player& ply);


int main(int argc, char* argv[]) {
	std::string file = "wuerfel0.txt";
	if (argc == 2) {
		file = (std::string)argv[1];
	}
	if (!getDice(file)) {
		return 4;
	}

	std::vector<std::vector<int>> result;
	std::vector<int> absoluteWins;
	fillResult(result, absoluteWins);

	Player ply1;
	Player ply2;
	int longestMatch = 0;
	for (int i = 0; i < dice.size(); i++) {
		ply1.giveDie(&dice.at(i));
		for (int j = 0; j <= i; j++) {  // Rotate through every possible die combination
			ply2.giveDie(&dice.at(j));

			if (dice.at(i).gotNo6() && dice.at(j).gotNo6()) {
				continue;
			} else if (dice.at(i).gotNo6() && !dice.at(j).gotNo6()) {
				result.at(j).at(i) = iterations;  // Second player wins every game
				absoluteWins.at(j) = iterations;
				continue;
			} else if (dice.at(j).gotNo6() && !dice.at(i).gotNo6()) {
				result.at(i).at(j) = iterations;  // First player wins every game
				absoluteWins.at(i) = iterations;
				continue;
			}

			for (int k = 0; k < iterations; k++) {
				bool ply1Turn = k % 2;  // Set alternating to true and false
				int turns = 0;
				int notMovedSince = 0;
				do {  // Loop for one game
					if (ply1Turn) {
						if (ply1.move()) {
							notMovedSince = 0;
						} else {
							notMovedSince += 1;
						}
						ply1.canHit(ply2);
					} else {
						if (ply2.move()) {
							notMovedSince = 0;
						} else {
							notMovedSince += 1;
						}
						ply2.canHit(ply1);
					}
					ply1Turn = !ply1Turn;
					if (turns >= 500) {  // Game is going very long -> Check if there is a softlock
						if (!determineWinable(ply1) && !determineWinable(ply2)) {
							break;
						}
					}
					if (notMovedSince >= 200) {  // If there was no movement for 200 turns -> Only very slim chance there is no softlock
						break;  // In reality a game would be quit if nobody moved for 200 turns as well
					}
					turns++;
				} while (!(ply1.won() || ply2.won()));

				if (ply1.won()) {
					result.at(i).at(j) += 1;  // First player wins
					absoluteWins.at(i) += 1;
				} else if (ply2.won()) {
					result.at(j).at(i) += 1;  // Second player wins
					absoluteWins.at(j) += 1;
				}

				ply1.initialize();
				ply2.initialize();
			}
			std::cout << "Running" << std::endl;
		}
	}
	/*
	 * Explanation of output:
	 * First Column: Relative wins of one cube in every game (order of cubes from input file); Movement: Downwards
	 * Second: Table:
	 * One row describes one cube
	 * In column can be seen its pairing with another cube
	 * Number represents relative amount of wins when playing with cube of row against cube of column
	 */
	if (!output(file, result, absoluteWins)) {
		return 5;
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

void fillResult(std::vector<std::vector<int>>& r, std::vector<int>& generalR) {
	for (int i = 0; i < dice.size(); i++) {
		std::vector<int> temp;
		for (int j = 0; j < dice.size(); j++) {
			temp.push_back(0);
		}
		r.push_back(temp);
		generalR.push_back(0);
	}
}

bool determineWinable(Player& ply) {
	std::set<int> unoccupied = ply.unoccupiedFinish();

	for (Figure f : ply.getFigures()) {
		for (auto i = unoccupied.begin(); i != unoccupied.end(); i++) {
			if (ply.getDie().has(*i - f.getPosition()) || *i - f.getPosition() > ply.getDie().smallest()) {
				return true;
			}
		}
	}

	return false;
}

bool output(const std::string& file, const std::vector<std::vector<int>>& result, const std::vector<int>& absoluteWins) {
	std::string path = "../out/" + file;
	std::ofstream outFile(path);
	if (!outFile) {
		return false;
	}

	int numberOfMatches = 0;
	std::vector<std::string> winStringBuffer;
	for (int i : absoluteWins) {
		numberOfMatches += i;
	}
	for (int i = 0; i < absoluteWins.size(); i++) {
		double relativeVal = (double)absoluteWins.at(i)/numberOfMatches*100;
		int frontOfPoint = (int)relativeVal;
		std::string str = "";
		for (int k = 0; k < 3-std::to_string(frontOfPoint).size(); k++) {
			str += " ";
		}
		winStringBuffer.push_back(str);
	}

	for (int i = 0; i < result.size(); i++) {
		std::cout << std::fixed << std::setprecision(2) << winStringBuffer.at(i) << (double)absoluteWins.at(i)/numberOfMatches*100 << ":  ";
		outFile << std::fixed << std::setprecision(2) << winStringBuffer.at(i) << (double)absoluteWins.at(i)/numberOfMatches*100 << ":  ";
		for (int j = 0; j < result.size(); j++) {
			double relativeVal = (double)result.at(i).at(j)/iterations*100;
			int frontOfPoint = (int)relativeVal;
			for (int k = 0; k < 3-std::to_string(frontOfPoint).size(); k++) {
				std::cout << " ";
				outFile << " ";
			}
			std::cout << std::fixed << std::setprecision(2) << (double)result.at(i).at(j)/iterations*100 << "  ";
			outFile << std::fixed << std::setprecision(2) << (double)result.at(i).at(j)/iterations*100 << "  ";
		}
		std::cout << std::endl;
		outFile << std::endl;
	}

	return true;
}
