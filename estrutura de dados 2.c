#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de um processo
typedef struct {
    long long id;
    char numero[25];
    char data_ajuizamento[25];
    int id_classe;
    int id_assunto;
    int ano_eleicao;
} Processo;

// Função para ler dados do arquivo
int ler_dados(char *nome_arquivo, Processo *processos, int max_processos) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[256];
    int cont = 0;

    // Ignorar a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    // Ler dados do arquivo linha a linha
    while (fgets(linha, sizeof(linha), arquivo) && cont < max_processos) {
        sscanf(linha, "%lld,\"%[^\"]\",%s,%d,%d,%d",
               &processos[cont].id,
               processos[cont].numero,            // Remover o '&' aqui
               processos[cont].data_ajuizamento,  // Remover o '&' aqui
               &processos[cont].id_classe,
               &processos[cont].id_assunto,
               &processos[cont].ano_eleicao);
        cont++;
    }

    fclose(arquivo);
    return cont;
}

// Função para ordenar processos por ID (ordem crescente)
int comparar_por_id(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;
    return (p1->id > p2->id) - (p1->id < p2->id);
}

// Função para contar processos por id_classe
int contar_por_id_classe(Processo *processos, int num_processos, int id_classe) {
    int cont = 0;
    for (int i = 0; i < num_processos; i++) {
        if (processos[i].id_classe == id_classe) {
            cont++;
        }
    }
    return cont;
}

// Função principal
int main() {
    Processo processos[100];
    int num_processos = ler_dados("processo_043_202409032338.txt", processos, 100);

    if (num_processos == -1) {
        return 1;
    }

    // Ordenar por ID
    qsort(processos, num_processos, sizeof(Processo), comparar_por_id);

    // Exibir os processos ordenados por ID
    printf("Processos ordenados por ID:\n");
    for (int i = 0; i < num_processos; i++) {
        printf("%lld, %s, %s, %d, %d, %d\n", processos[i].id, processos[i].numero, processos[i].data_ajuizamento,
               processos[i].id_classe, processos[i].id_assunto, processos[i].ano_eleicao);
    }

    // Contar processos por id_classe
    int id_classe = 12554;
    int count_classe = contar_por_id_classe(processos, num_processos, id_classe);
    printf("\nProcessos vinculados ao id_classe %d: %d\n", id_classe, count_classe);

    return 0;
}
