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

        if (diff == 0) return false; // Dois números consecutivos iguais desclassificam a linha
        if (diff > 3 || diff < -3) return false; // Diferença maior que 3 ou menor que -3.

        if (numeros[i] < numeros[i - 1]) crescente = false;
        if (numeros[i] > numeros[i - 1]) decrescente = false;
    }

    return crescente || decrescente;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINE_LENGTH];
    int linhasAprovadas = 0;

    // Abra o arquivo para leitura
    arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Leia o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        int numeros[MAX_LINE_LENGTH];
        int tamanho = 0;

        // Converte a linha em uma lista de números
        char *token = strtok(linha, " \t\n");
        while (token != NULL) {
            numeros[tamanho++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }

        // Verifique se a linha passa nos critérios
        if (verificaLinha(numeros, tamanho)) {
            linhasAprovadas++;
        }
    }

    fclose(arquivo);

    // Exiba o total de linhas que passaram no teste
    printf("Total de linhas aprovadas: %d\n", linhasAprovadas);

    return EXIT_SUCCESS;
}
