/**
 * MP7 Test Cases.
 * Ported by Jack Toole
 * Provided test cases created by Sean Massung.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "png.h"
#include "dsets.h"

#include "mp_part.h"
#if MP_PART(2)
#include "maze.h"
#include "mazereader.h"
#endif

#include "proxy.h"

using namespace std;
using namespace util;

#define GENERATE_SOLUTIONS 0

#if MP_PART(1)

#if MONAD_SPLIT

UNIT_TEST(addElements1, 20, 1, 5000)
{
	DisjointSets disjSets;
	disjSets.addelements(4);
	ASSERT_EQUALS(2, disjSets.find(2));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(addElements2, 20, 1, 5000)
{
	DisjointSets disjSets;
	disjSets.addelements(7);
	ASSERT_EQUALS(0, disjSets.find(0));
	disjSets.addelements(3);
	ASSERT_EQUALS(9, disjSets.find(9));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(testFindAndSetUnion1, 20, 1, 5000)
{
	DisjointSets disjSets;
	disjSets.addelements(3);
	disjSets.setunion(1, 2);
	ASSERT_EQUALS(disjSets.find(2), disjSets.find(1));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(testFindAndSetUnion2, 20, 1, 5000)
{
	DisjointSets disjSets;
	disjSets.addelements(7);
	
	disjSets.setunion(4, 1);
	disjSets.setunion(2, 3);
	disjSets.setunion(6, 5);
	disjSets.setunion(1, 3);
	
	ASSERT_EQUALS(0, disjSets.find(0));
	ASSERT_EQUALS(4, disjSets.find(1));
	ASSERT_EQUALS(4, disjSets.find(2));
	ASSERT_EQUALS(4, disjSets.find(3));
	ASSERT_EQUALS(4, disjSets.find(4));
	ASSERT_EQUALS(6, disjSets.find(5));
	ASSERT_EQUALS(6, disjSets.find(6));
}

#endif
#endif // MP_PART(1)

#if MP_PART(2)

// maze is not const to avoid compilation failures
void assert_maze_acyclic(SquareMaze & maze, int width, int height);
void assert_maze_connected(SquareMaze & maze, int width, int height);
void assert_maze_tree(SquareMaze & maze, int width, int height);
void copyMaze(const MazeReader & source, SquareMaze * dest);
void advancePosition(int * x, int * y, int dir);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);

#define READ_SOLUTION_PNG(width, height)  \
	read_solution(string("soln_") + __func__ + string(".png"), width, height)

#define READ_UNSOLVED_PNG(width, height)  \
	read_unsolved(string("soln_") + __func__ + string(".png"), width, height)

#define READ_SOLUTION_MAZE(width, height)  \
	MazeReader(READ_SOLUTION_PNG(width, height))

#define READ_UNSOLVED_MAZE(widht, height)  \
	MazeReader(READ_UNSOLVED_PNG(width, height))

#if MONAD_SPLIT // assert maze helpers

/**
 * Traverse the maze with a DFS, counting the number of recursive calls.
 */
void recDFS(SquareMaze & maze, vector<vector<uint8_t> > * visited, int x, int y, int width, int height, int * calls)
{
	(*calls)++;
	if ((*visited)[x][y] != 0)
		return;
	(*visited)[x][y] = 1;

	if (x < width-1 && maze.canTravel(x, y, 0))
		recDFS(maze, visited, x+1, y, width, height, calls);
	if (y < height-1 && maze.canTravel(x, y, 1))
		recDFS(maze, visited, x, y+1, width, height, calls);
	if (x > 0 && maze.canTravel(x, y, 2))
		recDFS(maze, visited, x-1, y, width, height, calls);
	if (y > 0 && maze.canTravel(x, y, 3))
		recDFS(maze, visited, x, y-1, width, height, calls);
}

/**
 * Explores the whole maze whether connected or not.
 * @return pair containing (num components, num recursive calls from DFS)
 */
