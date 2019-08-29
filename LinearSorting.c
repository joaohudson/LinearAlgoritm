#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DIGITS(value) ( !(value) ? 1 : (int)floor(log10(abs(value))) + 1 )
#define SWAP(a, b) { int aux = a; a = b; b = aux; }

//Imprime um array dado ele e seu tamanho.
void ShowArray(const int ar[], int size)
{
    for(int i = 0; i < size; i++)
        printf("\n[%d] = %d", i, ar[i]);
}

//Imprime o array no arquivo especificado.
void PrintArray(const int ar[], int size, const char *dir)
{
	FILE *file = fopen(dir, "w");
	
	for(int i = 0; i < size; i++)
		fprintf(file, "%d\n", ar[i]);
	
	fclose(file);
}

//Carrega um array a partir de um arquivo, e informa seu tamanho pelo parâmetro size.
int* LoadArray(const char* dir, int *size)
{
	FILE *file = fopen(dir, "r");
	int *data;
	
	fscanf(file, "%d", size);
	data = (int*)malloc((*size) * sizeof(int));
	
	for(int i = 0; i < *size; i++)
	{
		fscanf(file, "\n%d", data + i);
	}
	
	fclose(file);
	
	return data;
}
//Retorna o maior elemento do array:
int FindMax(int ar[], int size)
{
	int aux = 0;

	for(int i = 1; i < size; i++)
	{
		if(ar[aux] < ar[i])
			aux = i;		
	}

	return ar[aux];
}
//Retorna o menor elemento do array:
int FindMin(int ar[], int size)
{
	int aux = 0;

	for(int i = 1; i < size; i++)
	{
		if(ar[aux] > ar[i])
			aux = i;		
	}

	return ar[aux];
}

int* CountSort(int input[], int output[], int size, int maxValue, int minValue)
{
    int k = maxValue - minValue + 1;
    int aux[k];
    
    for(int i = 0; i < k; i++)
    {
        aux[i] = 0;
    }
    
    for(int i = 0; i < size; i++)
    {
        aux[input[i] - minValue]++;
    }
    
    for(int i = 1; i < k; i++)
    {
        aux[i] = aux[i] + aux[i - 1];
    }
    
    for(int i = 0; i < size; i++)
    {
        aux[input[i] - minValue]--;
        output[aux[input[i] - minValue]] = input[i];
    }

    return output;
}
//Auxilia no radix sort:
static void CountSortForRadix(int in[], int out[], int size, int potency)
{
    int aux[19] = {0};
    
    for(int i = 0; i < size; i++)
    {
        aux[((in[i] / potency) % 10) + 9]++;
    }
    
    for(int i = 1; i < 19; i++)
    {
        aux[i] = aux[i] + aux[i - 1];
    }
    
    for(int i = size - 1; i >= 0; i--)
    {
        out[--aux[((in[i] / potency) % 10) + 9]] = in[i];
    }
}

int* RadixSort(int in[], int out[], int size, int maxValue)
{
    int nDigits = NUMBER_OF_DIGITS(maxValue);
    int potency = 1;
    int i;
    
    for(i = 0; i < nDigits; i++, potency *= 10)
    {
        if(i % 2)
            CountSortForRadix(out, in, size, potency);
        else
            CountSortForRadix(in, out, size, potency);
    }
    
    return i % 2 ? out : in;
}

int* SelectionSort(int in[], int size)
{
  int minor = 0;

  for(int i = 0; i < size - 1; i++)
  {
    minor = i;
    for(int j = i + 1; j < size; j++)
    {
      if(in[minor] > in[j])
        minor = j;
    }
    SWAP(in[minor], in[i])
  }

  return in;
}

int* InsertionSort(int in[], int size)
{
  int aux;
  int i, j;

  for(i = 0; i < size; i++)
  {
    aux = in[i];

    for(j = i - 1; j >= 0 && aux < in[j]; j--)
    {
      in[j + 1] = in[j];
    }

    in[j + 1] = aux;
  }

  return in;
}

int main(int argc, char **argv)
{
    	int *out;
	int *data;
	int *aux;
	int size;
	
    if(argc < 4)
	{
		fprintf(stderr, "Erro: parametros invalidos");
		exit(1);
	}

	if(!strcmp(argv[1], "SelectionSort"))
	{
		data = LoadArray(argv[2], &size);
		
		out = SelectionSort(data, size);
		
		PrintArray(out, size, argv[3]);
		
		free(data);
	}
	else if(!strcmp(argv[1], "CountSort"))
	{
		data = LoadArray(argv[2], &size);
		aux = malloc(size * sizeof(int));
		
		out = CountSort(data, aux, size, FindMax(data, size), FindMin(data, size));
		
		PrintArray(out, size, argv[3]);
		
		free(data);
		free(aux);
	}
	else if(!strcmp(argv[1], "RadixSort"))
	{
		data = LoadArray(argv[2], &size);
		aux = malloc(size * sizeof(int));
		
		out = RadixSort(data, aux, size, FindMax(data, size));
		
		PrintArray(out, size, argv[3]);
		
		free(data);
		free(aux);
	}
	else if(!strcmp(argv[1], "InsertionSort"))
	{
		data = LoadArray(argv[2], &size);
		
		out = InsertionSort(data, size);
		
		PrintArray(out, size, argv[3]);
		
		free(data);
	}
	
    return 0;
}
