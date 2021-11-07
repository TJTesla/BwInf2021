//
// Created by Theodor Teslia on 26.10.21.
//

#include "Classes.h"

// TODO: Clean up file:
// TODO: Add comments

Die::Die(const std::vector<int>& pSides) {
	this->sides = pSides;
	srand((unsigned)time(nullptr));

	this->has6 = false;
	for (int& s : this->sides) {
		if (s == 6) {
			this->has6 = true;
			break;
		}
	}
}

int Die::roll() {
	return sides.at(rand() % sides.size());
}

bool Die::gotNo6() const {
	return !has6;
}


Figure::Figure() {
	this->position = 0;
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
	this->board = std::array<Figure*, boardLength>();
	this->figs = std::array<Figure, 4>();
	this->alreadyMovedInTurn = false;

	std::fill_n(this->board.begin(), boardLength, nullptr);
	std::fill_n(this->figs.begin(), 4, Figure());

	board.at(0) = &figs.at(0);
	figs.at(0).setField(Fields::RUNWAY);

	std::sort(figs.begin(), figs.end());
}

void Player::move() {
	if (this->currentDie == nullptr) {
		return;
	}
	this->alreadyMovedInTurn = false;

	int dieResult = this->currentDie->roll();

	if (board.at(0) != nullptr) {  // Still figure on start field -> Needs to be moved away
		for (int i = figs.size() - 1; i >= 0; i--) {  // Start from last figure
			int nextPosition = figs.at(i).getPosition() + dieResult;
			if (nextPosition >= board.size()) {
				continue;
			}
			if (board.at(nextPosition) == nullptr && figs.at(i).getField() == Fields::RUNWAY) {
				changePosition((int) i, dieResult);  // Casting becuse my IDE annoys me with unsigned int to int warning
				break;
			}
		}

		if (dieResult == 6) {
			this->move();
		} else {
			return;
		}
	}

	if (dieResult == 6) {
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
			board.at(0) = &(figs.at(firstOnBIndex));

			std::sort(figs.begin(), figs.end());
			this->alreadyMovedInTurn = true;

			this->move();
		}
	}

	if (everythingOn(Fields::B) && dieResult != 6) {  // Everything on B and no 6 -> Nothing can move out
		return;
	}
	for (int i = 0; i < figs.size(); i++) {  // Search for first element that can move
		int nextPos = figs.at(i).getPosition() + dieResult;
		if (nextPos >= board.size()) {
			continue;
		}

		if (figs.at(i).getField() == Fields::RUNWAY) {
			if (board.at(nextPos) == nullptr) {
				changePosition(i, dieResult);
				break;
			}
		}
	}

	if (dieResult == 6) {
		this->move();
	}
}

void Player::changePosition(int index, int amount) {
	if (this->alreadyMovedInTurn) {
		return;
	}
	board.at(figs.at(index).getPosition()) = nullptr;
	figs.at(index).moveBy(amount);
	board.at(figs.at(index).getPosition()) = &figs.at(index);

	std::sort(figs.begin(), figs.end());
	this->alreadyMovedInTurn = true;
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
	fillActivePlayers(f1, this->figs);
	fillActivePlayers(f2, ply2.figs);

	int tempBoardLength = boardLength-4;

	for (auto& i : f1) {
		int adjustedIndex = (tempBoardLength + i->getPosition() - (tempBoardLength-4)/2) % tempBoardLength;
		for (auto& j : f2) {

			if (adjustedIndex == j->getPosition()) {
				ply2.board.at(j->getPosition()) = nullptr;
				j->setField(Fields::B);
				j->setPosition(0);
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
	for (unsigned int i = board.size()-1; i >= board.size() - 4; i--) {
		if (board.at(i) == nullptr) {
			return false;
		}
	}
	return true;
}

void Player::initialize() {
	std::fill_n(this->board.begin(), boardLength, nullptr);
	std::fill_n(this->figs.begin(), 4, Figure());

	board.at(0) = &figs.at(0);
	figs.at(0).setField(Fields::RUNWAY);

	std::sort(figs.begin(), figs.end());
}

void Player::giveDie(Die* newDie) {
	this->currentDie = newDie;
}