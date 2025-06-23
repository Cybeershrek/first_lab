#include "my_string.h"
#include "char.h"
#include "TypeInfo.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

const char* error_to_string(StringErrors error) {
    switch (error) {
        case STRING_OPERATION_OK: return "Success";
        case STRING_DOESNT_EXIST: return "String doesn't exist";
        case MEMORY_ALLOCATION_FAILED: return "Memory error";
        case OPERATION_NOT_DEFINED: return "Operation undefined";
        case INDEX_DOESNT_EXIST: return "Invalid index";
        default: return "Unknown error";
    }
}

void test_create_string() {
    printf("Running test_create_string... ");
    StringErrors error;
    
    // Normal creation
    my_string* str = create_string(GetCharTypeInfo(), "Hello", &error);
    assert(str != NULL);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)str->data, "Hello") == 0);
    assert(str->length == 5);
    free_string(str);
    
    // NULL data
    str = create_string(GetCharTypeInfo(), NULL, &error);
    assert(str == NULL);
    assert(error == STRING_DOESNT_EXIST);
    
    // Empty string
    str = create_string(GetCharTypeInfo(), "", &error);
    assert(str != NULL);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)str->data, "") == 0);
    assert(str->length == 0);
    free_string(str);
    
    printf("Passed!\n");
}

void test_concatenation() {
    printf("Running test_concatenation... ");
    StringErrors error;
    
    my_string* str1 = create_string(GetCharTypeInfo(), "Hello", &error);
    my_string* str2 = create_string(GetCharTypeInfo(), "World", &error);
    my_string* result = create_string(GetCharTypeInfo(), "", &error);
    
    // Normal concatenation
    error = concaten(str1, str2, result);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)result->data, "HelloWorld") == 0);
    assert(result->length == 10);
    
    // Concatenate with empty string
    free_string(str2);
    str2 = create_string(GetCharTypeInfo(), "", &error);
    error = concaten(str1, str2, result);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)result->data, "Hello") == 0);
    
    // Insufficient memory (simulate by shrinking buffer)
    free(result->data);
    result->data = malloc(1);
    result->length = 0;
    error = concaten(str1, str2, result);
    assert(error == MEMORY_ALLOCATION_FAILED);
    
    free_string(str1);
    free_string(str2);
    free_string(result);
    printf("Passed!\n");
}

void test_recoding() {
    printf("Running test_recoding... ");
    StringErrors error;
    
    my_string* input = create_string(GetCharTypeInfo(), "ABC123", &error);
    my_string* output = create_string(GetCharTypeInfo(), "", &error);
    error = recoding(input, output);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)output->data, "@AB012") == 0);
    assert(output->length == 6);
    free_string(input);
    input = create_string(GetCharTypeInfo(), "", &error);
    error = recoding(input, output);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)output->data, "") == 0);
    
    free_string(input);
    free_string(output);
    printf("Passed!\n");
}

void test_substring() {
    printf("Running test_substring... ");
    StringErrors error;
    
    my_string* str = create_string(GetCharTypeInfo(), "HelloWorld", &error);
    my_string* result = create_string(GetCharTypeInfo(), "", &error);
    error = get_substring(str, 3, 7, result);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)result->data, "loWo") == 0);
    error = get_substring(str, 0, 9, result);
    assert(error == STRING_OPERATION_OK);
    assert(strcmp((char*)result->data, "HelloWorld") == 0);
    error = get_substring(str, -1, 5, result);
    assert(error == INDEX_DOESNT_EXIST);
    
    error = get_substring(str, 5, 100, result);
    assert(error == INDEX_DOESNT_EXIST);
    
    error = get_substring(str, 7, 3, result);
    assert(error == INDEX_DOESNT_EXIST);
    
    free_string(str);
    free_string(result);
    printf("Passed!\n");
}

void test_splitting() {
    printf("Running test_splitting... ");
    StringErrors error;
    
    my_string* str = create_string(GetCharTypeInfo(), "apple,banana,cherry", &error);
    char** parts = NULL;
    int count = 0;
    error = splitting(str, ',', &parts, &count);
    assert(error == STRING_OPERATION_OK);
    assert(count == 3);
    assert(strcmp(parts[0], "apple") == 0);
    assert(strcmp(parts[1], "banana") == 0);
    assert(strcmp(parts[2], "cherry") == 0);
    for (int i = 0; i < count; i++) free(parts[i]);
    free(parts);
    error = splitting(str, ';', &parts, &count);
    assert(error == STRING_OPERATION_OK);
    assert(count == 1);
    assert(strcmp(parts[0], "apple,banana,cherry") == 0);
    
    for (int i = 0; i < count; i++) free(parts[i]);
    free(parts);
    free_string(str);
    printf("Passed!\n");
}

void test_substring_search() {
    printf("Running test_substring_search... ");
    StringErrors error;
    my_string* str = create_string(GetCharTypeInfo(), "HelloWorld", &error);
    my_string* substr1 = create_string(GetCharTypeInfo(), "World", &error);
    my_string* substr2 = create_string(GetCharTypeInfo(), "XYZ", &error);
    int found = 0;
    error = find_substring(str, substr1, &found);
    assert(error == STRING_OPERATION_OK);
    assert(found == 1);
    error = find_substring(str, substr2, &found);
    assert(error == STRING_OPERATION_OK);
    assert(found == 0);
    free_string(substr2);
    substr2 = create_string(GetCharTypeInfo(), "", &error);
    error = find_substring(str, substr2, &found);
    assert(error == STRING_OPERATION_OK);
    assert(found == 1);
    
    free_string(str);
    free_string(substr1);
    free_string(substr2);
    printf("Passed!\n");
}

void test_memory_handling() {
    printf("Running test_memory_handling... ");
    StringErrors error;
    my_string* str = create_string(GetCharTypeInfo(), "test", &error);
    free(str->data);  
    void* original_data = str->data;
    str->data = NULL;
    my_string* result = create_string(GetCharTypeInfo(), "", &error);
    error = concaten(str, result, result);
    assert(error == MEMORY_ALLOCATION_FAILED);
    str->data = original_data;
    free_string(str);
    free_string(result);
    printf("Passed!\n");
}

int main() {
    printf("Starting unit tests...\n\n");
    
    test_create_string();
    test_concatenation();
    test_recoding();
    test_substring();
    test_splitting();
    test_substring_search();
    test_memory_handling();
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}