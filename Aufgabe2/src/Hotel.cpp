//
// Created by Theodor Teslia on 08.10.21.
//

#include "Hotel.h"

Hotel::Hotel(int d, int s) {
	this->distance = d;
	this->score = s;
}

int Hotel::getDistance() const {
	return this->distance;
}

int Hotel::getScore() const {
	return this->score;
}