//
// Created by Theodor Teslia on 26.10.21.
//

#include "Classes.h"


Die::Die(const std::vector<int>& pSides) {
	this->sides = pSides;
	srand((unsigned)time(nullptr));

	this->has6 = false;
	for (int& s : this->sides) {
		if (s == 6) {
			this->has6 = true;
			break;
		}
		sidesSet.insert(s);
	}
}

int Die::roll() {
	return sides.at(rand() % sides.size());
}

bool Die::has(int num) {
	return sidesSet.find(num) != sidesSet.end();
}

bool Die::gotNo6() const {
	return !has6;
}

int Die::smallest() const {
	return *(sidesSet.begin());
}


Figure::Figure() {
	this->position = -1;
	this->field = Fields::B;
}

void Figure::moveBy(int val) {
	this->position += val;
}

void Figure::setField(Fields pField) {
	this->field = pField;
}

void Figure::setPosition(int pos) {
	this->position = pos;
}

int Figure::getPosition() const {
	return this->position;
}

Fields Figure::getField() const {
	return this->field;
}

bool Figure::operator< (const Figure& f2) const {
	if (this->position == f2.position) {
		return this->getField() == Fields::RUNWAY;
	}
	return this->position > f2.position;
}


Player::Player() {
	this->currentDie = nullptr;
	this->occupiedSpaces = std::set<int>();
	this->figs = std::array<Figure, 4>();
	this->alreadyMovedInTurn = false;

	std::fill_n(this->figs.begin(), 4, Figure());

	occupiedSpaces.insert(0);
	figs.at(0).setField(Fields::RUNWAY);
	figs.at(0).setPosition(0);

	sortFigures();
}

bool Player::move() {
	if (this->currentDie == nullptr) {
		return false;
	}
	this->alreadyMovedInTurn = false;
	bool changed = false;

	int dieResult = this->currentDie->roll();

	if (onField(0)) {  // Still figure on start field -> Needs to be moved away
		for (int i = figs.size() - 1; i >= 0; i--) {  // Start from last figure
			int nextPosition = figs.at(i).getPosition() + dieResult;
			if (nextPosition <= boardLength-1 && !onField(nextPosition) && figs.at(i).getField() == Fields::RUNWAY) {
				changePosition(i, dieResult);
				changed = true;
				break;
			}
		}

		if (dieResult == 6) {
			this->move();
		}
		return changed;
	}

	if (dieResult == 6 && !everythingOn(Fields::RUNWAY)) {  // Set figure from B field on runway
		int firstOnBIndex = -1;
		for (int i = 0; i < figs.size(); i++) {
			if (figs.at(i).getField() == Fields::B) {
				firstOnBIndex = i;
				break;
			}
		}
		if (firstOnBIndex != -1) {
			figs.at(firstOnBIndex).setField(Fields::RUNWAY);
			figs.at(firstOnBIndex).setPosition(0);
			occupiedSpaces.insert(0);
			changed = true;

			sortFigures();
			this->alreadyMovedInTurn = true;

			this->move();
			return changed;
		}
	}

	if (dieResult != 6 && everythingOn(Fields::B)) {  // Everything on B and no 6 -> Nothing can move out
		return changed;
	}
	for (int i = 0; i < figs.size(); i++) {  // Search for first element that can move
		int nextPos = figs.at(i).getPosition() + dieResult;

		if (nextPos <= boardLength-1 && !onField(nextPos) && figs.at(i).getField() == Fields::RUNWAY) {
			changePosition(i, dieResult);
			changed = true;
			break;
		}
	}

	if (dieResult == 6) {
		this->move();
	}
	return changed;
}

bool Player::onField(const int& f) {
	return this->occupiedSpaces.find(f) != occupiedSpaces.end();
}

void Player::changePosition(int index, int amount) {
	if (this->alreadyMovedInTurn) {
		return;
	}
	occupiedSpaces.erase( occupiedSpaces.find(figs.at(index).getPosition()) );
	figs.at(index).moveBy(amount);
	occupiedSpaces.insert(figs.at(index).getPosition());

	sortFigures();
	this->alreadyMovedInTurn = true;
}

void Player::sortFigures() {  // Simple bubble sort implementation
	for (int i = 0; i < figs.size(); i++) {
		for (int j = 0; j < figs.size()-i-1; j++) {
			if (figs.at(j+1) < figs.at(j)) {
				Figure temp = figs.at(j+1);
				figs.at(j+1) = figs.at(j);
				figs.at(j) = temp;
			}
		}
	}
}

bool Player::everythingOn(Fields type) {
	for (Figure f : figs) {
		if (f.getField() != type) {
			return false;
		}
	}
	return true;
}

void Player::canHit(Player& ply2) {
	std::vector<Figure*> f1, f2;
	fillActivePlayers(f1, this->figs);  // Ignore player on B fields
	fillActivePlayers(f2, ply2.figs);

	int tempBoardLength = boardLength-4;

	for (auto& i : f1) {
		int adjustedIndex = (tempBoardLength + i->getPosition() - (tempBoardLength-4)/2) % tempBoardLength;  // Readjust board for offset second board
		for (auto& j : f2) {

			if (adjustedIndex == j->getPosition()) {
				ply2.occupiedSpaces.erase( ply2.occupiedSpaces.find(j->getPosition()) );
				j->setField(Fields::B);
				j->setPosition(-1);
				ply2.sortFigures();
			}

		}
	}

}

void Player::fillActivePlayers(std::vector<Figure*>& vct, const std::array<Figure, 4>& figArr) {
	for (Figure f : figArr) {
		if (f.getPosition() < boardLength-4 && f.getField() == Fields::RUNWAY) {
			vct.push_back(&f);
		}
	}
}

bool Player::won() {
	int toBeOccupied = boardLength-1;
	for (Figure& f : figs) {
		if (f.getPosition() != toBeOccupied) {
			return false;
		}
		toBeOccupied -= 1;
	}
	return true;
}

void Player::initialize() {
	occupiedSpaces.clear();
	std::fill_n(this->figs.begin(), 4, Figure());

	occupiedSpaces.insert(0);
	figs.at(0).setField(Fields::RUNWAY);
	figs.at(0).setPosition(0);

	sortFigures();
}

void Player::giveDie(Die* newDie) {
	this->currentDie = newDie;
}

Die Player::getDie() const {
	return *currentDie;
}

std::set<int> Player::unoccupiedFinish() {  // Returns fields of goal fields where no figure is on
	std::set<int> res = { 40, 41, 42, 43 };
	for (int i = 40; i < boardLength; i++) {
		if (onField(i)) {
			res.erase(res.find(i));
		}
	}
	return res;
}

std::array<Figure, 4> Player::getFigures() const {
	return this->figs;
}