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
        case STRING_OPERATION_OK: return "�������";
        case STRING_DOESNT_EXIST: return "������ �� ����������";
        case MEMORY_ALLOCATION_FAILED: return "������ ��������� ������";
        case OPERATION_NOT_DEFINED: return "�������� �� ����������";
        case INDEX_DOESNT_EXIST: return "������������ �������";
        default: return "����������� ������";
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
        printf("�������� ��������:\n");
        printf("1. ���������� �����\n");
        printf("2. ��������������� ������\n");
        printf("3. ��������� ���������\n");
        printf("4. ���������� ������\n");
        printf("5. ����� ���������\n");
        printf("6. ��������� ��������\n");
        printf("0. �����\n");
        printf("��� �����: ");
        scanf("%d", &choice);
        getchar();

        my_string *mstr1 = NULL, *mstr2 = NULL, *moutput = NULL;
        
        switch (choice) {
            case 1:
                printf("������� ������ ������: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("������� ������ ������: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������ 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������ 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� �������� ������: %s\n", error_to_string(error));
                    free_string(mstr1);
                    free_string(mstr2);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = concaten(mstr1, mstr2, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("���������: %s\n", (char*)moutput->data);
                } else {
                    printf("������ ��������: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 2:
                printf("������� ������ ��� ���������������: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� �������� ������: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = recoding(mstr1, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("���������: %s\n", (char*)moutput->data);
                } else {
                    printf("������ ��������: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 3:
                printf("������� ������: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("������� ��������� ������: ");
                scanf("%d", &start);
                printf("������� �������� ������: ");
                scanf("%d", &end);
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� �������� ������: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = get_substring(mstr1, start, end, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("���������: %s\n", (char*)moutput->data);
                } else {
                    printf("������ ��������: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 4:
                printf("������� ������ ��� ����������: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("������� ������-�����������: ");
                delimiter = getchar();
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                error = splitting(mstr1, delimiter, &parts, &count);
                if (error == STRING_OPERATION_OK) {
                    printf("��������� ��������� (%d ������):\n", count);
                    for (int i = 0; i < count && parts[i] != NULL; i++) {
                        printf("����� %d: %s\n", i + 1, parts[i]);
                        free(parts[i]);
                    }
                    free(parts);
                } else {
                    printf("������ ��������: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                printf("===========================================\n");
                break;

            case 5:
                printf("������� ������: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("������� ��������� ��� ������: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������ 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("������ �������� ������ 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                error = find_substring(mstr1, mstr2, &found);
                if (error == STRING_OPERATION_OK) {
                    if (found)
                        printf("��������� �������.\n");
                    else
                        printf("��������� �� �������.\n");
                } else {
                    printf("������ ��������: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                printf("===========================================\n");
                break;
                
            case 6:
                printf("\n===== ������� �� ��������� �� �������� =====\n");
                printf("1. ��������� ����� - ����������� ���� ����� � ����\n");
                printf("2. ��������������� ������ - ����� ������� ������� � ASCII �� -1\n");
                printf("3. ��������� ��������� - ���������� ����� ������ �� ��������\n");
                printf("4. ���������� ������ - ��������� ������ �� �����������\n");
                printf("5. ����� ��������� - �������� ������� ��������� � ������\n");
                printf("6. ������� - �������� ��� ����������\n");
                printf("0. ����� - ���������� ���������\n");
                printf("===========================================\n");
                break;

            case 0:
                printf("�����...\n");
                return 0;

            default:
                printf("�������� �����. ���������� �����.\n");
        }
    }
    return 0;
}