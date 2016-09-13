/**
 * lab_gdb Unit Tests
 * Written for Fall 2011 by Jack Toole.
 * Modified for Spring 2012 by Chase Geigle.
 * Modified for Spring 2014 by Veer Dedhia.
 */
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <map>

/**
 * Attempt to prevent students from cheating by using stl reverse.
 */
template <class RandomAccessIterator>
void reverse(RandomAccessIterator first, RandomAccessIterator last) {}

#include "proxy.h"
#include "list.h"

using namespace std;

/**
 * Enumeration of ways to check a given List.
 */
enum check_t
{
	CHECK_NONE	 = 0x0,
	CHECK_SIZE	 = 0x1,
	CHECK_FORWARD  = 0x2,
	CHECK_ALL	  = 0x7
};

/**
 * Helper function that checks a given list against a solution vector.
 *
 * @param list List to check.
 * @param vect Solution vector.
 * @param whichcheck Which type of check to run.
 * @return A pair that contains boolean values: first is size, second is forward traversal
 */
pair<bool, bool> checkList(List<int> const & list, vector<int> const & vect, check_t whichcheck)
{
	pair<bool, bool> ret;
	ret.first = ret.second = true;

	if (whichcheck == CHECK_NONE)
		return ret;

	if ((whichcheck & CHECK_SIZE) != 0)
		ret.first = (vect.size() == static_cast<size_t>(list.size())); // need static cast here because list.size() is int

	if ((whichcheck & CHECK_FORWARD) != 0)
	{
		vector<int> forward(list.begin(), list.end());
		ret.second = (forward == vect);
	}

	return ret;
}

/**
 * Helper function for use in test cases that will cause a test case to
 * fail if the given list does not match the solution vector with the given
 * check.
 *
 * @param list List to be checked.
 * @param vect Solution vector.
 * @param whichcheck Type of check to run.
 */
void assertListEquals(List<int> const & list, vector<int> const & vect, check_t whichcheck)
{
	pair<bool, bool> result = checkList(list, vect, whichcheck);
	cout << list << endl;
	if (!result.first)
		FAIL("List does not match solution's size");
	if (!result.second)
		FAIL("List does not match solution");
}

void savePointersToMap(map<const int *, int> * pointerMap, List<int> const & list) {
	for (List<int>::iterator it = list.begin(); it != list.end(); ++it)
		(*pointerMap)[&(*it)] = *it;
}

/**
 * Constructs a map that keeps track of ListNode data. 
 *
 * Keys are the memory locations of the data elements, and values are the 
 * value of the data elements theselves. To check if there are new ListNode
 * allocations, we can iterate over a given list and check that all of the
 * data elements memory locations are in our map. To check if data elements
 * have been modified, we can check the data stored in the map associated
 * with a ListNode's data element's memory location.
 *
 * @param list List to create the map from
 * @return A pointer to a map that stores information about ListNodes in the parameter list. We will need to free this when done.
 */
map<const int *, int> * makeListNodeMap(List<int> const & list) {
	map<const int *, int> * pointerMap = new map<const int *, int>();
	savePointersToMap(pointerMap, list);
		return pointerMap;
}


/**
 * Checks a given list against a map of ListNode data created from
 * makeListNodeMap.
 *
 * Performs memory checks against a given List to see if students have
 * allocated new memory for ListNodes or have modified data elements.
 *
 * @see makeListNodeMap(List<int>)
 * @param list List to check against the map
 * @param pointerMap Pointer to the map that we are using for our check.
 */
void checkListAgainstMap(List<int> const & list, map<const int *, int> * pointerMap) {
	for (List<int>::iterator it = list.begin(); it != list.end(); ++it) {
		if (pointerMap->find(&(*it)) == pointerMap->end())
			FAIL("Function allocated new ListNodes");
		if ((*pointerMap)[&(*it)] != *it)
			FAIL("Function modified ListNode data elements");
	}
}

/**
 * Compiler macros that save typing in writing the test cases.
 */
#define SAVE_POINTERS(list) \
	map<const int *, int> * pointerMap = makeListNodeMap(list);

#define SAVE_MORE_POINTERS(list) \
	savePointersToMap(pointerMap, list);

#define CHECK_POINTERS(list, check_ptrs) \
	if (check_ptrs) { \
		checkListAgainstMap(list, pointerMap); \
	} \
	delete pointerMap;


