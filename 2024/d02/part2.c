#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Função para verificar se a linha está em ordem válida e respeita as regras
bool verificaLinha(int numeros[], int tamanho) {
    if (tamanho <= 1) return true; // Uma linha com um único número está automaticamente "aprovada".

    bool crescente = true, decrescente = true;

    for (int i = 1; i < tamanho; i++) {
        int diff = numeros[i] - numeros[i - 1];

        if (diff == 0) return false;               // Dois números consecutivos iguais desclassificam a linha
        if (diff > 3 || diff < -3) return false;   // Diferença maior que 3 ou menor que -3.

        if (numeros[i] < numeros[i - 1]) crescente = false;
        if (numeros[i] > numeros[i - 1]) decrescente = false;
    }

    return crescente || decrescente;
}

// Função para verificar a linha com o "Problem Dampener" (Parte 2)
bool verificaLinhaDampener(int numeros[], int tamanho) {
    // Verifica se já é válido
    if (verificaLinha(numeros, tamanho)) return true;

    // Caso contrário, tente remover cada número
    for (int i = 0; i < tamanho; i++) {
        int temp[MAX_LINE_LENGTH];
        int novoTamanho = 0;

        // Copia todos os elementos exceto o i-ésimo
        for (int j = 0; j < tamanho; j++) {
            if (j != i) {
                temp[novoTamanho++] = numeros[j];
            }
        }

        // Se essa versão for válida → linha aprovada
        if (verificaLinha(temp, novoTamanho)) {
            return true;
        }
    }

    return false;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINE_LENGTH];
    int linhasAprovadas = 0;
    int numLinhaAtual = 0;

    // Abra o arquivo para leitura
    arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Leia o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        numLinhaAtual++;
        int numeros[MAX_LINE_LENGTH];
        int tamanho = 0;

        // Converte a linha em uma lista de números
        char *token = strtok(linha, " \t\n");
        while (token != NULL) {
            numeros[tamanho++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }

        // Verifica se a linha passa nos critérios estabelecidos (Parte 2)
        if (verificaLinhaDampener(numeros, tamanho)) {
            linhasAprovadas++;
            printf("Linha aprovada: %d\n", numLinhaAtual);
        }
    }

    fclose(arquivo);

    // Exiba o total de linhas que passaram no teste
    printf("\nTotal de linhas aprovadas: %d\n", linhasAprovadas);

    return EXIT_SUCCESS;
}