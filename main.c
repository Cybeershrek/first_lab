#include "my_string.h"

#define MAX_LEN 256
#define MAX_PARTS 20

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    char str1[MAX_LEN], str2[MAX_LEN], output[MAX_LEN];
    char delimiter;
    char* parts[MAX_PARTS];
    int start, end, found;

    while (1) {
        printf("Выберите операцию:\n");
        printf("1. Сцепление строк (concaten)\n");
        printf("2. Перекодирование строки (recoding)\n");
        printf("3. Получение подстроки (get_substring)\n");
        printf("4. Разделение строки (splitting)\n");
        printf("5. Поиск подстроки (find_substring)\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Введите первую строку: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите вторую строку: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                concaten(str1, str2, output);
                printf("Результат: %s\n", output);
                break;

            case 2:
                printf("Введите строку для перекодирования: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                recoding(str1, output);
                printf("Результат: %s\n", output);
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
                get_substring(str1, &start, &end, output);
                printf("Подстрока: %s\n", output);
                break;

            case 4:
                printf("Введите строку для разделения: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите символ-разделитель: ");
                delimiter = getchar();
                getchar();

                splitting(str1, &delimiter, parts);
                printf("Результат разбиения:\n");
                for (int i = 0; i < MAX_PARTS && parts[i] != NULL; i++) {
                    printf("Часть %d: %s\n", i + 1, parts[i]);
                    free(parts[i]);
                }
                break;

            case 5:
                printf("Введите строку: ");
                fgets(str1, MAX_LEN, stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Введите подстроку для поиска: ");
                fgets(str2, MAX_LEN, stdin);
                str2[strcspn(str2, "\n")] = '\0';
                find_substring(str1, str2, &found);
                if (found)
                    printf("Подстрока найдена.\n");
                else
                    printf("Подстрока не найдена.\n");
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