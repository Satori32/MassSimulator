#include <iostream>
#include <cstdint>
#include <random>

#include "MassSim.h"

#include <conio.h>

//https://ja.wikipedia.org/wiki/ライフゲーム
//チュウリング完全デス！

int GetKey() {
	int k = 0;
	if (_kbhit()) {
		k = _getch();
	}
	return k;
}

namespace Cell {
	enum {
		//Zero=0,
		Empty,
		Die,
		Live,
		Full,
	};
}

template<class T>
bool Show(const MassSimulator<T>& MS) {

	for (std::size_t i = 0; i < MS.Height(); i++) {
		for (std::size_t j = 0; j < MS.Width(); j++) {
			const T& M = MS.Index(j, i);
			if (M == Cell::Empty) std::cout << ' ';
			if (M == Cell::Die) std::cout << 'D';
			if (M == Cell::Live) std::cout << '*';
		}
		std::cout << std::endl;
	}

	return true;
}

template<class T>
MassSimulator<T> MakeProblem(std::size_t W, std::size_t H, unsigned int S = 0) {

	std::mt19937 mt(S);
	std::uniform_int_distribution<> ui(Cell::Empty, Cell::Full - 1);
	MassSimulator<T> R(W, H);
	for (std::size_t Y = 0; Y < R.Height(); Y++) {
		for (std::size_t X = 0; X < R.Width(); X++) {
			R.Set(X, Y, ui(mt));
		}
	}

	return R;
}

int main() {
	std::random_device rd;
	MassSimulator<char> MS= MakeProblem<char>(80,22,rd());

	auto F = [](auto& MS, auto& M, std::intmax_t X, std::intmax_t Y) {//life game logix.

		std::uintmax_t L = 0;
		std::uintmax_t D = 0;

		for (std::intmax_t i = Y - 1; i < Y + 2; i++) {
				if (i == MS.Height()) { continue; }				
			if (i < 0) { continue; }
			for (std::intmax_t j = X - 1; j < X + 2; j++) {
				if (j == MS.Width()) { continue; }				
				if (j < 0) { continue; }
				if (j == X && i==Y) { continue; }
				if (MS.Index(j, i) == Cell::Live) { L++; }
				if (MS.Index(j, i) == Cell::Die) { D++; }
			}
		}

		if (MS.Index(X, Y) == Cell::Die && L == 3) { M = Cell::Live; }
		else if (MS.Index(X, Y) == Cell::Die) { M = Cell::Empty; }
		if (MS.Index(X, Y) == Cell::Live && (L == 3||L==2)) { M = Cell::Live; }
		if (MS.Index(X, Y) == Cell::Live && L <=1) { M = Cell::Die; }
		if (MS.Index(X, Y) == Cell::Live && L >=4) { M = Cell::Die; }

		return true;
	};

	while (!GetKey()){
		//_getch();
		MS.UpDate(F);
		system("cls");
		Show(MS);
		std::cout << "Hit Any key to end!"<<std::endl;
	}


}