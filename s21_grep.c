#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Добавить динамический массив для шаблонов
// Добавить перебор шаблонов
// Добавить отчистку памяти
void array_add(int *array, int *capasity, int *number, int element)
{
}
int main(int argc, char *argv[])
{
    int e_flag = 0, i_flag = 0, v_flag = 0, c_flag = 0, l_flag = 0, n_flag = 0, execute_flag = 1, shablon = -1, flag = 1, string_counter = 0, all_strings_counter = 0, number_of_shablons = 0;
    int number_of_files = 0;
    size_t string_len = 1;
    char *now_string, *output, *variable;
    int *shablons = malloc(sizeof(int) * argc);
    int *files = malloc(sizeof(int) * argc);
    FILE *file;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
                if (argv[i][j] == 'i')
                    i_flag = 1;
                else if (argv[i][j] == 'n')
                    n_flag = 1;
                else if (argv[i][j] == 'l')
                    l_flag = 1;
                else if (argv[i][j] == 'v')
                    v_flag = 1;
                else if (argv[i][j] == 'c')
                    c_flag = 1;
                else if (argv[i][j] == 'e')
                {
                    e_flag = 1;
                    shablons[number_of_shablons] = i + 1;
                    i += 1;
                    number_of_shablons++;
                    break;
                }
                else
                {
                    printf("grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n", argv[i][j]);
                    execute_flag = 0;
                }
        }
        else
        {
            files[number_of_files] = i;
            number_of_files++;
        }
    }
    for (int i = 1; i < argc && flag == 1 && !e_flag; ++i)
    {
        if (argv[i][0] != '-')
        {
            shablons[0] = i;
            flag = 0;
            number_of_shablons++;
        }
    }
    for (int i = 0; i < number_of_files; ++i)
    {
            if(files[i]!=shablons[0]){
            file = fopen(argv[files[i]], "r");
            if (file)
            {
                string_counter = 0;
                all_strings_counter = 0;
                while (getline(&now_string, &string_len, file) != -1)
                {
                    all_strings_counter++;
                    for (int j = 0; j < number_of_shablons; ++j)
                    {
                        variable = strstr(now_string, argv[shablons[j]]);
                        if ((variable != NULL && v_flag == 0) || (variable == NULL && v_flag == 1))
                        {
                            string_counter++;
                            if (!c_flag && !l_flag)
                            {
                                printf("%s:", argv[files[i]]);
                                if (n_flag)
                                    printf("%d: ", all_strings_counter);
                                printf("%s", now_string);
                            }
                        }
                        if (string_counter != 0 && l_flag)
                        {
                            printf("%s", argv[i]);
                        }
                        if (!l_flag && c_flag)
                        {
                            printf("%s: %d", argv[files[i]], string_counter);
                        }
                    }
                }
            }
            else
            {
                printf("grep: %s: No such file or directory\n", argv[files[i]]);
            }
            }
        
    }

    // printf("\n%d\n", shablon);
    // printf("%s\n", strstr('aa', 'faa a aa'));
}