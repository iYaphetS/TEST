#include <stdio.h>

int main()
{
    if(2>0)
        goto l;

    if(-1<0)
        goto s;

l:
    printf("--------------2----------\n");

s:
    printf("--------------1-----------\n");


    return 0;
}
