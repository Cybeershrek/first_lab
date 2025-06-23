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
        case STRING_OPERATION_OK: return "Óñïåøíî";
        case STRING_DOESNT_EXIST: return "Ñòðîêà íå ñóùåñòâóåò";
        case MEMORY_ALLOCATION_FAILED: return "Îøèáêà âûäåëåíèÿ ïàìÿòè";
        case OPERATION_NOT_DEFINED: return "Îïåðàöèÿ íå îïðåäåëåíà";
        case INDEX_DOESNT_EXIST: return "Íåêîððåêòíûå èíäåêñû";
        default: return "Íåèçâåñòíàÿ îøèáêà";
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
        printf("Âûáåðèòå îïåðàöèþ:\n");
        printf("1. Ñîåäèíåíèå ñòðîê\n");
        printf("2. Ïåðåêîäèðîâàíèå ñòðîêè\n");
        printf("3. Ïîëó÷åíèå ïîäñòðîêè\n");
        printf("4. Ðàçäåëåíèå ñòðîêè\n");
        printf("5. Ïîèñê ïîäñòðîêè\n");
        printf("6. Ïîÿñíåíèÿ îïåðàöèé\n");
        printf("0. Âûõîä\n");
        printf("Âàø âûáîð: ");
        scanf("%d", &choice);
        getchar();

        my_string *mstr1 = NULL, *mstr2 = NULL, *moutput = NULL;
        
        switch (choice) {
            case 1:
                printf("Ââåäèòå ïåðâóþ ñòðîêó: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Ââåäèòå âòîðóþ ñòðîêó: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ âûõîäíîé ñòðîêè: %s\n", error_to_string(error));
                    free_string(mstr1);
                    free_string(mstr2);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = concaten(mstr1, mstr2, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Ðåçóëüòàò: %s\n", (char*)moutput->data);
                } else {
                    printf("Îøèáêà îïåðàöèè: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 2:
                printf("Ââåäèòå ñòðîêó äëÿ ïåðåêîäèðîâàíèÿ: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ âûõîäíîé ñòðîêè: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = recoding(mstr1, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Ðåçóëüòàò: %s\n", (char*)moutput->data);
                } else {
                    printf("Îøèáêà îïåðàöèè: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 3:
                printf("Ââåäèòå ñòðîêó: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Ââåäèòå íà÷àëüíûé èíäåêñ: ");
                scanf("%d", &start);
                printf("Ââåäèòå êîíå÷íûé èíäåêñ: ");
                scanf("%d", &end);
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                moutput = create_string(GetCharTypeInfo(), "", &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ âûõîäíîé ñòðîêè: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (moutput) free_string(moutput);
                    break;
                }
                
                error = get_substring(mstr1, start, end, moutput);
                if (error == STRING_OPERATION_OK) {
                    printf("Ïîäñòðîêà: %s\n", (char*)moutput->data);
                } else {
                    printf("Îøèáêà îïåðàöèè: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(moutput);
                printf("===========================================\n");
                break;

            case 4:
                printf("Ââåäèòå ñòðîêó äëÿ ðàçäåëåíèÿ: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Ââåäèòå ñèìâîë-ðàçäåëèòåëü: ");
                delimiter = getchar();
                getchar();
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                error = splitting(mstr1, delimiter, &parts, &count);
                if (error == STRING_OPERATION_OK) {
                    printf("Ðåçóëüòàò ðàçáèåíèÿ (%d ÷àñòåé):\n", count);
                    for (int i = 0; i < count && parts[i] != NULL; i++) {
                        printf("×àñòü %d: %s\n", i + 1, parts[i]);
                        free(parts[i]);
                    }
                    free(parts);
                } else {
                    printf("Îøèáêà îïåðàöèè: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                printf("===========================================\n");
                break;

            case 5:
                printf("Ââåäèòå ñòðîêó: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Ââåäèòå ïîäñòðîêó äëÿ ïîèñêà: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                
                mstr1 = create_string(GetCharTypeInfo(), str1, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè 1: %s\n", error_to_string(error));
                    if (mstr1) free_string(mstr1);
                    break;
                }
                
                mstr2 = create_string(GetCharTypeInfo(), str2, &error);
                if (error != STRING_OPERATION_OK) {
                    printf("Îøèáêà ñîçäàíèÿ ñòðîêè 2: %s\n", error_to_string(error));
                    free_string(mstr1);
                    if (mstr2) free_string(mstr2);
                    break;
                }
                
                error = find_substring(mstr1, mstr2, &found);
                if (error == STRING_OPERATION_OK) {
                    if (found)
                        printf("Ïîäñòðîêà íàéäåíà.\n");
                    else
                        printf("Ïîäñòðîêà íå íàéäåíà.\n");
                } else {
                    printf("Îøèáêà îïåðàöèè: %s\n", error_to_string(error));
                }
                
                free_string(mstr1);
                free_string(mstr2);
                printf("===========================================\n");
                break;
                
            case 6:
                printf("\n===== Ñïðàâêà ïî îïåðàöèÿì ñî ñòðîêàìè =====\n");
                printf("1. Ñöåïëåíèå ñòðîê - Îáúåäèíåíèå äâóõ ñòðîê â îäíó\n");
                printf("2. Ïåðåêîäèðîâàíèå ñòðîêè - Ñäâèã êàæäîãî ñèìâîëà â ASCII íà -1\n");
                printf("3. Ïîëó÷åíèå ïîäñòðîêè - Èçâëå÷åíèå ÷àñòè ñòðîêè ïî èíäåêñàì\n");
                printf("4. Ðàçäåëåíèå ñòðîêè - Ðàçáèåíèå ñòðîêè ïî ðàçäåëèòåëþ\n");
                printf("5. Ïîèñê ïîäñòðîêè - Ïðîâåðêà íàëè÷èÿ ïîäñòðîêè â ñòðîêå\n");
                printf("6. Ñïðàâêà - Ïîêàçàòü ýòó èíôîðìàöèþ\n");
                printf("0. Âûõîä - Çàâåðøåíèå ïðîãðàììû\n");
                printf("===========================================\n");
                break;

            case 0:
                printf("Âûõîä...\n");
                return 0;

            default:
                printf("Íåâåðíûé âûáîð. Ïîïðîáóéòå ñíîâà.\n");
        }
    }
    return 0;
}

//1)main файл у нас пустой, здесь мы только вызываем меню и тесты
//2)зачем нужно typeinfo? чем подробнее - тем лучше
//3)сдвиг строки - передаем также величину сдвига
//4)MAX_LEN не имеем никакого отношения к меню, это должно быть в string
//5)еще 1 метод: является ли строка палиндромом? + покрыть этот метод тестами (пробелы и регистры НЕ учитывваются)
