#include "mazereader.h"

MazeReader::MazeReader(const PNG & image)
	: width((image.width() - 1) / 10),
	  height((image.height() - 1) / 10),
	  walls(width * height)
{
	RGBAPixel black(0, 0, 0);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (*image(x * 10 + 10, y * 10 + 5) == black)
				walls[y*height + x] |= RIGHTWALL;
			if (*image(x*10 + 5, y * 10 + 10) == black)
				walls[y*height + x] |= DOWNWALL;
		}
	}

	int x = 0;
	int y = 0;
	RGBAPixel red(255, 0, 0);
	while (true)
	{
		if (*image(x*10 + 6, y*10 + 5) == red && (solution.empty() || solution.back() != LEFT))
		{
			solution.push_back(RIGHT);
			x++;
		}
		else if (*image(x*10 + 5, y*10 + 6) == red && (solution.empty() || solution.back() != UP))
		{
			solution.push_back(DOWN);
			y++;
		}
		else if (*image(x*10 + 4, y*10 + 5) == red && (solution.empty() || solution.back() != RIGHT))
		{
			solution.push_back(LEFT);
			x--;
		}
		else if (*image(x*10 + 5, y*10 + 4) == red && (solution.empty() || solution.back() != DOWN))
		{
			solution.push_back(UP);
			y--;
		}
		else break;
	}

	destination_x = x;
	destination_y = y;
}

bool MazeReader::isWallInDir(int x, int y, int dir) const
{
	if (dir == LEFT) { x--; dir = RIGHT; }
	if (dir == UP) { y--; dir = DOWN; }
	if (x < 0 || y < 0) return true;
	if (x >= width || y >= height) return true;
	wall_t wall = (dir == RIGHT) ? RIGHTWALL : DOWNWALL;
	return isWall(x, y, wall);
}
