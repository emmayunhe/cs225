#ifndef CARTALK_PUZZLE_H
#define CARTALK_PUZZLE_H

#include <string>
#include <tuple>

#include "pronounce_dict.h"

typedef std::tuple< std::string, std::string, std::string > StringTriple;
typedef std::tuple< std::string, std::string> StringPair;


std::vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                           const std::string& word_list_fname);

#endif /* CARTALK_PUZZLE_H */
