#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da struct para representar uma peça
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único da peça
} Peca;

// Constantes para a fila circular
#define MAX_QUEUE 10  // Tamanho máximo da fila (para permitir enqueues)

// Variáveis globais para a fila circular
Peca queue[MAX_QUEUE];  // Array para armazenar as peças
int front = 0;          // Índice do início da fila
int rear = 0;           // Índice do final da fila
int count = 0;          // Número de elementos na fila
int next_id = 0;        // Contador para gerar IDs únicos

// Array de tipos de peças para geração aleatória
char tipos[4] = {'I', 'O', 'T', 'L'};

// Função para gerar uma nova peça automaticamente
Peca gerarPeca() {
    Peca novaPeca;
    novaPeca.nome = tipos[rand() % 4];  // Seleciona um tipo aleatório
    novaPeca.id = next_id++;             // Atribui um ID único e incrementa o contador
    return novaPeca;
}

// Função para inserir uma peça no final da fila (enqueue)
void enqueue(Peca p) {
    if (count < MAX_QUEUE) {
        queue[rear] = p;                 // Insere a peça na posição rear
        rear = (rear + 1) % MAX_QUEUE;   // Atualiza rear de forma circular
        count++;                         // Incrementa o contador de elementos
    } else {
        printf("Erro: Fila cheia, não é possível inserir nova peça.\n");
    }
}

// Função para remover uma peça do início da fila (dequeue)
void dequeue() {
    if (count > 0) {
        // Remove a peça do front (não precisa retornar, apenas remove)
        front = (front + 1) % MAX_QUEUE;  // Atualiza front de forma circular
        count--;                          // Decrementa o contador de elementos
    } else {
        printf("Erro: Fila vazia, não é possível jogar peça.\n");
    }
}

// Função para exibir o estado atual da fila
void displayQueue() {
    printf("Fila de peças\n");
    if (count == 0) {
        printf("(Fila vazia)\n");
        return;
    }
    // Percorre a fila de front até rear de forma circular
    for (int i = front; ; i = (i + 1) % MAX_QUEUE) {
        printf("[%c %d] ", queue[i].nome, queue[i].id);
        if (i == rear - 1 || (rear == 0 && i == MAX_QUEUE - 1)) break;  // Para quando chegar ao rear
    }
    printf("\n");
}

// Função para inicializar a fila com um número fixo de peças
void initQueue(int num) {
    for (int i = 0; i < num; i++) {
        enqueue(gerarPeca());  // Gera e insere peças na fila
    }
}

// Função principal
int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    initQueue(5);       // Inicializa a fila com 5 peças

    int opcao;
    while (1) {
        displayQueue();  // Exibe o estado da fila antes do menu
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();  // Remove a peça da frente
                break;
            case 2:
                if (count < MAX_QUEUE) {
                    enqueue(gerarPeca());  // Insere uma nova peça gerada automaticamente
                } else {
                    printf("Fila cheia, não é possível inserir nova peça.\n");
                }
                break;
            case 0:
                printf("Saindo do programa.\n");
                exit(0);  // Encerra o programa
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
