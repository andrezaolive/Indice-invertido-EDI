/* Trabalho de Estrutura de Dados
Entrada:
Um arquivo no formato .txt, contendo várias strings em várias linhas. (exemplo: um arquivo com frases, cada uma em uma linha diferente)
Discente: Andreza Oliveira Gonçalves 2023010404
*/    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linha e a quantidade de vezes que a palavra aparece nessa linha.
typedef struct ocorrencia {
    int linha;
    int quantidade;
    struct ocorrencia *prox;
} Ocorrencia;

// Palavra do dicionário e contém uma lista de ocorrências.
typedef struct node {
    char *palavra;
    Ocorrencia *ocorrencias;
    struct node *prox;
} Node;

typedef struct {
    Node *inicio;
} Lista;

// Inicializa a lista de palavras
void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
}

// Adiciona ou atualiza uma ocorrência de uma palavra
void adicionarOcorrencia(Ocorrencia **listaOcorrencias, int linha) {
    Ocorrencia *atual = *listaOcorrencias;

    while (atual != NULL) {
        if (atual->linha == linha) {
            atual->quantidade++;
            return;
        }
        atual = atual->prox;
    }
    // Uma nova ocorrência
    Ocorrencia *novaOcorrencia = (Ocorrencia *)malloc(sizeof(Ocorrencia));
    novaOcorrencia->linha = linha;
    novaOcorrencia->quantidade = 1;
    novaOcorrencia->prox = *listaOcorrencias;
    *listaOcorrencias = novaOcorrencia;
}

// Adiciona uma nova palavra ao dicionário ou atualiza suas ocorrências
void inserirLista(Lista *lista, char *palavra, int linha) {
    Node *atual = lista->inicio;
    
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            adicionarOcorrencia(&atual->ocorrencias, linha);
            return;
        }
        atual = atual->prox;
    }
    // Uma nova palavra
    Node *novoNode = (Node *)malloc(sizeof(Node));
        novoNode->palavra = strdup(palavra);
        novoNode->ocorrencias = NULL;
        novoNode->prox = lista->inicio;
        lista->inicio = novoNode;

        adicionarOcorrencia(&novoNode->ocorrencias, linha);
}

// Exibe o dicionário e as informações de ocorrência
void imprimirLista(Lista *lista) {
    Node *atual = lista->inicio;
    
    while (atual != NULL) {
        printf("\n%s: ", atual->palavra);
        Ocorrencia *ocorrenciaAtual = atual->ocorrencias;

        while (ocorrenciaAtual != NULL) {
            printf("(%d | %d) ", ocorrenciaAtual->linha, ocorrenciaAtual->quantidade);
            ocorrenciaAtual = ocorrenciaAtual->prox;
            if (atual->prox != NULL) {
                printf(", ");
            }
        }
        atual = atual->prox;
    }
}

// Libera toda a memória alocada para o dicionário
void liberarLista(Lista *lista) {
    Node *atual = lista->inicio;

    while (atual != NULL) {
        Node *temp = atual;
        Ocorrencia *ocorrenciaAtual = atual->ocorrencias;

        while (ocorrenciaAtual != NULL) {
            Ocorrencia *tempOcorrencia = ocorrenciaAtual;
            ocorrenciaAtual = ocorrenciaAtual->prox;
            free(tempOcorrencia);
        }

        atual = atual->prox;
        free(temp->palavra);
        free(temp);
    }
}

int main() {
    FILE *arquivo;
    char linha[100];
    Lista dicionario;
    int numeroLinha = 0;

    inicializarLista(&dicionario);
    arquivo = fopen("strings.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        exit(1);
    }

    // Processa o arquivo por linhas com 'strtok' para separar as palavras de cada linha.
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *palavra = strtok(linha, " \t\n");
        while (palavra != NULL) {
            inserirLista(&dicionario, palavra, numeroLinha);
            palavra = strtok(NULL, " \t\n");
        }
        numeroLinha++;
    }
    fclose(arquivo);
    
    imprimirLista(&dicionario);
    liberarLista(&dicionario);
    return 0;
}