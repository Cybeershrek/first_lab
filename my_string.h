#ifndef MYSTRING_H
#define MYSTRING_H

#include "TypeInfo.h"
#include "stringErrors.h"
#include "char.h"
#include "integer.h"


typedef struct
{
    void* c; 
    TypeInfo * typeinfo;    
}my_string;

my_string* createString(TypeInfo* typeinfo, void *c, StringErrors* operationResult);
void free_string(my_string* string);
StringErrors concaten(const my_string* str1, const my_string* str2, const my_string* result);
StringErrors recoding(const my_string* str1, const void* offset, const my_string* result);
StringErrors get_substring(const my_string* str1, const void* arg1, const void* arg2, const my_string* result);



#endif 