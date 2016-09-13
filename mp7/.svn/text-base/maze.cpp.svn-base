/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <stdlib.h>
#include <vector>
#include <queue>

using std::queue;
using std::vector;

//Default Constructor
SquareMaze::SquareMaze(){
	width = 0;
	height = 0;
}

//copy Constructor
/*SquareMaze::SquareMaze(SquareMaze const &other){
	copy(other);
}

//helper function copy
void SquareMaze::copy(SquareMaze const &other){
	width = other.width;
	height = other.height;
	maze = new pair<bool, bool> *[width];
	for(int i=0; i<width; i++){
		maze[i] = new pair<bool, bool> [height];
		for(int j=0; j<height; j++){
			maze[i][j] = other.maze[i][j];
		}
	}
}

//destructor
SquareMaze::~SquareMaze(){
	clear();
}

//helper function clear
void SquareMaze::clear(){
	Wall.clear();
}

//operator=
SquareMaze &SquareMaze::operator=(SquareMaze const &other){
	if(this != &other){
		clear();
		copy(other);
	}
	return *this;
}
*/
//public functions
void SquareMaze::makeMaze(int width, int height){

	Wall.clear();
	this->width = width;
	this->height = height;

	//create a grid maze
/*	maze = new pair<bool, bool> *[width];
	for(int i=0; i<width; i++){
		maze[i] = new pair<bool, bool> [height];
		for(int j=0; j<height; j++){
			maze[i][j].first = true; //rightWall
			maze[i][j].second = true; //downWall
		}
	}
*/

	for(int i = 0; i < (int)width*height; i++){
		Wall.push_back(std::make_pair(true, true));
	}

	//initialize a set
	DisjointSets set;
	set.addelements(width*height);

	//srand(time(NULL));

	int size = width * height;
	int i = 0;
	while(size > 1){
		int wall = i;
		int next = rand() % 2;
		//not the last column, go right
		if(next == 0 && wall%width!=width-1 && set.find(wall)!=set.find(wall+1)){
			setWall(wall%width, wall/width, 0, false);
			set.setunion(wall, wall+1);
			size--;
		}
		//not the last row, go down
		else if(next == 1 && wall/width!=height-1 && set.find(wall)!=set.find(wall+width)){
			setWall(wall%width, wall/width, 1, false);
			set.setunion(wall, wall+width);
			size--;			
		}
		//is the last column, go down
/*		else if(next == 0 && wall%width==width-1 && set.find(wall)!=set.find(wall+width)){
			setWall(wall%width, wall/width, 1, false);
			set.setunion(wall, wall+width);
			size--;	
		}
		//is the last row, go right
		else if(next == 0 && wall/width!=height-1 && set.find(wall)!=set.find(wall+1)){
			setWall(wall%width, wall/width, 0, false);
			set.setunion(wall, wall+1);
			size--;			
		}
		*/
		//when the size is not full but i has already gone to the last element
		i++;
		if (i>=width*height){
			i = 0;
		}
	}




	//int counter = 0;

	/*while(size > 1){
		int randIndex;
		randIndex = rand()%(width*height);
		int next = rand() % 2;

		if(next==0 && (randIndex+1)%width!=0 && set.find(randIndex)!=set.find(randIndex+1)){
			setWall(randIndex%width-1, randIndex/width-1, 0, false);
			set.setunion(randIndex, randIndex+1);
			size--;
		}

		else if(next==0 && (randIndex+width+1)%height!=0 && set.find(randIndex)!=set.find(randIndex+width)){
			setWall(randIndex%width-1, randIndex/width-1, 1, false);
			set.setunion(randIndex, randIndex+width);
			size--;
		}
*/
/*		else if(next==0 && (randIndex+1)%width == 0){
			setWall(randIndex%width, randIndex/width, 1, false);
			set.setunion(randIndex, randIndex+width);
			size--;
		}

		else if(next==0 && (randIndex+width+1)%height == 0){
			setWall(randIndex%width, randIndex/width, 0, false);
			set.setunion(randIndex, randIndex+1);
			size--;
		}
		*/
	//}
}

//helper function to get the index
int SquareMaze::getIndex(int x, int y)const{
	return y*width + x;
}

