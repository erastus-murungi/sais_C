#include <stdio.h>
#include <ctype.h>
#include "string_type.h"


void print_str_upper(char_t c, void *args) {
    printf("%c", (char) toupper(c));
}


int main() {
    string_t *tabby = string_from("Tabitha Kemunto");
    string_println(stdout, tabby);
    string_t *tabby_copy = string_copy(tabby);
    string_println(stdout, tabby_copy);
    string_t *sub = string_substring(tabby, 1, 4);
    string_println(stdout, sub);

    string_foreach(tabby, print_str_upper, NULL);

    string_free(tabby);
    string_free(tabby_copy);
    string_free(sub);
    string_t *s = string_join(NULL, 8, '\n', 'E', 'r', 'a', 's', 't', 'u', 's');
    string_println(stdout, s);
}
