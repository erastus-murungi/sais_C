//
// Created by Erastus Murungi on 7/21/22.
//

#ifndef SUFFIX_ARRAY_ERROR_STRINGS_H
#define SUFFIX_ARRAY_ERROR_STRINGS_H

// we don't expect to print more than 256 chars for printing digits
#define MAX_CHARS_FOR_DIGITS (256)

const char * ERR_NULL_STRING_TO_PRINT = "expected string_t for printing but received NULL";
const char * ERR_NULL_CHAR_FIELD = "expected char_t* for but received NULL";
const char * ERR_NULL_STRING = "expected string_t but received NULL";
const char * ERR_CONSTRUCTION_FROM_NULL_STRING = "can't construct string_t from NULL";
const char * ERR_NULL_FILE = "expected FILE but received NULL";
const char * ERR_END_INDEX_OUT_OF_BOUNDS = "end index %zu out for bounds for string ending at %zu";
const char * ERR_START_INDEX_OUT_OF_BOUNDS = "start index %zu out for bounds for string starting at %zu";
const char * ERR_START_INDEX_GT_END_INDEX = "invalid slice: start index > end index";
const char * ERR_NO_STRINGS_TO_JOIN = "not strings to join, count = 0";


#endif //SUFFIX_ARRAY_ERROR_STRINGS_H
