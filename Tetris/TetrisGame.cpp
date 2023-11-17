#include "TetrisGame.h"
#include "Gameboard.h"
#include <iostream>
#include <cassert>
#include <cstdlib>	
#define print(x) std::cout << x << '\n'

// constructor
	//   initialize/assign private member vars names that match param names
	//   reset() the game
	//   load font from file: fonts/RedOctober.ttf
	//   setup scoreText
	// - params: already specified
TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset) : window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset) {
	reset();
	
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) {
		assert(false && "Missing font style: RedOctober.ttf");
	}
	
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(50, 50);
}

// Draw anything to do with the game,
//   includes the board, currentShape, nextShape, score
//   called every game loop
// - params: none
// - return: nothing
void TetrisGame::draw() {
	drawGameboard(); 
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	window.draw(scoreText);
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
// - param 1: sf::Event event
// - return: nothing
void TetrisGame::onKeyPressed(sf::Event event) {
	if (event.key.code == sf::Keyboard::Up) {
		attemptRotate(currentShape);
	}
	else if (event.key.code == sf::Keyboard::Left) {
		attemptMove(currentShape, -1, 0);
	}
	else if (event.key.code == sf::Keyboard::Right) {
		attemptMove(currentShape, 1, 0);
	}
	else if (event.key.code == sf::Keyboard::Down) {
		attemptMove(currentShape, 0, 1);
	}
	else if (event.key.code == sf::Keyboard::Space) {
		drop(currentShape);
		lock(currentShape);
	}
}

// called every game loop to handle ticks & tetromino placement (locking)
// - param 1: float secondsSinceLastLoop
// return: nothing
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {

}

// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock() 
// the currentShape (it can move no further).
// - params: none
// - return: nothing
void TetrisGame::tick() {
	print("tick");

	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
}

// reset everything for a new game (use existing functions) 
	//  - set the score to 0 and call updateScoreDisplay()
	//  - call determineSecondsPerTick() to determine the tick rate.
	//  - clear the gameboard,
	//  - pick & spawn next shape
	//  - pick next shape again (for the "on-deck" shape)
	// - params: none
	// - return: nothing
void TetrisGame::reset() {
	score = 0;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
}

// assign nextShape.setShape a new random shape  
// - params: none
// - return: nothing
void TetrisGame::pickNextShape() {
	TetShape shape = static_cast<TetShape>(rand() % static_cast<int>(TetShape::COUNT));
	nextShape.setShape(shape);
}

// copy the nextShape into the currentShape (through assignment)
//   position the currentShape to its spawn location.
// - params: none
// - return: bool, true/false based on isPositionLegal()
bool TetrisGame::spawnNextShape() {
	currentShape = nextShape;

	if (isPositionLegal(currentShape)) {
		return true;
	}
	return false;
}

// Test if a rotation is legal on the tetromino and if so, rotate it. 
//  To accomplish this:
//	 1) create a (local) temporary copy of the tetromino
//	 2) rotate it (temp.rotateClockwise())
//	 3) test if temp rotation was legal (isPositionLegal()), 
//      if so - rotate the original tetromino.
// - param 1: GridTetromino shape
// - return: bool, true/false to indicate successful movement
bool TetrisGame::attemptRotate(GridTetromino& shape) {
	GridTetromino tempShape = shape;
	tempShape.rotateClockwise();
	if (isPositionLegal(tempShape)) {
		shape = tempShape;
		return true;
	}
	return false;
}

// test if a move is legal on the tetromino, if so, move it.
//  To do this:
//	 1) create a (local) temporary copy of the tetromino
//	 2) move it (temp.move())
//	 3) test if temp move was legal (isPositionLegal(),
//      if so - move the original.	
// - param 1: GridTetromino shape
// - param 2: int x;
// - param 3: int y;
// - return: true/false to indicate successful movement
bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
	GridTetromino tempShape = shape;
	tempShape.move(x, y);
	if (isPositionLegal(tempShape)) {
		shape = tempShape;
		return true;
	}
	return false;
}

// drops the tetromino vertically as far as it can 
//   legally go.  Use attemptMove(). This can be done in 1 line.
// - param 1: GridTetromino shape
// - return: nothing;
void TetrisGame::drop(GridTetromino& shape) {

}

// copy the contents (color) of the tetromino's mapped block locs to the grid.
	//	 1) get the tetromino's mapped locs via tetromino.getBlockLocsMappedToGrid()
	//   2) use the board's setContent() method to set the content at the mapped locations.
	//   3) record the fact that we placed a shape by setting shapePlacedSinceLastGameLoop
	//      to true
	// - param 1: GridTetromino shape
	// - return: nothing
void TetrisGame::lock(GridTetromino& shape) {

}

// Graphics methods ==============================================

// Draw a tetris block sprite on the canvas		
// The block position is specified in terms of 2 offsets: 
//    1) the top left (of the gameboard in pixels)
//    2) an x & y offset into the gameboard - in blocks (not pixels)
//       meaning they need to be multiplied by BLOCK_WIDTH and BLOCK_HEIGHT
//       to get the pixel offset.
//	 1) set the block color using blockSprite.setTextureRect()
//   2) set the block location using blockSprite.setPosition()   
//	 3) draw the block using window.draw()
//   For details/instructions on these 3 operations see:
//       www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
//       use member variables: window and blockSprite (assigned in constructor)
// param 1: Point topLeft
// param 2: int xOffset
// param 3: int yOffset
// param 4: TetColor color
// return: nothing
void TetrisGame::drawBlock(Point topLeft, int xOffset, int yOffset, TetColor color) {

}

// Draw the gameboard blocks on the window
//   Iterate through each row & col, use drawBlock() to 
//   draw a block if it isn't empty.
// params: none
// return: nothing
void TetrisGame::drawGameboard() {

}

// Draw a tetromino on the window
//	 Iterate through each mapped loc & drawBlock() for each.
//   The topLeft determines a 'base point' from which to calculate block offsets
//      If the Tetromino is on the gameboard: use gameboardOffset
// param 1: GridTetromino tetromino
// param 2: Point topLeft
// return: nothing
void TetrisGame::drawTetromino(GridTetromino tetromino, Point topLeft) {

}

// update the score display
// form a string "score: ##" to display the current score
// user scoreText.setString() to display it.
// params: none:
// return: nothing
void TetrisGame::updateScoreDisplay() {
	scoreText.setString("Score : " + std::to_string(score));
}

// State & gameplay/logic methods ================================

// Determine if a Tetromino can legally be placed at its current position
// on the gameboard.
//   Tip: Make use of Gameboard's areLocsEmpty() and pass it the shape's mapped locs.
// - param 1: GridTetromino shape
// - return: bool, true if shape is within borders (isWithinBorders()) and 
//           the shape's mapped board locs are empty (false otherwise).
bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
	if (board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid()) && isWithinBorders(shape) && board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid())) {
		return true;
	}
	return false;
}


// Determine if the shape is within the left, right, & bottom gameboard borders
//   * Ignore the upper border because we want shapes to be able to drop
//     in from the top of the gameboard.
//   All of a shape's blocks must be inside these 3 borders to return true
// - param 1: GridTetromino shape
// - return: bool, true if the shape is within the left, right, and lower border
//	         of the grid, but *NOT* the top border (false otherwise)
bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {

}


// set secsPerTick 
//   - basic: use MAX_SECS_PER_TICK
//   - advanced: base it on score (higher score results in lower secsPerTick)
// params: none
// return: nothing
void TetrisGame::determineSecondsPerTick() {

}