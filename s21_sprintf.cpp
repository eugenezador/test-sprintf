#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  st_format_item format_item = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
      format_item.nullik = 0;
      format_item.grill = 0;
      format_item.width = 0;
      format_item.precision = 0;
      format_item.precision_set = 0;
      format_item.length = 0;
      format_item.specifier = 0;
    }
    format = parse_flags(&format_item, format);
    format = parse_width(&format_item, format, args);
    if (*format == '.') {
      format++;
      format = parse_precision(&format_item, format, args);
      format_item.precision_set = 1;
    }
    format = parse_length(&format_item, format);
    format = parse_specifier(&format_item, format);

    memset(result, '\0', BUF_SIZE);
    arg_selector(format_item, result, args);
    str = add_to_string(str, result);



    // вывода символов при спец n не производиться
    if (format_item.specifier == 'n') {
      int *res = va_arg(args, int *);
      *res = str - str_begin;
    }

    //    if (--*str == '\0') {
    //      str++;
    //      break;
    //    }
  }

  *str = '\0';
  va_end(args);
  return str - str_begin;
}

const char *parse_flags(st_format_item *format_item, const char *format) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
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
      case '0':
        format_item->nullik = 1;
        break;
      case '#':
        format_item->grill = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *parse_width(st_format_item *format_item, const char *format,
                        va_list args) {
  int width = 0;

  if (*format == '*') {
    width = va_arg(args, int);
    format++;
  } else {
    format = get_number(format, &width);
  }
  format_item->width = width;
  return format;
}

const char *parse_precision(st_format_item *format_item, const char *format,
                            va_list args) {
  int precision = 0;

  if (*format == '*') {
    precision = va_arg(args, int);
    format++;
  } else {
    format = get_number(format, &precision);
  }
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
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    format_item->length = *format;
    format++;
  }
  return format;
}

const char *parse_specifier(st_format_item *format_item, const char *format) {
  if (is_specifier(*format)) {
    format_item->specifier = *format;
    format++;
  }
  return format;
}

int is_specifier(char ch) {
  int result = 0;
  if (ch == 'c' || ch == 'd' || ch == 'i' || ch == 'f' || ch == 's' ||
      ch == 'u' || ch == '%' || ch == 'o' || ch == 'g' || ch == 'G' ||
      ch == 'e' || ch == 'E' || ch == 'x' || ch == 'X' || ch == 'n' ||
      ch == 'p') {
    result = 1;
  }
  return result;
}

void arg_selector(st_format_item format_item, char *result, va_list args) {
  char temp[BUF_SIZE] = {'\0'};
  char formated_temp[BUF_SIZE] = {'\0'};

//  switch(format_item.specifier) {
//  case 'c':
//      char_processing(result, args, format_item);
//      break;

//  }

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
  } else if (format_item.specifier == 'o') {
    octal_processing(result, args, temp, format_item, formated_temp);
  } else if (format_item.specifier == 'p') {
    p_processing(result, args, format_item, temp, formated_temp);
  } else if (format_item.specifier == 'x' || format_item.specifier == 'X') {
    hex_processing(result, args, format_item, temp, formated_temp);
  } else if (format_item.specifier == 'g' || format_item.specifier == 'G') {
    g_G_processing(result, args, format_item, temp);
  } else if (format_item.specifier == 'e' || format_item.specifier == 'E') {
    e_E_processing(result, args, format_item, temp);
  } else if (format_item.specifier == '%') {
    result[0] = '%';  // !!!!
  }

  if (format_item.specifier == 'X' || format_item.specifier == 'E' || format_item.specifier == 'G') {
      up(result);
  }
//  printf("selector res = %s\n", result);

}

