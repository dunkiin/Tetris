#include <iostream>
#include <vector>
#include "Point.h"
#include "Gameboard.h"
#include <iomanip>
#include <cassert>
#define print(x) std::cout << x 

// Constructor
Gameboard::Gameboard() {
	empty();
}

void Gameboard::empty() {
	for (int y = 0; y < MAX_Y; y++) {
		fillRow(y, EMPTY_BLOCK);
	}
}

void Gameboard::printToConsole() const {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (grid[y][x] == EMPTY_BLOCK) {
				print(std::setw(2)) << ".";
			}
			else {
				print(std::setw(2)) << grid[y][x];
			}
		}
		print('\n');
	}
}

bool Gameboard::isValidPoint(int x, int y) const {
	//if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
	//	return true;
	//}
	//else {
	//	return false;
	//}

	return x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y;
}

bool Gameboard::isValidPoint(const Point& pt) const {
	return isValidPoint(pt.getX(), pt.getY());
}

bool Gameboard::isValidRow(int y) const {
	return y >= 0 && y < MAX_Y;
}


int Gameboard::getContent(const Point& pt) const {
	assert(isValidPoint(pt));
	int x = pt.getX(); 
	int y = pt.getY();

	return grid[y][x];// you can call return grid[pt.getY()][pt.getX()]
	
}

int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];


	
}

void Gameboard::setContent(const Point& pt, int content) {
	if (isValidPoint(pt)) {
		int x = pt.getX();
		int y = pt.getY();
		
		grid[y][x] = content; // you can avoid creating temp variables grid[pt.getY()][pt.getX()]
	}
}

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}
}


void Gameboard::setContent(const std::vector<Point>& locs, int content) {
	for (Point pt : locs) {
		setContent(pt, content);
	}
}


bool Gameboard::areAllLocsEmpty(const std::vector<Point> locs) const {
	for (Point pt : locs) {
		int x = pt.getX();
		int y = pt.getY();
		if (isValidPoint(pt) && grid[y][x] != EMPTY_BLOCK) { //grid[pt.getY()][pt.getX()]
			return false;
		}
	}

	return true;
}


int Gameboard::removeCompletedRows() {
	std::vector<int> completeRows = getCompletedRowIndices();

	removeRows(completeRows);
	return completeRows.size();
}

Point Gameboard::getSpawnLoc() const {
	return spawnLoc;
}

void Gameboard::fillRow(int rowIndex, int content) {
	assert(isValidRow(rowIndex));
	for (int x = 0; x < MAX_X; x++) {
		grid[rowIndex][x] = content;
	}
}

bool Gameboard::isRowCompleted(int rowIndex) const {
	assert(isValidRow(rowIndex));
	for (int x = 0; x < MAX_X; x++) {
		if (grid[rowIndex][x] == EMPTY_BLOCK) {
			return false;
		}
	}

	return true;
}

void Gameboard::copyRowIntoRow(int sourceRow, int targetRow) {

	//assert(sourceRow >= 0 && sourceRow < MAX_Y);
	assert(isValidRow(sourceRow));
	assert(isValidRow(targetRow));

    for (int x = 0; x < MAX_X; x++) {
		
        grid[targetRow][x] = grid[sourceRow][x];
    }
}

void Gameboard::removeRow(int rowIndex) {
	assert(isValidRow(rowIndex));
    for (int y = rowIndex; y > 0; y--) {
        copyRowIntoRow(y -1, y);
        
    }
    fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(const std::vector<int> rowIndices) {
    for (int rowIndex : rowIndices) {
        removeRow(rowIndex);
    }
}

std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;
	for (int y = 0; y < MAX_Y; y++) {
		if (isRowCompleted(y)) {
			completedRows.push_back(y);
		}
	}

	return completedRows;
}