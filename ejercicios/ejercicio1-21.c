 #include <stdio.h>
 #include <stdint.h>

uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);
uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize){
    int posicionRes=0;
    for (int i = 0; i < arr1Size; i++)
    {
        int elemento = 0;
        for (int j = 0; j < arr2Size; j++)
        {
            if (*(arr1+i)==*(arr2+j))
            {
                int a  = 0;
                
                elemento = *(arr1+i);
                for (int k = 0; k < arrResSize; k++)
                {
                    if (elemento==*(arrRes+k))
                    {
                        a=0;
                    }
                    else
                    {
                        a=1;
                    }
                }
                if (a=1)
                {
                    *(arrRes+posicionRes++) = elemento;
                }
            }
        }
    }
}


int main(void)
{
    int arr1[]={1,2,3,4,5,6,7,8,9,10};

    int arr1Size =10;
    int arr2[]={10,11,12,13,14,2,6};
    int arr2Size= 7;
    int arrRes[3];
    int arrResSize = 3;
    arrayCommon(&arr1,arr1Size,&arr2,arr2Size,&arrRes,arrResSize);
    for (int i = 0; i < arrResSize; i++)
    {
        printf("%d\n",arrRes[i]);
    }
    
    return 0;
}
