/*
#include <stdio.h>
#include <stdarg.h>

void funk(va_list factor, char* t) {
    *t = va_arg(factor, char);
    printf("funk = %d\n", *t);
}


void display(const char* format, ...)
{
    char d = 0;
    double f;
    va_list factor;         // указатель на необязательный параметр
    va_start(factor, format);   // устанавливаем указатель


    for( const char *c = format;*c; c++)
    {
        if(*c!='%')
        {
            printf("%c", *c);
            continue;
        }
        switch(*++c)    // если символ - %, то переходим к следующему символу
        {
            case 'c':
                funk(factor, &d);
                printf("d = %c\n", d);
                break;
            case 'f':
                f = va_arg(factor, double);
                printf("%.2lf", f);
                break;
            default:
                printf("%c", *c);
        }
    }
    va_end(factor);
}


int main(void)
{
    display("%c : %c\n", '-', '+');
    return 0;
}
*/





#include <stdio.h>
#include <stdarg.h>

// нужно реализовать atoi
#include <stdlib.h>

#define BUF_SIZE 4096

#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

typedef struct {
  //  flags
  int minus;
  int plus;
  int space;

  unsigned int width;

  unsigned int precision;

  char length;

  char specifier;

} st_format_item;

int s21_sprintf(char *str, const char *format, ...);

const char *get_number(const char *format, int *value);

int is_number(char c);

const char *parse_specifier(st_format_item *format_item, const char *format);

void arg_selector(st_format_item format_item, char *buf,
                  va_list ptr);

void int_to_string(long long int_value, char* result);

char* add_to_string(char *string, char *temp);

    int main() {
        printf("hello\n");
        char str[255] ={'\0'};
        s21_sprintf(str, "%c : %d\n", '*', 41);
        printf("res str = %s\n", str);
        return 0;
    }

int s21_sprintf(char *str, const char *format, ...) {
  st_format_item format_item = {0, 0, 0, 0, 0, 0, 0};
  char *str_begin = str;
  va_list ptr;
  va_start(ptr, format);
  char buf[BUF_SIZE] = {'\0'};
  while (*format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
      continue;
    } else {
        format++;
        format_item.minus = 0;
        format_item.plus = 0;
        format_item.space = 0;
        format_item.width = 0;
        format_item.precision = 0;
        format_item.length = 0;
        format_item.specifier = 0;
    }
    printf("format = %c\n", *format);
    format = parse_specifier(&format_item, format);

    printf("buf = %s\n", buf);
    arg_selector(format_item, buf, ptr);
    printf("buf = %s\n", buf);

    str = add_to_string(str, buf);
  }

  va_end(ptr);
  *str = '\0';
  return str - str_begin;
}



const char* get_number(const char *format, int *value) {
  char tmp_digit[4] = {'\0'};
  int k = 0;
  while (1) {
    if (is_number(*format)) {
      tmp_digit[k++] = *format;
    } else {
      break;
    }
    format++;
  }
  *value = atoi(tmp_digit);
  return format;
}

int is_number(char c) {
  int result = 0;
  if (c >= '0' && c <= '9') {
    result = 1;
  }
  return result;
}

const char* parse_specifier(st_format_item *format_item, const char *format) {
  if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u') {
    format_item->specifier = *format;
    format++;
  }
  return format;
}

void arg_selector(st_format_item format_item, char *buf,
                  va_list ptr) {

  char char_value = '\0';
  int int_value = 0;
  char temp_string[BUF_SIZE] = {'\0'};

  if (format_item.specifier == 'c') {
    char_value = va_arg(ptr, int);
    *buf = char_value;
    printf("2buf = %s\n", buf);
  } else if (format_item.specifier == 'd' || format_item.specifier == 'i') {
    int_value = va_arg(ptr, int);
    int_to_string(int_value, temp_string);
    add_to_string(buf, temp_string);
    }
}

void int_to_string(long long int_value, char* result) {
  // char result[BUF_SIZE] = {'\0'};
    int k = 0;

        if(int_value < 0) {
      int_value = -int_value;
    }

    if(int_value == 0) {
      result[k] = '0';
      k++;
    }

    while (int_value > 0)
    {
        result[k] = int_value % 10 + '0';
        int_value = int_value / 10;
        k++;
    }

    if(int_value < 0) {
      result[k] = '-';
      k++;
    }

    result[k] = '\0';

    char tmp;
    for (int i = 0; i < k / 2; i++)
    {
        tmp = result[i];
        result[i] = result[k - 1 - i];
        result[k - 1 - i] = tmp;
    }
}

char* add_to_string(char *string, char *temp) {
  while(*temp) {
    *string = *temp;
    string++;
    temp++;
  }
  // rerurn current string pos
  return string;
}

