/**
 * mosaiccanvas.h
 *
 * This is the actual mosaic data-structure which will hold the matrix
 * of sub-images to be written.  This is effectively just a 2-D array
 * of TileImage objects which can be accessed via convenience methods.
 *
 * Authors:
 * Jack Toole
 * Matt Sachtler
 * Scott Wegner
 *
 * Developed for CS225 PhotoMosaic MP, Fall 2008
 * Rewritten Fall 2011 by Jack Toole
 */

#ifndef MOSAICCANVAS_H
#define MOSAICCANVAS_H

#include <vector>
#include "png.h"
#include "tileimage.h"

using namespace std;

class MosaicCanvas
{
	public:
	static bool enableOutput;

	/**
	 * Default constructor
	 *
	 * @param theRows Number of rows to divide the canvas into
	 * @param theColumns Number of columns to divide the canvas into
	 */
	MosaicCanvas(int theRows, int theColumns);

	/**
	 * Copy constructor
	 *
	 * @param source The MosaicCanvas object to copy
	 */
	MosaicCanvas(const MosaicCanvas& source);

	/**
	 * Retrieve the number of rows of images
	 *
	 * @return The number of rows in the mosaic, or -1 on error
	 */
	int getRows() const;

	/**
	 * Retrieve the number of columns of images
	 *
	 * @return The number of columns in the mosaic, or -1 on error
	 */
	int getColumns() const;

	/**
	 * Set the TiledImage for a particular region.  Note
	 * that row and tile indices should be zero-based.
	 *
	 * @param row The row
	 * @param column The column
	 * @param i The TileImage to set
	 *
	 * @return 0 on success, or non-zero otherwise
	 */
	void setTile(int row, int column, const TileImage & img);

	/**
	 * Retrieve the current TileImage for a particular
	 * row and column.  If the row or column is out of
	 * bounds, the default TileImage is returned.  Note
	 * that row and tile indices should be zero-based.
	 *
	 * @param row The row
	 * @param column The column
	 *
	 * @return The current TileImage for a particular,
	 * or the default TileImage if none is set.
	 */
	const TileImage & getTile(int row, int column) const;

	/**
	 * Save the current MosaicCanvas as a file with
	 * the following dimensions.  To obtain a reasonable
	 * mosaic, the dimensions should preserve the aspect
	 * ratio set by the Rows and Columns of the MosaicCanvas.
	 *
	 * If the specified file exists on the file system, then
	 * the overwrite parameter specifies how to handle it.  If
	 * overwrite is set to false, then the file will be preserved,
	 * and the method will return an error code.  Otherwise, the
	 * file will be overwritten.
	 *
	 * @param width The width, in pixels
	 * @param height The height, in pixels
	 * @param fileName Name of file on the filesystem to
	 * write to.
	 * @param overwrite If the file exists on the filesystem,
	 * whether to overwrite it.
	 *
	 * @return 0 on success, or non-zero otherwise.
	 */
	PNG drawMosaic(int pixelsPerTile) const;

	private:
	/**
	 * Number of image rows in the Mosaic
	 */
	int rows;
	
	/**
	 * Number of image columns in the Mosaic
	 */
	int columns;

	/**
	 * The actual matrix of Image data
	 */
	vector<TileImage> myImages;

	TileImage & images(int x, int y);
	const TileImage & images(int x, int y) const;

	static uint64_t divide(uint64_t a, uint64_t b);
};

inline TileImage & MosaicCanvas::images(int row, int col)
{
	return myImages[row*columns + col];
}

inline const TileImage & MosaicCanvas::images(int row, int col) const
{
	return myImages[row*columns + col];
}

inline uint64_t MosaicCanvas::divide(uint64_t a, uint64_t b)
{
	return (a + b/2) / b;
}

#endif // _MOSAICCANVAS_H
