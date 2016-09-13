/*
	point.h

	Written by Matt Sachtler for CS225 MP6
	Spring 2009
	Revision history:
		3/21/2009		Created
*/

#ifndef __POINT_H__
#define __POINT_H__

#include <cstdarg>
#include <iostream>
#include <stdexcept>

using std::out_of_range;
using std::cout;
using std::endl;

template<int Dim>
class Point
{
  public:
	static bool enable_mines_provided;

  private:
	double vals[Dim];
	bool am_mine;

  public:
	Point();
	Point(double arr[Dim]);
	Point(double arr[Dim], bool mine);
	template <typename T>
	Point(T x, ...);
	template <typename T>
	Point(T x0, T x1, T x2);

	double operator[](int index) const;
	double & operator[](int index);
	bool operator==(const Point<Dim> p) const;
	bool operator!=(const Point<Dim> p) const;
	bool operator<(const Point<Dim> p) const;
	bool operator<=(const Point<Dim> p) const;
	bool operator>(const Point<Dim> p) const;
	bool operator>=(const Point<Dim> p) const;

	void set(int index, double val);
	bool is_mine() { return am_mine; }

	void print(std::ostream & out = std::cout) const;
};

template<int Dim>
std::ostream & operator<<(std::ostream & out, const Point<Dim> & p);

#include "point.cpp"

#endif
