#include <algorithm>
#include <iostream>

#include "png.h"
#include "rgbapixel.h"

using namespace std;

PNG rotate(PNG in, PNG out){
	for(size_t y = 0; y < in.height(); y++){
		for(size_t x = 0; x < in.width(); x++){
			out(x,y)->red = in(in.width()-x-1, in.height()-y-1)->red;
			out(x,y)->green = in(in.width()-x-1, in.height()-y-1)->green;
			out(x,y)->blue = in(in.width()-x-1, in.height()-y-1)->blue;
			out(x,y)->alpha = in(in.width()-x-1, in.height()-y-1)->alpha;
		}
	}
	return out;
}

int main(){
	PNG in("in.png");
	PNG out("in.png");
	out = rotate(in, out);
    	out.writeToFile("out.png");
	return 0;
}
