#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} Flags;

void free_matrix(char **matrix, int rows);
void print_str(char *fileName, char *str, int count, int countFile,
               int count_line, Flags flags);
int analizFile(Flags flags, char *nameFile, char **template,
               int sizeArrayTemplate, int countFile);
int parseScan(int argc, char *argv[]);
void searchStr(char **template, int sizeArrayTemplate, Flags flags, char *line,
               char *nameFile, int lineSize, int countFile, int *count_sovp_str,
               int count_line);
int read_temlateFile(char *nameFile, Flags flags, char ***template,
                     int *sizeArrayTemplate, int *countTemplate);
int count_substr(char *str, char **template, int sizeArrayTemplate,
                 char *fileName, int countFile, int count_line, Flags flags);

int main(int argc, char *argv[]) {
  parseScan(argc, argv);
  return 0;
}
int count_substr(char *str, char **template, int sizeArrayTemplate,
                 char *fileName, int countFile, int count_line, Flags flags) {
  int count = 0;
  char *min = str + strlen(str), *k = str, *p = str,
       *temp = malloc(sizeof(char) * strlen(template[0] + 1)),
       *sub_str = template[0];
  size_t len = 0;
  char *lineCopy = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(lineCopy, str);
  do {
    min = str + strlen(str);
    for (int i = 0; i < sizeArrayTemplate; ++i) {
      if (flags.i == true) {
        for (int j = 0; j < (int)strlen(template[i]); ++j)
          template[i][j] = tolower(template[i][j]);
        for (int j = 0; j < (int)strlen(str); ++j) str[j] = tolower(str[j]);
      }
      sub_str = template[i];
      if ((p = strstr(k, sub_str)) != NULL) {
        if (p < min) {
          min = p;
          len = strlen(sub_str);
          temp = realloc(temp, (len + 2) * sizeof(char));
          char *var = &lineCopy[p - str];
          strncpy(temp, (char *)var, len);
          temp[len] = '\0';
          strcat(temp, "\n");
        }
      }
    }
    k = min + len;
    if (min != str + strlen(str) && flags.n == false)
      print_str(fileName, temp, -1, countFile, count_line, flags);
    else if (min != str + strlen(str))
      print_str(fileName, temp, -3, countFile, count_line, flags);
    count++;
  } while (min != str + strlen(str));
  free(temp);
  free(lineCopy);
  return count;
}
int read_temlateFile(char *nameFile, Flags flags, char ***template,
                     int *sizeArrayTemplate, int *countTemplate) {
  int returning = 0;
  FILE *fp;
  fp = fopen(nameFile, "r");
  if (fp == NULL) {
    if (flags.s == false) printf("Error open to file_temlate(%s) \n", nameFile);
    returning = 1;
  } else {
    int lineSize = 0;  // lineSize = 2
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
      lineSize = (int)len;
      if (*countTemplate > 0) {
        ++*sizeArrayTemplate;
        *template = realloc(*template, (*sizeArrayTemplate) * sizeof(char *));
      }
      (*template)[*countTemplate] = malloc(sizeof(char) * (lineSize + 1));

      if (line[0] != '\n') {
        for (int i = 0; i < lineSize; ++i) {
          if (line[i] != '\n')
            (*template)[*countTemplate][i] = line[i];
          else {
            (*template)[*countTemplate][i] = '\0';
            break;
          }
        }
      } else {
        (*template)[*countTemplate][0] = '\n';
        (*template)[*countTemplate][1] = '\0';
      }
      ++*countTemplate;
    }
    free(line);
    fclose(fp);
  }
  return returning;
}

void print_str(char *fileName, char *str, int count, int countFile,
               int count_line,
               Flags flags) {  //-1 выводит строку -2 имя файла -3 выводит
  // номер строки иначе количтво строк
  if (count == -3) {
    if (countFile > 1 && flags.h == false)
      printf("%s:%d:%s", fileName, count_line, str);
    else
      printf("%d:%s", count_line, str);
  } else if (count == -2) {
    printf("%s\n", fileName);
  } else if (count == -1) {
    if (countFile > 1 && flags.h == false)
      printf("%s:%s", fileName, str);
    else
      printf("%s", str);
  } else {
    if (countFile > 1 && flags.h == false)
      printf("%s:%d\n", fileName, count);
    else
      printf("%d\n", count);
  }
}

