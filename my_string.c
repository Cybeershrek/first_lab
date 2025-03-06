#include "my_string.h"


my_string* createString(TypeInfo* typeinfo, void* c, StringErrors* operationResult){
    my_string* string = (my_string*)mallok(sizeof(my_string));
    if (string == NULL){
        *operationResult = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    string -> typeinfo = typeinfo;
    string -> c = malloc(typeinfo->size);
    memcpy(string->c, c, typeinfo->size);

    *operationResult = STRING_OPERATION_OK;
    return string;
}

void free_String(my_string* string){
    free(string->c);
    free(string);
}


StringErrors concaten(const my_string* str1, const my_string* str2, const void* result){ 
    char_concaten(str1->c, str2->c, result);
}