pair<int, int> assert_maze_helper(SquareMaze & maze, int width, int height)
{
	vector<vector<uint8_t> > visited;
	for (int i = 0; i < width; i++)
		visited.push_back(vector<uint8_t>(height));

	int components = 0;
	int calls = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (visited[i][j] == 0) {
				recDFS(maze, &visited, i, j, width, height, &calls);
				components++;
			}
		}
	}

	return make_pair(components, calls);
}

void assert_maze_acyclic(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (calls + components != width * height * 2)
		FAIL("Maze has a cycle");
}

void assert_maze_connected(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (components != 1)
		FAIL("Maze is not connected");
}

void assert_maze_tree(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (calls + components != width * height * 2)
		FAIL("Maze has a cycle");
	if (components != 1)
		FAIL("Maze is not connected");
}

PNG read_solution(const string & filename, int width, int height)
{
#if GENERATE_SOLUTIONS
	SquareMaze solnMaze;
	solnMaze.makeMaze(width, height);
	PNG * output = solnMaze.drawMazeWithSolution();
	PNG result(*output);
	delete output;
	result.writeToFile(filename);
	return result;
#else
	return PNG (filename);
#endif
}

PNG read_unsolved(const string & filename, int width, int height)
{
#if GENERATE_SOLUTIONS
	SquareMaze solnMaze;
	solnMaze.makeMaze(width, height);
	PNG * output = solnMaze.drawMaze();
	PNG result(*output);
	delete output;
	result.writeToFile(filename);
	return result;
#else
	return PNG (filename);
#endif
}

void copyMaze(const MazeReader & source, SquareMaze * dest)
{
	dest->makeMaze(source.getWidth(), source.getHeight());
	for (int x = 0; x < source.getWidth(); x++)
	{
		for (int y = 0; y < source.getHeight(); y++)
		{
			if (x < source.getWidth() - 1)
				dest->setWall(x, y, 0, source.isWall(x, y, MazeReader::RIGHTWALL));
			if (y < source.getHeight() - 1)
				dest->setWall(x, y, 1, source.isWall(x, y, MazeReader::DOWNWALL));
		}
	}
}

void advancePosition(int * x, int * y, int dir)
{
	 if (dir == MazeReader::RIGHT)
		(*x)++;
	 else if (dir == MazeReader::DOWN)
		(*y)++;
	 else if (dir == MazeReader::LEFT)
		(*x)--;
	 else if (dir == MazeReader::UP)
		(*y)--;
}

#endif


#if MONAD_SPLIT
UNIT_TEST(testMakeSmallMaze, 0, 1, 5000)
{
	SquareMaze maze;
	maze.makeMaze(2, 2);
	assert_maze_tree(maze, 2, 2);
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMakeMazeConnected, 0, 1, 5000)
{
	SquareMaze maze;
	maze.makeMaze(15, 15);
	assert_maze_connected(maze, 15, 15);
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMakeMazeAcyclic, 0, 1, 5000)
{
	SquareMaze maze;
	maze.makeMaze(12, 14);
	assert_maze_acyclic(maze, 12, 14);
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMakeMazeTree800, 0, 1, 14000)
{
	SquareMaze maze;
	maze.makeMaze(800, 800);
	assert_maze_tree(maze, 800, 800);
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testMakeMazeRandom, 0, 1, 10000)
{
	SquareMaze maze1;
	maze1.makeMaze(42, 47);
	sleep(2); // if student is using time(NULL), ensure we get a new seed
	SquareMaze maze2;
	maze2.makeMaze(42, 47);

	for (int y = 0; y < 47; y++)
	{
		for (int x = 0; x < 42; x++)
		{
            // find a different solution
			if (maze1.canTravel(x, y, 0) != maze2.canTravel(x, y, 0))
				PASS;
			if (maze1.canTravel(x, y, 1) != maze2.canTravel(x, y, 1))
				PASS;
		}
	}
	FAIL("Generated the same 42x47 maze twice");
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testSolveMazeValidPath, 0, 1, 5000)
{
	SquareMaze maze;
	MazeReader soln = READ_SOLUTION_MAZE(25, 25);
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	if (solution.empty())
		FAIL("No solution was generated");
	
	int x = 0;
	int y = 0;
	for (size_t i = 0; i < solution.size(); i++)
	{
		if (soln.isWallInDir(x, y, solution[i]))
			FAIL("Solution passes through walls");
		advancePosition(&x, &y, solution[i]);
	}
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testSolutionBottomRow, 0, 1, 5000)
{
	SquareMaze maze;
	MazeReader soln = READ_SOLUTION_MAZE(15, 15);
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	int x = 0;
	int y = 0;
	for (size_t i = 0; i < solution.size(); i++)
		advancePosition(&x, &y, solution[i]);

	if (y != soln.getDestinationY())
		FAIL("Didn't end up at the bottom row");
}
#endif

