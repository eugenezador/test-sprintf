
#include "s21_sprintf.h"

int main()
{
//    char str1[BUF_SIZE];
//      char str2[BUF_SIZE];
//      char *format = "%5x";
//      unsigned val = 858158158;
//      int a = s21_sprintf(str1, format, val);
//      int b = sprintf(str2, format, val);


//        char str1[100] = "";
//        char str2[100] = "";
//        char *str3 = "Test %x Test";
//        int val = 0x32;

//        int a = sprintf(str1, str3, val);
//        int b = s21_sprintf(str2, str3, val);


// FAIL
        char str1[100];
        char str2[100];
        char *str3 = "%X Test %x Test %x";
        int val = 0x7a4;
        int val2 = 0x91ba123f;
        int val3 = 0x3123;
        int a = sprintf(str1, str3, val, val2, val3);
        int b = s21_sprintf(str2, str3, val, val2, val3);



//        char str1[100];
//        char str2[100];
//        char *str3 = "%x Test %x Test %x";
//        int val = 0x3015;
//        int val2 = 0x712;
//        int val3 = 0x99;
//        int a = sprintf(str1, str3, val, val2, val3);
//        int b = s21_sprintf(str2, str3, val, val2, val3);


//        char str1[100];
//        char str2[100];
//        char *str3 = "%lx Test %lx Test %hx GOD %hx";
//        long int val = 3088675747373646;
//        long val2 = 33030030303;
//        unsigned short int val3 = 22600;
//        unsigned short val4 = 120;
//        int a = sprintf(str1, str3, val, val2, val3, val4);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4);


//        char str1[100];
//        char str2[100];
//        char *str3 = "%3x Test %5x Test %10x";
//        int val = 3015;
//        int val2 = 01234;
//        int val3 = 99;
//        int a = sprintf(str1, str3, val, val2, val3);
//        int b = s21_sprintf(str2, str3, val, val2, val3));


//        char str1[200];
//        char str2[200];
//        char *str3 = "%6.5x Test %.23x Test %3.x TEST %.x";
//        int val = 3015;
//        int val2 = 712;
//        int val3 = 99;
//        int val4 = 38;
//        int a = sprintf(str1, str3, val, val2, val3, val4);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%-10.5x Test %-.8x Test %-7x TEST %-.x";
//        int val = 3015;
//        int val2 = 712;
//        int val3 = 99;
//        int val4 = 2939;
//        int a = sprintf(str1, str3, val, val2, val3, val4);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4));


//        char str1[200];
//        char str2[200];
//        char *str3 = "%0x Test %0.x Test %0.0x TEST %0x GOD %.x";
//        int val = 3015;
//        int val2 = 712;
//        int val3 = 99;
//        int val4 = 2939;
//        int val5 = 0123;
//        int a = sprintf(str1, str3, val, val2, val3, val4, val5);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4, val5);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%+x Test %+3.x Test %+5.7x TEST %+10x";
//        int val = 3015;
//        int val2 = 712;
//        int val3 = 99;
//        int val4 = 2939;
//        int a = sprintf(str1, str3, val, val2, val3, val4);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%x Test %3.x Test %5.7x TEST %10x %#x %-x %+x %.x % .x";
//        int val = 0;
//        int a = sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
//        int b = s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);



//        char str1[200];
//        char str2[200];
//        char *str3 = "% x Test % 3.x Test % 5.7x TEST % 10x GOD %.x";
//        int val = 32;
//        int val2 = 8899;
//        int val3 = 91918;
//        int val4 = 32311;
//        int val5 = 23;
//        int a = sprintf(str1, str3, val, val2, val3, val4, val5);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4, val5);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%+x Test %+3.x Test %+5.7x TEST %+10x GOD %+.x";
//        int val = 32;
//        int val2 = 8899;
//        int val3 = 91918;
//        int val4 = 32311;
//        int val5 = 3261;
//        int a = sprintf(str1, str3, val, val2, val3, val4, val5);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4, val5);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%#x Test %#3x Test %#5.7x TEST %#.7x Oof %#.x";
//        int val = 32;
//        int val2 = 8899;
//        int val3 = 91918;
//        int val4 = 32311;
//        int val5 = 8894;
//        int a = sprintf(str1, str3, val, val2, val3, val4, val5);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4, val5);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%0x Test %06x Test %05.7x TEST %0.7x Oof %0.x";
//        int val = 32;
//        int val2 = 8899;
//        int val3 = 91918;
//        int val4 = 32311;
//        int val5 = 8894;
//        int a = sprintf(str1, str3, val, val2, val3, val4, val5);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4, val5);


//        char str1[200];
//        char str2[200];
//        char *str3 = "%*x Test %-*x Test %*.*x TEST %.*x";
//        int val = 32;
//        int val2 = 8899;
//        int val3 = 919;
//        int val4 = 32311;
//        int ast = 2;
//        int ast2 = 5;
//        int ast3 = 4;
//        int ast4 = 10;
//        int ast5 = 7;
//        int a = sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4);
//        int b = s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
//                        val4));


//        char str1[200];
//        char str2[200];
//        char *str3 = "%- x Test %- 15x sdasda %- 15x sdsad %- x";
//        int val = -3231;
//        int val2 = -3231;
//        int val3 = 3231;
//        int val4 = 3231;
//        int a = sprintf(str1, str3, val, val2, val3, val4);
//        int b = s21_sprintf(str2, str3, val, val2, val3, val4));



//        char str1[200];
//        char str2[200];
//        char *str3 = "fdsdsds %lx";
//        long int val = ULONG_MAX;
//        int a = sprintf(str1, str3, val);
//        int b = s21_sprintf(str2, str3, val);



      printf("or = %s\n", str1);
      printf("my = %s\n", str2);

      if(strcmp(str1, str1) == 0 && a == b) {
          printf("TEST OK!\n");
      } else {
          printf("FAIL!\n");
      }

    return 0;
}

