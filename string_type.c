//
// Created by Erastus Murungi on 7/21/22.
//

#include "string_type.h"
#include "error_strings.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define PRINT_COLOR_ERROR(...) fprintf(stderr, "%s:%s:%zu \033[34m %s \033[0m\n", __VA_ARGS__);

int print_error(const char *error_msg_prefix, const char *file_name, const char *function_name, long line_num) {
    return PRINT_COLOR_ERROR(file_name, function_name, line_num, error_msg_prefix)
}


void *print_error_and_return_null(const char *error_msg_prefix, const char *file_name, const char *function_name,
                                  long line_num) {
    print_error(error_msg_prefix, file_name, function_name, line_num);
    return NULL;
}

int print_error_and_return_error_code(const char *error_msg_prefix, const char *file_name, const char *function_name,
                                      long line_num, int error_code) {
    print_error(error_msg_prefix, file_name, function_name, line_num);
    return error_code;
}

void
print_error_and_exit(const char *error_msg_prefix, const char *file_name, const char *function_name, long line_num) {
    print_error(error_msg_prefix, file_name, function_name, line_num);
    exit(EXIT_FAILURE);
}

inline string_t *string_new(size_t length) {
    string_t *s = malloc(sizeof(string_t));
    if (s == NULL) {
        return print_error_and_return_null(strerror(errno), __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    char_t *chars = malloc((length + 1) * sizeof(char_t));
    if (chars == NULL) {
        return print_error_and_return_null(strerror(errno), __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    s->length = length;
    s->chars = chars;
    return s;
}

char *string_fill_char_no_check(string_t *s, const char *source, size_t length) {
    return memccpy(s->chars, source, 0, sizeof(char) * length);
}

inline string_t *string_from(const char *source) {
    if (source == NULL) {
        return print_error_and_return_null(ERR_CONSTRUCTION_FROM_NULL_STRING, __FILE_NAME__, __PRETTY_FUNCTION__,
                                           __LINE__);
    }
    size_t length = strlen(source);
    string_t *s = string_new(length);
    if (s == NULL) {
        return s;
    } else {
        s->length = length;
        string_fill_char_no_check(s, source, length);
        return s;
    }
}

size_t string_length(string_t *s) {
    if (s == NULL) {
        print_error_and_exit(ERR_NULL_STRING, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    return s->length;
}

string_t *string_copy(string_t *s) {
    if (s == NULL) {
        return print_error_and_return_null(ERR_NULL_STRING_TO_PRINT, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    } else if (s->chars == NULL) {
        return print_error_and_return_null(ERR_NULL_CHAR_FIELD, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }

    string_t *s_copy = string_new(s->length);
    if (s_copy == NULL) {
        return s_copy;
    }
    s_copy->length = s->length;
    for (size_t i = 0; i < s->length; i++) {
        s_copy->chars[i] = s->chars[i];
    }
    return s_copy;
}


inline int string_print(FILE *file, string_t *s) {
    if (s == NULL) {
        return print_error_and_return_error_code(ERR_NULL_STRING_TO_PRINT, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__,
                                                 EXIT_FAILURE);
    }
    if (file == NULL) {
        return print_error_and_return_error_code(ERR_NULL_FILE, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__,
                                                 EXIT_FAILURE);
    }
    for (size_t i = 0; i < string_length(s); i++) {
        fprintf(file, "%c", s->chars[i]);
    }
    return EXIT_SUCCESS;
}

inline int string_println(FILE *file, string_t *s) {
    const int ret_code = string_print(file, s);
    fprintf(file, "%c", '\n');
    return ret_code;
}

string_t *string_substring(string_t *s, size_t from, size_t to) {
    if (s == NULL) {
        return print_error_and_return_null(ERR_NULL_STRING, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    if (from >= s->length) {
        char err_buffer[strlen(ERR_START_INDEX_OUT_OF_BOUNDS) + MAX_CHARS_FOR_DIGITS];
        sprintf(err_buffer, ERR_START_INDEX_OUT_OF_BOUNDS, from, s->length);
        return print_error_and_return_null(ERR_START_INDEX_OUT_OF_BOUNDS, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }

    if (to >= s->length) {
        char err_buffer[strlen(ERR_END_INDEX_OUT_OF_BOUNDS) + MAX_CHARS_FOR_DIGITS];
        sprintf(err_buffer, ERR_END_INDEX_OUT_OF_BOUNDS, to, s->length);
        return print_error_and_return_null(ERR_END_INDEX_OUT_OF_BOUNDS, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    if (from > to) {
        return print_error_and_return_null(ERR_START_INDEX_GT_END_INDEX, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    string_t *sub_str = string_new(to - from);
    sub_str->length = to - from;
    for (size_t i = from; i < to; i++) {
        sub_str->chars[i - from] = s->chars[i];
    }
    return sub_str;
}

void string_free(string_t *s) {
    if (s == NULL) {
        print_error_and_exit(ERR_NULL_STRING, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    if (s->chars == NULL) {
        print_error_and_exit(ERR_NULL_CHAR_FIELD, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    free(s->chars);
    free(s);
}


void string_foreach(string_t *s, char_t_map_fn *f, void *args) {
    if (s == NULL) {
        print_error_and_exit(ERR_NULL_STRING, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    if (s->chars == NULL) {
        print_error_and_exit(ERR_NULL_CHAR_FIELD, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    for (size_t i = 0; i < s->length; i++) {
        char_t c = s->chars[i];
        f(c, args);
    }
}

string_t *string_join(const char_t *joiner, int count, ...) {
    if (count == 0) {
        return print_error_and_return_null(ERR_NO_STRINGS_TO_JOIN, __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__);
    }
    string_t *s = string_new(joiner == NULL ? count : count + (count - 1));
    if (s == NULL) {
        return s;
    }

    va_list args;
    va_start(args, count);

    if (joiner == NULL) {
        for (int i = 0; i < count; i++) {
            s->chars[i] = va_arg(args, char_t);
        }
    } else {
        for (int i = 0; i < count; i++) {
            s->chars[i * 2] = va_arg(args, char_t);
            if (i < (count - 1))
                s->chars[(i * 2) + 1] = *joiner;
        }
    }
    return s;
}


