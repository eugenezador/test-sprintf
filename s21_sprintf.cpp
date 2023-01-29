#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  st_format_item format_item = {0, 0, 0, 0, 0, 0, 0};
  char *str_begin = str;
  va_list args;
  va_start(args, format);
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
    format = parse_flags(&format_item, format);
    format = parse_width(&format_item, format);
    format = parse_precision(&format_item, format);
    format = parse_length(&format_item, format);
    format = parse_specifier(&format_item, format);

    memset(buf, '\0', BUF_SIZE);
    arg_selector(format_item, buf, args); // returns buf

    str = add_to_string(str, buf);
  }

  va_end(args);
  *str = '\0';
  return str - str_begin;
}

const char *parse_flags(st_format_item *format_item, const char *format) {
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

const char *parse_width(st_format_item *format_item, const char *format) {
  int width = 0;
  format = get_number(format, &width);
  format_item->width = width;
  return format;
}

const char *parse_precision(st_format_item *format_item, const char *format) {
  int precision = 0;
  format = get_number(format, &precision);
  format_item->precision = precision;
  return format;
}

const char *get_number(const char *format, int *value) {
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

const char *parse_length(st_format_item *format_item, const char *format) {
  if (*format == 'h' || *format == 'l') {
    format_item->length = *format;
    format++;
  }
  return format;
}

const char *parse_specifier(st_format_item *format_item, const char *format) {
  if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u') {
    format_item->specifier = *format;
    format++;
  }
  return format;
}

void arg_selector(st_format_item format_item, char *buf, va_list args) {
  char temp_string[BUF_SIZE] = {'\0'};

  if (format_item.specifier == 'c') {
    char_processing(buf, args, format_item);
  } else if (format_item.specifier == 'd' || format_item.specifier == 'i') {
    int_processing(buf, args, temp_string, format_item);
  } else if (format_item.specifier == 'u') {
    u_int_processing(buf, args, temp_string, format_item);
  } else if (format_item.specifier == 's') {
    s_processing(buf, args, format_item);
  } else if (format_item.specifier == 'f') {
    f_processing(buf, format_item, args, temp_string);
  }
}

void char_processing(char *buf, va_list args, st_format_item format_item) {
//  wint_t c_value = va_arg(args, wint_t);
  if(format_item.length == 'l') {
      wint_t c_value = va_arg(args, wint_t); // ???
      *buf = c_value;
  } else {
      char c_value = va_arg(args, int);
      *buf = c_value;
  }
}

void int_processing(char *buf, va_list args, char *temp, st_format_item format_item) {

    long long int d_value = va_arg(args, long long int);

    if(format_item.length == 'h') {
        d_value = (short int)d_value;
    } else if(format_item.length == 'l') {
        d_value = (long int)d_value;
    }
  int_to_string(d_value, temp);
  add_to_string(buf, temp);
}

void u_int_processing(char *buf, va_list args, char *temp, st_format_item format_item) {
  unsigned long long int u_value = va_arg(args, unsigned long long int);

  if(format_item.length == 'h') {
      u_value = (unsigned short int)u_value;
  } else if(format_item.length == 'l') {
      u_value = (unsigned long int)u_value;
  }

  int_to_string(u_value, temp);
  add_to_string(buf, temp);
}

void s_processing(char *buf, va_list args, st_format_item format_item) {
    if(format_item.length == 'l') {
        wchar_t *s_value = va_arg(args, wchar_t*);

        // what is wchar ? how to process it?
    } else {
        char *s_value = va_arg(args, char *);
        add_to_string(buf, s_value);
    }
}

void f_processing(char *buf, st_format_item format_item, va_list args,
                  char *temp) {
  double f_value = va_arg(args, double);
  double_to_string(f_value, format_item, temp);
  add_to_string(buf, temp);
}

void int_to_string(long long int_value, char *result) {
  int k = 0;
  int add_sign = 0;

  if (int_value < 0) {
    int_value = -int_value;
    add_sign = 1;
  }

  if (int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (int_value > 0) {
    result[k] = int_value % 10 + '0';
    int_value = int_value / 10;
    k++;
  }

  if (add_sign) {
    result[k] = '-';
    k++;
  }

  result[k] = '\0';

  char tmp;
  for (int i = 0; i < k / 2; i++) {
    tmp = result[i];
    result[i] = result[k - 1 - i];
    result[k - 1 - i] = tmp;
  }
}

char *add_to_string(char *string, char *temp) {
  while (*temp) {
    *string = *temp;
    string++;
    temp++;
  }
  // rerurn current string pos
  return string;
}

void double_to_string(long double double_value, st_format_item format_item,
                      char *result) {
  long double left = 0.0;
  long double right = 0.0;
  long long i_left = 0;
  long long i_right = 0;
  char buf[BUF_SIZE] = {'\0'};

  right = modfl(double_value, &left);
  i_left = left;

  if (format_item.precision == 0) {
    format_item.precision = 6;
  }

  for (unsigned int i = 0; i < format_item.precision; i++) {
    right *= 10;
  }

  right = roundl(right);
  i_right = right;

  int_to_string(i_left, buf);
  result = add_to_string(result, buf);
  char dot[2] = ".";
  result = add_to_string(result, dot /*"."*/);

  memset(buf, '\0', BUF_SIZE);
  int_to_string(i_right, buf);
  result = add_to_string(result, buf);
}
