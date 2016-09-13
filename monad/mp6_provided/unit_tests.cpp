/**
 * MP5 Provided Test Cases.
 * Ported by Jack Toole
 */

#include "algorithm"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "png.h"
#include "proxy.h"
#include "no_sort.h"
#include "kdtree.h"

#if MP_PART(2)
#include "maptiles.h"
#endif

using namespace std;
using namespace util;

#define GENERATE_SOLUTIONS 0

template <int K>
string printTree(const KDTree<K> & tree)
{
	stringstream output;
	tree.printTree(output);
	return output.str();
}

#if GENERATE_SOLUTIONS
#define ASSERT_TREE_EQUALS(tree, filename)        \
	do {                                          \
		string output = printTree(tree);          \
		ofstream fout(string(filename).c_str());  \
		fout << output;                           \
		fout.close();                             \
	} while (0)
#else
#define ASSERT_TREE_EQUALS(tree, filename)        \
	do {                                          \
		string output = printTree(tree);          \
		cout << output;                           \
		ASSERT(output == readFile(filename));     \
	} while (0)
#endif

#if MP_PART(1)

UNIT_TEST(testSmallerDimVal, 1, 1, 5000)
{
	vector<Point<3> > pts;
	KDTree<3> tree(pts);
	Point<3> a(1, 2, 3);
	Point<3> b(3, 2, 1);
	
	ASSERT_EQUALS(true,  tree.smallerDimVal(a, b, 0));
	ASSERT_EQUALS(false, tree.smallerDimVal(a, b, 2));
	ASSERT_EQUALS(true,  tree.smallerDimVal(a, b, 1));
}

UNIT_TEST(testShouldReplace, 1, 1, 5000)
{
	vector<Point<3> > pts;
	KDTree<3> tree(pts);
	
	Point<3> target(1, 3, 5);
	Point<3> currentBest1(1, 3, 2);
	Point<3> possibleBest1(2, 4, 4);
	Point<3> currentBest2(1, 3, 6);
	Point<3> possibleBest2(2, 4, 4);
	Point<3> currentBest3(0, 2, 4);
	Point<3> possibleBest3(2, 4, 6);

	ASSERT_EQUALS(true,  tree.shouldReplace(target, currentBest1, possibleBest1));
	ASSERT_EQUALS(false, tree.shouldReplace(target, currentBest2, possibleBest2));
	ASSERT_EQUALS(false, tree.shouldReplace(target, currentBest3, possibleBest3));
}


template <int K>
void testLinearCtor(int size)
{
	vector<Point<K> > points;
	points.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Point<K> p;
		for (int j = 0; j < K; j++)
			p[j] = i;
		points.push_back(p);
	}

	KDTree<K> tree(points);

	ASSERT_TREE_EQUALS(tree, "soln_testLinearCtor_" + to_string(K) + "_" + to_string(size) + ".out");
}

UNIT_TEST(testLinearCtor_1_10, 1, 1, 5000) { testLinearCtor<1>(10); }
UNIT_TEST(testLinearCtor_3_31, 1, 1, 5000) { testLinearCtor<3>(31); }

template <int K>
void testLinearNNS(int size)
{
	vector< Point<K> > points;
	points.reserve(size);
	for (int i = 0; i < size; i++)
	{
		Point<K> p;
		for (int j = 0; j < K; j++)
			p[j] = i;
		points.push_back(p);
	}
	
	KDTree<K> tree(points);

	for (size_t i = 0; i < points.size(); i++)
		ASSERT_EQUALS(points[i], tree.findNearestNeighbor(points[i]));
}

UNIT_TEST(testLinearNNS_1_10, 1, 1, 5000) { testLinearNNS<1>(10); }
UNIT_TEST(testLinearNNS_3_31, 1, 1, 5000) { testLinearNNS<3>(31); }


