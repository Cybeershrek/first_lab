#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "stringErrors.h"
#include "output.h"

typedef void (*Operation)(const void*, const void*, void*);

typedef struct {
    size_t size;
    Operation con;
    Operation get_sub;
    Operation rec; 
    Operation split; 
    Operation find_sub;
    Operation is_palindrome;
    void(*print)(const void*);
}TypeInfo;



#endif 