#include "processo.h"

void salvar_em_csv(const char *filename, Processo processos[], int count, int ordenar_por) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao criar o arquivo");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%ld,\"%s\",\"%s\",{%ld},{%ld},%d\n",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento,
                processos[i].id_classe,
                processos[i].id_assunto,
                processos[i].ano_eleicao);
    }

    fclose(file);
}

int main() {
    Processo processos[MAX_PROCESSOS];
    int count;

    ler_processos("processo_043_202409032338", processos, &count);

    // Ordenar por ID
    ordenar_por_id(processos, count);
    salvar_em_csv("processos_ordenados_id.csv", processos, count, 1);

    // Ordenar por Data
    ordenar_por_data(processos, count);
    salvar_em_csv("processos_ordenados_data.csv", processos, count, 2);

    // Contar por id_classe (exemplo: 12554)
    long id_classe = 12554;
    int quantidade = contar_por_id_classe(processos, count, id_classe);
    printf("Quantidade de processos com id_classe %ld: %d\n", id_classe, quantidade);

    // Contar id_assuntos
    int num_assuntos = contar_id_assuntos(processos, count);
    printf("Quantidade de id_assuntos: %d\n", num_assuntos);

    // Calcular dias em tramitação do primeiro processo
    int dias = dias_em_tramitacao(processos[0].data_ajuizamento);
    printf("O primeiro processo está em tramitação há %d dias.\n", dias);

    return 0;
}