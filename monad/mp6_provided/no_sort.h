/**
 * @file no_sort.h
 * Masks std sorting algorithms with error messages to prevent students from
 *  using the STL's sorting functions.
 * @author Sean Massung
 * @date Summer 2012
 */

#ifndef _NO_SORT_H_
#define _NO_SORT_H_

#include "algorithm"
#include <iostream>
#include <vector>

// included specifically for MP6
#include "point.h"


// tolar2: taken from libc++ 3.5

namespace std {

template <class _ForwardIterator, class _Predicate>
inline _LIBCPP_INLINE_VISIBILITY
_ForwardIterator
partition(_ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    FAIL("std::partition not allowed");
}
 
template <class _InputIterator, class _OutputIterator1,
          class _OutputIterator2, class _Predicate>
pair<_OutputIterator1, _OutputIterator2>
partition_copy(_InputIterator __first, _InputIterator __last,
               _OutputIterator1 __out_true, _OutputIterator2 __out_false,
               _Predicate __pred)
{
    FAIL("std::partition_copy not allowed");
}

template<class _ForwardIterator, class _Predicate>
_ForwardIterator
partition_point(_ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    FAIL("std::partition_point not allowed");
}

template <class _ForwardIterator, class _Predicate>
inline _LIBCPP_INLINE_VISIBILITY
_ForwardIterator
stable_partition(_ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    FAIL("std::stable_partition not allowed");
}


template <class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    FAIL("std::sort not allowed");
}

template <class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
void
sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    FAIL("std::sort not allowed");
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
void
sort(_Tp** __first, _Tp** __last)
{
    FAIL("std::sort not allowed");
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
void
sort(__wrap_iter<_Tp*> __first, __wrap_iter<_Tp*> __last)
{
    FAIL("std::sort not allowed");
}

template <class _Tp, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
sort(__wrap_iter<_Tp*> __first, __wrap_iter<_Tp*> __last, _Compare __comp)
{
    FAIL("std::sort not allowed");
}

template <class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    FAIL("std::stable_sort not allowed");
}

template <class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
void
stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    FAIL("std::stable_sort not allowed");
}

template <class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    FAIL("std::sort_heap not allowed");
}

template <class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
void
sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    FAIL("std::sort_heap not allowed");
}

template <class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
partial_sort(_RandomAccessIterator __first, _RandomAccessIterator __middle, _RandomAccessIterator __last,
             _Compare __comp)
{
    FAIL("std::partial_sort not allowed");
}

template <class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
void
partial_sort(_RandomAccessIterator __first, _RandomAccessIterator __middle, _RandomAccessIterator __last)
{
    FAIL("std::partial_sort not allowed");
}

template <class _InputIterator, class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
_RandomAccessIterator
partial_sort_copy(_InputIterator __first, _InputIterator __last,
                  _RandomAccessIterator __result_first, _RandomAccessIterator __result_last, _Compare __comp)
{
    FAIL("std::partial_sort_copy not allowed");
}

template <class _InputIterator, class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
_RandomAccessIterator
partial_sort_copy(_InputIterator __first, _InputIterator __last,
                  _RandomAccessIterator __result_first, _RandomAccessIterator __result_last)
{
    FAIL("std::partial_sort_copy not allowed");
}

template <class _RandomAccessIterator, class _Compare>
inline _LIBCPP_INLINE_VISIBILITY
void
nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth, _RandomAccessIterator __last, _Compare __comp)
{
    FAIL("std::nth_element not allowed");
}

template <class _RandomAccessIterator>
inline _LIBCPP_INLINE_VISIBILITY
void
nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth, _RandomAccessIterator __last)
{
    FAIL("std::nth_element not allowed");
}

}
 

#endif
