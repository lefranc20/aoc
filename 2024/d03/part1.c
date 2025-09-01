#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 // verificar

// Função para processar uma linha e somar todos os mul(X,Y) válidos
int processaLinha(const char *linha) {
    int soma = 0;
    const char *ptr = linha;

    while ((ptr = strstr(ptr, "mul(")) != NULL) {
        int x, y;
        // Tenta ler no formato mul(num,num)
        if (sscanf(ptr, "mul(%d,%d)", &x, &y) == 2) {
            soma += x * y;
        }
        // Avança o ponteiro para não travar em loop infinito
        ptr += 4;
    }

    return soma;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINE_LENGTH];
    int somaTotal = 0;  // seria bom utilizar o long long para evitar overflow

    // Abra o arquivo para leitura
    arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Leia o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%d\n", somaTotal); // ainda está retornando com erro
        somaTotal += processaLinha(linha);
    }

    fclose(arquivo);

    // Exiba o resultado total
    printf("Soma total dos produtos: %d\n", somaTotal);

    return EXIT_SUCCESS;
}