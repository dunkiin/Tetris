#include <iostream>
#include "Point.h"

#include <sstream>

// swap x and y
void Point::swapXY() {
	int temp = x;
	x = y;
	y = temp;
}

// multiply x by some factor
void Point::multiplyX(int factor) {
	x *= factor;
}


// multiply y by some factor
void Point::multiplyY(int factor) {
	y *= factor;
}


// return a string in the form "[x,y]" to represent the state of the Point instance
// (for debugging) You could use stringstream if you want to try a forming a string in
// the same way you use cout
std::string Point::toString() const {
	std::stringstream wordCount;
	wordCount << "[" << x << "," << y << "]";
	return wordCount.str();
}