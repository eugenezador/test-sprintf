#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  st_format_item format_item = {0, 0, 0, 0, 0, 0, 0, 0};
  char *str_begin = str;
  va_list args;
  va_start(args, format);
  char result[BUF_SIZE] = {'\0'};  // аргумент преобрахованный в строку
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
      format_item.precision_set = 0;
      format_item.length = 0;
      format_item.specifier = 0;
    }
    format = parse_flags(&format_item, format);
    format = parse_width(&format_item, format);
    if (*format == '.') {
      format++;
      format = parse_precision(&format_item, format);
      format_item.precision_set = 1;
    }
    format = parse_length(&format_item, format);
    format = parse_specifier(&format_item, format);

    memset(result, '\0', BUF_SIZE);
    arg_selector(format_item, result, args);  // returns buf

    str = add_to_string(str, result);
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
  if (/**format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u'*/ is_specifier(*format)) {
    format_item->specifier = *format;
    format++;
  }
  return format;
}

int is_specifier(char ch) {
    int result = 0;
    if (ch == 'c' || ch == 'd' || ch == 'i' || ch == 'f' ||
        ch == 's' || ch == 'u' || ch == '%' || ch == 'o' ||
        ch == 'g' || ch == 'G' || ch == 'e' || ch == 'E' ||
        ch == 'x' || ch == 'X' || ch == 'n' || ch == 'p') {
        result = 1;
    }
    return result;
}

void arg_selector(st_format_item format_item, char *result, va_list args) {
  char temp[BUF_SIZE] = {'\0'};
  char formated_temp[BUF_SIZE] = {'\0'};

  if (format_item.specifier == 'c') {
    char_processing(result, args, format_item);
  } else if (format_item.specifier == 'd' || format_item.specifier == 'i') {
    int_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 'u') {
    u_int_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 's') {
    s_processing(result, args, format_item);
  } else if (format_item.specifier == 'f') {
    f_processing(result, format_item, args, temp);
  } else if (format_item.specifier == '%') {
    result[0] = '%'; // !!!!
  }
}

void char_processing(char *result, va_list args, st_format_item format_item) {
  if (format_item.length == 'l') {
    // wchar_t wide_c;
    // wide_c = va_arg(args, wchar_t);
    // !!!!!!!!!!!
    // *result = c_value;
  } else {
    char c_value = va_arg(args, int);
    *result = c_value;
  }
}

// void wide_char_processing(st_format_item args, char *buff, wchar_t w_c) {
//   if (!f.minus && f.width) {
//     char tmp[BUFF_SIZE] = {'\0'};
//     wcstombs(tmp, &w_c, BUFF_SIZE);
//     for (s21_size_t i = 0; i < f.width - s21_strlen(tmp); i++) buff[i] = ' ';
//     s21_strcat(buff, tmp);
//   } else if (f.width) {
//     wcstombs(buff, &w_c, BUFF_SIZE);
//     for (int i = s21_strlen(buff); i < f.width; i++) buff[i] = ' ';
//   } else {
//     wcstombs(buff, &w_c, BUFF_SIZE);
//   }
// }

void int_processing(char *result, va_list args, char *temp,
                    st_format_item format_item, char *formated_temp) {
//   int64_t d_value = va_arg(args, int64_t);
//   printf("d val = %lld\n", d_value);
  // printf("1 int = %ld\n", d_value);
  if (format_item.length == 'h') {
    int d_value = va_arg(args, int);
    d_value = (short int)d_value;
    int_to_string(d_value, temp);
    // add_to_string(result, temp);
  } else if (format_item.length == 'l') {
    long d_value = va_arg(args, long);
    int_to_string(d_value, temp);
    // add_to_string(result, temp);
  } else {
    int d_value = va_arg(args, int);
    int_to_string(d_value, temp);
    // presicion_processing(format_item, temp, result);
    // add_to_string(result, temp);
  }

  presicion_processing(format_item, temp, formated_temp);
  flags_processing(format_item, formated_temp, result);
}

void u_int_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp) {
  unsigned long long int u_value = va_arg(args, unsigned long long int);

  if (format_item.length == 'h') {
    u_value = (unsigned short int)u_value;
  } else if (format_item.length == 'l') {
    u_value = (unsigned long int)u_value;
  }

  int_to_string(u_value, temp);
  presicion_processing(format_item, temp, formated_temp);
  flags_processing(format_item, formated_temp, result);
}

void s_processing(char *result, va_list args, st_format_item format_item) {
  if (format_item.length == 'l') {
    // wchar_t *s_value = va_arg(args, wchar_t *);

    // what is wchar ? how to process it?
  } else {
    char *s_value = va_arg(args, char *);
    add_to_string(result, s_value);
  }
}

void f_processing(char *result, st_format_item format_item, va_list args,
                  char *temp) {
  double f_value = va_arg(args, double);
  if (!format_item.precision_set) {
    format_item.precision = 6;
  }
  double_to_string(f_value, format_item, temp);
  flags_processing(format_item, temp, result);
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

  char tmp = '\0';
  for (int i = 0; i < k / 2; i++) {
    tmp = result[i];
    result[i] = result[k - 1 - i];
    result[k - 1 - i] = tmp;
  }
}

