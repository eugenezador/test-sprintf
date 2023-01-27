
#include <stdio.h>
#include <stdarg.h>

void display(const char* format, ...)
{
    int d;
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
            case 'd':
                d = va_arg(factor, int);
                printf("d = %d\n", d);
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
    display("%d : %d\n", 24, 68);
    return 0;
}



/*




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

const char *parse_flags(st_format_item *format_item, const char *format);

const char* parse_width(st_format_item *format_item, const char *format);

const char* parse_precision(st_format_item *format_item, const char *format);

const char *get_number(const char *format, int *value);

int is_number(char c);

const char *parse_length(st_format_item *format_item, const char *format);

const char *parse_specifier(st_format_item *format_item, const char *format);

void arg_selector(st_format_item format_item, char *buf,
                  va_list ptr);

void int_to_string(long long int_value, char* result);

char* append_to_string(char *string, char *temp);

    int main() {
        char str[255] ={'\0'};
        s21_sprintf(str, "hello %d , %d", 41, 42);
        printf("res str : %s\n", str);
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
//    format = parse_flags(&format_item, format);
//    format = parse_width(&format_item, format);
//    if (*format == '.') {
//      format++;
//      format = parse_precision(&format_item, format);
//    }
//    format = parse_length(&format_item, format);
    format = parse_specifier(&format_item, format);
    printf("spec = %c\n", format_item.specifier);


    arg_selector(format_item, buf, ptr);
    str = append_to_string(str, buf);
  }

  va_end(ptr);
  *str = '\0';
  return str - str_begin;
}

const char* parse_flags(st_format_item *format_item, const char *format) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        format_item->minus = 1;
        break;
      case '+':
        format_item->plus = 1;
        break;
      case ' ':
        format_item->space = 1;
        break;
    }
    format++;
  }
  return format;
}

const char* parse_width(st_format_item *format_item, const char *format) {
  int width = 0;
  format = get_number(format, &width);
  format_item->width = width;
  return format;
}

const char* parse_precision(st_format_item *format_item, const char *format) {
  int precision = 0;
  format = get_number(format, &precision);
  format_item->precision = precision;
  return format;
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

const char* parse_length(st_format_item *format_item, const char *format) {
  if (*format == 'h' || *format == 'h') {
    format_item->length = *format;
    format++;
  }
  return format;
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

    printf("__arg selector function__\n");
  char char_value = 'c';
  int int_value = 0;
  char temp_string[BUF_SIZE] = {'\0'};

  if (format_item.specifier == 'c') {
    char_value = va_arg(ptr, char);
    *buf = char_value;
    buf++;
  } else if (format_item.specifier == 'd' || format_item.specifier == 'i') {
    int_value = va_arg(ptr, int);
    int_to_string(int_value, temp_string);
    append_to_string(buf, temp_string);
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

char *append_to_string(char *string, char *temp) {
    printf("str = %s\n", string);
    printf("temp = %s\n", temp);
  while(*temp) {
    *string = *temp;
      printf("str : %c : tmp : %c\n", *string, *temp);
    string++;
    temp++;
  }
  printf("add int str = %c\n", *string);
  return string;
}
*/
