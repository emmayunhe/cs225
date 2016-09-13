#include <stdlib.h>
#include "gradientColorPicker.h"

/**
 * Constructs a new gradientColorPicker.
 *
 * @param fadeColor1 The first color to start the gradient at.
 * @param fadeColor2 The second color to end the gradient with.
 * @param radius How quickly to transition to fadeColor2.
 * @param centerX X coordinate for the center of the gradient.
 * @param centerY Y coordinate for the center of the gradient.
 */
gradientColorPicker::gradientColorPicker( RGBAPixel fadeColor1, 
		RGBAPixel fadeColor2, int radius, int centerX, int centerY ) {
	/** 
	 * @todo Construct your gradientColorPicker here! You may find it
	 *	helpful to create additional member variables to store things.
	 */
	 this->fadeColor1 = fadeColor1;
	 this->fadeColor2 = fadeColor2;
	 _radius = radius;
	 _centerX = centerX;
	 _centerY = centerY;
}

/**
 * Picks the color for pixel (x, y).
 *
 * The first color fades into the second color as you move from the initial
 * fill point, the center, to the radius. Beyond the radius, all pixels
 * should be just color2. 
 *
 * You should calculate the distance between two points using the standard
 * Manhattan distance formula, 
 * 
 * \f$d = |center\_x - given\_x| + |center\_y - given\_y|\f$
 *
 * Then, scale each of the three channels (R, G, and B) from fadeColor1 to
 * fadeColor2 linearly from d = 0 to d = radius. 
 *
 * For example, the red color at distance d where d is less than the radius
 * must be
 *
 * \f$ redFill = fadeColor1.red - \left\lfloor
   \frac{d*fadeColor1.red}{radius}\right\rfloor +
   \left\lfloor\frac{d*fadeColor2.red}{radius}\right\rfloor\f$
 *
 * Note that all values are integers. If you do not follow this formula,
 * your colors may be very close but round differently than ours.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
RGBAPixel gradientColorPicker::operator()(int x, int y)
{
	RGBAPixel color;
	/**
	 * @todo Return the correct color here!
	 */
	int d;
	d = abs(_centerX-x) + abs(_centerY-y);

	if(d >= 0 && d <= _radius){
		color.red = fadeColor1.red - floor(d*fadeColor1.red/_radius) + floor(d*fadeColor2.red/_radius);
		color.blue = fadeColor1.blue - floor(d*fadeColor1.blue/_radius) + floor(d*fadeColor2.blue/_radius);
		color.green = fadeColor1.green - floor(d*fadeColor1.green/_radius) + floor(d*fadeColor2.green/_radius);
		return color;
	}
	return fadeColor2;
}


/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    
    solidColorPicker color(fillColor);
    return filler::dfs::fill(img, x, y, color, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker color(gridColor, gridSpacing);
    return filler::dfs::fill(img, x, y, color, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker color(fadeColor1, fadeColor2, radius, x, y);
    return filler::dfs::fill(img, x, y, color, tolerance, frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */

    return filler::fill<Stack> (img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker color(fillColor);
    return filler::bfs::fill(img, x, y, color, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker color(gridColor, gridSpacing);
    return filler::bfs::fill(img, x, y, color, tolerance, frameFreq);   
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker color(fadeColor1, fadeColor2, radius, x, y);
    return filler::bfs::fill(img, x, y, color, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
    return filler::fill<Queue> (img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure. Then, until the structure is
     * empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure. 
     *
     *        If it has not been processed before and if its color is
     *        within the tolerance distance (up to and **including**
     *        tolerance away in square-RGB-space-distance) to the original
     *        point's pixel color [that is, \f$(currentRed - OriginalRed)^2 +
              (currentGreen - OriginalGreen)^2 + (currentBlue -
              OriginalBlue)^2 \leq tolerance\f$], then: 
     *        1.    indicate somehow that it has been processed (do not mark it
     *              "processed" anywhere else in your code) 
     *        2.    change its color in the image using the appropriate
     *              colorPicker
     *        3.    add all of its neighbors to the ordering structure, and 
     *        4.    if it is the appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq. 
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     */
    animation a;
    OrderingStructure<int> pngX;
    OrderingStructure<int> pngY;
    int w = img.width();
    int h = img.height();
    pngX.add(x);
    pngY.add(y);


    bool** processed = new bool *[w];
    for (int i = 0; i < w; i++){
        processed[i] = new bool [h];
        for (int j = 0; j < h; j++){
            processed[i][j] = false;
        }
    }

    RGBAPixel orig = *img(x,y);
    //RGBAPixel temp;

    int xx, yy;
    int temp_tolerance;
    int total_pixel = 0;
    int Red, Blue, Green;

    while (!pngX.isEmpty() && !pngY.isEmpty()){
        xx = pngX.peek();
        yy = pngY.peek();
        pngX.remove();
        pngY.remove();

        if(xx >= 0 && xx < h && yy >= 0 && yy < w){
            //temp = *img(xx, yy);
            Red = img(xx, yy)->red - orig.red;
            Blue = img(xx, yy)->blue - orig.blue;
            Green = img(xx, yy)->green - orig.green;
            temp_tolerance = Red*Red+Blue*Blue+Green*Green;

            if(!processed[xx][yy] && temp_tolerance<=tolerance){
                *img(xx, yy) = fillColor(xx, yy);
                processed[xx][yy] = true;
                total_pixel++;

                if(xx + 1 < w){
                    if(!processed[xx+1][yy]){
                        pngX.add(xx+1);
                        pngY.add(yy);
                    }
                }

                if(yy + 1 < h){
                    if(!processed[xx][yy+1]){
                        pngX.add(xx);
                        pngY.add(yy+1);
                    }
                }

                if(xx - 1 >= 0){
                    if(!processed[xx-1][yy]){
                        pngX.add(xx-1);
                        pngY.add(yy);
                    }
                }

                if(yy - 1 >= 0){
                    if(!processed[xx][yy-1]){
                        pngX.add(xx);
                        pngY.add(yy-1);
                    }
                }
            }
        }

        if (total_pixel == frameFreq){
            a.addFrame(img);
            total_pixel = 0;
        }

    }

    for (int k=0; k<w; k++){
        delete [] processed[k];
    }
    delete [] processed;


    return a;
}