UNIT_TEST(testDeceptiveNNOneLevelCtor, 1, 1, 5000)
{
	double coords[6][2] = {{-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};

	vector< Point<2> > points;
	for (int i = 0; i < 6; ++i)
		points.push_back(Point<2>(coords[i]));

	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testDeceptiveNNOneLevelCtor.out");
}

UNIT_TEST(testDeceptiveNNOneLevelNNS, 1, 1, 5000)
{
	double coords[6][2] = {{-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};
	double targetCoords[2] = {-13,1};
	double expectedCoords[2] = {-13,-1};

	vector< Point<2> > points;
	for (int i = 0; i < 6; ++i)
		points.push_back(Point<2>(coords[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);

	KDTree<2> tree(points);
	
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
}

UNIT_TEST(testMinesCtor, 1, 1, 5000)
{
	//                              NN
	double coords[10][2] = {{-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7}, 
	                       {2, -7}, {3, 0}, {5, -4}, {6, -3}, {7, -6}};
	//                     M        M       M        M        M
	bool isMine[10] = { false, false, false, false, false, true, true, true, true, true };

	vector< Point<2> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<2>(coords[i], isMine[i]));
	
	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testMinesCtor.out");
}

UNIT_TEST(testMinesNNS, 1, 1, 5000)
{
	//                              NN
	double coords[10][2] = {{-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7}, 
	                       {2, -7}, {3, 0}, {5, -4}, {6, -3}, {7, -6}};
	//                     M        M       M        M        M
	bool isMine[10] = { false, false, false, false, false, true, true, true, true, true };
	double targetCoords[2] = {-7,5};
	double expectedCoords[2] = {-6,4};

	vector< Point<2> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<2>(coords[i], isMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);
	// Turn on land mines to make sure we don't step on them
	Point<2>::enable_mines_provided = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<2>::enable_mines_provided = false;
}


double deceptiveMinesCoords[20][2] = {
	{84, 44}, // mine
	{74, 0},  // mine
	{54, 62}, // mine
	{59, 0},  // mine
	{34, 15}, // mine
	{42, 63},
	{96, 56}, // mine
	{44, 79},
	{44, 43},
	{28, 10}, // mine
	{60, 30}, // mine
	{88, 72}, // mine
	{75, 68}, // mine
	{43, 65},
	{48, 0},  // mine
	{14, 15}, // mine
	{49, 83},
	{51, 35},
	{95, 50}, // mine
	{82, 20}};// mine
bool deceptiveMinesIsMine[20] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1};

UNIT_TEST(testDeceptiveMinesCtor, 1, 1, 5000)
{
	double targetCoords[2] = {45, 59};
	double expectedCoords[2] = {42, 63};

	vector< Point<2> > points;
	for (int i = 0; i < 20; ++i)
		points.push_back(Point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testDeceptiveMinesCtor.out");
}

UNIT_TEST(testDeceptiveMinesNNS, 1, 1, 5000)
{
	double targetCoords[2] = {45, 59};
	double expectedCoords[2] = {42, 63};

	vector< Point<2> > points;
	for (int i = 0; i < 20; ++i)
		points.push_back(Point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
	Point<2> target(targetCoords);
	Point<2> expected(expectedCoords);
	
	KDTree<2> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<2>::enable_mines_provided = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<2>::enable_mines_provided = false;
}


double tieBreakingCoords[14][3] = {
	{0, 0, 100}, // mine
	{0, 100, 100},  // mine
	{0, 50, 50},  // mine
	{0, 0, 50}, // mine
	{100, 0, 100}, // mine
	{100, 100, 0},
	{0, 0, 0},
	{0, 50, 0},  // mine
	{50, 0, 0}, // mine
	{50, 0, 50}, // mine
	{100, 0, 0}, // mine
	{50, 50, 0},
	{0, 100, 0},  // mine
	{50, 50, 50}
};

UNIT_TEST(testTieBreakingCtor, 1, 1, 5000)
{
	vector< Point<3> > points;
	for (int i = 0; i < 14; ++i)
		points.push_back(Point<3>(tieBreakingCoords[i]));
	
	KDTree<3> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testTieBreakingCtor.out");
}

UNIT_TEST(testTieBreakingNNS, 1, 1, 5000)
{
	double targetCoords[3] = {50, 100, 0};
	double expectedCoords[3] = {0, 100, 0};
	double targetCoords2[3] = {14, 17, 20};
	double expectedCoords2[3] = {0, 0, 0};

	vector< Point<3> > points;
	for (int i = 0; i < 14; ++i)
		points.push_back(Point<3>(tieBreakingCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	Point<3> target2(targetCoords2);
	Point<3> expected2(expectedCoords2);
	
	KDTree<3> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<3>::enable_mines_provided = true;
	ASSERT_EQUALS(expected,  tree.findNearestNeighbor(target));
	ASSERT_EQUALS(expected2, tree.findNearestNeighbor(target2));
	Point<3>::enable_mines_provided = false;
}


double leftRecurseCoords[10][3] = {
	{5, 3, 1},
	{3, 1, 10},
	{2, 0, 8},
	{4, 3, 0},
	{0, 2, 9},
	{10, 10, 10},
	{11, 11, 11},
	{12, 12, 12},
	{13, 13, 13},
	{14, 14, 14}
};

UNIT_TEST(testLeftRecurseCtor, 1, 1, 5000)
{
	double targetCoords[3] = {1, 1, 9};
	double expectedCoords[3] = {0, 2, 9};

	vector< Point<3> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<3>(leftRecurseCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	
	KDTree<3> tree(points);
	ASSERT_TREE_EQUALS(tree, "soln_testLeftRecurseCtor.out");
}

UNIT_TEST(testLeftRecurseNNS, 1, 1, 5000)
{
	double targetCoords[3] = {1, 1, 9};
	double expectedCoords[3] = {0, 2, 9};

	vector< Point<3> > points;
	for (int i = 0; i < 10; ++i)
		points.push_back(Point<3>(leftRecurseCoords[i]));
	Point<3> target(targetCoords);
	Point<3> expected(expectedCoords);
	
	KDTree<3> tree(points);

	// Turn on land mines to make sure we don't step on them
	Point<3>::enable_mines_provided = true;
	ASSERT_EQUALS(expected, tree.findNearestNeighbor(target));
	Point<3>::enable_mines_provided = false;
}

#endif

#if MP_PART(2)

UNIT_TEST(testCheckeredMosaic, 1, 1, 5000)
{
	PNG sourcePNG("testsource.png");
	SourceImage source(sourcePNG, 8);

	vector<TileImage> tileList;
	PNG a(1,1);
	PNG b(1,1);
	PNG c(1,1);
	*a(0,0) = RGBAPixel(255, 0, 0);
	*b(0,0) = RGBAPixel(0, 255, 0);
	*c(0,0) = RGBAPixel(0, 0, 255);
	tileList.push_back(TileImage(a));
	tileList.push_back(TileImage(b));
	tileList.push_back(TileImage(c));

	MosaicCanvas* canvas = mapTiles(source, tileList);
	if (canvas == NULL)
		FAIL("ERROR: Returned NULL MosaicCanvas when shouldn't have");

	PNG soln_testmaptiles("soln_testmaptiles.png");
	ASSERT(canvas->drawMosaic(10) == soln_testmaptiles);

	delete canvas;
}

#endif
