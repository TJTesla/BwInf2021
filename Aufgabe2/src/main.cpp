#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Hotel.h"

/*
 * Error codes:
 * 4: Could not reach input file
 * -4: Could not reach output file
 */

constexpr int maxDistancePerDay = 6*60;  // 360
constexpr int maxTripLength = 5;  // In days, not hotels

std::pair<std::vector<Hotel>, int> createList(const std::string& file);
int calculateDistance(const int& value, const std::vector<Hotel>& hotels);
int calculateDistance(const int& value, const std::vector<Hotel>& hotels, int index);
void makeWay(int ratingThreshold, std::vector<Hotel>& result, std::vector<Hotel>& list, const int& tripLength);
bool printOutResult(const std::vector<Hotel>& result, const std::string& file, const int& ratingThreshold);
bool printOutFailure(const std::string& file);

int main(int argc, char* argv[]) {
	std::vector<Hotel> hotelList;
	std::string file = "hotels1.txt";  // Input default file
	if (argc == 2) {
		file = (std::string)argv[1];
	}
	hotelList = createList(file).first;
	int roadtripLength = createList(file).second;
	if (hotelList.empty()) {
		return 4;
	}

	std::vector<Hotel> result;
	int highestPossibleRating = 51;
	do {
		if (highestPossibleRating == 0) {
			std::cout << "Es gibt leider keine Möglichkeit innerhalb von fünf Tagen bzw. vier Übernachtungen nach Portugal zu fahren." << std::endl;
			if (!printOutFailure(file)) {
				return -4;
			}

			return 0;
		}
		result.clear();  // Initialize values
		highestPossibleRating -= 1;

		makeWay(highestPossibleRating, result, hotelList, roadtripLength);
	} while (calculateDistance(roadtripLength, result) > maxDistancePerDay || result.size() >= maxTripLength);

	std::cout << "Die geringste Bewertung eines Hotels ist " << std::setprecision(2) << (double)highestPossibleRating/10 << std::endl;
	std::cout << "Die Distanzen, an denen ein Hotel aufgesucht wird sind:" << std::endl;
	for (Hotel& h : result) {
		std::cout << h.getDistance() << std::endl;
	}

	if (!printOutResult(result, file, highestPossibleRating)) {
		return -4;
	}

	return 0;
}


void makeWay(int ratingThreshold, std::vector<Hotel>& result, std::vector<Hotel>& list, const int& tripLength) {  // Main algorithm
	int index = 0;  // Marks index in result that gets changed
	bool added = false;
	for (int i = 0; i < list.size(); i++) {
		Hotel h = list.at(i);

		if (h.getScore() < ratingThreshold) {
			continue;
		}
		if (calculateDistance(h.getDistance(), result, index-1) > maxDistancePerDay) {  // If hotel is to far -> Start new cycle
			if (!added) {
				return;
			}
			index += 1;  // Enter last hotel that was near and good enough
			added = false;
			i -= 1;  // Try again with same hotel
			if (calculateDistance(tripLength, result) <= maxDistancePerDay) {
				return;  // Check whether already existing list is sufficient
			}
			continue;
		}
		if (added) {
			result.at(index) = h;
		} else {  // If first hotel in cycle -> push_back
			result.push_back(h);
			added = true;
		}
	}
}

int calculateDistance(const int& value, const std::vector<Hotel>& hotels) {  // Basic subtraction; But when vector is empty -> Avoid error
	if (hotels.empty()) {
		return value - 0;
	}
	return value - hotels.at(hotels.size()-1).getDistance();
}

int calculateDistance(const int& value, const std::vector<Hotel>& hotels, int index) {
	if (hotels.empty() || index < 0) {
		return value - 0;
	}
	return value - hotels.at(index).getDistance();
}

std::pair<std::vector<Hotel>, int> createList(const std::string& file) {  // Get input
	std::string path = "../examples/" + file;
	std::ifstream inFile(path);
	if (!inFile) {
		return std::pair<std::vector<Hotel>, int>(std::vector<Hotel>(), -1);
	}

	std::string fileLineStorage;

	std::getline(inFile, fileLineStorage);
	int amount = std::stoi(fileLineStorage);

	std::getline(inFile, fileLineStorage);
	int length = std::stoi(fileLineStorage);

	std::vector<Hotel> res;
	int distance, score;
	for (int i = 0; i < amount; i++) {
		inFile >> fileLineStorage;
		distance = std::stoi(fileLineStorage);

		inFile >> fileLineStorage;
		fileLineStorage.erase(fileLineStorage.begin()+1);  // Delete decimal point -> Same as multiplication w/ 10
		score = std::stoi(fileLineStorage);  // Avoids problems with floating point precision

		Hotel temp(distance, score);
		res.push_back(temp);
	}

	return std::pair<std::vector<Hotel>, int>(res, length);
}

bool printOutResult(const std::vector<Hotel>& result, const std::string& file, const int& ratingThreshold) {
	std::string path = "../out/" + file;
	std::ofstream outFile(path);
	if (!outFile) {
		std::cout << "Could not reach output file" << std::endl;
		return false;
	}

	outFile << "Die geringste Bewertung eines Hotels ist " << std::setprecision(2) << (double)ratingThreshold/10 << std::endl;
	outFile << "Die Distanzen, an denen ein Hotel aufgesucht wird sind:" << std::endl;
	for (Hotel h : result) {
		outFile << h.getDistance() << std::endl;
	}

	return true;
}

bool printOutFailure(const std::string& file) {
	std::string path = "../out/" + file;
	std::ofstream outFile(path);
	if (!outFile) {
		std::cout << "Could not reach output file" << std::endl;
		return false;
	}

	outFile << "Es gibt leider keine Möglichkeit innerhalb von fünf Tagen bzw. vier Übernachtungen nach Portugal zu fahren." << std::endl;
	return true;
}
