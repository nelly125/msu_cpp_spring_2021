//
// Created by nelly on 3/29/21.
//

#pragma once

#include <iostream>
#include <cstdint>
#include <cassert>
#include "TokenParser.hpp"

void end();

/*** Functions for the first test with nullptr ***/

void sum_of_numbers(const uint64_t number);

void sum_of_string_tokens(const std::string &str);

void test_1_without_callback_functions();

void test_2_with_strings_and_numbers();

void test_3_mixed_string();

void test_4_with_delimiters();

void test_5_digit_more_than_uint64();

void test_6_symbols();