#include <stdio.h>
int v[3]; // O vetor deve ser declarado como uma variável global
int *primos(void)
{
    v[0]=1009;
    v[1]=1013;
    v[2]=1019;
    return v;
}
int main()
{
    primos();
    printf("%d,\n %d, \n %d,\n %d\n", &v, v[0],v[1],v[2]);
    return 0;
}



