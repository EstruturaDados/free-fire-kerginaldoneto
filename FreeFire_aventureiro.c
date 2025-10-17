#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Constantes do sistema
#define MAX_ITENS 100
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define RESET "\033[0m"

// ==================== ESTRUTURAS DE DADOS ====================

// Struct que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== VARIÁVEIS GLOBAIS ====================

// Estrutura com VETOR
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Estrutura com LISTA ENCADEADA
No* inicioLista = NULL;
int totalItensLista = 0;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

// Funções auxiliares
void limparBuffer();
void exibirMenuPrincipal();
void exibirMenuOperacoes();
void pausar();

// Funções do VETOR
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// Funções da LISTA ENCADEADA
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();
No* criarNo(Item item);
void liberarLista();

// Função de comparação
void compararDesempenho();

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    int escolhaEstrutura, opcao;
    
    printf("%s", AZUL);
    printf("=======================================================\n");
    printf("  SISTEMA COMPARATIVO DE INVENTÁRIO\n");
    printf("  Vetor vs Lista Encadeada - Análise de Desempenho\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    do {
        exibirMenuPrincipal();
        printf("Escolha a estrutura de dados: ");
        scanf("%d", &escolhaEstrutura);
        limparBuffer();
        printf("\n");
        
        if(escolhaEstrutura == 3) {
            compararDesempenho();
            continue;
        }
        
        if(escolhaEstrutura == 4) {
            printf("%sEncerrando sistema... Boa sorte na zona de perigo!%s\n", VERDE, RESET);
            break;
        }
        
        if(escolhaEstrutura != 1 && escolhaEstrutura != 2) {
            printf("%sOpcao invalida!%s\n\n", VERMELHO, RESET);
            continue;
        }
        
        do {
            exibirMenuOperacoes(escolhaEstrutura);
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            limparBuffer();
            printf("\n");
            
            if(escolhaEstrutura == 1) { // VETOR
                switch(opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                    case 7: break;
                    default: printf("%sOpcao invalida!%s\n\n", VERMELHO, RESET);
                }
            } else { // LISTA ENCADEADA
                switch(opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                    case 5: break;
                    default: printf("%sOpcao invalida!%s\n\n", VERMELHO, RESET);
                }
            }
            
        } while(opcao != 7 && opcao != 5);
        
    } while(escolhaEstrutura != 4);
    
    liberarLista();
    return 0;
}

// ==================== FUNÇÕES DE MENU ====================

void exibirMenuPrincipal() {
    printf("-------------------------------------------------------\n");
    printf("%sESCOLHA A ESTRUTURA DE DADOS:%s\n", AMARELO, RESET);
    printf("-------------------------------------------------------\n");
    printf("1. Mochila com VETOR (Lista Sequencial)\n");
    printf("2. Mochila com LISTA ENCADEADA (Estrutura Dinamica)\n");
    printf("3. Comparar Desempenho das Estruturas\n");
    printf("4. Sair\n");
    printf("-------------------------------------------------------\n");
}

void exibirMenuOperacoes(int estrutura) {
    printf("-------------------------------------------------------\n");
    if(estrutura == 1) {
        printf("%sOPERAÇÕES - VETOR%s\n", VERDE, RESET);
        printf("-------------------------------------------------------\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (Busca Sequencial)\n");
        printf("5. Ordenar itens por nome\n");
        printf("6. Buscar item (Busca Binaria - requer ordenacao)\n");
        printf("7. Voltar ao menu principal\n");
    } else {
        printf("%sOPERAÇÕES - LISTA ENCADEADA%s\n", VERDE, RESET);
        printf("-------------------------------------------------------\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (Busca Sequencial)\n");
        printf("5. Voltar ao menu principal\n");
    }
    printf("-------------------------------------------------------\n");
}

// ==================== FUNÇÕES DO VETOR ====================

