#ifndef POINT_H
#define POINT_H

#include <string>


class Point {
	friend class TestSuite;
// public: +
// private: -
// protect: #
private:
	int x;
	int y;

public:
	Point() : x{ 0 }, y{ 0 } {

	}
	Point(int newX, int newY) : x{ newX }, y{ newY } {

	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	};

	void swapXY();
	void multiplyX(int factor);
	void multiplyY(int factor);
	std::string toString() const;
};


#endif
