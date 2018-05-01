#ifndef MAZE_H
#define MAZE_H
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>

class SquareMaze{
public:
 	SquareMaze ();
	void makeMaze (int width, int height);
	bool canTravel (int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	std::vector<int> solveMaze();
	cs225::PNG* drawMaze() const;
	cs225::PNG* drawMazeWithSolution();
private:
	int width_;
	int height_;
  int size_;
  std::vector<bool> rightWall;
  std::vector<bool> downWall;
  DisjointSets maze_;
};

#endif
