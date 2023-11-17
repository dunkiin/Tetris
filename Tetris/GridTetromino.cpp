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

	for (auto& blockLoc : blockLocs) {
		mappedLocs.push_back(Point(blockLoc.getX() + gridLoc.getX(), blockLoc.getY() + gridLoc.getY()));
	}

	return mappedLocs;
}