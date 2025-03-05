#ifndef CHAR_H
#define CHAR_H

#include "TypeInfo.h"

static TypeInfo* CHAR_TYPE_INFO = NULL;
void concaten(void* string1, void* string2, void* result);
void recoding(void* string1, void* recult);
TypeInfo* GetCharTypeInfo();



#endif