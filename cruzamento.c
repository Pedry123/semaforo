#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_uteis.h"

int main() {
    srand(time(NULL));

    Veiculo veiculos[NUM_VEICULOS];
    inicializarVeiculos(veiculos);

    Rotatoria rotatoria;
    inicializarRotatoria(&rotatoria);

    for (int cenario = 0; cenario < NUM_CENARIOS; cenario++) {
        printf("Cenario %d\n", cenario + 1);

        // (1) a situacao atual, com duas pistas em cada via sem semaforo;
        // (2) a proposta Via, com tres pistas em cada via sem semaforo;
        // (3) a proposta Semaforo, com duas pistas em cada via com semaforo;
        // (4) a proposta Via + Semaforo, com tres pistas em cada via com semaforo.

        // Simulacao para cada cenario
        Via* via;
        Veiculo* veiculo;
        double tempoTotalEspera = 0;
        int veiculosProcessados = 0;

        switch(cenario) {
            case 0: //situacao atual
                for (int i = 0; i < NUM_VEICULOS; i++) {
                    adicionarVeiculo(&rotatoria.vias[i % NUM_VIAS], &veiculos[i]);
                }
                
                while (veiculosProcessados < NUM_VEICULOS) {
                    for (int i = 0; i < NUM_VIAS; i++) {
                        via = &rotatoria.vias[i];
                        if (!filaVazia(via)) {
                            veiculo = removerVeiculo(via);

                            // Verifica colisoes
                            verificaColisao(veiculo);

                            // Calculo do tempo de espera
                            double tempoEspera = veiculo->tempoReacao;
                            if (veiculo->tipo == PRIORITARIO) { //caso tenha veiculo prioritario na pista
                                tempoEspera *= 1.5;
                            } else if (veiculo->envolvidoColisao) {//caso tenha veiculo envolvido em colisao na pista
                                tempoEspera *= 1.2;
                            }
                            processaTempo(veiculo, &tempoEspera, &tempoTotalEspera, veiculosProcessados++);
                        }
                    }
                }
                printf("Tempo medio de espera: %.5f\n\n", tempoTotalEspera / NUM_VEICULOS);
            break;
            case 1: //proposta Via
                for (int i = 0; i < NUM_VEICULOS; i++) {
                    adicionarVeiculo(&rotatoria.vias[i % NUM_VIAS], &veiculos[i]);
                }

                tempoTotalEspera = 0;
                veiculosProcessados = 0;

                while (veiculosProcessados < NUM_VEICULOS) {
                    for (int i = 0; i < NUM_VIAS; i++) {
                        via = &rotatoria.vias[i];
                        if (!filaVazia(via)) {
                            veiculo = removerVeiculo(via);

                            // Verifica colisoes
                           verificaColisao(veiculo);

                            // Calculo do tempo de espera
                            double tempoEspera = veiculo->tempoReacao;

                            //caso tenha veiculo envolvido em colisao na pista
                            if (veiculo->envolvidoColisao) {
                                tempoEspera *= 1.2;
                            }

                            processaTempo(veiculo, &tempoEspera, &tempoTotalEspera, veiculosProcessados++);
                        }
                    }
                }
                printf("Tempo medio de espera: %.5f\n\n", tempoTotalEspera / NUM_VEICULOS);
            break;
            case 2: //proposta Semaforo
                for (int i = 0; i < NUM_VEICULOS; i++) {
                    adicionarVeiculo(&rotatoria.vias[i % NUM_VIAS], &veiculos[i]);
                }

                tempoTotalEspera = 0;
                veiculosProcessados = 0;
                while (veiculosProcessados < NUM_VEICULOS) {
                    for (int i = 0; i < NUM_VIAS; i++) {
                        via = &rotatoria.vias[i];
                        if (!filaVazia(via)) {
                            veiculo = removerVeiculo(via);

                            // Calculo do tempo de espera
                            double tempoEspera = veiculo->tempoReacao;

                            //caso tenha veiculo prioritario na pista
                            if (veiculo->tipo == PRIORITARIO) {
                                tempoEspera *= 1.5;
                            }

                            processaTempo(veiculo, &tempoEspera, &tempoTotalEspera, veiculosProcessados++);
                        }
                    }
                }
                printf("Tempo medio de espera: %.5f\n\n", tempoTotalEspera / NUM_VEICULOS);
            break;
            case 3: //proposta Semaforo + via
                for (int i = 0; i < NUM_VEICULOS; i++) {
                    adicionarVeiculo(&rotatoria.vias[i % NUM_VIAS], &veiculos[i]);
                }

                tempoTotalEspera = 0;
                veiculosProcessados = 0;
                while (veiculosProcessados < NUM_VEICULOS) {
                    for (int i = 0; i < NUM_VIAS; i++) {
                        via = &rotatoria.vias[i];
                        if (!filaVazia(via)) {
                            veiculo = removerVeiculo(via);

                            // Calculo do tempo de espera
                            double tempoEspera = veiculo->tempoReacao;

                            processaTempo(veiculo, &tempoEspera, &tempoTotalEspera, veiculosProcessados++);
                        }
                    }
                }
                printf("Tempo medio de espera: %.5f\n\n", tempoTotalEspera / NUM_VEICULOS);
            break;
        }

        // Reseta a rotatoria e as informacoes dos veiculos para a proxima simulacao
        inicializarRotatoria(&rotatoria);
        resetaInformacoesVeiculos(veiculos);
    }

    return 0;
}
