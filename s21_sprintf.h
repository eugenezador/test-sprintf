#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdarg.h>

// нужно реализовать atoi
// используется стандартный memset
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096

#define INT32_MAX 2147483647
// #define INT32_MIN -2147483648

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

const char *parse_width(st_format_item *format_item, const char *format);

const char *parse_precision(st_format_item *format_item, const char *format);

const char *get_number(const char *format, int *value);

int is_number(char c);

const char *parse_length(st_format_item *format_item, const char *format);

const char *parse_specifier(st_format_item *format_item, const char *format);

void arg_selector(st_format_item format_item, char *buf, va_list args);

void char_processing(char *buf, va_list args, st_format_item format_item);

void int_processing(char *buf, va_list args, char *temp, st_format_item format_item);

void u_int_processing(char *buf, va_list args, char *temp, st_format_item format_item);

void s_processing(char *buf, va_list args, st_format_item format_item);

void f_processing(char *buf, st_format_item format_item, va_list args,
                  char *temp);

void int_to_string(long long int_value, char *result);

char *add_to_string(char *string, char *temp);

void double_to_string(long double double_value, st_format_item format_item,
                      char *result);

#endif  //  SRC_S21_SPRINTF_H_
