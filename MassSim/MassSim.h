#pragma once

#include <vector>

//https://ja.wikipedia.org/wiki/チューリング完全
//Isn't it?

template<class T>
class MassSimulator {
	typedef std::vector<std::vector<T>> Surface;
public:

	MassSimulator(const std::size_t& Width, const std::size_t& Height) {
		S.resize(Height);
		for (auto& o : S) {
			o.resize(Width);
		}
		H = Height;
		W = Width;
	}
	
	const T& Index(const std::size_t& X, const std::size_t& Y) const{
		return S[Y][X];
	}

	bool Set(const std::size_t& X, const std::size_t& Y,const T& In) {
		S[Y][X]=In;
		return true;
	}

	template<class Fun>
	bool UpDate(const Fun& F){
		Surface B;

		B.resize(H);
		for (auto& o : B) {
			o.resize(W);
		}

		for (std::size_t Y = 0; Y < B.size(); Y++) {
			for (std::size_t X = 0; X < B[Y].size(); X++) {
				F(*this, B[Y][X],X,Y);//B[Y][X] is rewiterable.
			}
		}
		S = B;

		return true;
	}

	std::size_t Width() const {
		return W;
	}
	std::size_t Height() const{
		return H;
	}

protected:
	Surface S;

	std::size_t W = 0;
	std::size_t H = 0;
};