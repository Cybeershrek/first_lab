#include "my_string.h"

void concaten(const void* char1, const void* char2, void* result){
    int lenRes = strlen((char*)char1) + strlen((char*)char2);
    char* tempStr = (char*)malloc((lenRes + 1) * sizeof(char));
    if (tempStr == NULL){
        *(char*)result = NULL;
        return NULL;
    }
    for (int x = 0; x < strlen((char*)char1); x++){
        tempStr[x] = ((char*)char1)[x];
    }
    for (int y = 0; y < strlen((char*)char2); y++){
        tempStr[y + strlen((char*)char1)] = ((char*)char2)[y];
    }
    memcpy(result, &tempStr, sizeof(char*));
    free(tempStr);
}


void recoding(const void* string1, void* result){
    int lenRes = strlen((char*)string1);
    char* tempStr = (char*)malloc((lenRes + 1) * sizeof(char));
    for (int i = 0; i < lenRes; i++){
        tempStr[i] = ((char*)string1)[i] - 1;
    }
    memcpy(result, &tempStr, sizeof(char*)); 
    free(tempStr);
}

void splitting(const void* string1, const void* char1, void* result){
    int lenRes = strlen((char*)string1);
    char* tempStr[lenRes];
    for (int j = 0; j < lenRes; j++){
        tempStr[j] = (char*)malloc((lenRes) * sizeof(char));
    }
    int point1 = 0, point2 = 0, i = 0;; 
    for (point2; point2 < lenRes; point2++){
        if (((char*)string1)[point1] == (char*)char1){
            if (point1 == 0) {
                point2 = point1 + 1;
                continue;
            }
            get_substring(string1, point1 - 1, point2, tempStr[i]);
            point2 = point1 + 1;
        }
    }
}

void find_substring(const void* string1, const void* string2, void* result){
    int lenstr1 = strlen((char*)string1);
    int lenstr2 = strlen((char*)string2);
    if (lenstr2 > lenstr1){
        *(char*)result = NULL;
        return NULL;
    } 
    int j = 0;
    for (int i = 0; i < lenstr1; i++){
        if (((char*)string1)[i] == ((char*)string2)[j]){
            j++;
            if (j == lenstr2) *(int*)result = 1;
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
}  