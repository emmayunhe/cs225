// Cs 225 Lab06 Unit Tests

#include "stack"
#include "queue"
#include <iostream>
#include <sstream>
#include <string>

#include "proxy.h"
#include "util.h"

#include "exercises.h"
#include "quackfun.h"

using namespace std;
using namespace util;

// sumDigits
#if MONAD_SPLIT
UNIT_TEST(sumDigits_243, 3, 3, 1000)
{
	ASSERT_EQUALS(9, RecursionExercises::sumDigits(243));
}

UNIT_TEST(sumDigits_49, 2, 2, 1000)
{
	ASSERT_EQUALS(13, RecursionExercises::sumDigits(49));
}

UNIT_TEST(sumDigits_1, 2, 2, 1000)
{
	ASSERT_EQUALS(1, RecursionExercises::sumDigits(1));
}

UNIT_TEST(sumDigits_0, 3, 3, 1000)
{
	ASSERT_EQUALS(0, RecursionExercises::sumDigits(0));
}
#endif


// triangle
#if MONAD_SPLIT
UNIT_TEST(triangle_0, 2, 2, 1000)
{
	ASSERT_EQUALS(0, RecursionExercises::triangle(0));
}

UNIT_TEST(triangle_3, 2, 2, 1000)
{
	ASSERT_EQUALS(6, RecursionExercises::triangle(3));
}

UNIT_TEST(triangle_6, 3, 3, 1000)
{
	ASSERT_EQUALS(21, RecursionExercises::triangle(6));
}

UNIT_TEST(triangle_8, 3, 3, 1000)
{
	ASSERT_EQUALS(36, RecursionExercises::triangle(8));
}
#endif


// sum
#if MONAD_SPLIT
UNIT_TEST(sum_136, 20, 20, 1000)
{
	stack<int> s;
	for (int i = 0; i <= 16; i++)
		s.push(i);
	stack<int> s2 = s;
	
	int sum = QuackFun::sum<int>(s);
	
	if (sum != 136)
		FAIL("Expected sum = 136; Actual = " + to_string(sum));
	else if (s != s2)
		FAIL("Stack was modified");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(sum_floats, 20, 20, 1000)
{
    stack<double> s;
    for (int i = 0; i <= 10; i++)
        s.push(2.1+4.5*i);
    stack<double> s2 = s;

    stack<double>::_ctor_count = 0;
    double sum = QuackFun::sum<double>(s);
    
    if (sum < 270.59 || sum > 270.61)
        FAIL("Expected sum = 270.6; Actual = " + to_string(sum));
    else if (s != s2)
        FAIL("Stack was modified");
    else if (stack<double>::_ctor_count != 0)
        FAIL("You may not make a second stack object");
}
#endif


// scramble
#if MONAD_SPLIT
UNIT_TEST(scramble_17, 20, 20, 1000)
{
	queue<int> q;
	for (int i = 1; i <= 17; i++)
		q.push(i);

	QuackFun::scramble<int>(q);

	stringstream scrambled_output;
	while (!q.empty())
	{
		scrambled_output << q.front() << ' ';
		q.pop();
	}
	string scrambled = scrambled_output.str();
	string expected = "1 3 2 4 5 6 10 9 8 7 11 12 13 14 15 17 16 ";

	cout << "Scrambled queue: " << scrambled << endl;
	cout << "Expected:        " << expected << endl;

	if (scrambled != expected)
		FAIL("See output below");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(scramble_9, 20, 20, 1000)
{
    queue<int> q;
    for (int i = 4; i <= 12; i++)
        q.push(i);

    QuackFun::scramble<int>(q);

    stringstream scrambled_output;
    while (!q.empty())
    {
        scrambled_output << q.front() << ' ';
        q.pop();
    }
    string scrambled = scrambled_output.str();
    string expected = "4 6 5 7 8 9 12 11 10 ";

    cout << "Scrambled queue: " << scrambled << endl;
    cout << "Expected:        " << expected << endl;

    if (scrambled != expected)
        FAIL("See output below");
}
#endif


// verifySame
#if MONAD_SPLIT
UNIT_TEST(verifySame, 10, 10, 1000)
{
	// Test different
	{
		stack<int> s;
		queue<int> q;
		for (int i = 2; i < 7; i++)
		{
			s.push(i);
			q.push(i);
		}
		s.push(4);
		q.push(6);
		for (int i = 7; i < 10; i++)
		{
			s.push(i);
			q.push(i);
		}
		stack<int> sb = s;
		queue<int> qb = q;

		bool result = QuackFun::verifySame(s, q);
		if (result == true)
			FAIL("Expected false, returned true");
		else if (s != sb)
			FAIL("Stack was modified");
		else if (q != qb)
			FAIL("Queue was modified");
	}

	// Test the same
	{
		stack<int> s;
		queue<int> q;
		for (int i = 2; i < 7; i++)
		{
			s.push(i);
			q.push(i);
		}
		stack<int> sb = s;
		queue<int> qb = q;
		
		bool result = QuackFun::verifySame(s, q);
		if (result == false)
			FAIL("Expected true, returned false");
		else if (s != sb)
			FAIL("Stack was modified");
		else if (q != qb)
			FAIL("Queue was modified");
	}
}
#endif

#if MONAD_SPLIT
UNIT_TEST(verifySame_no_modify, 15, 15, 1000)
{
    // Test different
    {
        stack<int> s;
        queue<int> q;
        for (int i = 2; i < 7; i++)
        {
            s.push(i);
            q.push(i);
        }
        s.push(4);
        q.push(6);
        for (int i = 7; i < 10; i++)
        {
            s.push(i);
            q.push(i);
        }
        stack<int> sb = s;
        queue<int> qb = q;

        stack<int>::_ctor_count = 0;
        queue<int>::_ctor_count = 0;
        bool result = QuackFun::verifySame(s, q);
        if (result == true)
            FAIL("Expected false, returned true");
        else if (s != sb)
            FAIL("Stack was modified");
        else if (q != qb)
            FAIL("Queue was modified");
        else if (stack<int>::_ctor_count != 0)
            FAIL("You may not make a second stack object");
        else if (queue<int>::_ctor_count != 0)
            FAIL("You may not make a second queue object");
    }

    // Test the same
    {
        stack<int> s;
        queue<int> q;
        for (int i = 2; i < 7; i++)
        {
            s.push(i);
            q.push(i);
        }
        stack<int> sb = s;
        queue<int> qb = q;
        
        stack<int>::_ctor_count = 0;
        queue<int>::_ctor_count = 0;
        bool result = QuackFun::verifySame(s, q);
        if (result == false)
            FAIL("Expected true, returned false");
        else if (s != sb)
            FAIL("Stack was modified");
        else if (q != qb)
            FAIL("Queue was modified");
        else if (stack<int>::_ctor_count != 0)
            FAIL("You may not make a second stack object");
        else if (queue<int>::_ctor_count != 0)
            FAIL("You may not make a second queue object");
    }
}
#endif
