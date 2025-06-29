#ifndef MYSTRING_H
#define MYSTRING_H
#include "TypeInfo.h"

typedef struct {
    void* data;
    size_t length;
    TypeInfo* typeinfo;
} my_string;

my_string* create_string(TypeInfo* typeinfo, const void* data, StringErrors* error);
void free_string(my_string* str);

StringErrors concaten(const my_string* str1, const my_string* str2, my_string* result);
StringErrors recoding(const my_string* str, const void* shift, my_string* result);
StringErrors get_substring(const my_string* str, int start, int end, my_string* result);
StringErrors splitting(const my_string* str, char delimiter, char*** parts, int* count);
StringErrors find_substring(const my_string* str, const my_string* substr, int* found);
StringErrors is_palindrome(const my_string* str, int* result);

#endif