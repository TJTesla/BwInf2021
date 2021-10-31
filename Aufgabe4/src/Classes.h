//
// Created by Theodor Teslia on 26.10.21.
//

#ifndef AUFGABE4_CLASSES_H
#define AUFGABE4_CLASSES_H

#include <vector>
#include <array>
#include <ctime>
#include <random>
#include <algorithm>

constexpr int boardLength = 44;

class Die {
private:
	std::vector<int> sides;
public:
	explicit Die(const std::vector<int>& pSides);
	int roll();
};


enum Fields {
	RUNWAY, B
};


class Figure {
private:
	int position;
	Fields field;
public:
	Figure();
	void moveBy(int val);
	void setField(Fields pField);
	void setPosition(int pos);
	[[nodiscard]] int getPosition() const;
	[[nodiscard]] Fields getField() const;

	bool operator< (const Figure& f2) const;
};


class Player {
private:  // Attributes
	Die* currentDie;
	std::array<Figure*, boardLength> board{};
	std::array<Figure, 4> figs;
	bool alreadyMovedInTurn;

private:  // Functions
	bool everythingOn(Fields type);
	void changePosition(int index, int amount);
	void fillActivePlayers(std::vector<Figure*>& vct);

public:
	Player();
	~Player() = default;
	void move();
	void canHit(Player& ply2);
	bool won();
	void giveDie(Die* newDie);

	[[nodiscard]] std::array<Figure*, boardLength> getBoard() const;
	[[nodiscard]] std::array<Figure, 4> getFigures() const;
};

#endif //AUFGABE4_CLASSES_H
