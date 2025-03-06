#include "char.h"

void char_concaten(const void* char1, const void* char2, void* result){
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
}


void char_recoding(const void* char1, const void* offset, void* result){
    *(char*) result = (char*)char1 - (int*)offset;
}

TypeInfo* GetCharTypeInfo() {
    if (CHAR_TYPE_INFO == NULL) {
        CHAR_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        CHAR_TYPE_INFO->size = sizeof(char);
        CHAR_TYPE_INFO->con = concaten;
        CHAR_TYPE_INFO->rec = recoding;
    }
}