// first score is for the part, second for full MP
UNIT_TEST(testInsertFront, 5, 5, 1000)
{
	List<int> list;
	vector<int> soln;
	for (int i = 0; i < 14; i++)
	{
		list.insertFront(i);
		soln.push_back(14 - i - 1);
	}
	assertListEquals(list, soln, CHECK_ALL);
}

//@todo change timeout
UNIT_TEST(testInsertBack, 15, 15, 10000)
{
	List<int> list;
	vector<int> soln;
	for (int i = 0; i < 7; i++)
	{
		list.insertBack(i);
		soln.push_back(i);
	}
	assertListEquals(list, soln, CHECK_ALL);
}

//@todo change timeout
VALGRIND_TEST(testDestructor10, 10, 10, 20000)
{
	List<int> * list = new List<int>();
	vector<int> soln;
	for (int i = 1; i <= 10; i++)
	{
		list->insertBack(i);
		soln.push_back(i);
	}
	assertListEquals(*list, soln, CHECK_FORWARD);
	delete list;
}

VALGRIND_TEST(testDestructor37, 10, 10, 2000)
{
	List<int> list;
	vector<int> soln;
	for (int i = 0; i < 37; i++)
	{
		list.insertFront(i);
		soln.push_back(37 - i - 1);
	}
	assertListEquals(list, soln, CHECK_ALL);
}

void testReverse(int length, check_t whichcheck, bool check_ptrs = true)
{
	List<int> list;
	vector<int> soln;
	for (int i = 0; i < length; i++)
	{
		list.insertFront(i);
		soln.push_back(i);
	}

	SAVE_POINTERS(list);
	list.reverse();
	CHECK_POINTERS(list, check_ptrs);
	assertListEquals(list, soln, whichcheck);
}

/**
 * Reverse tests.
 */
UNIT_TEST(testReverse20_size,				1,	3,	1000)	{	testReverse(20, CHECK_SIZE);			}
UNIT_TEST(testReverse20,					3,	5,	1000)	{	testReverse(20, CHECK_FORWARD);			}
UNIT_TEST(testReverse37_size,				1,	3,	1000)	{	testReverse(37, CHECK_SIZE);			}
UNIT_TEST(testReverse37,					2,	5,	1000)	{	testReverse(37, CHECK_FORWARD);			}
VALGRIND_TEST(testReverse_memory,			5,  4,  10000)  {   testReverse(9, CHECK_ALL);				}
VALGRIND_TEST(testReverseEmpty_memory,		5,  5,  10000)  {   testReverse(0,  CHECK_ALL);				}
VALGRIND_TEST(testReverse20_memory,			3,	5,	10000)	{	testReverse(20, CHECK_ALL);				}


void testShuffle(int length, check_t whichcheck, bool check_ptrs = true)
{
	List<int> list;
	vector<int> soln;

	// Build the list
	for (int i = length; i > 0; i--)
		list.insertFront(i);

	// Build the solution
	int half = (length + 1) / 2;
	for (int i = 1; i <= half; i++)
	{
		soln.push_back(i);
		soln.push_back(i + half);
	}
	if (length % 2 == 1)
		soln.pop_back();

	// check the shuffle
	SAVE_POINTERS(list);
	list.shuffle();
	CHECK_POINTERS(list, check_ptrs);
	assertListEquals(list, soln, whichcheck);
}

/**
 * Shuffle tests.
 */
UNIT_TEST(testShuffle20_size,				1,	5,	1000)	{	testShuffle(20, CHECK_SIZE);			}
UNIT_TEST(testShuffle20,					3,	4,	1000)	{	testShuffle(20, CHECK_FORWARD);			}
UNIT_TEST(testShuffle37_size,				1,	5,	1000)	{	testShuffle(37, CHECK_SIZE);			}
UNIT_TEST(testShuffle37,					2,	4,	1000)	{	testShuffle(37, CHECK_FORWARD);			}
VALGRIND_TEST(testShuffle_memory,			5,  4,  10000)  {   testShuffle(9, CHECK_ALL);				}
VALGRIND_TEST(testShuffleEmpty_memory,		5,  3,  10000)  {   testShuffle(0, CHECK_ALL);				}
VALGRIND_TEST(testShuffle20_memory,			3,	5,	10000)	{	testShuffle(20, CHECK_ALL);				}

