#include "my_string.h"

void concaten(const void* char1, const void* char2, void* result){
    int len1 = strlen((char*)char1);
    int len2 = strlen((char*)char2);
    int lenRes = len1 + len2;
    char* tempStr = (char*)malloc((lenRes + 1) * sizeof(char));
    if (tempStr == NULL){
        result;
        return ;
    }
    memcpy(tempStr, (char*)char1, len1);
    strcpy(tempStr + len1, (char*)char2);
    memcpy(result, tempStr, lenRes + 1);
    free(tempStr);
}

void recoding(const void* string1, void* result) {
    int len = strlen((char*)string1);
    char* tempStr = (char*)malloc(len + 1);
    if (tempStr == NULL) {
        ((char*)result)[0] = '\0';
        return;
    }
    for (int i = 0; i < len; i++) {
        tempStr[i] = ((char*)string1)[i] - 1;
    }
    tempStr[len] = '\0';
    strcpy((char*)result, tempStr);
    free(tempStr);
}

void splitting(const void* string1, const void* char1, void* result) {
    const char* str = (char*)string1;
    char char12 = *((char*)char1);
    char** output = (char**)result;

    int len = strlen(str);
    int start = 0;
    int partIndex = 0;

    for (int i = 0; i <= len; i++) {
        if (str[i] == char12 || str[i] == '\0') {
            int partLen = i - start;
            output[partIndex] = (char*)malloc(partLen + 1);

            if (output[partIndex] == NULL) {
                return;
            }

            strncpy(output[partIndex], str + start, partLen);
            output[partIndex][partLen] = '\0';
            partIndex++;
            start = i + 1;
        }
    }
}


void find_substring(const void* string1, const void* string2, void* result){
    int lenstr1 = strlen((char*)string1);
    int lenstr2 = strlen((char*)string2);
    if (lenstr2 > lenstr1){
        *(int*)result = 0;;
        return;
    } 
    int j = 0;
    for (int i = 0; i < lenstr1; i++){
        if (((char*)string1)[i] == ((char*)string2)[j]){
            j++;
            if (j == lenstr2) {
                *(int*)result = 1;
                return;
            }
        } else{
            j = 0;
        }
    }
    *(int*)result = 0;
}

TypeInfo* GetCharTypeInfo() {
    if (CHAR_TYPE_INFO == NULL) {
        CHAR_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        CHAR_TYPE_INFO->size = sizeof(char);
        CHAR_TYPE_INFO->con = concaten;
        CHAR_TYPE_INFO->rec = recoding; 
    }
    return CHAR_TYPE_INFO;
}  