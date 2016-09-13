#include "proxy.h"
#include "btree.h"

#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <numeric>

using namespace std;

const static std::vector<size_t> sizes = {
    10,
    100,
    1000,
    10000,
    100000,
};

vector< pair< int, int > > make_int_data(int n, 
                                         bool random)
{
    vector< pair< int, int > > data;
    if(random)
    {
        for(int i = 0; i < n; i++)
        {
            int rand_val = rand();
            data.emplace_back(rand_val, rand_val);
        }
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            data.emplace_back(i, i);
        }
    }
    return data;
}

template<class K, class V> 
void do_inserts(vector< pair< K, V> >& data, BTree< K, V>& b)
{
    for(auto& key_val : data)
    {
        b.insert(key_val.first, key_val.second);
    }
}

template<class K, class V> 
void verify_finds(vector< pair< K, V> >& data, BTree< K, V>& b)
{
    for(auto& key_val : data)
    {
        V ret = b.find(key_val.first);
        ASSERT_EQUALS(key_val.second, ret);
    }
}

unordered_map< size_t, vector< int > > vecs;


#if MONAD_SPLIT
UNIT_TEST(test_insertion_idx_emp, 10, 10, 1000)
{
    vector< int > v;
    ASSERT_EQUALS(0, insertion_idx(v, 0));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_insertion_idx_small, 10, 10, 1000)
{
    vector< int > data = { 1, 3, 5, 7 };
    ASSERT_EQUALS(0, insertion_idx(data, -1));
    ASSERT_EQUALS(0, insertion_idx(data, 1));
    ASSERT_EQUALS(4, insertion_idx(data, 99));
}
#endif

size_t insertion_idx_time(vector< int >* vec)
{
	// check needed since monad calls this with a vector of size 1 (to ``warm up'' the generator/timing function)
	if (vec->size() <= 2)
	{
		size_t val = 0;
		size_t ret = insertion_idx(*vec, (*vec)[val]);
		ASSERT_EQUALS(val, ret);
		return ret;
	}

	size_t val = 1;
	size_t ret = insertion_idx(*vec, (*vec)[val]);
	ASSERT_EQUALS(val, ret);

	val = vec->size() - 2;
	ret = insertion_idx(*vec, (*vec)[val]);
	ASSERT_EQUALS(val, ret);

	return ret;
}

vector< int >* vec_gen(size_t n)
{
	size_t vec_key = n;
	if(vecs.find(vec_key) == vecs.end())
	{
		vecs[vec_key] = vector< int >(n, 0);
		iota(vecs[vec_key].begin(), vecs[vec_key].end(), 0);
	}
	return &vecs[vec_key];
}

#if MONAD_SPLIT
UNIT_TEST(test_insertion_idx_logn, 10, 10, 10000)
{
	ASSERT_TIME_CURVE(vec_gen, insertion_idx_time, LOGN_TIME, sizes);
}
#endif

#if MONAD_SPLIT
VALGRIND_TEST(test_btree3_small, 10, 10, 5000)
{
    vector< pair< int, int > > data = { {1, 5}, {4, 7}, {5, 43}, {-43, 3},
                                        {99, 2}, {23, 7}, {3, 2}, {9, 4} };
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT_EQUALS(0, b.find(-999));
    ASSERT(b.is_valid(3));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_btree3_large_seq, 10, 10, 1000)
{
    auto data = make_int_data(10000, false);
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT_EQUALS(0, b.find(-9999));
    ASSERT(b.is_valid(3));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_btree3_large_rand, 10, 10, 1000)
{
    srand(225);
    auto data = make_int_data(10000, true);
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT(b.is_valid(3));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_btree64_large_seq, 10, 10, 1500)
{
    auto data = make_int_data(100000, false);
    BTree< int, int > b(64);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT_EQUALS(0, b.find(-9999));
    ASSERT(b.is_valid(64));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_btree64_large_rand, 10, 10, 1500)
{
    srand(225);
    auto data = make_int_data(100000, true);
    BTree< int, int > b(64);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT(b.is_valid(64));
}
#endif

#if MONAD_SPLIT
VALGRIND_TEST(test_btree128_med_rand, 10, 10, 5500)
{
    srand(225);
    auto data = make_int_data(20000, true);
    BTree< int, int > b(128);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT(b.is_valid(128));
}
#endif


#if MONAD_SPLIT
UNIT_TEST(test_btree12_strings, 10, 10, 1000)
{
    vector< pair< string, string> > data = 
                                { {"lls", "skye"}, {"mjoras", "yogi"},
                                  {"collin", "meco"}, {"fred", "skye"},
                                  {"arya", "nymeria"}, {"jon", "ghost"},
                                  {"bran", "summer"}, {"robb", "grey wind"},
                                  {"sansa", "lady"}, {"rickon", "shaggydog"} };
    BTree< string, string > b(5);
    do_inserts(data, b);
    verify_finds(data, b);
    ASSERT(b.is_valid(5));
}
#endif
