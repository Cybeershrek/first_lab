#include "my_string.h"

void get_substring(const void* string, const void* i, const void* j, void* result){
    int len = strlen((char*)string);
    int start = *(int*)i;
    int finish = *(int*)j;
    if ( start < 0 || finish < 0 || start > len || finish > len){
        ((char*)result)[0] = '\0';
        return ;
    }
    int lensub = abs(finish - start) + 2;
    char* tempStr = (char*)malloc(lensub * sizeof(char));
    for (int k = 0; k < finish - start; k++) {
        tempStr[k] = ((char*)string)[start + k];
    }
    tempStr[finish - start] = '\0';
    memcpy(result, tempStr, strlen(tempStr) + 1);
    free(tempStr);
}

TypeInfo* GetIntTypeInfo() {
    if (INT_TYPE_INFO == NULL) {
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->get_sub = get_substring;
    }
    return INT_TYPE_INFO;
}