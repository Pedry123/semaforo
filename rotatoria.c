#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int id;
    char tipo;
    int tempo;
} Veiculo;

typedef struct {
    Veiculo *veiculos;
    int tempo;
    int posicoes;
} Via;


typedef struct {
    int id;
    int tempo;
    int posicoes;
} Rotatoria;

int main() {
    return 0;
}
