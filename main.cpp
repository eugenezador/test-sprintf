#include "s21_sprintf.h"

int main()
{

    char origin[BUF_SIZE];
    char my[BUF_SIZE];


//      s21_sprintf(my, "%.18f", -100.070088);
//      sprintf(origin, "%.18f", -100.070088);

//    s21_sprintf(my, "%7.20f", 11.09000823456);
//    sprintf(origin, "%7.20f", 11.09000823456);

//        s21_sprintf(my, "%s:%s", "11.09000823456");
//        sprintf(origin, "%s:%s", "11.09000823456");

    s21_sprintf(my, "%-40.8s:", "11.09000823456");
    sprintf(origin, "%-40.8s:", "11.09000823456");

    if(strcmp(origin, my) == 0) {
        printf("TEST OK!\n");
    } else {
        printf("FAIL!\n");
    }
    printf("origin = %s\n", origin);
    printf("    my = %s\n", my);



    return 0;
}


