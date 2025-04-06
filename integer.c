#include "my_string.h"

void get_substring(const void* string, const void* i, const void* j, void* result){
    int len = strlen((char*)string);
    int start = *(int*)i;
    int finish = *(int*)j;
    if ( start < 0 || finish < 0 || start > len || finish > len){
        *(char*)result = NULL;
        return NULL;
    }
    int lensub = abs(finish - start) + 2;
    char* tempStr = (char*)malloc(lensub * sizeof(char));
    for (int k = start; k < finish; k++){
        tempStr[k] = ((char*)string)[k];
    }
    tempStr[finish] = '\0';
    memcpy(result, &tempStr, sizeof(char*));
    free(tempStr);
}

TypeInfo* GetIntTypeInfo() {
    if (INT_TYPE_INFO == NULL) {
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->get_sub = get_substring;
    }
}