//
// Created by Theodor Teslia on 08.10.21.
//

#ifndef AUFGABE2_HOTEL_H
#define AUFGABE2_HOTEL_H


class Hotel {
private:
	int distance;
	int score;
public:
	Hotel(int d, int s);
	~Hotel() = default;
	[[nodiscard]] int getDistance() const;
	[[nodiscard]] int getScore() const;
};


#endif //AUFGABE2_HOTEL_H
