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

// TODO: Write in output file

const int maxDistancePerDay = 6*60;  // 360
std::pair<std::vector<Hotel>, int> createList(const std::string& file);
int calculateDistance(const int& value, const std::vector<Hotel>& hotels);
int calculateDistance(const int& value, const std::vector<Hotel>& hotels, int index);
void makeWay(int ratingThreshold, std::vector<Hotel>& result, std::vector<Hotel>& list);

int main(int argc, char* argv[]) {
	std::vector<Hotel> hotelList;
	std::string defaultFile = "hotels2.txt";
	if (argc == 1) {
		hotelList = createList(defaultFile).first;
	} else {
		hotelList = createList((std::string)argv[1]).first;
	}
	int roadtripLength = createList(defaultFile).second;
	if (hotelList.empty()) { return 4; }

	std::vector<Hotel> result;
	int highestPossibleRating = 51;
	do {
		if (highestPossibleRating == 0) {
			std::cout << "Es gibt leider keine Möglichkeit innerhalb von fünf Tagen bzw. vier Übernachtungen nach Portugal zu fahren." << std::endl;
			return 0;
		}
		result.clear();
		highestPossibleRating -= 1;

		makeWay(highestPossibleRating, result, hotelList);
	} while (calculateDistance(roadtripLength, result) > maxDistancePerDay || result.size() > 4);

	std::cout << "Die geringste Bewertung eines Hotels ist " << std::setprecision(2) << (double)highestPossibleRating/10 << std::endl;
	std::cout << "Die Distanzen, an denen ein Hotel aufgesucht wird sind:" << std::endl;
	for (Hotel& h : result) {
		std::cout << h.getDistance() << std::endl;
	}
}


void makeWay(int ratingThreshold, std::vector<Hotel>& result, std::vector<Hotel>& list) {
	int index = 0;
	bool added = false;
	for (int i = 0; i < list.size(); i++) {
		Hotel h = list.at(i);

		if (h.getScore() < ratingThreshold) {
			continue;
		}
		if (calculateDistance(h.getDistance(), result, index-1) > maxDistancePerDay) {
			if (!added) {
				return;
			}
			index += 1;
			added = false;
			i -= 1;
			continue;
		}
		if (added) {
			result.at(index) = h;
		} else {
			result.push_back(h);
			added = true;
		}
	}
}

int calculateDistance(const int& value, const std::vector<Hotel>& hotels) {
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

std::pair<std::vector<Hotel>, int> createList(const std::string& file) {
	std::string path = "../examples/" + file;
	std::ifstream inFile(path);
	if (!inFile) return std::pair<std::vector<Hotel>, int>(std::vector<Hotel>(), -1);

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
		fileLineStorage.erase(fileLineStorage.begin()+1);
		score = std::stoi(fileLineStorage);

		Hotel temp(distance, score);
		res.push_back(temp);
	}

	return std::pair<std::vector<Hotel>, int>(res, length);
}