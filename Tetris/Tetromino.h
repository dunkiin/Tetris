#ifndef TETROMINO_H
#define TETROMINO_H
#include "Point.h"

#include <vector>
enum class TetColor {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE_LIGHT,
	BLUE_DARK,
	PURPLE
};

enum class TetShape {
	S,
	Z,
	L,
	J,
	O,
	I,
	T,
	COUNT
};

class Tetromino {

	friend class TestSuite;
	// public: +
	// private: -
	// protect: #
protected:
	std::vector<Point> blockLocs;
private:
	TetColor color;
	TetShape shape;
public:
	Tetromino() {
		setShape(TetShape::S);
	}
	
	TetColor getColor() const {
		return color;
	}
	TetShape getShape() const {
		return shape;
	}
	void setShape(TetShape shape);

	// rotate the shape 90 degrees around [0,0] (clockwise)
	// to do this:
	// - iterate through blockLocs
	// - rotate each Point 90 degrees clockwise around [0,0]
	// hint: as you rotate the point [1,2] clockwise around [0,0], note
	// how the x,y values change. Once you find the pattern you can use
	// a couple existing methods in the Point class to accomplish this.
	// make it so that the TetShape::O doesn¡¯t rotate
	void rotateClockwise();
	void printToConsole() const;
};

#endif // !TEROMINO_H