void searchStr(char **template, int sizeArrayTemplate, Flags flags, char *line,
               char *nameFile, int lineSize, int countFile, int *count_sovp_str,
               int count_line) {
  char *lineCopy = malloc(sizeof(char) * lineSize);
  int index = -1;
  if (flags.n == true) index = -3;
  strcpy(lineCopy, line);
  for (int i = 0; i < sizeArrayTemplate; ++i) {
    if (flags.i == true) {
      for (int j = 0; j < (int)strlen(template[i]); ++j)
        template[i][j] = tolower(template[i][j]);
      for (int j = 0; j < (int)strlen(line); ++j) line[j] = tolower(line[j]);
    }
    if (strstr(line, template[i]) != NULL) {
      if (flags.v == true) break;
      ++*count_sovp_str;
      if (flags.c == false && flags.l == false)
        print_str(nameFile, lineCopy, index, countFile, count_line, flags);
      break;
    } else if (flags.v == true && i == sizeArrayTemplate - 1) {
      ++*count_sovp_str;
      if (flags.c == false && flags.l == false)
        print_str(nameFile, lineCopy, index, countFile, count_line, flags);
    }
    strcpy(line, lineCopy);
  }
  free(lineCopy);
}

int analizFile(Flags flags, char *nameFile, char **template,
               int sizeArrayTemplate, int countFile) {
  int returning = 0;
  FILE *fp;
  fp = fopen(nameFile, "r");
  if (fp == NULL) {
    if (flags.s == false) printf("Error open to file(%s) \n", nameFile);
    returning = 1;
  } else {
    int lineSize = 0, count_sovp_str = 0, count_line = 0;  // lineSize = 2
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
      count_line++;
      lineSize = (int)len;
      if (flags.o == true && flags.c == false && flags.l == false)
        count_substr(line, template, sizeArrayTemplate, nameFile, countFile,
                     count_line, flags);
      else
        searchStr(template, sizeArrayTemplate, flags, line, nameFile, lineSize,
                  countFile, &count_sovp_str, count_line);
    }
    fclose(fp);
    if (flags.c == true && flags.l == false)
      print_str(nameFile, "0", count_sovp_str, countFile, count_line, flags);
    if (flags.l == true && count_sovp_str != 0)
      print_str(nameFile, "-2", -2, countFile, count_line, flags);
    free(line);
  }
  return returning;
}

void free_matrix(char **matrix, int rows) {
  for (int i = 0; i < rows; ++i) {
    free(matrix[i]);
  }
  free(matrix);
}
int parseScan(int argc, char *argv[]) {
  int countTemplate = 0, sizeArrayTemplate = 1, countFile = 0,
      sizefilesArray = 1, returning = 0;
  char **template, **filesArray;
  template = malloc(sizeof(char *) * sizeArrayTemplate);
  filesArray = malloc(sizeof(char *) * sizefilesArray);
  Flags flags = {false, false, false, false, false,
                 false, false, false, false, false};

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      flags.e = false;
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        if (argv[i][j] == 'e' && flags.f == false) {
          flags.e = true;
        } else if (argv[i][j] == 'i' && flags.e == false && flags.f == false) {
          flags.i = true;
        } else if (argv[i][j] == 'v' && flags.e == false && flags.f == false) {
          flags.v = true;
        } else if (argv[i][j] == 'c' && flags.e == false && flags.f == false) {
          flags.c = true;
        } else if (argv[i][j] == 'l' && flags.e == false && flags.f == false) {
          flags.l = true;
        } else if (argv[i][j] == 'n' && flags.e == false && flags.f == false) {
          flags.n = true;
        } else if (argv[i][j] == 'h' && flags.e == false && flags.f == false) {
          flags.h = true;
        } else if (argv[i][j] == 's' && flags.e == false && flags.f == false) {
          flags.s = true;
        } else if (argv[i][j] == 'f' && flags.e == false) {
          flags.f = true;
        } else if (argv[i][j] == 'o' && flags.e == false) {
          flags.o = true;
        } else {
          printf(
              "Error flags, valid flags [e i v c l n] and the [e] [f] flag "
              "should be in after the other flags\n");
          returning = 1;
        }
      }
    } else if (((countTemplate > 0 && flags.e == true) ||
                (countTemplate == 0)) &&
               flags.f == false) {
      flags.e = false;
      if (countTemplate > 0) {
        sizeArrayTemplate++;
        template = realloc(template, sizeArrayTemplate * sizeof(char *));
      }
      template[countTemplate] = malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(template[countTemplate], argv[i]);
      countTemplate++;
    } else if (flags.f == true) {
      returning = read_temlateFile(argv[i], flags, &template,
                                   &sizeArrayTemplate, &countTemplate);
      flags.f = false;
    } else {
      if (countFile >= sizefilesArray) {
        sizefilesArray++;
        filesArray = realloc(filesArray, sizeof(char *) * sizefilesArray);
      }
      filesArray[countFile] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(filesArray[countFile], argv[i]);
      countFile++;
    }
  }

  for (int i = 0; i < countFile; i++) {
    if (analizFile(flags, filesArray[i], template, sizeArrayTemplate,
                   countFile) == 1) {
      returning = 1;
    }
  }
  free_matrix(template, sizeArrayTemplate);
  free_matrix(filesArray, sizefilesArray);
  return returning;
}
