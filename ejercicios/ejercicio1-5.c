#include <stdio.h>
int suma(int ,int );
int suma(int sumando1,int sumando2){
    return sumando1+sumando2;
}

int resta(int ,int );
int resta(int minuendo,int sustraendo){
    return minuendo-sustraendo;
}

int multiplicar(int ,int );
int multiplicar(int multiplicando,int multiplicador){
    return (multiplicando) * (multiplicador);
}

int main(void)
{
    int entrada;
    do
    {
        printf("1 para sumar dos numeros\n2 para restar dos numeros\n3 para multiplicar dos numeros\n0 para salir\n");
        scanf("%d",&entrada);
        if (entrada==1)
        {
            int sumando1;
            int sumando2;
            printf("Ingrese el primer sumando\n");
            scanf("%d",&sumando1);
            printf("Ingrese el segundo sumando\n");
            scanf("%d",&sumando2);
            printf("%d + %d = %d\n",sumando1,sumando2,suma(sumando1,sumando2));
        }
        else if (entrada==2)
        {
            int minuendo;
            int sustraendo;
            printf("Ingrese el minuendo\n");
            scanf("%d",&minuendo);
            printf("Ingrese el sustraendo\n");
            scanf("%d",&sustraendo);
            printf("%d - %d = %d\n",minuendo,sustraendo,resta(minuendo,sustraendo));
        }
        else if (entrada==3)
        {
            int multiplicando;
            int multiplicador;
            printf("Ingrese el multiplicando\n");
            scanf("%d",&multiplicando);
            printf("Ingrese el multiplicador\n");
            scanf("%d",&multiplicador);
            printf("%d x %d = %d\n",multiplicando,multiplicador,multiplicar(multiplicando,multiplicador));
        }      
    } while (entrada!=0);
    return 0;
}