void up(char * temp) {
  char * name;
  name = strtok(temp,":");

  // Convert to upper case
  char *s = name;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

void char_processing(char *result, va_list args, st_format_item format_item) {
  if (format_item.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(args, wchar_t);
    do_wide_char(format_item, result, w_c);
  } else {
    char c;
    c = va_arg(args, int);
    do_char(format_item, result, c);
  }
}

void do_char(st_format_item format_item, char *result, char c_value) {
  int i = 0;
  int width = format_item.width;
  if (!format_item.minus && width) {
    while (i < width) {
      *result = ' ';
      if (i == width - 1) {
        *result = c_value;
      }
      result++;
      i++;
    }
  } else if (width) {
    *result++ = c_value;
    i++;
    while (i < width) {
      *result++ = ' ';
      i++;
    }
  } else {
    *result = c_value;
  }
}

void do_wide_char(st_format_item format_item, char *result, wchar_t w_c) {
  if (!format_item.minus && format_item.width) {
    char tmp[BUF_SIZE] = {'\0'};
    wcstombs(tmp, &w_c, BUF_SIZE);
    for (size_t i = 0; i < format_item.width - strlen(tmp); i++) {
      result[i] = ' ';
    }
    strcat(result, tmp);
  } else if (format_item.width) {
    wcstombs(result, &w_c, BUF_SIZE);
    for (int i = strlen(result); i < format_item.width; i++) {
      result[i] = ' ';
    }
  } else {
    wcstombs(result, &w_c, BUF_SIZE);
  }
}

void octal_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp) {
  temp[0] = '0';


    if (format_item.length == 'h') {
    int o_value = va_arg(args, int);
    o_value = (short int)o_value;
    octal_to_string(o_value, temp + format_item.grill);
  } else if (format_item.length == 'l') {
    long o_value = va_arg(args, long);
    octal_to_string(o_value, temp + format_item.grill);
  } else {
    int o_value = va_arg(args, int);
    octal_to_string(o_value, temp + format_item.grill);
  }

    precicion_processing(format_item, temp, result);
    // printf("pre = %s\n", result);
    flags_processing(result, format_item, formated_temp);
    // printf("fla = %s\n", result);
}

void octal_to_string(long long octal_value, char *result) {
  int k = 0;
  int add_sign = 0;

  if (octal_value < 0) {
    octal_value = -octal_value;
    add_sign = 1;
  }

  if (octal_value == 0) {
    result[k] = '0';
    k++;
  }

  while (octal_value > 0) {
    result[k] = octal_value % 8 + '0';
    octal_value = octal_value / 8;
    k++;
  }

  if (add_sign) {
    result[k] = '-';
    k++;
  }

  result[k] = '\0';

  reverse_array(result);
}

void int_processing(char *result, va_list args, char *temp,
                    st_format_item format_item, char *formated_temp) {
  if (format_item.length == 'h') {
    int d_value = va_arg(args, int);
    d_value = (short int)d_value;
    int_to_string(d_value, temp);
  } else if (format_item.length == 'l') {
    long int d_value = va_arg(args, long long int);
    // printf("int = %ld\n", d_value);
    int_to_string(d_value, temp);
    printf("int = %s\n", temp);
  } else {
    int d_value = va_arg(args, int);
    int_to_string(d_value, temp);
  }

  precicion_processing(format_item, temp, result);
  // printf("pre = %s\n", result);
  flags_processing(result, format_item, formated_temp);
  // printf("fla = %s\n", result);
}

void u_int_processing(char *result, va_list args, char *temp,
                      st_format_item format_item, char *formated_temp) {
  unsigned long long int u_value = va_arg(args, unsigned long long int);

  if (format_item.length == 'h') {
    u_value = (unsigned short int)u_value;
  } else if (format_item.length == 'l') {
    u_value = (unsigned long int)u_value;
  }

  u_int_to_string(u_value, temp);
  precicion_processing(format_item, temp, result);
  // printf("pres res = %s\n", result);
  flags_processing(result, format_item, formated_temp);
  // printf("flag res = %s\n", result);
}

void p_processing(char *result, va_list args, st_format_item format_item,
                  char *temp, char *formated_temp) {
  unsigned long long int p_value = va_arg(args, unsigned long long int);

  if (format_item.length == 'h') {
    p_value = (unsigned short int)p_value;
  } else if (format_item.length == 'l') {
    p_value = (unsigned long int)p_value;
  }
  hex_u_int_to_string(p_value, temp);
  precicion_processing(format_item, temp, result);
//  add_ox(result, format_item);
  flags_processing(result, format_item, formated_temp);
}

