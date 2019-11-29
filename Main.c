// Calc
#include "Calc.h"
#include <ctype.h>
#include <conio.h>
//char * MyRealloc(const char *s, int size, int oldsize)
//{
//  char *res = malloc(size * sizeof(char));
//
//  memcpy_s(res, size * sizeof(char), s, oldsize * sizeof(char));
//  free((void *)s);
//  return res;
//
//}
int main( int argc, const char *argv[] )
{
  int size = 10, delta = 50, cur = 0, i, curf = 0;
  int brcheck = 0; // brackets 
  int comment_flag = 0, empty_flag = 1, end_flag = 0;
  int error = 0;   //error inside
  int skip_error = 0; // no memory-> skip
  char *s = NULL, *s1 = NULL, c = 0;
  char *format = NULL, *format1 = NULL;
  double ans = 0;
  FILE *F = NULL;

  // from file
  if (argc == 2)
  {
   // F = fopen(argv[1], "rt");// error
    if (fopen_s(&F, argv[1], "rt") != 0)
    {
      printf("error: no file found");
      return 1;
    }
  }
  if (argc == 1)
    F = stdin;
  if (argc > 2)
  {
    fprintf(stdout, "ERROR: WRONG PARAMERERS");
    return 1;
  }

  //s = (char *)malloc(sizeof(char) * size);
  //if (s == NULL)
  //{
  //  if (argc == 2)
  //    fclose(F);
  //  fprintf(stdout, "ERROR: no mem\n");  //: memory not allocated
  //  return 0;
  //}

  // one string work
  //scan from file
  while (1)
  {
    skip_error = 0;
    if (s1 != NULL)
    {
      free(s1);
      s1 = NULL;
    }
    size = 10;
    s = malloc(size * sizeof(char));
    if (s == NULL && skip_error != 1)
    {
      fprintf(stdout, "ERROR: no mem\n");  //: memory not allocated
      skip_error = 1;
      break;
    }
    cur = 0;
    curf = 0;
    comment_flag = 0;
    empty_flag = 1;
    error = 0;
    do
    {
      c = (char)fgetc(F);
      if ((c == -1) || (c == '\n'))
      {
        s[cur] = 0;
        s1 = s;
        /*if (c == '\n' && empty_flag == 1)
        {
          s[cur] = c;
          cur++;
        }*/
        break;
      }
 
     // comments
     if (cur >=1 && s[0] == '/' && c == '/')
     {
       comment_flag = 1;
       empty_flag = 0;
     }
     if (isspace(c) == 0 && c != '/')
       empty_flag = 0;
     /// else if (empty_flag == 1)
     ///   empty_flag = -1;
     /// if (empty_flag == -1 && s[cur - 1] == '/' && c != '/')
     ///   empty_flag = 0;
     /// if (c == '/' && s[cur - 1] == '/' && empty_flag == -1)
     ///   empty_flag = 1;
     /// if (cur >= 1 && comment_flag != 1 && c == '/' && s[cur - 1] == '/' && empty_flag == 1)
     /// {
     ///   comment_flag = 1;
     ///   empty_flag = 1;
     /// }
      if (cur == size - 2) // for zero in the end
      {
        s = (char *)realloc(s, size + delta);
        if (s == NULL && skip_error != 1)
        {
          //if (argc == 2)
          //  fclose(F);
          fprintf(stdout, "ERROR: no mem\n");  //: memory not allocated
          skip_error = 1;
        }
        size += delta;
      } 
      ///if (c == '-' && cur > 0 && s[cur - 1] == '-' && comment_flag != 1)
      ///  cur--;
      
      
      if (comment_flag != 1)
      { 
        if (cur == '(')
          brcheck++;
        else if (cur == ')')
          brcheck--;
        if (brcheck < 0)
        {
          fprintf(stdout, "ERROR\n");  // wrong brackets
          error = 1;
        }
      }
      s[cur] = c;
      cur++;
      
      
    }
    while (end_flag == 0 && c != EOF);  ///!!!
    /*if (c == EOF)
    {
      end_flag = 1;
    }*/
    if (brcheck != 0 && comment_flag != 1)
    {
      fprintf(stdout, "ERROR\n");  // wrong brackets
      error = 1;
    }

    //scanned




    if (comment_flag != 1 && cur != 0 && empty_flag == 0 && skip_error != 1)
    {
      //s1 = malloc(sizeof(char) * cur);
      //if (s1 == NULL)
      //{
      //  fprintf(stdout, "ERROR: Malloc((\n");  // Malloc
      //  skip_error = 1;
      //}
      format = malloc(cur * 3 * sizeof(char));
      if (format == NULL && skip_error != 1)
      {
        fprintf(stdout, "ERROR: no mem\n");  //: memory not allocated
        skip_error = 1;
        break;
      }
      memset(format, 0, cur * 3 * sizeof(char));
      format1 = format;
      if (skip_error != 1)
      {
      //  strcpy(s1, s);
        s1 = s;
        
        // print no format str
        fprintf(stdout, "%s == ", s);
        // format it
        for (i = 0; i < cur; i++)
        {
          if (s[i] == '-')
          {
            format[curf] = '-';
            curf++;
            format[curf] = '1';
            curf++;
            format[curf] = '*';
            curf++;
          } 
          else
          {
            format[curf] = s[i];
            curf++;
          }
        }
        // calculate
        ans = 3;//Comp(format, curf, 1, &format, &error);
        if (error != 1)
          fprintf(stdout, "%g\n", ans);
        free(format1);
      }
    }
    else if (skip_error != 1)
    { 
      //s1 = s;
      if (c != EOF)
        fprintf(stdout, "%s\n", s);
    }
    if (c == EOF)
      break;
  }
  if (argc == 2)
    fclose(F);
  //free(s);
  if (s1 != NULL)
    free(s1);
  //_getch();
  return 0;
}