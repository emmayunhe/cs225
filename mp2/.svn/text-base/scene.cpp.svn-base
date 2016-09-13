#include "scene.h"
#include <iostream>
using namespace std;
#include "rgbapixel.h"
#include "image.h"
#include "png.h"

Scene::Scene (int max){
	_Image_arr = new Image * [max];
	_x = new int[max];
	_y = new int[max];
	maxnum = max;
	for (int i=0; i < max; i++)
	{
		_Image_arr[i]=NULL;
		_x[i] = 0;
		_y[i] = 0;
	}
}

void Scene::copy (const Scene & source)
{
	maxnum = source.maxnum;
	_Image_arr = new Image * [maxnum];
	_x = new int [maxnum];
	_y = new int [maxnum];
	for (int i = 0; i < maxnum; i++)
	{
		if(source._Image_arr[i] != NULL)
		{
			_Image_arr[i] = new Image (*(source._Image_arr[i]));
			_x[i] = source._x[i];
			_y[i] = source._y[i];
		}
		else
		{
			_Image_arr[i] = NULL;
			_x[i] = source._x[i];
			_y[i] = source._y[i];
		}
	}
}

void Scene::clear()
{
	for (int i = 0; i < maxnum; i++)
	{
		if (_Image_arr[i] != NULL)
			delete _Image_arr [i];
	}
		delete [] _Image_arr;
		delete [] _x;
		delete [] _y;
}

Scene::~Scene(){
	clear();
}

Scene::Scene(const Scene &source){
	copy(source);
}

const Scene & Scene::operator=(const Scene & source){
	if (this != &source){
		clear();
		copy(source);
	}
		return *this;
}

void Scene::changemaxlayers(int newmax){
	if (newmax < maxnum){
		for (int i = newmax; i<maxnum; i++){
			if (_Image_arr[i] != NULL){
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}

	Image **newImage_arr = new Image *[newmax];
	int *_newx = new int [newmax];
	int *_newy = new int [newmax];

	for (int j = 0; j< newmax; j++){
		newImage_arr[j] = NULL;
		_newx[j] = 0;
		_newy[j] = 0;
	}

	int bound;
	if (newmax <= maxnum){
		bound = newmax;
	}
	if (newmax > maxnum){
		bound = maxnum;
	}

	for (int i = 0; i < bound; i++){
		newImage_arr[i] = _Image_arr[i];
		_newx[i] = _x[i];		
		_newy[i] = _y[i];
	}

	delete [] _Image_arr;
	delete [] _x;
	delete [] _y;
	_x = _newx;
	_y = _newy;
	maxnum = newmax;
	_Image_arr = newImage_arr;
	newImage_arr = NULL;
	_newx = NULL;
	_newy = NULL;
}

void Scene::addpicture(const char* FileName, int index, int x, int y){
	if (index>(maxnum-1) || index<0){
		cout << "index out of bounds" << endl;
		return;
	}	

	if (_Image_arr[index] != NULL)
		delete _Image_arr[index];
		
	_Image_arr[index] = new Image();
	_Image_arr[index] -> readFromFile(FileName);
	_x[index] = x;
	_y[index] = y;
}

void Scene::changelayer(int index, int newindex){
	if (index == newindex){
		return;
	}
	if (index >= 0 && newindex >= 0 && index < maxnum && newindex < maxnum){

		if (_Image_arr[newindex] != NULL){
			delete _Image_arr[newindex];
			_Image_arr[newindex] = NULL;
		}
		_Image_arr[newindex] = _Image_arr[index];
		_x[newindex] = _x[index];
		_y[newindex] = _x[index];
		_Image_arr[index] = NULL;
		_x[index] = 0;
		_y[index] = 0;
	}

	else
		cout << "invalid index" << endl;
}

void Scene::translate (int index, int xcoord, int ycoord){
	if(index < 0 || index >= maxnum || (_Image_arr[index] == NULL)){
		cout << "invalid index" << endl;
		return;
	}

	else{
		_x[index] =xcoord;
		_y[index] =ycoord;
	}
}

void Scene::deletepicture(int index){
	if(index < 0 || index >= maxnum || (_Image_arr[index] == NULL)){
		cout << "invalid index" << endl;
		return;
	}
	else{
		delete _Image_arr[index];
		_Image_arr[index] = NULL;
	}
}

Image * Scene::getpicture(int index) const{
	if(index < 0 || index >= maxnum || _Image_arr[index]==NULL){
		cout << "invalid index" << endl;
		return NULL;
	}
	else{
		return _Image_arr[index];
	}
}

Image Scene::drawscene() const{
	Image output;
	if (_Image_arr != NULL){
		unsigned int max_x = 0;
		unsigned int temp_x = 0;
		unsigned int max_y = 0;
		unsigned int temp_y = 0;
		for (int i = 0; i < maxnum; i++){
			if (_Image_arr[i] != NULL){
				temp_x = _x[i]+_Image_arr[i]->width();
				if(temp_x > max_x)
					max_x = temp_x;
				temp_y = _y[i]+_Image_arr[i]->height();
				if(temp_y > max_y)
					max_y = temp_y;
			}
		}

		output.resize(max_x, max_y);

		for (int i=0; i < maxnum; i++){
			if (_Image_arr[i] != NULL){
				int width = _x[i];
				int height = _y[i];
				for (unsigned int j = _x[i]; j < (_x[i] + _Image_arr[i]->width()); j++){
					for (unsigned int k = _y[i]; k < (_y[i] + _Image_arr[i]->height()); k++){
						RGBAPixel color;
						color = (*(*(_Image_arr[i]))(j-width, k-height));
						*output(j,k)= color;
					}
				}
			}
		}
	}
	return output;
}
