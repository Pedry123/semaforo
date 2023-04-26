#include<stdio.h>
#include<stdlib.h>
#include "structs.h"

//Funcoes e metodos uteis para o programa

void inicializarVeiculos(Veiculo veiculos[NUM_VEICULOS]) {
    for (int i = 0; i < NUM_VEICULOS; i++) {
        double r = (double) rand() / RAND_MAX;
        if (r < PERC_ONIBUS) {
            veiculos[i].tipo = ONIBUS;
            veiculos[i].tempoReacao = 2;
        } else if (r < PERC_ONIBUS + PERC_CARROS * PERC_PRIORITARIOS) {
            veiculos[i].tipo = PRIORITARIO;
            veiculos[i].tempoReacao = 1;
        } else {
            veiculos[i].tipo = CARRO;
            veiculos[i].tempoReacao = 1;
        }
        veiculos[i].tempoEspera = 0;
        veiculos[i].envolvidoColisao = 0;
    }
}

void inicializarRotatoria(Rotatoria* rotatoria) {
    for (int i = 0; i < NUM_VIAS; i++) {
        rotatoria->vias[i].inicio = 0;
        rotatoria->vias[i].fim = 0;
    }
}

void adicionarVeiculo(Via* via, Veiculo* veiculo) {
    via->fila[via->fim] = veiculo;
    via->fim = (via->fim + 1) % NUM_VEICULOS;
}

Veiculo* removerVeiculo(Via* via) {
    Veiculo* veiculo = via->fila[via->inicio];
    via->inicio = (via->inicio + 1) % NUM_VEICULOS;
    return veiculo;
}

int filaVazia(Via* via) {
    return via->inicio == via->fim;
}

void verificaColisao(Veiculo* veiculo) {
    double probColisao = (double)rand() / RAND_MAX;
        if (probColisao < COLISAO_PROB) {
            veiculo->envolvidoColisao = 1;
        }
}

void processaTempo(Veiculo* veiculo, double *tempoEspera, double *tempoTotalEspera, int veiculosProcessados) {
    veiculo->tempoEspera += *tempoEspera;
    *tempoTotalEspera += *tempoEspera;
}

void resetaInformacoesVeiculos(Veiculo veiculos[NUM_VEICULOS]) {
    for (int i = 0; i < NUM_VEICULOS; i++) {
        veiculos[i].tempoEspera = 0;
        veiculos[i].envolvidoColisao = 0;
    }
}