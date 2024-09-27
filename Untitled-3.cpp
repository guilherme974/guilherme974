#include "processo.h"

void ler_processos(const char *filename, Processo processos[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    // Ignorar o cabeçalho
    fgets(buffer, sizeof(buffer), file);

    *count = 0;
    while (fgets(buffer, sizeof(buffer), file) && *count < MAX_PROCESSOS) {
        sscanf(buffer, "%ld,\"%[^\"]\",%[^,],{%ld},{%ld},%d",
               &processos[*count].id,
               processos[*count].numero,
               processos[*count].data_ajuizamento,
               &processos[*count].id_classe,
               &processos[*count].id_assunto,
               &processos[*count].ano_eleicao);
        (*count)++;
    }

    fclose(file);
}

void ordenar_por_id(Processo processos[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

void ordenar_por_data(Processo processos[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j + 1].data_ajuizamento) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

int contar_por_id_classe(Processo processos[], int count, long id_classe) {
    int contador = 0;
    for (int i = 0; i < count; i++) {
        if (processos[i].id_classe == id_classe) {
            contador++;
        }
    }
    return contador;
}

int contar_id_assuntos(Processo processos[], int count) {
    long assuntos[MAX_PROCESSOS];
    int num_assuntos = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < num_assuntos; j++) {
            if (assuntos[j] == processos[i].id_assunto) {
                found = 1;
                break;
            }
        }
        if (!found) {
            assuntos[num_assuntos++] = processos[i].id_assunto;
        }
    }
    return num_assuntos;
}

int dias_em_tramitacao(const char *data_ajuizamento) {
    struct tm tm;
    strptime(data_ajuizamento, "%Y-%m-%d %H:%M:%S", &tm);
    time_t data_inicio = mktime(&tm);
    time_t data_atual = time(NULL);
    return difftime(data_atual, data_inicio) / (60 * 60 * 24);
}