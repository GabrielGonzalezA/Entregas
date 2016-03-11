#include <stdio.h>

int hcf(int a, int b)
{
    int i, result;
    for(i=1; i<=a || i<=b; i++)
    {
        if(a%i==0 && b%i==0)
            result=i;
    }
    return (result);
}
int main()
{
    int num1, num2, i, x;

    printf("Numero 1: \n");
    scanf("%d", &num1);

    printf("Numero 2: \n");
    scanf("%d", &num2);

    x = hcf(num1,num2);

    printf("H.C.F of %d and %d is %d \n", num1, num2, x);
    return 0;

}