bool SquareMaze::canTravel(int x, int y, int dir)const{
	int index = 0;

	if(x>=0 && x<width && y>=0 && y<height){
		if(dir == 0){
			index = getIndex(x, y);
			return !(Wall[index].first);
		}
		else if(dir == 1){
			index = getIndex(x, y);
			return !(Wall[index].second);
		}
		else if(dir==2 && x>0){
			index = getIndex(x-1, y);
			return !(Wall[index].first);
		}
		else if(dir==3 && y>0){
			index = getIndex(x, y-1);
			return !(Wall[index].second);
		}
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int index = getIndex(x, y);
	if(x>=0 && x<width && y>=0 && y<height){
		if(dir == 0){
			Wall[index].first = exists;
		}
		else if(dir == 1){
			Wall[index].second = exists;
		}
	}
}

//helper function to get the x coor for a given index
int SquareMaze::getX(int index)const{
	return index%width;
}

//helper function to get the y coor for a given index
int SquareMaze::getY(int index)const{
	return index/width;
}

vector<int> SquareMaze::solveMaze(){
	int size = width*height;
	vector<int> distance(size, INT_MAX);
	vector<int> previous(size, -1);

	queue<int> q;
	q.push(getIndex(0,0));
	distance[getIndex(0,0)] = 0;

	while(!q.empty()){
		int idx = q.front();
		int x = getX(idx);
		int y = getY(idx);
		q.pop();

		vector<int> adjacent;
		if(canTravel(x, y, 0))
		adjacent.push_back(getIndex(x+1, y));
		if(canTravel(x, y, 1))
		adjacent.push_back(getIndex(x, y+1));
		if(canTravel(x, y, 2))
		adjacent.push_back(getIndex(x-1, y));
		if(canTravel(x, y, 3))
		adjacent.push_back(getIndex(x, y-1));

		for(size_t i=0; i < adjacent.size(); i++){
			if(distance[adjacent[i]]==INT_MAX){
				previous[adjacent[i]] = idx;
				distance[adjacent[i]] = distance[idx]+1;
				q.push(adjacent[i]);
			}
		}
	}
	
	//find max distance
	int max =0;
	int MAX =0;
	for(int i = 0; i < width; i++){
		int newIdx = getIndex(i, height-1);
		if(distance[newIdx] > MAX){
			MAX = distance[newIdx];
			max = newIdx;
		}
	}
	
	int prev = previous[max];
	int curr = max;
	while(prev!= -1){
		if(getX(prev)+1==getX(curr) && getY(prev)==getY(curr)){
			solution.push_back(0);
		}
		if(getX(prev)==getX(curr) && getY(prev)+1==getY(curr)){
			solution.push_back(1);
		}
		if(getX(prev)-1==getX(curr) && getY(prev)==getY(curr)){
			solution.push_back(2);
		}
		if(getX(prev)==getX(curr) && getY(prev)-1==getY(curr)){
			solution.push_back(3);
		}
		curr = prev;
		prev = previous[curr];
	}
	
	reverse(solution.begin(), solution.end());
	
	return solution;
}




PNG *SquareMaze::drawMaze()const{
	PNG *pic = new PNG(width*10+1, height*10+1);
	RGBAPixel black(0, 0, 0);

	*((*pic)(0,0)) = black;

	for(int i = 10; i < width*10+1; i++){
		*((*pic)(i, 0)) = black;
	}

	for(int j = 0; j < height*10+1; j++){
		*((*pic)(0, j)) = black;
	}

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			int index = getIndex(i, j);
			if(Wall[index].first){
				for(int k = 0; k <= 10; k++){
					(*pic)((i+1)*10, j*10+k)->red = 0;
					(*pic)((i+1)*10, j*10+k)->green = 0;
					(*pic)((i+1)*10, j*10+k)->blue = 0;
				}
			}
			if(Wall[index].second){
				for(int k = 0; k <= 10; k++){
					(*pic)(i*10+k, (j+1)*10)->red = 0;
					(*pic)(i*10+k, (j+1)*10)->green = 0;
					(*pic)(i*10+k, (j+1)*10)->blue = 0;
				}
			}
		}
	}
	return pic;
}

PNG *SquareMaze::drawMazeWithSolution(){
	PNG *pic = drawMaze();
	RGBAPixel white(255, 255, 255);
	RGBAPixel red(255, 0, 0);
	int x = 5;
	int y = 5;
	//int exit_x = 0;
	//int exit_y = 0;
	*(*pic)(x, y) = red;

	for(size_t i = 0; i < solution.size(); i++){
		if(x >= width*10 || y>=height*10){
			break;
		}

		if(solution[i] == 0){
			for(int j = 0; j <= 10; j++){
				*((*pic)(x+j, y)) = red;
			}
			x+=10;
		}

		if(solution[i] == 1){
			for(int j = 0; j <= 10; j++){
				*((*pic)(x, y+j)) = red;
			}
			y+=10;
		}

		if(solution[i] == 2){
			for(int j = 0; j <= 10; j++){
				*((*pic)(x-j, y)) = red;
			}
			x-=10;
		}

		if(solution[i] == 3){
			for(int j = 0; j <= 10; j++){
				*((*pic)(x, y-j)) = red;
			}
			y-=10;
		}
	}

	for(int k = x-4; k < x+5; k++){
		*((*pic)(k, y+5)) = white;
	}

	return pic;
}
