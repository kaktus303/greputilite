#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int e_flag = 0, i_flag = 0, v_flag = 0, c_flag = 0, l_flag = 0, n_flag = 0, execute_flag = 1;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
                if (argv[i][j] == 'i')
                    i = 1;
                else if (argv[i][j] == 'e')
                    e_flag = 1;
                else if (argv[i][j] == 'n')
                    n_flag = 1;
                else if (argv[i][j] == 'l')
                    l_flag = 1;
                else if (argv[i][j] == 'v')
                    v_flag = 1;
                else if (argv[i][j] == 'c')
                    c_flag = 1;
                else
                {
                    printf("grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n", argv[i][j]);
                    execute_flag = 0;
                }
        }
    }
    
}