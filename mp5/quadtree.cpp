// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
//mp5.1
//constructor with no arguments
Quadtree::Quadtree(){
	root = NULL;
	resolution = 1;
}

//constructor with 2 arguments
Quadtree::Quadtree(PNG &source, int resolution){
	root = new QuadtreeNode();
	buildTree(source, resolution);
}

//copy constructor
Quadtree::Quadtree(const Quadtree &other){
	resolution = other.resolution;
	copy(root, other.root);
}

//copies tree pointed by the secondNode to the location of firstNode
void Quadtree::copy(QuadtreeNode *&firstNode, QuadtreeNode * const &secondNode){

	if(secondNode == NULL){
		firstNode = NULL;
		return;
	}

	firstNode = new QuadtreeNode();
	firstNode->element = secondNode->element;

	copy(firstNode->neChild, secondNode->neChild);
   	copy(firstNode->nwChild, secondNode->nwChild);
   	copy(firstNode->seChild, secondNode->seChild);
   	copy(firstNode->swChild, secondNode->swChild);

   	return;
}

//destructor
Quadtree::~Quadtree(){
	clear(root);
	resolution = 1;
}

//assignment Operator
Quadtree & Quadtree::operator=(Quadtree const &other){
	resolution = other.resolution;
	if(this!=&other){
		clear(root);
		copy(root, other.root);
	}
	return *this;
}

void Quadtree::buildTree(PNG const &source, int resolution){
	if(root!=NULL){
		clear(root);
	}

	this->resolution = resolution;
	buildTree(root, source, 0, 0, resolution);
}

//helper function for buildTree
void Quadtree::buildTree(QuadtreeNode *&curNode, PNG const &source, int x, int y, int resolution){
	if(resolution == 1){
		curNode = new QuadtreeNode();
		curNode->element = *source(x,y);
		return;
	}

	curNode = new QuadtreeNode();
	buildTree(curNode->nwChild, source, x, y, resolution/2);
	buildTree(curNode->neChild, source, x+resolution/2, y, resolution/2);
	buildTree(curNode->swChild, source, x, y+resolution/2, resolution/2);
	buildTree(curNode->seChild, source, x+resolution/2, y+resolution/2, resolution/2);

	if(curNode->nwChild!=NULL){
		curNode->element.red = (curNode->nwChild->element.red + curNode->neChild->element.red + curNode->seChild->element.red + curNode->swChild->element.red)/4;
		curNode->element.blue = (curNode->nwChild->element.blue + curNode->neChild->element.blue + curNode->seChild->element.blue + curNode->swChild->element.blue)/4;
		curNode->element.green = (curNode->nwChild->element.green + curNode->neChild->element.green + curNode->seChild->element.green + curNode->swChild->element.green)/4;
		//curNode->element.alpha = (curNode->nwChild->element.alpha+curNode->neChild->element.alpha+curNode->seChild->element.alpha+curNode->swChild->element.alpha)/4;
	}
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
	if(root==NULL || x > resolution || y > resolution || x < 0 || y < 0){
		return RGBAPixel();
	}
	else{
		return getPixel(root, x, y, resolution);
	}
}

//helper function for getpixel
RGBAPixel Quadtree::getPixel(QuadtreeNode *curNode, int x, int y, int resolution)const{
	if(curNode->nwChild==NULL || resolution == 1){
		return curNode->element;
	}

	if(x < resolution/2 && y < resolution/2){
		return getPixel(curNode->nwChild, x, y, resolution/2);
	}
	else if(x < resolution/2 && y >= resolution/2){
		return getPixel(curNode->swChild, x, y-resolution/2, resolution/2);
	}
	else if(x >= resolution/2 && y < resolution/2){
		return getPixel(curNode->neChild, x-resolution/2, y, resolution/2);
	}
	else{	
		return getPixel(curNode->seChild, x-resolution/2, y-resolution/2, resolution/2);
	}
}

PNG Quadtree::decompress() const{
	if(root==NULL){
		return PNG();
	}

	PNG result = PNG(resolution, resolution);
	for (int j = 0; j < resolution; j++){
		for (int i = 0; i < resolution; i++){
			*result(i, j) = getPixel(i, j);
		}
	}
	return result;
}

