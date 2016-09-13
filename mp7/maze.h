/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include "png.h"

class SquareMaze{
	public:
		//big 3
		SquareMaze();
		//~SquareMaze();
		//SquareMaze(SquareMaze const &other);
		//SquareMaze &operator=(SquareMaze const &other);

		//public functions
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir)const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
		PNG *drawMaze()const;
		PNG *drawMazeWithSolution();

		vector<int> solution;

	private:

		//status of rightWall and downWall corresponding to first and second
		vector<pair<bool, bool>> Wall;
		int width;
		int height;

		//big 3 helper function
		//void copy(SquareMaze const &other);
		//void clear();

		//helper functions for public functions
		int getIndex(int x, int y)const;
		int getX(int index)const;
		int getY(int index)const;
};

#endif