void add_hex_Ox(char *value, st_format_item format_item) {
    if(not_all_zeroes(value)) {
    memmove(value + 2, value, strlen(value));
    value[0] = '0';
    value[1] = 'x';
//    printf("ad ox = %s\n", value);
    }
}

int not_all_zeroes(char *array) {
  int result = 0;
  while (*array) {
    if (*array != '0') {
      result = 1;
    }
    array++;
  }
  return result;
}

void hex_processing(char *result, va_list args, st_format_item format_item,
                    char *temp, char *formated_temp) {
  unsigned long long hex = va_arg(args, unsigned long long);
  if (format_item.length == 'h') {
    hex = (unsigned short)hex;
  } else if (format_item.length == 'l') {
    hex = (unsigned long long)hex;
  } else {
    hex = (unsigned)hex;
  }

  hex_u_int_to_string(hex, temp);

  precicion_processing(format_item, temp, result);

  if (format_item.grill) {
    add_hex_Ox(result, format_item);
  }

  flags_processing(result, format_item, formated_temp);
//  printf("fl res = %s\n", result);
}

void s_processing(char *result, va_list args, st_format_item format_item) {
  if (format_item.length == 'l') {
    wchar_t *wstr = va_arg(args, wchar_t *);
    do_wide_string(format_item, result, wstr);
  } else {
    char *s_value = va_arg(args, char *);
    do_string(format_item, result, s_value);
  }
}

void do_string(st_format_item format_item, char *result, char *s_value) {
  char tmp[BUF_SIZE] = {'\0'};
  strcpy(tmp, s_value);
  if (format_item.precision_set) {
    tmp[format_item.precision] = '\0';
  }

  int len = strlen(tmp);
  int gap = format_item.width - len;

  if (!format_item.minus && gap > 0) {
    memset(result, ' ', gap);
    strcpy(result + gap, tmp);
  } else if (format_item.minus && gap > 0) {
    strcpy(result, tmp);
    memset(result + len, ' ', gap);
  } else {
    strcpy(result, tmp);
  }
}

void do_wide_string(st_format_item format_item, char *result, wchar_t *wstr) {
  char tmp[BUF_SIZE] = {'\0'};
  char str[BUF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUF_SIZE);
  strcpy(tmp, str);
  if (format_item.precision_set) {
    tmp[format_item.precision] = '\0';
  }

  int len = strlen(tmp);
  int gap = format_item.width - len;

  if (format_item.minus && gap > 0) {
    strcpy(result, tmp);
    memset(result + len, ' ', gap);
  } else if (gap > 0) {
    memset(result, ' ', gap);
    strcpy(result + gap, tmp);
  } else {
    strcpy(result, tmp);
  }
}

void f_processing(char *result, st_format_item format_item, va_list args,
                  char *temp) {
  long double f_value = 0.0;
  if (format_item.length == 'L') {
    f_value = va_arg(args, long double);
  } else {
    f_value = va_arg(args, double);
  }
  if (!format_item.precision_set) {
    format_item.precision = 6;
  }
  double_to_string(f_value, format_item, result);
  // printf("res double = %s\n", result);
  flags_processing(result, format_item, temp);
}

