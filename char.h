#ifndef CHAR_H
#define CHAR_H

#include "TypeInfo.h"

static TypeInfo* CHAR_TYPE_INFO = NULL;
void concaten(const void* string1,const void* string2, void* result);
void recoding(const void* string1, const void* offset, void* recult);
TypeInfo* GetCharTypeInfo();

#endif