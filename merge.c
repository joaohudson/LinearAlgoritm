#include <stdio.h>
#include <math.h>

/**
 * Exibe um array de inteiros.
 */
static void PrintArray(int ar[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("\n[%d] = %d", i, ar[i]);
    }

    printf("\n");
}

/**
 * Função auxiliar Merge, ordena um array
 * parcialmente ordenado, onde cada metade
 * se encontra já ordenada.
 * Ex.: [4, 5, 6, 1, 2, 3]
 */
static void Merge(int ar[], int begin, int mid, int end)
{
    int size = end - begin + 1;
    int aux[size];
    int i = begin;
    int j = mid + 1;
    int k = 0;

    for(; i <= mid && j <= end; k++)
    {
        if(ar[i] < ar[j])
        {
            aux[k] = ar[i];
            i++;
        }
        else
        {
            aux[k] = ar[j];
            j++;
        }
    }

    while(i <= mid)
    {
        aux[k] = ar[i];
        i++;
        k++;
    }

    while(j <= end)
    {
        aux[k] = ar[j];
        j++;
        k++;
    }

    for(k = 0, i = begin; i <= end; i++, k++)
    {
        ar[i] = aux[k];
    }
}

/**
 * Algoritmo de ordenação Merge Sort.
 * 
 * Parâmetros:
 *  ar: Um array de inteiros.
 *  begin: O índice inicial do array,
 *  normalmente zero.
 *  end: O fim do array, normalmente
 *  tamanho - 1.
 * 
 * Custo:
 *  Melhor caso: O(n * log n)
 *  Caso médio: O(n * log n)
 *  Pior caso: O(n * log n)
 */
void MergeSort(int ar[], int begin, int end)
{
    int mid;
    if(begin < end)
    {
        mid = floor((begin + end) / 2.0f);
        MergeSort(ar, begin, mid);
        MergeSort(ar, mid + 1, end);
        Merge(ar, begin, mid, end);
    }
}

int main(void)
{
    int data[] = {5, 2, 3, 1, 8, -9};

    MergeSort(data, 0, 5);

    PrintArray(data, 6);

    return 0;
}