void inserirItemVetor() {
    if(totalItensVetor >= MAX_ITENS) {
        printf("%sERRO: Mochila cheia! Limite de %d itens.%s\n\n", VERMELHO, MAX_ITENS, RESET);
        return;
    }
    
    printf("%s=== INSERIR ITEM (VETOR) ===%s\n", AZUL, RESET);
    
    printf("Nome do item: ");
    fgets(mochilaVetor[totalItensVetor].nome, 30, stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(mochilaVetor[totalItensVetor].tipo, 20, stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    limparBuffer();
    
    if(mochilaVetor[totalItensVetor].quantidade <= 0) {
        printf("%sERRO: Quantidade invalida!%s\n\n", VERMELHO, RESET);
        return;
    }
    
    totalItensVetor++;
    printf("%sSUCESSO: Item inserido! Total: %d itens%s\n\n", VERDE, totalItensVetor, RESET);
}

void removerItemVetor() {
    if(totalItensVetor == 0) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    char nomeBusca[30];
    printf("%s=== REMOVER ITEM (VETOR) ===%s\n", AZUL, RESET);
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca e remove o item
    for(int i = 0; i < totalItensVetor; i++) {
        if(strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            // Desloca os elementos posteriores
            for(int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("%sSUCESSO: Item removido! Total: %d itens%s\n\n", VERDE, totalItensVetor, RESET);
            return;
        }
    }
    
    printf("%sERRO: Item nao encontrado!%s\n\n", VERMELHO, RESET);
}

void listarItensVetor() {
    printf("%s=== INVENTÁRIO (VETOR) ===%s\n", AZUL, RESET);
    printf("Total: %d/%d itens\n\n", totalItensVetor, MAX_ITENS);
    
    if(totalItensVetor == 0) {
        printf("Mochila vazia.\n\n");
        return;
    }
    
    for(int i = 0; i < totalItensVetor; i++) {
        printf("[%d] %s | Tipo: %s | Qtd: %d\n", 
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
    printf("\n");
}

void buscarSequencialVetor() {
    if(totalItensVetor == 0) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    char nomeBusca[30];
    comparacoesSequencial = 0;
    
    printf("%s=== BUSCA SEQUENCIAL (VETOR) ===%s\n", AZUL, RESET);
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    clock_t inicio = clock();
    
    // Busca sequencial com contagem de comparações
    for(int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if(strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            
            printf("\n%s[ITEM ENCONTRADO]%s\n", VERDE, RESET);
            printf("Posicao: %d\n", i + 1);
            printf("Nome: %s\n", mochilaVetor[i].nome);
            printf("Tipo: %s\n", mochilaVetor[i].tipo);
            printf("Quantidade: %d\n", mochilaVetor[i].quantidade);
            printf("\n%s[ESTATÍSTICAS]%s\n", AMARELO, RESET);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            printf("Tempo de busca: %.4f ms\n\n", tempo);
            return;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("%sItem nao encontrado!%s\n", VERMELHO, RESET);
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
    printf("Tempo de busca: %.4f ms\n\n", tempo);
}

void ordenarVetor() {
    if(totalItensVetor == 0) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    printf("%s=== ORDENANDO VETOR (BUBBLE SORT) ===%s\n", AZUL, RESET);
    
    clock_t inicio = clock();
    
    // Bubble Sort - ordena por nome
    for(int i = 0; i < totalItensVetor - 1; i++) {
        for(int j = 0; j < totalItensVetor - i - 1; j++) {
            if(strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("%sSUCESSO: Itens ordenados por nome!%s\n", VERDE, RESET);
    printf("Tempo de ordenacao: %.4f ms\n\n", tempo);
    
    listarItensVetor();
}

void buscarBinariaVetor() {
    if(totalItensVetor == 0) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    char nomeBusca[30];
    comparacoesBinaria = 0;
    
    printf("%s=== BUSCA BINÁRIA (VETOR) ===%s\n", AZUL, RESET);
    printf("%sATENCAO: Certifique-se de que o vetor esta ordenado!%s\n", AMARELO, RESET);
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    clock_t inicio = clock();
    
    // Busca binária
    int esquerda = 0, direita = totalItensVetor - 1;
    int encontrado = -1;
    
    while(esquerda <= direita) {
        comparacoesBinaria++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nomeBusca);
        
        if(cmp == 0) {
            encontrado = meio;
            break;
        } else if(cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    if(encontrado != -1) {
        printf("\n%s[ITEM ENCONTRADO]%s\n", VERDE, RESET);
        printf("Posicao: %d\n", encontrado + 1);
        printf("Nome: %s\n", mochilaVetor[encontrado].nome);
        printf("Tipo: %s\n", mochilaVetor[encontrado].tipo);
        printf("Quantidade: %d\n", mochilaVetor[encontrado].quantidade);
        printf("\n%s[ESTATÍSTICAS]%s\n", AMARELO, RESET);
        printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
        printf("Tempo de busca: %.4f ms\n\n", tempo);
    } else {
        printf("%sItem nao encontrado!%s\n", VERMELHO, RESET);
        printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
        printf("Tempo de busca: %.4f ms\n\n", tempo);
    }
}

// ==================== FUNÇÕES DA LISTA ENCADEADA ====================

No* criarNo(Item item) {
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo == NULL) {
        printf("%sERRO: Falha na alocacao de memoria!%s\n", VERMELHO, RESET);
        exit(1);
    }
    novoNo->dados = item;
    novoNo->proximo = NULL;
    return novoNo;
}

void inserirItemLista() {
    Item novoItem;
    
    printf("%s=== INSERIR ITEM (LISTA ENCADEADA) ===%s\n", AZUL, RESET);
    
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';
    
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    if(novoItem.quantidade <= 0) {
        printf("%sERRO: Quantidade invalida!%s\n\n", VERMELHO, RESET);
        return;
    }
    
    // Cria novo nó e insere no início da lista
    No* novoNo = criarNo(novoItem);
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    totalItensLista++;
    
    printf("%sSUCESSO: Item inserido! Total: %d itens%s\n\n", VERDE, totalItensLista, RESET);
}

void removerItemLista() {
    if(inicioLista == NULL) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    char nomeBusca[30];
    printf("%s=== REMOVER ITEM (LISTA ENCADEADA) ===%s\n", AZUL, RESET);
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    No* atual = inicioLista;
    No* anterior = NULL;
    
    // Busca o item na lista
    while(atual != NULL) {
        if(strcmp(atual->dados.nome, nomeBusca) == 0) {
            if(anterior == NULL) {
                // Remove o primeiro nó
                inicioLista = atual->proximo;
            } else {
                // Remove nó do meio ou final
                anterior->proximo = atual->proximo;
            }
            free(atual);
            totalItensLista--;
            printf("%sSUCESSO: Item removido! Total: %d itens%s\n\n", VERDE, totalItensLista, RESET);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("%sERRO: Item nao encontrado!%s\n\n", VERMELHO, RESET);
}

void listarItensLista() {
    printf("%s=== INVENTÁRIO (LISTA ENCADEADA) ===%s\n", AZUL, RESET);
    printf("Total: %d itens\n\n", totalItensLista);
    
    if(inicioLista == NULL) {
        printf("Mochila vazia.\n\n");
        return;
    }
    
    No* atual = inicioLista;
    int posicao = 1;
    
    while(atual != NULL) {
        printf("[%d] %s | Tipo: %s | Qtd: %d\n", 
               posicao, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        posicao++;
    }
    printf("\n");
}

void buscarSequencialLista() {
    if(inicioLista == NULL) {
        printf("%sAVISO: Mochila vazia!%s\n\n", AMARELO, RESET);
        return;
    }
    
    char nomeBusca[30];
    comparacoesSequencial = 0;
    
    printf("%s=== BUSCA SEQUENCIAL (LISTA ENCADEADA) ===%s\n", AZUL, RESET);
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    clock_t inicio = clock();
    
    No* atual = inicioLista;
    int posicao = 1;
    
    while(atual != NULL) {
        comparacoesSequencial++;
        if(strcmp(atual->dados.nome, nomeBusca) == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            
            printf("\n%s[ITEM ENCONTRADO]%s\n", VERDE, RESET);
            printf("Posicao: %d\n", posicao);
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("\n%s[ESTATÍSTICAS]%s\n", AMARELO, RESET);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            printf("Tempo de busca: %.4f ms\n\n", tempo);
            return;
        }
        atual = atual->proximo;
        posicao++;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("%sItem nao encontrado!%s\n", VERMELHO, RESET);
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
    printf("Tempo de busca: %.4f ms\n\n", tempo);
}

void liberarLista() {
    No* atual = inicioLista;
    while(atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicioLista = NULL;
    totalItensLista = 0;
}

// ==================== FUNÇÃO DE COMPARAÇÃO ====================

void compararDesempenho() {
    printf("%s", AZUL);
    printf("=======================================================\n");
    printf("  ANÁLISE COMPARATIVA DE DESEMPENHO\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    printf("%s[VETOR - Lista Sequencial]%s\n", VERDE, RESET);
    printf("Total de itens: %d\n", totalItensVetor);
    printf("%sVantagens:%s\n", AMARELO, RESET);
    printf("  - Acesso direto por indice O(1)\n");
    printf("  - Busca binaria possivel apos ordenacao O(log n)\n");
    printf("  - Uso eficiente de memoria (contiguidade)\n");
    printf("%sDesvantagens:%s\n", AMARELO, RESET);
    printf("  - Tamanho fixo (maximo %d itens)\n", MAX_ITENS);
    printf("  - Remocao requer deslocamento O(n)\n");
    printf("  - Insercao ordenada custosa O(n)\n\n");
    
    printf("%s[LISTA ENCADEADA - Estrutura Dinamica]%s\n", VERDE, RESET);
    printf("Total de itens: %d\n", totalItensLista);
    printf("%sVantagens:%s\n", AMARELO, RESET);
    printf("  - Tamanho dinamico (cresce conforme necessario)\n");
    printf("  - Insercao no inicio O(1)\n");
    printf("  - Remocao eficiente O(1) apos localizar\n");
    printf("%sDesvantagens:%s\n", AMARELO, RESET);
    printf("  - Acesso sequencial obrigatorio O(n)\n");
    printf("  - Busca binaria nao aplicavel\n");
    printf("  - Overhead de memoria (ponteiros)\n\n");
    
    printf("%s[RECOMENDAÇÕES PARA ZONA DE PERIGO]%s\n", VERMELHO, RESET);
    printf("- Use VETOR quando: precisar de buscas rapidas frequentes\n");
    printf("- Use LISTA quando: houver muitas insercoes/remocoes\n");
    printf("- ORDENACAO + BUSCA BINÁRIA: ideal para itens criticos\n\n");
    
    pausar();
}

// ==================== FUNÇÕES AUXILIARES ====================

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("Pressione ENTER para continuar...");
    getchar();
    printf("\n");
}