#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef void (*Char_Operation)(const void*, const void*, void*);
typedef void (*Substring_Operation)(const void*, const void*, const void*, void*);

typedef struct {
    size_t size;
    Char_Operation con;  // процесс конкатенации
    Substring_Operation get_sub; // получение подстроки
    Char_Operation rec; // перекодирование
    Char_Operation split; // разбиение одной строки на несколько
    Char_Operation find_sub; // нахождение подстроки
    void(*print)(const void*);
}TypeInfo;



#endif 