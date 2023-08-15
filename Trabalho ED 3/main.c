#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIMENSOES 100
#define MAX_PESO 10

typedef struct {
    char remetente[100];
    char destinatario[100];
    char tipoCliente[20];
    int peso;
    int dimensoes;
} Encomenda;

typedef struct Node {
    Encomenda data;
    struct Node* next;
} Node;

typedef struct {
    Node* frente;
    Node* tras;
} Fila;

typedef struct {
    Encomenda data[MAX_DIMENSOES];
    int topo;
} Pilha;

void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

int filaVazia(Fila* fila) {
    return (fila->frente == NULL);
}

void enfileirar(Fila* fila, Encomenda encomenda) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->data = encomenda;
    novoNo->next = NULL;

    if (filaVazia(fila)) {
        fila->frente = novoNo;
        fila->tras = novoNo;
    } else {
        fila->tras->next = novoNo;
        fila->tras = novoNo;
    }
}

Encomenda desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila esta vazia.\n");
        Encomenda encomendaVazia;
        encomendaVazia.peso = 0;
        encomendaVazia.dimensoes = 0;
        return encomendaVazia;
    } else {
        Node* temp = fila->frente;
        Encomenda encomenda = temp->data;
        fila->frente = fila->frente->next;

        if (fila->frente == NULL)
            fila->tras = NULL;

        free(temp);
        return encomenda;
    }
}

void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return (pilha->topo == -1);
}

void empilhar(Pilha* pilha, Encomenda encomenda) {
    if (pilha->topo == MAX_DIMENSOES - 1) {
        printf("Pilha esta cheia.\n");
        return;
    }

    pilha->topo++;
    pilha->data[pilha->topo] = encomenda;
}

Encomenda desempilhar(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha esta vazia.\n");
        Encomenda encomendaVazia;
        encomendaVazia.peso = 0;
        encomendaVazia.dimensoes = 0;
        return encomendaVazia;
    } else {
        Encomenda encomenda = pilha->data[pilha->topo];
        pilha->topo--;
        return encomenda;
    }
}

int main() {
    srand(time(NULL));
    Fila filaEntrada;
    inicializarFila(&filaEntrada);
    Pilha pilhaListaEspera;
    inicializarPilha(&pilhaListaEspera);
    Fila filaSaida;
    inicializarFila(&filaSaida);
    int pesoMaximo = MAX_PESO;
    int dimensoesMaximas = MAX_DIMENSOES;
    int tempo = 0;
    while (1) {
        tempo++;
        if (tempo % 5 == 0) {
            Encomenda novaEncomenda;
            sprintf(novaEncomenda.remetente, "Remetente %d", tempo);
            sprintf(novaEncomenda.destinatario, "Destinatario %d", tempo);
            sprintf(novaEncomenda.tipoCliente, (tempo % 10 == 0) ? "Preferencial" : "Regular");
            novaEncomenda.peso = rand() % (pesoMaximo + 1);
            novaEncomenda.dimensoes = rand() % (dimensoesMaximas + 1);

            enfileirar(&filaEntrada, novaEncomenda);

            printf("Nova encomenda adicionada na fila de entrada:\n");
            printf("Remetente: %s\n", novaEncomenda.remetente);
            printf("Destinatario: %s\n", novaEncomenda.destinatario);
            printf("Tipo de cliente: %s\n", novaEncomenda.tipoCliente);
            printf("Peso: %d\n", novaEncomenda.peso);
            printf("Dimensoes: %d\n\n", novaEncomenda.dimensoes);
        }
        if (!pilhaVazia(&pilhaListaEspera)) {
            Encomenda encomenda = desempilhar(&pilhaListaEspera);
            if (encomenda.peso <= pesoMaximo && encomenda.dimensoes <= dimensoesMaximas) {
                if (strcmp(encomenda.tipoCliente, "Preferencial") == 0) {
                    enfileirar(&filaSaida, encomenda);
                    printf("Encomenda priorizada para envio:\n");
                } else {
                    enfileirar(&filaSaida, encomenda);
                    printf("Encomenda adicionada na fila de saida:\n");
                }
                printf("Remetente: %s\n", encomenda.remetente);
                printf("Destinatario: %s\n", encomenda.destinatario);
                printf("Tipo de cliente: %s\n", encomenda.tipoCliente);
                printf("Peso: %d\n", encomenda.peso);
                printf("Dimensoes: %d\n\n", encomenda.dimensoes);
            }
        }
        if (!filaVazia(&filaEntrada)) {
            Encomenda encomenda = desenfileirar(&filaEntrada);
            empilhar(&pilhaListaEspera, encomenda);
        }
        if (tempo == 50)
            break;
    }

    return 0;
}
