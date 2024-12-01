#include <stdio.h>
#include <stdlib.h>

// Função para contar quantas vezes um número aparece em um vetor
int contar_ocorrencias(int *vetor, int tamanho, int numero) {
    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == numero) {
            contador++;
        }
    }
    return contador;
}

int main() {
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

    // Calcula o resultado
    int soma_total = 0;
    for (int i = 0; i < n; i++) {
        int numero = coluna1[i];
        int ocorrencias = contar_ocorrencias(coluna2, n, numero);
        soma_total += numero * ocorrencias;
    }

    // Exibe o resultado
    printf("Soma total dos produtos: %d\n", soma_total);

    // Libera a memória alocada
    free(coluna1);
    free(coluna2);

    return 0;
}
