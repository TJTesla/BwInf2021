#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Classes.h"

// TODO: Print in output file; Change iterations number

/*
 * Error codes:
 * 4: Could not reach input file
 * -4: Could not reach output file
 */

std::vector<Die> dice;
constexpr int iterations = 1000;  // Just for testing purposes; Production value should be 10000

bool getDice(const std::string& file);
void fillResult(std::vector<std::vector<int>>& r);

int main(int argc, char* argv[]) {
	std::string file = "wuerfel0.txt";
	if (argc == 2) {
		file = (std::string)argv[1];
	}
	if (!getDice(file)) {
		return 4;
	}

	std::vector<std::vector<int>> result;
	fillResult(result);

	Player ply1;
	Player ply2;
	int counter = 1;
	for (int i = 0; i < dice.size(); i++) {
		ply1.giveDie(&dice.at(i));
		for (int j = 0; j <= i; j++) {  // Rotate through every possible die combination
			ply2.giveDie(&dice.at(j));

			if (dice.at(i).gotNo6() && dice.at(j).gotNo6()) {
				continue;
			} else if (dice.at(i).gotNo6() && !dice.at(j).gotNo6()) {
				result.at(j).at(i) = iterations;  // Second player wins every game
				continue;
			} else if (dice.at(j).gotNo6() && !dice.at(i).gotNo6()) {
				result.at(i).at(j) = iterations;  // First player wins every game
				continue;
			}

			for (int k = 0; k < iterations; k++) {
				bool ply1Turn = k % 2;  // Set alternating to true and false
				int turns = 0;
				do {  // Loop for one game
					if (ply1Turn) {
						ply1.move();
						ply1.canHit(ply2);
					} else {
						ply2.move();
						ply2.canHit(ply1);
					}
					ply1Turn = !ply1Turn;
					turns++;
				} while (!(ply1.won() || ply2.won()));

				if (ply1.won()) {
					result.at(i).at(j) += 1;  // First player wins
				} else if (ply2.won()) {
					result.at(j).at(i) += 1;  // Second player wins
				}

				ply1.initialize();
				ply2.initialize();
				//std::cout << "initialized: " << counter << "; " << i << "; " << j << "; " << turns << std::endl;
				//counter++;
			}
			std::cout << "Running" << std::endl;
		}
	}

	/*
	 * Explanation of output:
	 * First: Relative wins of one cube in every game (order of cubes from input file)  // TODO: Implement this
	 * Second: Table:
	 * One row describes one cube
	 * In column can be seen its pairing with another cube
	 * Number represents relative amount of wins when playing with cube of row against cube of column
	 */
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result.size(); j++) {
			double relativeVal = (double)result.at(i).at(j)/iterations*100;
			int frontOfPoint = (int)relativeVal;
			for (int k = 0; k < 3-std::to_string(frontOfPoint).size(); k++) {
				std::cout << " ";
			}
			std::cout << std::fixed << std::setprecision(2) << (double)result.at(i).at(j)/iterations*100 << "  ";
		}
		std::cout << std::endl;
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

void fillResult(std::vector<std::vector<int>>& r) {
	for (int i = 0; i < dice.size(); i++) {
		std::vector<int> temp;
		for (int j = 0; j < dice.size(); j++) {
			temp.push_back(0);
		}
		r.push_back(temp);
	}
}