void int_to_string(long long int_value, char *result) {
  int k = 0;
  int add_sign = 0;
  int flag = 0;

  if (int_value < 0) {
    int_value *= -1;
    add_sign = 1;
  }
  if (int_value < 0) {
    int_value -= 1;
    add_sign = 1;
    flag = 1;
  }

  if (int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (llabs(int_value) > 0) {
    result[k] = int_value % 10 + '0';
    // printf("resu [%d] = %c\n", k, result[k]);
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
  if (flag) {
    // printf("here h\n");
    result[k - 1] += 1;
  }
}

void u_int_to_string(unsigned long long int u_int_value, char *result) {
  int k = 0;

  if (u_int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (u_int_value > 0) {
    result[k] = u_int_value % 10 + '0';
    u_int_value = u_int_value / 10;
    k++;
  }

  result[k] = '\0';

  reverse_array(result);

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

void hex_u_int_to_string(unsigned long long u_int_value, char *result) {

  int k = 0;
  char bukva = 0;

  if (u_int_value == 0) {
    result[k] = '0';
    k++;
  }

  while (u_int_value != 0) {

          bukva = (u_int_value % 16);

          if (bukva < 10) {
              bukva = bukva + 48;
          }
          else {
              bukva = bukva + 87;
          }
          // printf("hex resu [%d] = %c\n", k, result[k]);
          result[k++] = bukva;
          u_int_value /= 16;
      }

  result[k] = '\0';

  reverse_array(result);
}

void double_to_string(long double double_value, st_format_item format_item,
                      char *result) {
  long double left = 0.0, right = 0.0;
  long double temp_right = 0;
  long long int_left = 0;
  long long int_right = 0;
  char buf[BUF_SIZE] = {'\0'};
  int k = 0;  // buf_iterator
  int do_round = 0;
  // int add_sign = 0, negative = 0;

  right = modfl(double_value, &left);

  // целая часть
  if (format_item.precision_set && format_item.precision == 0) {
    int_left = roundl(double_value);
  } else if (format_item.precision) {
    int_left = (long long)double_value;
  }

  if (double_value < 0) {
    right *= -1.0;
    // negative = 1;
  }
  // if (double_value == 0 && negative) {
  //   buf[0] = '-';
  //   add_sign = 1;
  // }

  temp_right = my_round(right, format_item.precision);
  if ((int)temp_right && format_item.precision) {
    (int_left > 0) ? int_left++ : int_left--;
    do_round = 1;
  }
  // printf("temp right = %Lf\n", temp_right);

  int_to_string(labs(int_left), buf);
  if (double_value < 0) result = add_to_string(result, "-");
  result = add_to_string(result, buf);

  // добавляем точку если есть решетка
  if (format_item.grill &&
      !((format_item.precision_set && format_item.precision != 0) ||
        !format_item.precision_set)) {
    result = add_to_string(result, ".");
  }
  //

  if ((format_item.precision_set && format_item.precision != 0) ||
      !format_item.precision_set) {
    result = add_to_string(result, ".");
    memset(buf, '\0', BUF_SIZE);
//temp_right *= 10;
    for (int i = 0; i < format_item.precision; i++) {
      temp_right *= 10;
      printf("temp right = %Lf\n", temp_right);
//      if (do_round) {
//        buf[k++] = '0';
//      } else {
        int_right = fmodl(temp_right,10);
        buf[k] = int_right % 10 + '0';
        printf("buf[%d] = %c\n", k, buf[k]);
        k++;
//        temp_right *= 10;
//      }
    }
    buf[k] = '\0';
    result = add_to_string(result, buf);
  }
}

long double my_round(long double value, int precision) {
  for (int i = 0; i < precision; i++) value *= 10;

//  long long n = value;
  long double n = 0;
  modfl(value, &n);
  if (value - n >= 0.5) {
    n++;
  }
  value = n;
  for (int i = 0; i < precision; i++) value /= 10;
  printf("value = %Lf\n", value);
  return value;
}

void reverse_array(char *result) {
  char tmp = '\0';
  int len = strlen(result);
  for (int i = 0; i < len / 2; i++) {
    tmp = result[i];
    result[i] = result[len - 1 - i];
    result[len - 1 - i] = tmp;
  }
  result[len] = '\0';
}

void precicion_processing(st_format_item format_item, char *value,
                          char *result) {
  int len = strlen(value);
  int i = 0, sign = 0, null_value = 0;

  if (value[0] == '0') {
    null_value = 1;
  }

  if (value[0] == '-' && format_item.specifier != 'u') {
    result[0] = '-';
    sign = 1;
  }

  if (len < format_item.precision + sign) {
    if (sign) memmove(value, value + 1, len);
    while (format_item.precision + sign - len > 0) {
      if (!i && result[0] == '-') {
        i++;
        continue;
      }
      result[i] = '0';
      // printf("res [%d] = %c\n", i, result[i]);
      i++;
      format_item.precision--;
    }
  }
  if (format_item.precision_set && null_value) {
    value[1] = '\0';
  }
  if (!format_item.precision && null_value && format_item.precision_set) {
    value[0] = '\0';
  }
  add_to_string(result + i, value);
}

void flags_processing(char *value, st_format_item format_item, char *temp) {
  //    char tmp[BUF_SIZE + 1] = {'\0'};
  char formated_value[BUF_SIZE] = {'\0'};
  if (format_item.plus && !is_u_int_spec(format_item)) {
    temp[0] = value[0] == '-' ? value[0] : '+';
    add_to_string(temp + 1, value[0] == '-' ? value + 1 : value);
    add_to_string(value, temp);
  } else if (format_item.space && value[0] != '-' &&
             !is_u_int_spec(format_item)) {
    temp[0] = ' ';
    add_to_string(temp + 1, value);
    add_to_string(value, temp);
  }
  if (format_item.width > (int)strlen(value)) {
    int i = format_item.width - strlen(value);
    int sign = 0;
    if (!format_item.minus) {
      //            printf("t = %c: i = %d\n", value[0], i);
      if ((value[0] == '-' || value[0] == '+') && format_item.nullik) {
        sign = 1;
      }
      temp[0] = value[0];
      add_to_string(formated_value, value + sign);
      memset(temp + sign, format_item.nullik ? '0' : ' ', i);
      // printf("t = %c\n", temp[0]);
      add_to_string(temp + i + sign, formated_value);
    } else {
      add_to_string(temp, value);
      memset(temp + strlen(temp), ' ', i);
    }
    add_to_string(value, temp);
  }
  // printf("flags res = %s\n", value);
}

int is_u_int_spec(st_format_item format_item) {
    int result = 0;
    if(format_item.specifier == 'u' || format_item.specifier == 'x' || format_item.specifier == 'X') {
        result = 1;
    }
    return result;
}

void e_E_processing(char *result, va_list args, st_format_item format_item,
                    char *temp) {
  long double value = 0;
  if (format_item.length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  int power = 0;
  char sign = '0';
  if ((int)value == 0) {
    sign = '-';
  } else {
    sign = '+';
  }

  if ((int)value - value) {
    while ((int)value == 0) {
      power++;
      value *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)value / 10 != 0) {
    power++;
    value /= 10;
  }

  if (!format_item.precision_set) {
      format_item.precision = 6;
  }
  double_to_string(value, format_item, result);
  science_format(result, power, sign);
  flags_processing(result, format_item, temp);
}

void science_format(char *string, int power, char sign) {
  int length = strlen(string);
  string[length] = 'e';
  string[length + 1] = sign;
  string[length + 3] = power % 10 + '0';
  power /= 10;
  string[length + 2] = power % 10 + '0';
  string[length + 4] = '\0';
}

void g_G_processing(char *result, va_list args, st_format_item format_item,
                    char *temp) {
  long double value = 0;
  if (format_item.length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  if (!format_item.precision_set) format_item.precision = 6;
  if (format_item.precision == 0) format_item.precision = 1;
  long double copy_value = value;
  int power = 0;
  if ((int)value == 0) {
    while ((int)copy_value == 0) {
      copy_value *= 10;
      power++;
    }
  }
  if (power <= 4) {
    format_item.precision = 10;
    double_to_string(copy_value, format_item, result);
  } else {
    format_item.precision = 0;
    double_to_string(value, format_item, result);
  }
  gG_precision(result, format_item);
  if (power > 4) science_format(result, power, '-');
  remove_trailing_zeroes(result);
  flags_processing(result, format_item, temp);
}

void gG_precision(char *result, st_format_item format_item) {
  int flag = 0;
  int sign_val = 0;
  for (size_t i = 0; i < strlen(result); i++) {
    if ((result[i] == '0' && !flag) || result[i] == '.')
      continue;
    else
      flag = 1;

    if (is_number(result[i]) && flag) {
      sign_val++;
    }
    if (sign_val == format_item.precision && i + 1 < strlen(result)) {
      int temp = result[i + 1] == '.' ? 2 : 1;
      result[i] =
          result[i + temp] - '0' > 5 ? (char)(result[i] + 1) : result[i];
      result[i + 1] = '\0';
      break;
    }
  }
}

void remove_trailing_zeroes(char *result) {
  char *point = strchr(result, '.');
  if (point) {
    for (int i = strlen(result) - 1; result[i] != '.'; i--) {
      if (result[i] == '0')
        result[i] = '\0';
      else
        break;
    }
    if (point[1] == '\0') point[0] = '\0';
  }
}

