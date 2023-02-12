#include "s21_sprintf.h"

int main()
{


//    char str1[400];
//     char str2[400];
//     char str3[400] = "test: %-+ 30f!\ntest: % -27f!\ntest: %- 19f!";
//     double num = 365789.34;

//     int a = sprintf(str1, str3, num, num, num);
//     int b = s21_sprintf(str2, str3, num, num, num);





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



//      char str1[400];
//        char str2[400];
//        char str3[400] = "test: %020f!\ntest: %-020f!\ntest: %+025f!";
//        double num = 837564.4753366;
//        int a = sprintf(str1, str3, num, num, num);
//        int b = s21_sprintf(str2, str3, num, num, num);




//        char str1[400];
//           char str2[400];
//           char str3[400] = "test: %-+ 025.5f!\ntest: %- 020.4f\ntest: %+ 016.6f!";
//           double num = 837564.4753366;
//           int a = sprintf(str1, str3, num, num, num);
//           int b = s21_sprintf(str2, str3, num, num, num);

//       32 FAIL
//           char str1[400];
//              char str2[400];
//              char str3[400] = "test: %015f!\ttest: %-026f!\ttest: %+018f!";
//              double num = -947.6785643;
//              int a = sprintf(str1, str3, num, num, num);
//              int b = s21_sprintf(str2, str3, num, num, num);


//              char str1[400];
//                 char str2[400];
//                 char str3[400] = "test: %-+ 025.5f!\ntest: %- 020.4f\ntest: %+ 016.6f!";
//                 double num = 837564.4753366;
//                 int a = sprintf(str1, str3, num, num, num);
//                  int b =  s21_sprintf(str2, str3, num, num, num);


// 34 FAIL
//    char str1[400];
//    char str2[400];
//    char str3[400] = "test: % 15.1f!\ntest: % -26.15f!\ntest: %- 30.15f!";
//    double num = 278.723786;
//    int a = sprintf(str1, str3, num, num, num);
//    int b = s21_sprintf(str2, str3, num, num, num);


    // 35 Fail
       char str1[400];
       char str2[400];
       char str3[400] = "test: %+ 50.15f!\ntest: % +40.15f!";
       double num = -278.723786;
       int a = sprintf(str1, str3, num, num);
       int b = s21_sprintf(str2, str3, num, num);






     printf("32origin = :%s:\n", str1);
     printf("32    my = :%s:\n", str2);

    if(strcmp(str1, str1) == 0 && a == b) {
        printf("TEST OK!\n");
    } else {
        printf("FAIL!\n");
    }

    return 0;
}


