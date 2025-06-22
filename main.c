/******************************************************************************
bubble sort / insertion sort / heap sort / merge sort / radix sort
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Commom methods

int* criarVetor(int i) {
    int* v = malloc(sizeof(int) * i);
    for(int j = 0; j < i; j++) {
        v[j] = rand() % 1000;
    }
    return v;
}

int* copiaVetor(int* v, int i) {
    int *vetorNovo = malloc(sizeof(int) * i);
    for(int j = 0; j < i; j++) {
        vetorNovo[j] = v[j];
    }
    return vetorNovo;
}

void swap(int v[], int i, int j, int* cont) {
    (*cont)++;
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

//BubbleSort

int bubblesort(int v[], int n) {
    int cont = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            cont++;
            if(v[i] > v[j]) {
                swap(v, i, j, &cont);
            }
        }
    }
    return cont;
}

//InsertionSort

int insertionsort(int v[], int n) {
    int cont = 0;
    int pivo, j;
    for (int i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;
        cont++;
        while (j >= 0 && pivo < v[j]) {
            v[j + 1] = v[j];
            j--;
            cont += 2;
        }
        cont++;
        v[j + 1] = pivo;
    }
    return cont;
}

//Heapsort

void heapify(int v[], int n, int i, int* cont) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    (*cont)++;
    if (esquerda < n && v[esquerda] > v[raiz]) {
        raiz = esquerda;
    }
    (*cont)++;
    if (direita < n && v[direita] > v[raiz]) {
        raiz = direita;
    }
    if (raiz != i) {
        swap(v, i, raiz, cont);
        heapify(v, n, raiz, cont);
    }
}

int heapsort(int v[], int n) {
    int cont = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, &cont);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(v, 0, i, &cont);
        heapify(v, i, 0, &cont);
    }
  return cont;
}

//MergeSort

void merge(int v[], int inicio, int meio, int fim, int* cont) {
 int aux[fim - inicio + 1];
 int i = inicio, j = meio + 1, k = 0;
    (*cont)++;
    while (i <= meio && j <= fim) {
        aux[k++] = v[i] <= v[j] ? v[i++] : v[j++];
        (*cont)++;
    }
    (*cont)++;
    while (i <= meio) {
        aux[k++] = v[i++];
        (*cont)++;
    }
    (*cont)++;
    while (j <= fim) {
        aux[k++] = v[j++];
        (*cont)++;
    }
    (*cont)++;
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
        (*cont)++;
    }
}

void _mergesort(int v[], int inicio, int fim, int *cont) {
    int i, meio;
    for (meio = 1; meio < fim - inicio + 1; meio = 2 * meio) {
        for (i = inicio; i <= fim - meio; i += 2 * meio) {
            int j = (i + (2 * meio)) - 1;
            if (j > fim) j = fim;

            merge(v, i, i + meio - 1, j, cont);
        }
    }
}

int mergesort(int v[], int n) {
    int cont = 0;
    _mergesort(v, 0, n - 1, &cont);
    return cont;
}

//Quicksort

int partition(int v[], int inicio, int fim, int *cont) {
    int pivo = v[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        (*cont)++;
        if (v[j] < pivo) {
            i++;
            swap(v, i, j, cont);
        }
    }
    swap(v, i + 1, fim, cont);
    return i + 1;
}

void _quicksort(int v[], int inicio, int fim, int *cont) {
    if (inicio < fim) {
        int meio = partition(v, inicio, fim, cont);

        _quicksort(v, inicio, meio - 1, cont);
        _quicksort(v, meio + 1, fim, cont);
    }
}

int quicksort(int v[], int n) {
    int cont = 0;
    _quicksort(v, 0, n - 1, &cont);
    return cont;
}

//RadixSort

int max(int v[], int n, int* cont) {
    int max = v[0];
    for (int i = 1; i < n; i++) {
        (*cont)++;
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

void countingsort(int v[], int n, int expo, int* cont) {
    int saida[n], frequencia[10] = {0};
    for (int i = 0; i < n; i++) {
        frequencia[(v[i] / expo) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        frequencia[i] += frequencia[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        saida[frequencia[(v[i] / expo) % 10] - 1] = v[i];
        frequencia[(v[i] / expo) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        (*cont)++;
        v[i] = saida[i];
    }
}

int radixsort(int v[], int n) {
    int cont = 0;
    int m = max(v, n, &cont);
    for (int expo = 1; m / expo > 0; expo *= 10) {
        countingsort(v, n, expo, &cont);
    }
    return cont;
}

int main() {
    srand(time(NULL));

    FILE *arquivo = fopen("Result.txt", "w");
    int qtdOp;
    fprintf(arquivo, "Array Size, Qty operations, method\n");

    for(int j = 0; j < 30; j++) {
        for(int i = 0; i <= 1000; i++) {
            int* v = criarVetor(i);

            int* vetorBubblesort = copiaVetor(v, i);
            qtdOp = bubblesort(vetorBubblesort, i);
            fprintf(arquivo, "%d,%d,Bubblesort\n", i, qtdOp);

            int* vetorInsertionsort = copiaVetor(v, i);
            qtdOp = insertionsort(vetorInsertionsort, i);
            fprintf(arquivo, "%d,%d,Insertionsort\n", i, qtdOp);

            int* vetorHeapsort = copiaVetor(v, i);
            qtdOp = heapsort(vetorHeapsort, i);
            fprintf(arquivo, "%d,%d,Heapsort\n", i, qtdOp);

            int* vetorMergesort = copiaVetor(v, i);
            qtdOp = mergesort(vetorMergesort, i);
            fprintf(arquivo, "%d,%d,Mergesort\n", i, qtdOp);

            int* vetorQuicksort = copiaVetor(v, i);
            qtdOp = quicksort(vetorQuicksort, i);
            fprintf(arquivo, "%d,%d,Quicksort\n", i, qtdOp);

            int* vetorRadixsort = copiaVetor(v, i);
            qtdOp = radixsort(vetorRadixsort, i);
            fprintf(arquivo, "%d,%d,Radixsort\n", i, qtdOp);

            free(v);
            free(vetorBubblesort);
            free(vetorInsertionsort);
            free(vetorHeapsort);
            free(vetorMergesort);
            free(vetorQuicksort);
            free(vetorRadixsort);
        }
    }
    fclose(arquivo);
    return 0;
}