#include <stdint.h>

#include "s21_sprintf.h"

int main()
{

    /*
    START_TEST(sprintf_1_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      int a = 9;
      int b = 10;
      int c = 17;
      int d = 66;
      int e = 124;
      ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                       s21_sprintf(str2, str3, a, b, c, d, e));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_2_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      int a = -6;
      int b = -10;
      int c = -17;
      int d = -66;
      int e = -124;
      ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                       s21_sprintf(str2, str3, a, b, c, d, e));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_3_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      int a = 60;
      int b = 50;
      int c = 1744;
      int d = 386;
      int e = 257;
      ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                       s21_sprintf(str2, str3, a, b, c, d, e));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_4_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      int a = 60;
      int b = 50;
      int c = 1744;
      int d = 386;
      int e = 257;
      ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                       s21_sprintf(str2, str3, a, b, c, d, e));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_5_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      char a = 0;
      ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                       s21_sprintf(str2, str3, a, a, a, a, a));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_6_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%05c Test % 5c Test %lc Test";
      int a = 70;
      unsigned long int b = 70;
      ck_assert_int_eq(sprintf(str1, str3, a, a, b),
                       s21_sprintf(str2, str3, a, a, b));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_7_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%-010c Test % -10c Test %-lc";
      int a = 74;
      unsigned long int b = 74;
      ck_assert_int_eq(sprintf(str1, str3, a, a, b),
                       s21_sprintf(str2, str3, a, a, b));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_8_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%+010.5c Test % +10.5c Test %-10lc Test %-10lc Test %+10lc";
      char a = 92;
      unsigned long int b = 92;
      unsigned long int c = 92;
      ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                       s21_sprintf(str2, str3, a, a, b, c, c));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_9_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
      int a = 10;
      unsigned long int b = 10;
      unsigned long int c = 10;
      ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                       s21_sprintf(str2, str3, a, a, b, c, c));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_10_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
      int a = -10;
      unsigned long int b = 10;
      unsigned long int c = 10;
      ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                       s21_sprintf(str2, str3, a, a, b, c, c));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_11_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%#c Test %#c Test %#c Test %#c Test %#c";
      ck_assert_int_eq(sprintf(str1, str3, ' ', 'n', '5', '%', '\\'),
                       s21_sprintf(str2, str3, ' ', 'n', '5', '%', '\\'));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_12_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      ck_assert_int_eq(sprintf(str1, str3, '\n', '\0', '\0', '\0', 'c'),
                       s21_sprintf(str2, str3, '\n', '\0', '\0', '\0', 'c'));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_13_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      ck_assert_int_eq(sprintf(str1, str3, 'b', '4', '#', '@', '\0'),
                       s21_sprintf(str2, str3, 'b', '4', '#', '@', '\0'));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_14_c) {
      char str1[100];
      char str2[100];
      char *str3 = "%c Test %c Test %c Test %c Test %c";
      ck_assert_int_eq(sprintf(str1, str3, 'Y', 'G', 123, '\0', 'J'),
                       s21_sprintf(str2, str3, 'Y', 'G', 123, '\0', 'J'));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_15_c) {
      char str1[400];
      char str2[400];
      char *str3 = "%.7c Test %-7c Test %-50c Test % 54c Test %0188c";
      int a = 112;
      ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                       s21_sprintf(str2, str3, a, a, a, a, a));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_16_c) {
      char str1[400];
      char str2[400];
      char *str3 = "%.7c Test % -.7c Test %- 050c Test %- 54c Test %-0188c";
      int a = 45;
      ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                       s21_sprintf(str2, str3, a, a, a, a, a));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_17_c) {
      char str1[400];
      char str2[400];
      char *str3 = "%70c Test %-90c Test %080c Test %-065c Test %- 60c";
      int a = 255;
      ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                       s21_sprintf(str2, str3, a, a, a, a, a));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_18_c) {
      char str1[400];
      char str2[400];
      char *str3 = "%70c Test %-90c Test %080c Test %-065c Test %- 60c";
      int a = 255;
      ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                       s21_sprintf(str2, str3, a, a, a, a, a));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(sprintf_19_c) {
      char str1[100];
      char str2[100];  //%lc Test %llc Test %hc Test %hhc
      char *str3 = "%c Test %lc Test %hc";
      int a = 3;
      unsigned long int b = 103;
      unsigned short e = 255;
      ck_assert_int_eq(sprintf(str1, str3, a, b, e),
                       s21_sprintf(str2, str3, a, b, e));
      ck_assert_pstr_eq(str1, str2);
    }
    END_TEST

    START_TEST(simple_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "This is a simple value %d";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(precise_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.5i";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(width_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%5d";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(minus_width_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-5i";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(plus_width_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%+12d";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(padding_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%012i";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(star_width_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%0*d";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                       sprintf(str2, format, 5, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(star_precision_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%0.*i";
      int val = 69;
      ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                       sprintf(str2, format, 5, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(many_flags_many_ints) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char format[] = "%0.*i %d %4.*i %013d %d";
      int val = 69;
      ck_assert_int_eq(
          s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
          sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(flags_long_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%+5.31li";
      long int val = 698518581899;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(flags_short_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-16.9hi";
      short int val = 6958;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(flags_another_long_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%0.*ld";
      long val = 8581385185;
      ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                       sprintf(str2, format, 5, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(zero_precision_zero_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.0d";
      int val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(space_flag_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "% d";
      int val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%u";
      unsigned int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%15u";
      unsigned int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-16u";
      unsigned int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.51u";
      unsigned int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(unsigned_val_many_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "% 5.51u";
      unsigned int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(unsigned_val_short) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%hu";
      unsigned short int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val_long) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%lu";
      unsigned long int val = 949149114140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_val_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%lu, %u, %hu, %.5u, %5.u";
      unsigned long int val = 949149114140;
      ck_assert_int_eq(
          s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
          sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
                  (unsigned)14414, (unsigned)9681));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%15o";
      int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-16o";
      int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.51o";
      int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(octal_many_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-5.51o";
      int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_zero) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%o";
      ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_hash) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#o";
      int val = 57175;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(octal_short) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%hd";
      short int val = 14140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_long) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%lo";
      long int val = 949149114140;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%lo, %o, %ho, %.5o, %5.o";
      long int val = 949149114140;
      ck_assert_int_eq(
          s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
          sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
                  (unsigned)14414, (unsigned)9681));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(octal) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%lo";
      long int val = 84518;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(unsigned_zero) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%u";
      ck_assert_int_eq(s21_sprintf(str1, format, 0),
                       sprintf(str2, format, (unsigned)0));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(hex_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%5x";
      unsigned val = 858158158;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(hex_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#-10x";
      unsigned val = 858158158;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.15x";
      unsigned val = 858158158;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#-10x%x%X%#x%#X%5.5x";
      unsigned val = 858158158;
      ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
                       sprintf(str2, format, val, val, val, val, val, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_many_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#-5.10x";
      unsigned val = 858158158;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_zero) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#x";
      unsigned val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#x";
      unsigned val = 18571;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_short) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#hx";
      unsigned short val = 12352;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_long) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#lx";
      unsigned long val = 18571757371571;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(hex_one_longer_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#2x";
      unsigned val = 1;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(hex_two_longer_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%#30x";
      unsigned val = 1;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(one_char) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%c";
      char val = 'X';
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(one_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.5c";
      char val = 'c';
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(one_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "% -5c";
      char val = 'c';
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(one_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%15c";
      char val = 'c';
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(one_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
      char val = 'c';
      ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                       sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(one_many_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-5.3c";
      char val = 'c';
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(string) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%s";
      char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(string_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.15s";
      char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(string_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%15s";
      char *val = "69 IS MY FAVORITE NUMBER";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(string_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%-15.9s";
      char *val = "69 IS MY FAVORITE NUMBER";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(string_long) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%s";
      char *val =
          "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(string_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%s%s%s%s";
      char *val =
          "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
      char *s1 = "";
      char *s2 = "87418347813748913749871389480913";
      char *s3 = "HAHAABOBASUCKER";
      ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                       sprintf(str2, format, val, s1, s2, s3));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(ptr) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%p";
      ck_assert_int_eq(s21_sprintf(str1, format, format),
                       sprintf(str2, format, format));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(ptr_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%15p";
      ck_assert_int_eq(s21_sprintf(str1, format, format),
                       sprintf(str2, format, format));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(ptr_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%.5p";
      ck_assert_int_eq(s21_sprintf(str1, format, format),
                       sprintf(str2, format, format));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(null_ptr) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      char *format = "%p";
      char *ptr = NULL;
      ck_assert_int_eq(s21_sprintf(str1, format, ptr), sprintf(str2, format, ptr));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(string_width_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *val = "kjafdiuhfjahfjdahf";
      char *format = "%120s";
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(n_specifier) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      int ret = 0;
      char *format = "Hello, my sexy little aboba abobushka abobina %n";
      ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                       sprintf(str2, format, &ret));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(float_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%Lf";
      long double val = 513515.131513515151351;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(float_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%10Lf";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(float_precision_zero) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.0Lf";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(float_precision_empty) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.Lf";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(float_precision_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.15Lf";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(float_precision_huge_negative) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.15Lf";
      long double val = -15.35581134;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(float_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%Lf";
      long double val = 72537572375.1431341;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(float_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "% f";
      float val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(float_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "% .0f %.lf %Lf %f %lf %Lf";
      float val = 0;
      double val1 = 0;
      long double val2 = 3515315.153151;
      float val3 = 5.5;
      double val4 = 9851.51351;
      long double val5 = 95919539159.53151351131;
      ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                       sprintf(str2, format, val, val1, val2, val3, val4, val5));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_precision) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.17Le";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_precision_zero) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.0Le";
      long double val = 15.35;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(e_precision_empty) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.Le";
      long double val = 15.000009121;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_precision_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.15Le";
      long double val = 0.000000000000000123;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(e_precision_huge_negative) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.15Le";
      long double val = -15.35581134;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(e_huge) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%Le";
      long double val = 72537572375.1431341;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_flags) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%015E";
      float val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_width) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%15e";
      float val = 0;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST
    START_TEST(e_many) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "% .0e %.le %Le %e %le %Le";
      float val = 0;
      double val1 = 0;
      long double val2 = 3515315.153151;
      float val3 = 5.5;
      double val4 = 0.094913941;
      long double val5 = 95919539159.53151351131;
      ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                       sprintf(str2, format, val, val1, val2, val3, val4, val5));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(E_int) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      char *format = "%.17LE";
      long double val = 4134121;
      ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(all_empty) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];
      ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(empty_format_and_parameters) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(test_one_char) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST

    START_TEST(test_many_char) {
      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                       sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

      ck_assert_str_eq(str1, str2);
    }
    END_TEST


    */
//    START_TEST(test_one_string) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
//                       sprintf(str2, "%s", "Drop Sega PLS"));

//      ck_assert_str_eq(str1, str2);
//    }
//    END_TEST

//    START_TEST(test_many_string) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(
//          s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
//          sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

//      ck_assert_str_eq(str1, str2);
//    }
//    END_TEST

//    START_TEST(test_one_dec) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

//      ck_assert_str_eq(str1, str2);
//    }
//    END_TEST

//    START_TEST(test_many_dec) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
//                       sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

//      ck_assert_str_eq(str1, str2);
//    }
//    END_TEST

//    START_TEST(test_one_int) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

//      ck_assert_str_eq(str1, str2);
//    }
//    END_TEST

//    START_TEST(test_many_int) {
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
//                       sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

//      ck_assert_str_eq(str1, str2);



      char str1[BUF_SIZE];
      char str2[BUF_SIZE];

      int a = s21_sprintf(str2, "%f", 0.0001);
      int b = sprintf(str1, "%f", 0.0001);




//FAIL
//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str2, "%f %f %f %f", -999.00666, 0.0001, 666.999, -100.001);
//      int b = sprintf(str1, "%f %f %f %f", -999.00666, 0.0001, 666.999, -100.001);





//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str2, "%u", 100);
//      int b = sprintf(str1, "%u", (unsigned)100);





//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      int a = s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100);
//      int b = sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
//                               (unsigned)666, (unsigned)100);




//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      int a = s21_sprintf(str1, "%8c", '\t');
//      int b = sprintf(str2, "%8c", '\t');




//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];

//      int a = s21_sprintf(str1, "%-8c", '\t');
//      int b = sprintf(str2, "%-8c", '\t');



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's');
//      int b = sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's');





