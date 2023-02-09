#include "s21_sprintf.h"

int main()
{

    char origin[BUF_SIZE];
    char my[BUF_SIZE];

//    s21_sprintf(my, "%.20f", 0.000000000000001);
//    sprintf(origin, "%.20f", 0.000000000000001);
    s21_sprintf(my, "%.0f", 0.0002100);
    sprintf(origin, "%.0f", 0.0002100);
//    s21_sprintf(my, "%f", 0.0);
//    sprintf(origin, "%f", 0.0);

    printf("origin = %s\n", origin);
    printf("    my = %s\n", my);



    return 0;
}


