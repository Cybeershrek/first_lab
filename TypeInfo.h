#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*Operaions)(void* string1, void* string2, const void* arg1, const void* arg2, void* result);

typedef struct {
    size_t size;
    Operaions concaten;  // процесс конкатенации
    Operaions get_substring; // получение подстроки
    Operaions recoding; // перекодирование
    void(*print)(const void*);
}TypeInfo;



#endif 