#include "TypeInfo.h"
#include "my_string.h"
#include "char.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256
#define MAX_PARTS 20

const char* error_to_string(StringErrors error) {
    switch (error) {
        case STRING_OPERATION_OK: return "Успешно";
        case STRING_DOESNT_EXIST: return "Строка не существует";
        case MEMORY_ALLOCATION_FAILED: return "Ошибка выделения памяти";
        case OPERATION_NOT_DEFINED: return "Операция не определена";
        case INDEX_DOESNT_EXIST: return "Некорректные индексы";
        default: return "Неизвестная ошибка";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    char str1[MAX_LEN], str2[MAX_LEN];
    char delimiter;
    char** parts = NULL;
    int start, end, found;
    int count = 0;
    StringErrors error;

    while (1) {
        printf("Выберите операцию:\n");
        printf("1. Соединение строк\n");
        printf("2. Перекодирование строки\n");
        printf("3. Получение подстроки\n");
        printf("4. Разделение строки\n");
        printf("5. Поиск подстроки\n");
        printf("6. Пояснения операций\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar();

        my_string *mstr1 = NULL, *mstr2 = NULL, *moutput = NULL;
        
        switch (choice) {
            case 1:
                printf("Введите первую строку: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите вторую строку: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания выходной строки: %s\n", error_to_string(error));
                    free_string(mstr1);
                    free_string(mstr2);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = concaten(mstr1, mstr2, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Результат: %s\n", (char*)moutput->data);
                } else {
                    printf("Ошибка операции: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 2:
                printf("Введите строку для перекодирования: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания выходной строки: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = recoding(mstr1, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Результат: %s\n", (char*)moutput->data);
                } else {
                    printf("Ошибка операции: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 3:
                printf("Введите строку: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите начальный индекс: ");
                scanf("%d", &start);
                printf("Введите конечный индекс: ");
                scanf("%d", &end);
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания выходной строки: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = get_substring(mstr1, start, end, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Подстрока: %s\n", (char*)moutput->data);
                } else {
                    printf("Ошибка операции: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 4:
                printf("Введите строку для разделения: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите символ-разделитель: ");
                delimiter = getchar();
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                error = splitting(mstr1, delimiter, &parts, &count);
                if (error == STRING_OPERATION_OK) {
                    printf("Результат разбиения (%d частей):\n", count);
                    for (int i = 0; i < count && parts[i] != NULL; i++) {
                        printf("Часть %d: %s\n", i + 1, parts[i]);
                        free(parts[i]);
                    }
                    free(parts);
                } else {
                    printf("Ошибка операции: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                printf("===========================================\n");
                break;

            case 5:
                printf("Введите строку: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите подстроку для поиска: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Ошибка создания строки 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                error = find_substring(mstr1, mstr2, &found);
                if (error == STRING_OPERATION_OK) {
                    if (found)
                        printf("Подстрока найдена.\n");
                    else
                        printf("Подстрока не найдена.\n");
                } else {
                    printf("Ошибка операции: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                printf("===========================================\n");
                break;
                
            case 6:
                printf("\n===== Справка по операциям со строками =====\n");
                printf("1. Сцепление строк - Объединение двух строк в одну\n");
                printf("2. Перекодирование строки - Сдвиг каждого символа в ASCII на -1\n");
                printf("3. Получение подстроки - Извлечение части строки по индексам\n");
                printf("4. Разделение строки - Разбиение строки по разделителю\n");
                printf("5. Поиск подстроки - Проверка наличия подстроки в строке\n");
                printf("6. Справка - Показать эту информацию\n");
                printf("0. Выход - Завершение программы\n");
                printf("===========================================\n");
                break;

            case 0:
                printf("Выход...\n");
                return 0;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}