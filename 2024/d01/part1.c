#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // Função de comparação para qsort
}

int main() {
    // Declaração de variáveis
    FILE *arquivo;
    int *coluna1 = NULL, *coluna2 = NULL;
    int capacidade = 10; // Capacidade inicial dos vetores
    int n = 0;           // Quantidade de elementos lidos

    // Aloca memória inicial para os vetores
    coluna1 = (int *)malloc(capacidade * sizeof(int));
    coluna2 = (int *)malloc(capacidade * sizeof(int));
    if (coluna1 == NULL || coluna2 == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Abre o arquivo input.txt para leitura
    arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(coluna1);
        free(coluna2);
        return 1;
    }

    // Lê os dados do arquivo
    while (1) {
        int temp1, temp2;
        if (fscanf(arquivo, "%d %d", &temp1, &temp2) != 2) break;

        // Redimensiona os vetores se necessário
        if (n >= capacidade) {
            capacidade *= 2;
            coluna1 = (int *)realloc(coluna1, capacidade * sizeof(int));
            coluna2 = (int *)realloc(coluna2, capacidade * sizeof(int));
            if (coluna1 == NULL || coluna2 == NULL) {
                printf("Erro de alocação de memória.\n");
                fclose(arquivo);
                free(coluna1);
                free(coluna2);
                return 1;
            }
        }

        // Armazena os valores nos vetores
        coluna1[n] = temp1;
        coluna2[n] = temp2;
        n++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Ordena os vetores
    qsort(coluna1, n, sizeof(int), compare);
    qsort(coluna2, n, sizeof(int), compare);

    // Calcula a diferença (sempre maior - menor) para cada par e soma as diferenças
    int soma_diferencas = 0;
    for (int i = 0; i < n; i++) {
        int diferenca = coluna1[i] > coluna2[i] 
                            ? coluna1[i] - coluna2[i] 
                            : coluna2[i] - coluna1[i];
        soma_diferencas += diferenca;
    }

    // Exibe os resultados
    printf("Coluna 1 ordenada: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", coluna1[i]);
    }
    printf("\n\n");

    printf("Coluna 2 ordenada: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", coluna2[i]);
    }
    printf("\n\n");

    printf("Soma total das diferenças: %d\n", soma_diferencas);

    // Libera a memória alocada
    free(coluna1);
    free(coluna2);

    return 0;
}
