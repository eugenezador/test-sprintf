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
//      g_G_processing(result, args, format_item, temp, formated_temp);
    }
  else if (format_item.specifier == '%') {
    result[0] = '%';  // !!!!
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
  if (format_item.length == 'h') {
    int o_value = va_arg(args, int);
    o_value = (short int)o_value;
    octal_to_string(o_value, temp);
  } else if (format_item.length == 'l') {
    long o_value = va_arg(args, long);
    octal_to_string(o_value, temp);
  } else {
    int o_value = va_arg(args, int);
    octal_to_string(o_value, temp);
  }

  precicion_processing(format_item, temp, formated_temp);
  flags_processing(result, format_item, formated_temp);
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

  char tmp = '\0';
  for (int i = 0; i < k / 2; i++) {
    tmp = result[i];
    result[i] = result[k - 1 - i];
    result[k - 1 - i] = tmp;
  }
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
  printf("pre = %s\n", result);
  flags_processing(result, format_item, formated_temp);
  printf("fla = %s\n", result);
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
  hex_u_int_to_string(p_value, temp, format_item);
  precicion_processing(format_item, temp, result);
  add_ox(result, format_item);
  flags_processing(result, format_item, formated_temp);
}

void add_ox(char *value, st_format_item format_item) {
  if (!is_null_values(value) || format_item.specifier == 'p') {
    memmove(value + 2, value, strlen(value));
    value[0] = '0';
    value[1] = 'x';
  }
}

