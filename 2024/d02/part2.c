#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Adicionado para strtok

#define MAX_LINE_LENGTH 1024

// Função para verificar se uma linha é segura
bool is_safe(int *numbers, int size) {
    bool skipped = false; // Flag para indicar se um número já foi ignorado

    for (int i = 0; i < size - 1; i++) {
        int diff = abs(numbers[i + 1] - numbers[i]);

        if (numbers[i] == numbers[i + 1]) {
            // Regra: Números iguais desclassificam a linha
            return false;
        }

        if (diff > 3) {
            if (skipped) {
                // Já ignoramos um número antes, então não pode ser seguro
                return false;
            }

            // Tenta pular o próximo número
            if (i + 2 < size && abs(numbers[i + 2] - numbers[i]) <= 3) {
                skipped = true;
                i++; // Ignora o próximo número
            } else {
                // Não há solução viável
                return false;
            }
        }

        // Verifica consistência da ordem (crescente ou decrescente)
        if ((numbers[i] < numbers[i + 1] && numbers[i + 1] > numbers[i + 2]) ||
            (numbers[i] > numbers[i + 1] && numbers[i + 1] < numbers[i + 2])) {
            return false;
        }
    }

    return true;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    int safe_lines = 0;

    while (fgets(line, sizeof(line), file)) {
        int numbers[MAX_LINE_LENGTH];
        int count = 0;

        // Lê os números da linha
        char *token = strtok(line, " ");
        while (token) {
            numbers[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Verifica se a linha é segura
        if (is_safe(numbers, count)) {
            safe_lines++;
        }
    }

    fclose(file);

    printf("Total de linhas seguras: %d\n", safe_lines);
    return EXIT_SUCCESS;
}
