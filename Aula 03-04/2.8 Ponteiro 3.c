#include <stdio.h>

int main()
{   int i;
    int vec[]={3, 6, 9, 12, 15, 17};
    int *p;
    p = &vec;
    for (i=0; i<6;i++)
    {
        printf(" Valor %d = %d\n", i+1, *(p+i));
    }
    return 0;
}