#if MONAD_SPLIT
// The MazeReader object must be passed in because READ_SOLUTION uses
// the function name to name the file
void helpSolveMaze(const MazeReader & soln)
{
	SquareMaze maze;
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	cout << "first 10 steps in solution:" << endl;
	for (size_t i = 0; i < solution.size() && i < soln.getSolutionSize() && i < 10; i++)
		cout << "step " << i << ": actual=" << solution[i] << ", expected=" << soln.getSolutionAt(i) << endl;

	ASSERT_EQUALS(soln.getSolutionSize(), solution.size());
	
	for (size_t i = 0; i < solution.size(); i++)
		if (solution[i] != soln.getSolutionAt(i))
			FAIL("Solution is incorrect");
}
UNIT_TEST(testSolveMazeSmall, 0, 1, 5000) { helpSolveMaze(READ_SOLUTION_MAZE(2, 2)); }
UNIT_TEST(testSolveMazeLarge, 0, 1, 15000) { helpSolveMaze(READ_SOLUTION_MAZE(700, 700)); }
#endif // MONAD_SPLIT


#if MONAD_SPLIT
UNIT_TEST(testDrawMazeSmall, 0, 1, 5000)
{
	PNG solnImage = READ_UNSOLVED_PNG(2, 2);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile(__func__  + string(".png"));
	ASSERT(*actualOutput == solnImage);
}
#endif // MONAD_SPLIT


#if MONAD_SPLIT
UNIT_TEST(testDrawMazeMed, 0, 1, 10000)
{
	PNG solnImage = READ_UNSOLVED_PNG(50, 50);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile(__func__  + string(".png"));
	ASSERT(*actualOutput == solnImage);
}
#endif // MONAD_SPLIT


#if MONAD_SPLIT
UNIT_TEST(testDrawMazeLarge, 0, 1, 15000)
{
	PNG solnImage = READ_UNSOLVED_PNG(500, 500);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile(__func__  + string(".png"));
	ASSERT(*actualOutput == solnImage);
}
#endif // MONAD_SPLIT


#if MONAD_SPLIT
UNIT_TEST(testDrawSolutionMed, 0, 1, 10000)
{
	PNG solnImage = READ_SOLUTION_PNG(50, 50);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	maze.solveMaze();
	PNG * actualOutput = maze.drawMazeWithSolution();
	actualOutput->writeToFile(__func__  + string(".png"));
	ASSERT(*actualOutput == solnImage);
}
#endif


#if MONAD_SPLIT
UNIT_TEST(testDrawSolutionLarge, 0, 1, 15000)
{
	PNG solnImage = READ_SOLUTION_PNG(500, 500);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	maze.solveMaze();
	PNG * actualOutput = maze.drawMazeWithSolution();
	actualOutput->writeToFile(__func__  + string(".png"));
	ASSERT(*actualOutput == solnImage);
}
#endif


#endif // MP_PART(2)
