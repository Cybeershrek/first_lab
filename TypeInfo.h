#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*Operaions)(void* string1, void* string2, const void* arg1, const void* arg2, void* result);

typedef struct {
    size_t size;
    Operaions con;  // процесс конкатенации
    Operaions get_sub; // получение подстроки
    Operaions rec; // перекодирование
    Operaions split; // разбиение одной строки на несколько
    Operaions find_sub; // нахождение подстроки
    void(*print)(const void*);
}TypeInfo;



#endif 