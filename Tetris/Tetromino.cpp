#include <iostream>
#include "Tetromino.h"

// - set the shape
// - set the blockLocs for the shape
// - set the color for the shape
void Tetromino::setShape(TetShape shape) {
	this->shape = shape;

	// emptying vector
	blockLocs.clear();

	//std::string userInput;
	//std::cin >> userInput;
	//std::cout << "command?: " << userInput;

	if (shape == TetShape::O) {
		color = TetColor::YELLOW;
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(1, 1));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(1, 0));
	}
	else if (shape == TetShape::I) {
		color = TetColor::BLUE_LIGHT;
		blockLocs.push_back(Point(0, 2));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
	}
	else if (shape == TetShape::S) {
		color = TetColor::RED;
		blockLocs.push_back(Point(-1, 0));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(1, 1));
	}
	else if (shape == TetShape::Z) {
		color = TetColor::GREEN;
		blockLocs.push_back(Point(-1, 1));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(1, 0));
	}
	else if (shape == TetShape::L) {
		color = TetColor::ORANGE;
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(1, -1));
	}
	else if (shape == TetShape::J) {
		color = TetColor::BLUE_DARK;
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(-1, -1));
	}
	else if (shape == TetShape::T) {
		color = TetColor::PURPLE;
		blockLocs.push_back(Point(-1, 0));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(1, 0));
	}

}
// print a grid to display the current shape
// to do this: print out a ¡°grid¡± of text to represent a co-ordinate
// system. Start at top left [-3,3] go to bottom right [3,-3]
// (use nested for loops)
// for each [x,y] point, loop through the blockLocs and if the point exists
// in the list, print an 'x' instead of a '.'. You should end up with something
// like this: (results will vary depending on shape and rotation, eg: this
// one shows a T shape rotated clockwise once)
// .......
// .......
// ...x...
// ..xx...
// ...x...
// .......
void Tetromino::printToConsole() const{
	for (int y = 3; y >= -3; y--) {
		for (int x = -3; x <= 3; x++) {
			bool isX = false;
			for (auto& point : blockLocs) {
				if (point.getX() == x && point.getY() == y) {
					isX = true;
					break;
				}
			}
			if (isX) {
				std::cout << 'x';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
}


void Tetromino::rotateClockwise() {
	if ( shape == TetShape::O) {
		return;
	}

	for (auto& point : blockLocs) {
		point.swapXY();
		point.multiplyY(-1);
		//point.multiplyX(-1);
	}
}

