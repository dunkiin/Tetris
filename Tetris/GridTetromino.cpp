#include "GridTetromino.h"
#include <iostream>
#include <vector>


GridTetromino::GridTetromino() : gridLoc(0, 0) {

}

Point GridTetromino::getGridLoc() const {
	return gridLoc;
}

void GridTetromino::setGridLoc(int x, int y) {
	gridLoc.setXY(x, y);
}

void GridTetromino::setGridLoc(Point pt) {
	gridLoc = pt;
}

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setXY(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
	std::vector<Point> mappedLocs;

	for (int i = 0; i < blockLocs.size(); i++) {
		mappedLocs.push_back(Point(blockLocs[i].getX() + gridLoc.getX(), blockLocs[i].getY() + gridLoc.getY()));
	}

	return mappedLocs;
}