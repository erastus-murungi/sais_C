//
// Created by Erastus Murungi on 7/20/22.
//

#ifndef SUFFIX_ARRAY_STRING_TYPE_H
#define SUFFIX_ARRAY_STRING_TYPE_H

#include <sys/types.h>
#include <stdio.h>


typedef char char_t;

struct string_t {
    char_t *chars;
    size_t length;
};

typedef struct string_t string_t;

typedef void char_t_map_fn(char_t s, void *args);

int print_error(const char* error_msg_prefix, const char * file_name, const char *function_name, long line_num);

void* print_error_and_return_null(const char* error_msg_prefix, const char * file_name, const char *function_name, long line_num);

int print_error_and_return_error_code(const char* error_msg_prefix, const char * file_name, const char *function_name, long line_num, int err_code);

string_t* string_new(size_t length);

void string_free(string_t *s);

string_t* string_from(const char *source);

string_t* string_join(const char_t *joiner, int count, ...);

void string_foreach(string_t *s, char_t_map_fn* f, void *args);

string_t* string_substring(string_t *s, size_t from, size_t to);

string_t* string_copy(string_t *s);

int string_print(FILE *file, string_t* s);

int string_println(FILE *file, string_t* s);

inline size_t string_length(string_t* s);

#endif //SUFFIX_ARRAY_STRING_TYPE_H
