#include "image.h"
#include <iostream>

void Image::flipleft(){
	size_t h = this->height();
	size_t w = this->width();

	for (size_t x = 0; x < w/2; x++)
	{
		for (size_t y = 0; y < h; y++)
		{
			uint8_t tempRed = 0;
			uint8_t tempGreen = 0;
			uint8_t tempBlue = 0;
			uint8_t tempAlpha = 0;

			tempRed = (*this)(x,y)->red;
			(*this)(x,y)->red = (*this)(w-x-1,y)->red;
			(*this)(w-x-1,y)->red = tempRed;

			tempGreen = (*this)(x,y)->green;
			(*this)(x,y)->green = (*this)(w-x-1,y)->green;
			(*this)(w-x-1,y)->green = tempGreen;

			tempBlue = (*this)(x,y)->blue;
			(*this)(x,y)->blue = (*this)(w-x-1,y)->blue;
			(*this)(w-x-1,y)->blue = tempBlue;

			tempAlpha = (*this)(x,y)->alpha;
			(*this)(x,y)->alpha = (*this)(w-x-1,y)->alpha;
			(*this)(w-x-1,y)->alpha = tempAlpha;
		}
	}
}

void Image::adjustbrightness(int r,int g,int b){

	for (size_t x = 0; x < this->width(); x++){
		for(size_t y = 0; y < this->height(); y++){
			int temp;
			temp = ((*this)(x,y)->red) + r;
			if(temp < 0)
				(*this)(x,y)->red = 0;
			else if(temp > 255)
				(*this)(x,y)->red = 255;
			else
				(*this)(x,y)->red = temp;

			temp = ((*this)(x,y)->blue) + b;
			if(temp < 0)
				(*this)(x,y)->blue = 0;
			else if(temp > 255)
				(*this)(x,y)->blue = 255;
			else
				(*this)(x,y)->blue = temp;

			temp = ((*this)(x,y)->green) + g;
			if(temp < 0)
				(*this)(x,y)->green = 0;
			else if(temp > 255)
				(*this)(x,y)->green = 255;
			else
				(*this)(x,y)->green = temp;						
		}
	}
}		

void Image::invertcolors(){
	for(size_t x = 0; x < this->width(); x++){
		for(size_t y= 0; y < this->height(); y++){
			(*this)(x,y)->red = 255-(*this)(x,y)->red;
			(*this)(x,y)->green = 255-(*this)(x,y)->green;
			(*this)(x,y)->blue = 255-(*this)(x,y)->blue;
		}
	}
}
