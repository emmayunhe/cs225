/**
 * @file unit_tests.cpp
 * Unit tests for the Huffman Lab.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "binary_file_reader.h"
#include "decoder.h"
#include "encoder.h"
#include "huffman_tree.h"

#include "proxy.h"


#include <fstream>
#include <unordered_map>

using namespace std;

#define ADD_CHAR(c, freq) \
	do { \
		for( int i = 0; i < freq; ++i ) \
			text << c; \
	} while( 0 )

void buildText() {
	ofstream text( "text.txt" );
	ADD_CHAR( 'a', 20 );
	ADD_CHAR( 'b', 30 );
	ADD_CHAR( 'c', 60 );
	ADD_CHAR( 'd', 40 );
	text.close();
}

void buildText2() {
	ofstream text( "text.txt" );
    ADD_CHAR( 'a', 5 );
    ADD_CHAR( 'b', 6 );
    ADD_CHAR( 'c', 12 );
    ADD_CHAR( 'd', 13 );
    ADD_CHAR( 'e', 7 );
    ADD_CHAR( 'f', 8 );
	text.close();
}

void buildText( int start ) {
    ofstream text( "text.txt" );
    for( char c = 'a'; c < 'f'; ++c ) {
        ADD_CHAR( c, start );
        start *= 2;
    }
    text << endl;
    text.close();
}

void compareBinaryFiles( string yourFile, string ourFile ) {
	ifstream yourBinary( yourFile, ios::binary );
	stringstream yours;
	yours << yourBinary.rdbuf();
	ifstream ourBinary( ourFile, ios::binary );
	stringstream ours;
	ours << ourBinary.rdbuf();
	if( yours.str() != ours.str() )
		FAIL( "Your binary file \"" + yourFile + "\" does not match our binary file \"" + ourFile + "\"");
}

HuffmanTree constructTree( string inputFile ) {
	ifstream toEncode( inputFile );
	stringstream data;
	data << toEncode.rdbuf();
	string str(data.str());
	unordered_map<char, int> freqs;
	for( size_t i = 0; i < str.length(); ++i )
		freqs[str[i]]++;
	vector<Frequency> buildWith;
	for( auto it = freqs.begin(); it != freqs.end(); ++it )
		buildWith.push_back( Frequency( it->first, it->second ) );
	return HuffmanTree( buildWith );
}

UNIT_TEST(test_encoder_binary, 0, 1, 1000)
{
	buildText();
	encoder::encodeFile( "text.txt", "test.bin", "tree.huff" );
	compareBinaryFiles( "test.bin", "soln_test.bin" );
}

UNIT_TEST(test_encoder_binary2, 0, 1, 1000)
{
	buildText2();
	encoder::encodeFile( "text.txt", "test.bin", "tree.huff" );
	compareBinaryFiles( "test.bin", "soln_test2.bin" );
}

UNIT_TEST(test_encoder_writetree, 0, 1, 1000)
{
	buildText();
	encoder::encodeFile( "text.txt", "test.bin", "tree.huff" );
	compareBinaryFiles( "tree.huff", "soln_tree.huff" );
}

UNIT_TEST(test_encoder_writetree2, 0, 1, 1000)
{
	buildText2();
	encoder::encodeFile( "text.txt", "test.bin", "tree.huff" );
	compareBinaryFiles( "tree.huff", "soln_tree2.huff" );
}

UNIT_TEST(test_decode, 0, 1, 1000)
{
	buildText();
	HuffmanTree htree = constructTree( "text.txt" );
	BinaryFileReader bfile( "soln_test.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	ASSERT_EQUALS( expected.str(), decoded );
}

UNIT_TEST(test_decode2, 0, 1, 1000)
{
	buildText2();
	HuffmanTree htree = constructTree( "text.txt" );
	BinaryFileReader bfile( "soln_test2.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	ASSERT_EQUALS( expected.str(), decoded );
}

UNIT_TEST(test_decode_readtree, 0, 1, 1000)
{
	buildText();
	decoder::decodeFile( "soln_test.bin", "soln_tree.huff", "out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "text.txt" );
	expected << expect.rdbuf();
	ifstream out( "out.txt" );
	decoded << out.rdbuf();
	ASSERT_EQUALS( expected.str(), decoded.str() );
}

UNIT_TEST(test_decode_readtree2, 0, 1, 1000)
{
	buildText2();
	decoder::decodeFile( "soln_test2.bin", "soln_tree2.huff", "out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "text.txt" );
	expected << expect.rdbuf();
	ifstream out( "out.txt" );
	decoded << out.rdbuf();
	ASSERT_EQUALS( expected.str(), decoded.str() );
}

VALGRIND_TEST(test_the_works, 0, 2, 5000)
{
    buildText( 2 );
    encoder::encodeFile( "text.txt", "test.bin", "tree.huff" );
    decoder::decodeFile( "test.bin", "tree.huff", "out.txt" );
    stringstream expected;
    stringstream decoded;
    ifstream expect( "test.txt" );
    expected << expect.rdbuf();
    ofstream out( "out.txt" );
    decoded << out.rdbuf();
    ASSERT_EQUALS( expected.str(), decoded.str() );
    compareBinaryFiles( "tree.huff", "soln_tree_2.huff" );
    compareBinaryFiles( "test.bin", "soln_test_2.bin" );
}