char *add_to_string(char *result, char *temp) {
  while (*temp) {
    *result = *temp;
    result++;
    temp++;
  }
  // rerurn current result pos
  return result;
}

void double_to_string(long double double_value, st_format_item format_item,
                      char *result) {
  long double left = 0.0, right = 0.0;
  long long i_left = 0, i_right = 0;
  char buf[400] = {'\0'};
  int k = 0; //buf iterator

  right = modfl(double_value, &left);
  i_left = left;

  // левую часть записываем в результат
  int_to_string(i_left, buf);
  result = add_to_string(result, buf);
  //
  // добавляем часть после точки
  if( (format_item.precision_set && format_item.precision != 0) || !format_item.precision_set) {
     char dot[2] = ".";
     result = add_to_string(result, dot /*"."*/);

  memset(buf, '\0', 400); // чистим буфер

  //цикл записывает правую часть в буфер
  for (int i = 0; i < format_item.precision; i++) {
    right *= 10;
    if(roundl(right) == 0) {
        i_right = roundl(right);
        buf[k] = i_right + '0';
    } else {
        i_right = roundl(right);
        buf[k] = i_right % 10 + '0';

    }
//    printf("buf[%d] = %c\n", k, buf[k]);
//    printf("right = %Lf\n", right);
    k++;
  }
//  printf("\n");
//  printf("buf = %s\n", buf);

  result = add_to_string(result, buf);
}


//  right = roundl(right);
//  i_right = right;

//  printf("1 left = %lld\n", i_left);
//  printf("1 right = %lld\n", i_right);

//  int_to_string(i_left, buf);
//  result = add_to_string(result, buf);
//  if(format_item.precision_set && format_item.precision != 0) {
//      char dot[2] = ".";
//     result = add_to_string(result, dot /*"."*/);


//  memset(buf, '\0', 80);

//  int_to_string(i_right, buf);


//  // костыль если значение 0
//  if (buf[0] == '0') {
//    for (int i = 1; i < format_item.precision; i++) {
//      buf[i] = '0';
//    }
//  }

//  result = add_to_string(result, buf);
//  }
}

void presicion_processing(st_format_item format_item, char *value,
                          char *result) {
  int len = strlen(value);
  int i = 0;
  int sign = 0;
  int null_value = 0;
  if (value[0] == '0') {
    null_value = 1;
  }

  if (len < format_item.precision) {
    if (value[0] == '-') {
      result[0] = '-';
      value++;
      sign = 1;
    }
    while (format_item.precision + sign - len > 0) {
      if (result[i] == '-') {
        i++;
        continue;
      }
      result[i] = '0';
      // printf("res [%d] = %c\n", i, result[i]);
      i++;
      format_item.precision--;
    }
  }

  if (format_item.precision_set == 1 && null_value) {
    value[0] = '\0';
  }

  add_to_string(result + i, value);

  // printf("pres = %s\n", result);
}

void flags_processing(st_format_item format_item, char *value, char *result) {
  char f_temp[BUF_SIZE] = {'\0'};
  int i = 0;  // f_temp index
  int len = strlen(value);
  int sign = 0;
  // printf("1width = %d\n", format_item.width);
  if ((format_item.width > len) && !format_item.minus) {
    i = add_width_spaces_first(f_temp, format_item.width, len);
    if (value[0] == '-' || format_item.plus) {
      i--;
      // printf("do min\n");
    }
    if (value[0] == '-') sign = 1;
    // printf("i = %d\n", i);
  }

  if (!format_item.plus && format_item.space && value[0] != '-' &&
      format_item.specifier != 'u') {
    f_temp[0] = ' ';
    i++;
    // printf("in space\n");
  } else if (format_item.plus && value[0] != '-' &&
             format_item.specifier != 'u') {
    // printf("in plus\n");
    f_temp[i] = '+';
    i++;
    if (format_item.minus && (format_item.width > len)) {
      // printf("in minus\n");
      add_to_string(f_temp + i, value);
      add_width_spaces_to_end(f_temp + len, format_item.width, len);
    }
  } else if (format_item.minus && (format_item.width > len)) {
    // printf("in minus\n");
    add_to_string(f_temp + i, value);
    add_width_spaces_to_end(f_temp + len, format_item.width, len);
  }
  add_to_string(f_temp + i - sign, value);
  add_to_string(result, f_temp);
}

void add_width_spaces_to_end(char *result, int width, int value_len) {
  // add_to_string(result, value);
  int i = value_len;
  // result
  while (i < width) {
    *result = ' ';
    result++;
    i++;
  }
}

int add_width_spaces_first(char *result, int width, int value_len) {
  int i = 0;
  while (width > value_len) {
    *result = ' ';
    result++;
    i++;
    width--;
  }
  return i;
}
