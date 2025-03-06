#ifndef INTEGER_H
#define INTEGER_H

#include "TypeInfo.h"

static TypeInfo* INT_TYPE_INFO = NULL;
void get_substring(const void* string, const void* arg1, const void* arg2, void* result);
TypeInfo* GetIntTypeInfo();

#endif