#include <stdio.h>

void swap(int *p1, int *p2)
{
    int a;
    a=*p1;
    *p1=*p2;
    *p2=a;
}
int main()
{
    int x=10;
    int y=20;

    swap(&x,&y);

    printf("x:%d, y:%d\n", x, y);
    return 0;

}
