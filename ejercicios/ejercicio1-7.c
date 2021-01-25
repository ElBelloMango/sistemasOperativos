#include <stdio.h>
int main()
{
    int num;
    char key;
    printf("Prueba a scanf. Ingrese el numero 325 y presione ENTER:\n");
    scanf("%d",&num);
    printf("Ingrese cualquier tecla para terminar y presione ENTER:\n");
    getc(stdin);//obtener el caracter dejado por el flujo de entrada de el primer scanf
    scanf("%c",&key);
    return 0;
}