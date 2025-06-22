#include "TypeInfo.h"
#include "char.h"  
#include "my_string.h"
#include <stdlib.h>
#include <string.h>

my_string* create_string(TypeInfo* typeinfo, const void* data, StringErrors* error) {
    if (!data) {
        *error = STRING_DOESNT_EXIST;
        return NULL;
    }
    my_string* str = malloc(sizeof(my_string));
    if (!str) {
        *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    str->typeinfo = typeinfo;
    size_t data_size = strlen((const char*)data) + 1;
    str->data = malloc(data_size);
    if (!str->data) {
        free(str);
        *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    memcpy(str->data, data, data_size);
    str->length = data_size - 1;
    *error = STRING_OPERATION_OK;
    return str;
}

void free_string(my_string* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

StringErrors concaten(const my_string* str1, const my_string* str2, my_string* result) {
    if (!str1->typeinfo || !str1->typeinfo->con) 
        return OPERATION_NOT_DEFINED;
    
    size_t required_length = str1->length + str2->length;
    if (result->length < required_length) {
        void* new_data = realloc(result->data, required_length + 1);
        if (!new_data) {
            return MEMORY_ALLOCATION_FAILED;
        }
        result->data = new_data;
    }

    str1->typeinfo->con(str1->data, str2->data, result->data);
    result->length = strlen((char*)result->data);
    return STRING_OPERATION_OK;
}

StringErrors recoding(const my_string* str, my_string* result) {
    if (!str->typeinfo || !str->typeinfo->rec) 
        return OPERATION_NOT_DEFINED;
    
    size_t required_length = str->length;
    if (result->length < required_length) {
        void* new_data = realloc(result->data, required_length + 1);
        if (!new_data) {
            return MEMORY_ALLOCATION_FAILED;
        }
        result->data = new_data;
    }
    
    str->typeinfo->rec(str->data, NULL, result->data);
    result->length = strlen((char*)result->data);
    return STRING_OPERATION_OK;
}

StringErrors get_substring(const my_string* str, int start, int end, my_string* result) {
    if (!str->typeinfo || !str->typeinfo->get_sub) 
        return OPERATION_NOT_DEFINED;
    if (start < 0 || end < 0 || start > str->length || end > str->length || end < start)
        return INDEX_DOESNT_EXIST;
    typedef struct { int start; int end; } Indices;
    Indices indices = { start, end };
    
    size_t required_length = end - start + 1;
    if (result->length < required_length) {
        void* new_data = realloc(result->data, required_length + 1);
        if (!new_data) {
            return MEMORY_ALLOCATION_FAILED;
        }
        result->data = new_data;
    }
    
    str->typeinfo->get_sub(str->data, &indices, result->data);
    result->length = strlen((char*)result->data);
    return STRING_OPERATION_OK;
}

StringErrors splitting(const my_string* str, char delimiter, char*** parts, int* count) {
    if (!str->typeinfo || !str->typeinfo->split) 
        return OPERATION_NOT_DEFINED;
    
    char delim_str[2] = {delimiter, '\0'};
    str->typeinfo->split(str->data, delim_str, parts);
    *count = 0;
    while ((*parts)[*count] != NULL) {
        (*count)++;
    }
    return STRING_OPERATION_OK;
}

StringErrors find_substring(const my_string* str, const my_string* substr, int* found) {
    if (!str->typeinfo || !str->typeinfo->find_sub) 
        return OPERATION_NOT_DEFINED;
    
    str->typeinfo->find_sub(str->data, substr->data, found);
    return STRING_OPERATION_OK;
}