int is_null_values(char *array) {
  int result = 0;
  while (*array) {
    if (*array == '0') {
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

  hex_u_int_to_string(hex, temp, format_item);
  // printf("hek int = %s\n", temp);
  precicion_processing(format_item, temp, result);
  // printf("hek int = %s\n", formated_temp);
  if (format_item.grill) {
    add_ox(result, format_item);
  }
  // printf("hek int = %s\n", formated_temp);
  flags_processing(result, format_item, formated_temp);
  // printf("hek int = %s\n", formated_temp);
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
    printf("here h\n");
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

  // reverse
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

void hex_u_int_to_string(unsigned long long u_int_value, char *result, st_format_item format_item) {
  int k = 0;
  char ascii_shift = 0;
  char bukva = 0;
  if (u_int_value == 0) {
    result[k] = '0';
    k++;
  }
  if(format_item.specifier == 'X') {
      ascii_shift = 32;
  }

  while (u_int_value > 0) {
    bukva = (char)(u_int_value % 16);
    switch (bukva + ascii_shift) {
      case ('a'):
        result[k] = 'a' + ascii_shift;
        break;
    case 'b':
        result[k] = 'a' + ascii_shift;
        break;
    case 'c':
        result[k] = 'c' + ascii_shift;
        break;
    case 'd':
        result[k] = 'd' + ascii_shift;
        break;
    case 'e':
        result[k] = 'c' + ascii_shift;
        break;
    case 'f':
        result[k] = 'd' + ascii_shift;
        break;
    default:
        result[k] = u_int_value % 16 + '0';
        break;
    }
    // printf("hex resu [%d] = %c\n", k, result[k]);
    // result[k] = "0123456789abcdef"[u_int_value % 16];
    u_int_value = u_int_value / 16;
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

void double_to_string(long double double_value, st_format_item format_item,
                      char *result) {
  long double left = 0.0, right = 0.0;
  long long i_left = 0, i_right = 0;
  char buf[800] = {'\0'};
  char i_temp[200] = {'\0'};
  int k = 0;  // buf iterator
  right = modfl(double_value, &left);

  if (format_item.precision_set && format_item.precision == 0) {
    i_left = roundl(double_value);
  } else {
    i_left = (long long)double_value;
  }
  if (double_value < 0) {
    right *= -1.0;
  }
  int_to_string(i_left, buf);
  result = add_to_string(result, buf);
  // добавляем точку если есть решетка
  if (format_item.grill &&
      !((format_item.precision_set && format_item.precision != 0) ||
        !format_item.precision_set)) {
    result = add_to_string(result, ".");
  }
  // добавляем дробную часть
  if ((format_item.precision_set && format_item.precision != 0) ||
      !format_item.precision_set) {
    // char dot[2] = ".";
    result = add_to_string(result, ".");
    // обработка правой части
    memset(buf, '\0', 400);  // чистим буфер
    for (int i = 0; i < format_item.precision; i++) {
      right *= 10;
      // i_right = right;
      if (fabsl(double_value) > 0.0000 && fabsl(double_value) < 1.0000) {
        i_right = floor(right);
      } else {
        i_right = floor(right);
      }
      if (i_right == 0) {
        buf[k++] = i_right % 10 + '0';
        // printf("buf[%d] = %c\n", k, buf[k]);
      }
      // else {
      //   // i_right = right;
      //   buf[k++] = i_right % 10 + '0';
      // }
    }
    buf[k] = '\0';
    if (i_right) {
      i_right = roundl(right);
      int_to_string(i_right, i_temp);
      strcat(buf, i_temp);
    }
    result = add_to_string(result, buf);
  }
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
  if (format_item.plus && format_item.specifier != 'u') {
    temp[0] = value[0] == '-' ? value[0] : '+';
    add_to_string(temp + 1, value[0] == '-' ? value + 1 : value);
    add_to_string(value, temp);
  } else if (format_item.space && value[0] != '-' &&
             format_item.specifier != 'u') {
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

// void parse_float_g_G(flags f, char *buff, va_list va) {
//     long double val = 0;
//     if (f.length == 'L') {
//         val = va_arg(va, long double);
//     } else {
//         val = va_arg(va, double);
//     }

//    if (!f.is_precision_set) {
//        f.precision = 6;
//    }
//    if (f.precision == 0)
//        f.precision = 1;
//    int precision = f.precision;
//    long double m_val = val;
//    int pow = 0;
//    if ((int)val - val) {
//        while ((int)m_val == 0) {
//            pow++;
//            m_val *= 10;
//        }
//    }
//    if (pow > 4) {
//        f.precision = 0;
//        double_to_string(m_val, buff, f);
//    } else {
//        f.precision = 10;
//        double_to_string(val, buff, f);
//    }
//    format_gG_precision(buff, precision);
//    if (pow > 4)
//        prepend_mantiss(buff, pow, '-');
//    remove_trailing_zeroes(buff);
//    format_flags(buff, f);
//}

// void remove_trailing_zeroes(char *buff) {
//     int len = strlen(buff);
//     char *dot = strchr(buff, '.');
//     if (dot) {
//         for (int i = len - 1; buff[i] != '.'; i--) {
//             if (buff[i] == '0')
//                 buff[i] = '\0';
//             else
//                 break;
//         }
//         if (dot[1] == '\0')
//             dot[0] = '\0';
//     }
// }

// void format_gG_precision(char *buff, int precision) {
//     int sig_digs = 0;
//     size_t len = strlen(buff);
//     int not_zero_found = 0;
//     for (size_t i = 0; i < strlen(buff); i++) {
//         if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
//             continue;
//         else
//             not_zero_found = 1;

//        if (s21_isdigit(buff[i]) && not_zero_found) {
//            sig_digs++;
//        }
//        if (sig_digs == precision && i + 1 < len) {
//            int next = buff[i + 1] == '.' ? 2 : 1;
//            buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) :
//            buff[i]; buff[i + 1] = '\0'; break;
//        }
//    }
//}

//void parse_mantiss(flags f, char *buff, va_list va) {
//    long double val = 0;
//    if (f.length == 'L') {
//        val = va_arg(va, long double);
//    } else {
//        val = va_arg(va, double);
//    }
//    int pow = 0;
//    char sign = (int)val == 0 ? '-' : '+';

//    if ((int)val - val) {
//        while ((int)val == 0) {
//            pow++;
//            val *= 10;
//        }
//    } else {
//        sign = '+';
//    }
//    while ((int)val / 10 != 0) {
//        pow++;
//        val /= 10;
//    }

//    if (!f.is_precision_set)
//        f.precision = 6;
//    double_to_string(val, buff, f);
//    prepend_mantiss(buff, pow, sign);
//    format_flags(buff, f);
//}

//void prepend_mantiss(char *str, int pow, char sign) {
//    int len = s21_strlen(str);
//    str[len] = 'e';
//    str[len + 1] = sign;
//    str[len + 3] = pow % 10 + '0';
//    pow /= 10;
//    str[len + 2] = pow % 10 + '0';
//    str[len + 4] = '\0';
//}


// void double_to_string(long double double_value, st_format_item format_item,
//                       char *result) {
//   char buff[BUF_SIZE] = {'\0'};
//   int idx = BUF_SIZE - 2;
//   int neg = double_value < 0 ? 1 : 0;
//   double_value = neg ? double_value * -1 : double_value;
//   long double l = 0, r = modfl(double_value, &l);
//   if (format_item.precision == 0) {
//     l = roundl(double_value);
//     r = 0;
//   }
//   char fractions[BUF_SIZE] = {'\0'};
//   for (int i = 0; i < format_item.precision; i++) {
//     r = r * 10;
//     fractions[i] = (int)r + '0';
//   }
//   long long right = roundl(r), left = l;
//   if (!right) {
//     for (int i = 0; i < format_item.precision; idx--, i++) buff[idx] = '0';
//   } else {
//     for (int i = strlen(fractions); right || i > 0; right /= 10, idx--, i--)
//       buff[idx] = (int)(right % 10 + 0.05) + '0';
//   }
//   if ((format_item.precision_set && format_item.precision != 0) || (int)r ||
//       (!format_item.precision_set && double_value == 0) || strlen(fractions))
//     buff[idx--] = '.';
//   if (!left) {
//     buff[idx] = '0';
//     idx--;
//   } else {
//     for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
//   }
//   for (int i = 0; buff[idx + 1]; idx++, i++) {
//     if (neg && i == 0) {
//       result[i] = '-';
//       i++;
//     }
//     result[i] = buff[idx + 1];
//   }
// }

