#include "my_string.h"
#include "char.h" 
#include "TypeInfo.h"

static TypeInfo* CHAR_TYPE_INFO = NULL;

void char_concaten(const void* char1, const void* char2, void* result) {
    if (!char1 || !char2 || !result) {
        if (result) ((char*)result)[0] = '\0';
        return;
    }
    
    int len1 = strlen((char*)char1);
    int len2 = strlen((char*)char2);
    int lenRes = len1 + len2;
    char* tempStr = (char*)malloc((lenRes + 1) * sizeof(char));
    if (tempStr == NULL) {
        ((char*)result)[0] = '\0';
        return;
    }
    memcpy(tempStr, (char*)char1, len1);
    strcpy(tempStr + len1, (char*)char2);
    memcpy(result, tempStr, lenRes + 1);
    free(tempStr);
}

void char_recoding(const void* string1, const void* shift, void* result) {
    int len = strlen((char*)string1);
    char* tempStr = (char*)malloc(len + 1);
    if (tempStr == NULL) {
        ((char*)result)[0] = '\0';
        return;
    }
    if (!shift) {
    ((char*)result)[0] = '\0';
    return;
    }
    int shif = *(const int*)shift;
    for (int i = 0; i < len; i++) {
        tempStr[i] = ((const char*)string1)[i] - shif;
    }
    tempStr[len] = '\0';
    strcpy((char*)result, tempStr);
    free(tempStr);
}

void char_splitting(const void* string1, const void* char1, void* result) {
    if (!string1 || !result) return;
    
    char*** output = (char***)result;
    *output = NULL;
    const char* str = (char*)string1;
    char delimiter = *((char*)char1);

    int len = strlen(str);
    int max_parts = 20;
    *output = (char**)malloc((max_parts + 1) * sizeof(char*));
    if (!*output) return;
    
    int start = 0;
    int partIndex = 0;

    for (int i = 0; i <= len; i++) {
        if (str[i] == delimiter || str[i] == '\0') {
            int partLen = i - start;
            (*output)[partIndex] = (char*)malloc(partLen + 1);
            if (!(*output)[partIndex]) return;
            
            strncpy((*output)[partIndex], str + start, partLen);
            (*output)[partIndex][partLen] = '\0';
            partIndex++;
            start = i + 1;
            
            if (partIndex >= max_parts) break;
        }
    }
    (*output)[partIndex] = NULL;
}

void char_find_substring(const void* string1, const void* string2, void* result){
    int lenstr1 = strlen((char*)string1);
    int lenstr2 = strlen((char*)string2);
    if (lenstr2 > lenstr1){
        *(int*)result = 0;
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

void char_get_substring(const void* string, const void* indices, void* result){
    typedef struct { int start; int end; } Indices;
    const Indices* idx = (const Indices*)indices;
    int start = idx->start;
    int end = idx->end;
    
    int len = strlen((char*)string);
    if (start < 0 || end < 0 || start > len || end > len || start > end){
        ((char*)result)[0] = '\0';
        return;
    }
    
    int sub_len = end - start + 1;
    char* temp = malloc(sub_len + 1);
    if (!temp) {
        ((char*)result)[0] = '\0';
        return;
    }
    
    strncpy(temp, (char*)string + start, sub_len);
    temp[sub_len] = '\0';
    strcpy((char*)result, temp);
    free(temp);
}

void char_is_palindrome(const void* string, const void* unused, void* result) {
    (void)unused;
    const char* str = (const char*)string;
    int len = strlen(str);
    int left = 0;
    int right = len - 1;
    *(int*)result = 1;
    while (left < right) {
        while (left < right && str[left] == ' ') left++;
        while (left < right && str[right] == ' ') right--;
        if (tolower(str[left]) != tolower(str[right])) {
            *(int*)result = 0;
            return;
        }
        left++;
        right--;
    }
}

TypeInfo* GetCharTypeInfo() {
    if (!CHAR_TYPE_INFO) {
        CHAR_TYPE_INFO = malloc(sizeof(TypeInfo));
        CHAR_TYPE_INFO->size = sizeof(char);
        CHAR_TYPE_INFO->con = char_concaten;
        CHAR_TYPE_INFO->rec = char_recoding;
        CHAR_TYPE_INFO->split = char_splitting;
        CHAR_TYPE_INFO->find_sub = char_find_substring;
        CHAR_TYPE_INFO->get_sub = char_get_substring;
        CHAR_TYPE_INFO->is_palindrome = char_is_palindrome;
        CHAR_TYPE_INFO->print = NULL;
    }
    return CHAR_TYPE_INFO;
}