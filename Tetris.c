#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#define MAX 5
#define MAX_STACK 3
int ID = 0;
typedef struct Piece
{
    char name;
    int id;
} Piece;

typedef struct Queue
{
    Piece itens[MAX];
    int first;
    int last;
    int total;
} Queue;

typedef struct Stack
{
    Piece itens[MAX_STACK];
    int top;
} Stack;

struct Piece makePiece();

// Queue logic
void removePiece(Queue *q, Piece *p);
void initializeQueue(Queue *q);
int queueIsFull(Queue *q);
int queueIsEmpty(Queue *q);

// stack logic
void initializeStack(Stack *s);
int stackIsFull(Stack *s);
int stackIsEmpty(Stack *s);
void push(Stack *s, Piece new);     // add new element to top
void pop(Stack *s, Piece *removed); // remove top element
void showStack(Stack *s);

// game logic
void gameLogic();
void clearInput();
void clearTerminal();

int main()
{

    srand(time(NULL));

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().

    // struct Piece p = makePiece();
    // printf("Nome: %c, id: %d\n", p.name, p.id);

    //  struct Piece b = makePiece();
    // printf("Nome: %c, id: %d\n", b.name, b.id);

    gameLogic();

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    return 0;
}

struct Piece makePiece()
{
    struct Piece p;

    switch (rand() % 4)
    {
    case 0:
        p.name = 'I';
        break;
    case 1:
        p.name = 'O';
        break;
    case 2:
        p.name = 'T';
        break;
    case 3:
        p.name = 'L';
        break;
    default:
        break;
    }
    ID++;
    p.id = ID;
    return p;
}

void initializeQueue(Queue *q)
{
    q->first = 0;
    q->last = 0;
    q->total = 0;
}

int queueIsFull(Queue *q)
{
    return q->total == MAX;
}

int queueIsEmpty(Queue *q)
{
    return q->total == 0;
}

void insert(Queue *q, Piece p)
{
    if (queueIsFull(q))
    {
        printf("Fila cheia. Nao e possivel inserir.\n");
        return;
    }

    q->itens[q->last] = p;
    q->last = (q->last + 1) % MAX;
    q->total++;
}

void removePiece(Queue *q, Piece *p)
{
    if (queueIsEmpty(q))
    {
        printf("\n\nA lista esta vazia!\n");
        printf("Aperte enter para voltar\n");
        getchar();
        return;
    }

    *p = q->itens[q->first];
    q->first = (q->first + 1) % MAX;
    q->total--;
}

void showQueue(Queue *q)
{
    printf("Fila: ");
    for (int i = 0, idx = q->first; i < q->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%c, %d] ", q->itens[idx].name, q->itens[idx].id);
    }
    printf("\n");
}

int showMenu()
{
    int response;

    printf("---TETRIS---\n\n");
    printf("1. Jogar peca(remover primeira peca)\n");
    printf("2. Inserir nova peca\n");
    printf("3. Reservar peca\n");
    printf("4. Usar peca reservada\n");
    printf("0. Sair\n");
    printf("Digite a opcao: ");
    scanf("%d", &response);
    clearInput();
    return response;
}

void gameLogic()
{
    Queue *q = malloc(sizeof(Queue));
    initializeQueue(q);
    Stack stack;
    initializeStack(&stack);

    int flag = 1;

    while (flag)
    {
        showQueue(q);
        showStack(&stack);
        switch (showMenu())
        {
        case 1:
            // clearTerminal();
            //  printf("jogando uma peca\n");
            Piece p = {'-', -1};
            removePiece(q, &p);
            // if (p.id != -1)
            // {
            //     printf("%c, %d foi removido\n", p.name, p.id);
            // }
            insert(q, makePiece());

            break;

        case 2:

            // printf("Inserindo peca!\n");
            insert(q, makePiece());
            // showQueue(q);
            break;
        // case 2:
        //     printf("Mostrando lista: \n");
        //     break;
        case 3:
            Piece b = {'-', -1};
            removePiece(q, &b);
            if (b.id < 0)
            {
                break;
            }
            
            insert(q, makePiece());

            push(&stack, b);
            break;
        case 4:
            Piece t = {'-', -1};
            pop(&stack, &t);
            break;
        default:
            clearTerminal();
            printf("Saindo....\n");
            flag = 0;
            break;
        }
        clearTerminal();
    }

    free(q);
}

void clearTerminal()
{
    for (int i = 0; i < 30; i++)
    {
        printf("\n");
    }
}

void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void initializeStack(Stack *s)
{
    s->top = -1;
}

int stackIsEmpty(Stack *s)
{
    return s->top == -1;
}

int stackIsFull(Stack *s)
{
    return s->top == MAX_STACK - 1;
}

void push(Stack *s, Piece new)
{
    if (stackIsFull(s))
    {
        printf("\n\nPilha cheia. Nao e possivel inserir.\n");
        printf("Aperte enter para voltar\n");
        getchar();
        return;
    }

    s->top++;
    s->itens[s->top] = new;
}

void pop(Stack *s, Piece *removed)
{
    if (stackIsEmpty(s))
    {
        printf("\n\nPilha vazia. Nao e possivel remover\n");
        printf("Aperte enter para voltar\n");
        getchar();
        return;
    }

    *removed = s->itens[s->top];
    s->top--;
}

void showStack(Stack *s)
{
    printf("Pilha (topo -> base): \n");

    for (int i = s->top; i >= 0; i--)
    {
        printf("[%c, %d] ", s->itens[i].name, s->itens[i].id);
    }
    printf("\n");
}