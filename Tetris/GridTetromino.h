#include <iostream>
#include <vector>
#include "Tetromino.h"

class GridTetromino : public Tetromino {
private:
	Point gridLoc;
public:

	/// <summary>
	/// Constructor, Initialize with deault or specific values
	/// </summary>
	GridTetromino();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Point getGridLoc() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setGridLoc(int x, int y);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pt"></param>
	void setGridLoc(Point pt);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="xOffset"></param>
	/// <param name="yOffset"></param>
	void move(int xOffset, int yOffset);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::vector<Point> getBlockLocsMappedToGrid() const;
};