//mp5.2
void Quadtree::clockwiseRotate(){
	if(root==NULL){
		return;
	}
	clockwiseRotate(root);
}

//helper function for clockwiseRotate
void Quadtree::clockwiseRotate(QuadtreeNode *curNode){
	if(curNode->nwChild == NULL){
		return;
	}

	QuadtreeNode *temp1 = curNode->nwChild;
	QuadtreeNode *temp2 = curNode->neChild;
	QuadtreeNode *temp3 = curNode->swChild;
	QuadtreeNode *temp4 = curNode->seChild;

	curNode->nwChild = temp3;
	curNode->neChild = temp1;
	curNode->swChild = temp4;
	curNode->seChild = temp2;

	clockwiseRotate(curNode->nwChild);
	clockwiseRotate(curNode->neChild);
	clockwiseRotate(curNode->swChild);
	clockwiseRotate(curNode->seChild);
}

void Quadtree::prune(int tolerance){
	prune(tolerance, root);
}

//helper function for prune
void Quadtree::prune(int tolerance, QuadtreeNode *curNode){
	if(curNode==NULL){
		return;
	}

	if(curNode->nwChild==NULL){
		return;
	}

	if(checkPrune(curNode, curNode, tolerance)==true){
		clear(curNode->nwChild);
		clear(curNode->neChild);
		clear(curNode->swChild);
		clear(curNode->seChild);

		return;
	}

	prune(tolerance, curNode->nwChild);
	prune(tolerance, curNode->neChild);
	prune(tolerance, curNode->swChild);
	prune(tolerance, curNode->seChild);


}

//helper function for prune
bool Quadtree::checkPrune(QuadtreeNode *root, QuadtreeNode *curNode, int tolerance) const{
	if(curNode->nwChild == NULL){
		int diff = (((root->element).red)-((curNode->element).red)) * (((root->element).red)-((curNode->element).red))
					+ (((root->element).green)-((curNode->element).green)) * (((root->element).green)-((curNode->element).green))
						+ (((root->element).blue)-((curNode->element).blue)) * (((root->element).blue)-((curNode->element).blue));
		if(diff<=tolerance){
			return true;
		}
		else{
			return false;
		}
	}
	bool flag = true;
	flag = checkPrune(root, curNode->nwChild, tolerance) && checkPrune(root, curNode->neChild, tolerance) && checkPrune(root, curNode->swChild, tolerance) && checkPrune(root, curNode->seChild, tolerance);
	return flag;
}

int Quadtree::pruneSize(int tolerance) const{
	return pruneSize(root, tolerance);
}

//helper function for pruneSize
int Quadtree::pruneSize(QuadtreeNode *curNode, int tolerance) const{
	if(curNode==NULL){
		return 0;
	}

	if(checkPrune(curNode, curNode, tolerance)){
		return 1;
	}

	else{
		return 	pruneSize(curNode->nwChild, tolerance) +
				pruneSize(curNode->neChild, tolerance) +
				pruneSize(curNode->swChild, tolerance) +
				pruneSize(curNode->seChild, tolerance);
	}


}

int Quadtree::idealPrune(int numLeaves) const{
	int low = 0, high = 3*255*255;

	return search(numLeaves, low, high);
}

//helper function for idealPrune
int Quadtree::search(int numLeaves, int low, int high) const{
	if(low > high){
		return low;
	}

	int mid = (low+high)/2;
	int leaves =  pruneSize(mid);
	if(leaves > numLeaves){
		return search(numLeaves, mid+1, high);
	}

	return search(numLeaves, low, mid-1);
}




//other private helper functions
//clear function
void Quadtree::clear(QuadtreeNode *&curNode){
	if(curNode==NULL){
		return;
	}

	clear(curNode->nwChild);
	clear(curNode->neChild);
	clear(curNode->swChild);
	clear(curNode->seChild);

	delete curNode;
	curNode = NULL;

	return;
}

