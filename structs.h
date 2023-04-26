// Constantes 

#define NUM_VIAS 3
#define NUM_VEICULOS 500
#define PERC_ONIBUS 0.2
#define PERC_CARROS 0.8
#define PERC_PRIORITARIOS 0.01
#define COLISAO_PROB 0.05
#define NUM_CENARIOS 4

//Structs

typedef enum {
    CARRO, ONIBUS, PRIORITARIO
} TipoVeiculo;

typedef struct {
    TipoVeiculo tipo;
    double tempoReacao;
    double tempoEspera;
    int envolvidoColisao;
} Veiculo;

typedef struct {
    Veiculo* fila[NUM_VEICULOS];
    int inicio, fim;
} Via;

typedef struct {
    Via vias[NUM_VIAS];
} Rotatoria;