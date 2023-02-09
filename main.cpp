#include "s21_sprintf.h"

int main()
{

    char origin[BUF_SIZE];
    char my[BUF_SIZE];


      s21_sprintf(my, "%.18f", -100.00088);
      sprintf(origin, "%.18f", -100.00088);

//    s21_sprintf(my, "%7.10f", 11.123456);
//    sprintf(origin, "%7.10f", 11.123456);

    if(strcmp(origin, my) == 0) {
        printf("TEST OK!\n");
    } else {
        printf("FAIL!\n");
    }
    printf("origin = %s\n", origin);
    printf("    my = %s\n", my);



    return 0;
}