//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123);
//      int b = sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123);
//      int b = sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%7X", INT32_MAX);
//      int b = sprintf(str2, "%7X", INT32_MAX);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999);
//      int b = sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str2, "%#X", INT32_MIN);
//      int b = sprintf(str1, "%#X", (unsigned)INT32_MIN);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0,
//                      123213123);
//      int b = sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0, 123213123);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0,
//                      123213123);
//      int b = sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0, 123213123);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%*x", 11, INT32_MIN);
//      int b = sprintf(str2, "%*x", 11, (unsigned)INT32_MIN);




//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%*X", 11, INT32_MIN + 20 );
//      int b = sprintf(str2, "%*X", 11, (unsigned)INT32_MIN + 20);




//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
//                                   199, -123978, 3, -1251);
//      int b = sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1,
//                               199, -123978, 3, -1251);





//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
//                                   199, -123978, 3, -1251);
//      int b = sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
//                               -123978, 3, -1251);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%*.6x", 11, 0);
//      int b = sprintf(str2, "%*.6x", 11, 0);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
//      int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);




//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(
//          str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
//          4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
//      int b = sprintf(str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
//                      3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
//                      41, -41, 33);



//      char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      int a = s21_sprintf(str2, "%#3.*X %#3x %-7.*X %#-1.8x %4.3X %#2.15x %*.*X %*.1X %3X %-1X",
//                      3, -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
//                      41, -41, 33);
//      int b = sprintf(str1, "%#3.*X %#3x %-7.*X %#-1.8x %4.3X %#2.15x %*.*X %*.1X %3X %-1X", 3,
//                  -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
//                  -41, 33);





      printf("or = %s\n", str1);
      printf("my = %s\n", str2);

      if(strcmp(str1, str1) == 0 && a == b) {
          printf("TEST OK!\n");
      } else {
          printf("FAIL!\n");
      }

    return 0;
}

