#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} Flags;
void null_stuct(Flags *flags)
{
    flags->e = 0;
    flags->i = 0;
    flags->v = 0;
    flags->c = 0;
    flags->l = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->f = 0;
    flags->o = 0;
}

int find_flags(int argc, char *argv[], Flags *flags)
{
    int execute_flag = 1;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
                if (argv[i][j] == 'i')
                    flags->i = 1;
                else if (argv[i][j] == 'n')
                    flags->n = 1;
                else if (argv[i][j] == 'l')
                    flags->l = 1;
                else if (argv[i][j] == 'v')
                    flags->v = 1;
                else if (argv[i][j] == 'c')
                    flags->c = 1;
                else if (argv[i][j] == 'h')
                    flags->h = 1;
                else if (argv[i][j] == 's')
                    flags->s = 1;
                else if (argv[i][j] == 'f')
                    flags->f = 1;
                else if (argv[i][j] == 'o')
                    flags->o = 1;
                else if (argv[i][j] == 'e')
                {
                    flags->e = 1;
                    // shablons[number_of_shablons] = i + 1;
                    // i += 1;
                    // number_of_shablons++;
                    // break;
                }
                else
                {
                    printf("grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n", argv[i][j]);
                    execute_flag = 0;
                }
        }
    }
    return execute_flag;
}
void find_files_shablons(int argc, char *argv[], int *files, int *number_of_files, int *shablons, int *number_of_shablons)
{
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'e')
            {
                shablons[*number_of_shablons] = i + 1;
                i += 1;
                *number_of_shablons += 1;
            }
        }
        else
        {
            files[*number_of_files] = i;
            *number_of_files += 1;
        }
    }
}
void no_e_flag(int argc, char *argv[], int *shablons, int *number_of_shablons)
{
    for (int i = 1; i < argc && number_of_shablons == 0; ++i)
    {
        if (argv[i][0] != '-')
        {
            shablons[0] = i;
            *number_of_shablons += 1;
        }
    }
}
void register_down(char *strint)
{
    for (int i = 0; i < (int)strlen(strint); i++)
    {
        strint[i] = tolower(strint[i]);
    }
}
int main(int argc, char *argv[])
{
    Flags *flags = malloc(sizeof(Flags));
    int e_flag = 0, i_flag = 0, v_flag = 0, c_flag = 0, l_flag = 0, n_flag = 0, execute_flag = 1, shablon = -1, flag = 1, string_counter = 0, all_strings_counter = 0, number_of_shablons = 0;
    int number_of_files = 0;
    size_t string_len = 1;
    char *now_string, *output, *variable;
    int *shablons = malloc(sizeof(int) * argc);
    int *files = malloc(sizeof(int) * argc);
    FILE *file;
    if (find_flags(argc, argv, flags))
    {
        find_files_shablons(argc, argv, files, &number_of_files, shablons, &number_of_shablons);

        if (!flags->e)
            no_e_flag(argc, argv, shablons, &number_of_shablons);
        for (int i = 0; i < number_of_files; ++i)
        {
            if (files[i] != shablons[0])
            {
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
                            if(flags->i)
                            {
                                register_down(now_string);
                                register_down(argv[shablons[j]]);
                                // printf("%s", (unsigned int)strlen(variable));
                            }
                            variable = strstr(now_string, argv[shablons[j]]);
                            if ((variable != NULL && flags->v == 0) || (variable == NULL && flags->v == 1))
                            {
                                string_counter++;
                                if (!flags->c && !flags->l)
                                {
                                    if(!flags->h)
                                    printf("%s:", argv[files[i]]);
                                    if (flags->n)
                                        printf("%d: ", all_strings_counter);
                                    if(flags->o) printf("%s\n", argv[shablons[j]]);
                                    else printf("%s", now_string);
                                }
                            }
                        }
                    }
                    if (string_counter != 0 && flags->l)
                    {
                        printf("%s\n", argv[files[i]]);
                    }
                    if (!flags->l && flags->c)
                    {
                        printf("%s: %d\n", argv[files[i]], string_counter);
                    }
                }

                else
                {
                    if(!flags->s) printf("grep: %s: No such file or directory\n", argv[files[i]]);
                }
            }
        }
    }
}

// for (int i = 0; i < number_of_files; ++i)
// {
//     if (files[i] != shablons[0])
//     {
//         file = fopen(argv[files[i]], "r");
//         if (file)
//         {
//             string_counter = 0;
//             all_strings_counter = 0;
//             while (getline(&now_string, &string_len, file) != -1)
//             {
//                 all_strings_counter++;
//                 for (int j = 0; j < number_of_shablons; ++j)
//                 {
//                     variable = strstr(now_string, argv[shablons[j]]);
//                     if ((variable != NULL && v_flag == 0) || (variable == NULL && v_flag == 1))
//                     {
//                         string_counter++;
//                         if (!c_flag && !l_flag)
//                         {
//                             printf("%s:", argv[files[i]]);
//                             if (n_flag)
//                                 printf("%d: ", all_strings_counter);
//                             printf("%s", now_string);
//                         }
//                     }
//                     if (string_counter != 0 && l_flag)
//                     {
//                         printf("%s", argv[i]);
//                     }
//                     if (!l_flag && c_flag)
//                     {
//                         printf("%s: %d", argv[files[i]], string_counter);
//                     }
//                 }
//             }
//         }
//         else
//         {
//             printf("grep: %s: No such file or directory\n", argv[files[i]]);
//         }
//     }
// }

// printf("\n%d\n", shablon);
// printf("%s\n", strstr('aa', 'faa a aa'));
