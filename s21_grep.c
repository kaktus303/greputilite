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
            for (int j = 1; j < (int)strlen(argv[i]); ++j)
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
void find_files_shablons(int argc, char *argv[], int *files, int *number_of_files, int *shablons, int *number_of_shablons, int *shablon_files, int *number_of_shablon_files)
{
    int flag = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < (int)strlen(argv[i]); ++j)
            {
                if (argv[i][j] == 'e')
                {
                    shablons[*number_of_shablons] = i + 1;
                    flag = 1;
                    *number_of_shablons += 1;
                }
                if (argv[i][j] == 'f')
                {
                    shablon_files[*number_of_shablon_files] = i + 1;
                    flag = 1;
                    *number_of_shablon_files += 1;
                }
            }
        }
        else
        {
            if (flag == 0)
            {
                files[*number_of_files] = i;
                *number_of_files += 1;
            }
            else
                flag = 0;
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
void print_string_slice(char *string, int n)
{
    for (int i = 0; i < n && string[i] != '\n' && string[i] != '\0' && string[i] != EOF; ++i)
    {
        printf("%c", string[i]);
    }
}
void string_print(char *now_string, char *file_name, Flags *flags, int all_strings_counter)
{
    if (!flags->c && !flags->l)
    {
        if (!flags->h)
            printf("%s:", file_name);
        if (flags->n)
            printf("%d:", all_strings_counter);
        // if (flags->o)
        //     print_string_slice(variable, strlen(shablon));
        printf("%s", now_string);
        if (now_string[strlen(now_string) - 1] != '\n')
            printf("\n");
    }
}
int string_checking(char *now_string, char *shablon, Flags *flags)
{
    char *i_shablon = malloc(sizeof(char) * (int) strlen(shablon)+ 10);
    char *i_line = malloc(sizeof(char) * (int) strlen(now_string) + 10);
    char *variable;

    if (shablon[strlen(shablon) - 1] == '\n' && shablon[0] != '\n')
        shablon[strlen(shablon) - 1] = '\0';
    strcpy(i_shablon, shablon);
    strcpy(i_line, now_string);

    if (flags->i)
    {
        register_down(i_shablon);
        register_down(i_line);
        // printf("%s", (unsigned int)strlen(variable));
        variable = strstr(i_line, i_shablon);
    }
    else

        variable = strstr(now_string, shablon);
    // printf("\n*%s*\n", variable);
    // printf("\n*%s*%s*%s\n", shablon, now_string, strstr(now_string, shablon));
    free(i_line);
    free(i_shablon);
    
    if (variable != NULL)
    {
        // free(variable);
        return 1;
    }
    else
    {
        return 0;
    };
}
int main(int argc, char *argv[])
{
    Flags *flags = malloc(sizeof(Flags));
    int string_counter = 0, all_strings_counter = 0, number_of_shablons = 0, number_of_shablon_files = 0, string_flag = 0;
    int number_of_files = 0;
    size_t string_len = 1;
    char *now_string = NULL;
    int *shablons = malloc(sizeof(int) * argc);
    int *files = malloc(sizeof(int) * argc);
    int *shablon_files = malloc(sizeof(int) * argc);
    size_t shablon_string_len = 1;
    char *shablon_string = NULL;
    // pointer to an array of [lines] pointers

    // for (i = 0; i < number_of_shablons; ++i)
    //     shablons_matrix[i] = (int *)malloc(columns * sizeof(int));
    FILE *file = NULL;
    FILE *shablon_file = NULL;
    null_stuct(flags);
    if (find_flags(argc, argv, flags))
    {
        find_files_shablons(argc, argv, files, &number_of_files, shablons, &number_of_shablons, shablon_files, &number_of_shablon_files);

        if (!flags->e && !flags->f)
            no_e_flag(argc, argv, shablons, &number_of_shablons);
        // printf("%d, %d, %d\n", number_of_files, number_of_shablons, number_of_shablon_files);
        if (number_of_files == 1)
        {
            flags->h = 1;
        }
        // printf("%d", number_of_shablon_files);
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
                        string_flag = 0;
                        // printf("HORAY88\n");
                        for (int j = 0; j < number_of_shablons; ++j)
                        {
                            if (string_checking(now_string, argv[shablons[j]], flags) == 1)
                            {
                                string_flag = 1;
                            }
                        }
                        if (flags->f)
                        {
                            for (int k = 0; k < number_of_shablon_files; ++k)
                            {
                                shablon_file = fopen(argv[shablon_files[k]], "r");
                                if (shablon_file){
                                    while (getline(&shablon_string, &shablon_string_len, shablon_file) != -1)
                                    {
                                        // printf("111");
                                        // printf("\n***|%s|***\n", shablon_string);
                                        // if(shablon_string[strlen(shablon_string)-2] == '\n') shablon_string[shablon_string_len-2] = '\0';
                                        if (string_checking(now_string, shablon_string, flags) == 1)
                                        {
                                            string_flag = 1;
                                        }
                                    }
                                    fclose(shablon_file);
                                }
                                else
                                {
                                    if (!flags->s)
                                    printf("grep: %s: No such file or directory\n", argv[shablon_files[k]]);
                                }
                            }
                        }
                        string_counter += string_flag;
                        if ((string_flag == 1 && !flags->v) || (string_flag == 0 && flags->v))
                        {
                            string_print(now_string, argv[files[i]], flags, all_strings_counter);
                        }
                        // free(now_string);
                        // free(variable);
                    }
                    if (flags->l)
                    {
                        if((!flags->v && string_counter!=0)||(flags->v && all_strings_counter - string_counter!=0))
                        printf("%s\n", argv[files[i]]);
                        
                    }
                    if (!flags->l && flags->c)
                    {
                        if(!flags->h) printf("%s:", argv[files[i]]);
                        if (!flags->v)
                            printf("%d\n",string_counter);
                        else
                            printf("%d\n",all_strings_counter - string_counter);
                    }
                    fclose((file));
                }

                else
                {
                    if (!flags->s)
                        printf("grep: %s: No such file or directory\n", argv[files[i]]);
                }
            }
        }
    }
    free(flags);
    free(shablons);
    free(files);
    free(shablon_files);
    free(now_string);
    free(shablon_string);
}
