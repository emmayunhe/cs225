/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */

     //build a KDtree for tiles
     vector<Point<3>> tiles;
     map<Point <3>, TileImage> map;
     for(size_t i = 0; i < theTiles.size(); i++){
     	RGBAPixel currPixel = theTiles[i].getAverageColor();
     	Point<3> tilePoint(currPixel.red, currPixel.green, currPixel.blue);

     	map[tilePoint] = theTiles[i];
     	tiles.push_back(tilePoint);
     }

     KDTree<3> tileTree(tiles);

     //for MasaicCavas
     int row = theSource.getRows();
     int col = theSource.getColumns();
     MosaicCanvas *canvas = new MosaicCanvas(row, col);
     for(int i = 0; i < row; i++){
     	for(int j = 0; j < col; j++){
     		RGBAPixel regionColor = theSource.getRegionColor(i, j);
     		Point<3>::Point regionPoint(regionColor.red, regionColor.green, regionColor.blue);
     		Point<3>::Point nearestNeighbor = tileTree.findNearestNeighbor(regionPoint);
     		TileImage regionTile = map[nearestNeighbor];
     		canvas->setTile(i, j, regionTile);
     	}
     }


	return canvas;
}
