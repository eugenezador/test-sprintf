#include "s21_sprintf.h"

int main()
{


//    char str1[400];
//     char str2[400];
//     char str3[400] = "test: %f!\ttest: % -27f!\ttest: %- 19f!";
//     double num = 365789.34;

//     int a = sprintf(str1, str3, num, num, num);
//     int b = s21_sprintf(str2, str3, num, num, num);
//         printf("origin = :%s:\n", str1);
//          printf("    my = :%s:\n", str2);





//     char str1[400];
//     char str2[400];
//     char str3[400] = "test: %- 26Lf!\ntest: %+- 18Lf!\ntest: %60Lf!";
//     long double num = 3752765839673496.34;

//     int a =  sprintf(str1, str3, num, num, num);
//      int b = s21_sprintf(str2, str3, num, num, num);


//      char str1[400];
//        char str2[400];
//        char str3[400] = "test: % +15f!test: %100f!";
//        double num = 3752765839673496.34;
//        int a = sprintf(str1, str3, num, num);
//        int b = s21_sprintf(str2, str3, num, num);
//     printf("27origin = :%s:\n", str1);
//      printf("27    my = :%s:\n", str2);



// OK
//              char str1[400];
//                 char str2[400];
//                 char str3[400] = "test: %-+ 025.5f!\ttest: %- 020.4f\ttest: %+ 016.6f!";
//                 double num = 837564.4753366;
//                 int a = sprintf(str1, str3, num, num, num);
//                  int b =  s21_sprintf(str2, str3, num, num, num);
//        printf("origin = %s\n", str1);
//        printf("    my = %s\n", str2);


// 34 OK
//    char str1[400];
//    char str2[400];
//    char str3[400] = "test: :%0 +15.1f:!\ttest: % 0-26.4f!\ttest: %+ 30.4f!";
//    double num = 278.72;
//    int a = sprintf(str1, str3, num, num, num);
//    int b = s21_sprintf(str2, str3, num, num, num);
//    printf("34origin = %s\n", str1);
//    printf("34    my = %s\n", str2);


//    // 35 OK
//    char str1[400];
//    char str2[400];
//    char str3[400] = "test: %.2f!\ttest: %f!";
//    double num = -278.723786;
//    int a = sprintf(str1, str3, num, num);
//    int b = s21_sprintf(str2, str3, num, num);
//       printf("35origin = %s\n", str1);
//       printf("35    my = %s\n", str2);


//            char str1[400];
//            char str2[400];
//            char str3[400] = "test: %-+ 025.5f!"/*\ttest: %- 020.4f\ttest: %+ 016.6f!"*/;
//            double num = 837564.4753366;
//            int a = sprintf(str1, str3, num/*, num, num*/);
//            int b =  s21_sprintf(str2, str3, num/*, num, num*/);
//            printf("origin = %s\n", str1);
//            printf("    my = %s\n", str2);



    // OK
//          char str1[400];
//            char str2[400];
//            char str3[400] = "test: %020f!\ttest: %-020f!\ttest: %+025f!";
//            double num = -837564.4753366;
//            int a = sprintf(str1, str3, num, num, num);
//            int b = s21_sprintf(str2, str3, num, num, num);
//            printf("origin = %s\n", str1);
//            printf("    my = %s\n", str2);



    //  OK
//            char str1[400];
//               char str2[400];
//               char str3[400] = "test: %-+ 025.5f!\ttest: %- 020.4f\ttest: %+ 016.6f!";
//               double num = -837564.4753366;
//               int a = sprintf(str1, str3, num, num, num);
//               int b = s21_sprintf(str2, str3, num, num, num);
//        printf("origin = %s\n", str1);
//        printf("    my = %s\n", str2);

    //       32 FAIL
               char str1[400];
                  char str2[400];
                  char str3[400] = "test: %f!\ttest: % +-0f!\ttest: %+f!";
                  double num = -947.6785;
                  int a = sprintf(str1, str3, num, num, num);
                  int b = s21_sprintf(str2, str3, num, num, num);
                      printf("32origin = %s\n", str1);
                      printf("32    my = %s\n", str2);

        if(strcmp(str1, str1) == 0 && a == b) {
            printf("TEST OK!\n");
        } else {
            printf("FAIL!\n");
        }

    return 0;
}

