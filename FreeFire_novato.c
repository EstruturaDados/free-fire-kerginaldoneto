#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da capacidade máxima da mochila
#define MAX_ITENS 10

// Struct que representa um item do inventário
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item no inventário
} Item;

// Variáveis globais para controle do inventário
Item mochila[MAX_ITENS];  // Vetor que armazena os itens
int totalItens = 0;       // Contador de itens cadastrados

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void exibirMenu();
void limparBuffer();

// Função principal - ponto de entrada do programa
int main() {
    int opcao;
    
    printf("==============================================\n");
    printf("   SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT\n");
    printf("==============================================\n\n");
    
    // Loop principal do menu
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        // Processa a opção escolhida pelo usuário
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Encerrando o sistema... Boa sorte na missao!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n\n");
        }
        
    } while(opcao != 5);
    
    return 0;
}

// Função que exibe o menu principal
void exibirMenu() {
    printf("----------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("----------------------------------------------\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item\n");
    printf("5. Sair\n");
    printf("----------------------------------------------\n");
}

// Função para inserir um novo item na mochila
void inserirItem() {
    // Verifica se ainda há espaço na mochila
    if(totalItens >= MAX_ITENS) {
        printf("ERRO: Mochila cheia! Limite de %d itens atingido.\n\n", MAX_ITENS);
        return;
    }
    
    printf("=== CADASTRAR NOVO ITEM ===\n");
    
    // Lê o nome do item
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';
    
    // Lê o tipo do item
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';
    
    // Lê a quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    // Valida se a quantidade é positiva
    if(mochila[totalItens].quantidade <= 0) {
        printf("ERRO: Quantidade deve ser maior que zero!\n\n");
        return;
    }
    
    totalItens++;
    printf("\nSUCESSO: Item cadastrado com sucesso!\n\n");
    
    // Lista os itens após a inserção
    listarItens();
}

// Função para remover um item da mochila
void removerItem() {
    char nomeBusca[30];
    int i, encontrado = 0;
    
    // Verifica se há itens na mochila
    if(totalItens == 0) {
        printf("AVISO: Mochila vazia! Nenhum item para remover.\n\n");
        return;
    }
    
    printf("=== REMOVER ITEM ===\n");
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial pelo item
    for(i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Move todos os itens posteriores uma posição para trás
            for(int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            totalItens--;
            printf("\nSUCESSO: Item '%s' removido com sucesso!\n\n", nomeBusca);
            break;
        }
    }
    
    if(!encontrado) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n\n", nomeBusca);
    }
    
    // Lista os itens após a remoção
    listarItens();
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("==============================================\n");
    printf("   INVENTÁRIO DA MOCHILA\n");
    printf("==============================================\n");
    
    // Verifica se há itens na mochila
    if(totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("Total de itens: %d/%d\n\n", totalItens, MAX_ITENS);
        
        // Percorre e exibe todos os itens
        for(int i = 0; i < totalItens; i++) {
            printf("[%d] Nome: %s\n", i + 1, mochila[i].nome);
            printf("    Tipo: %s\n", mochila[i].tipo);
            printf("    Quantidade: %d\n", mochila[i].quantidade);
            printf("----------------------------------------------\n");
        }
    }
    printf("\n");
}

// Função de busca sequencial por nome
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;
    
    // Verifica se há itens na mochila
    if(totalItens == 0) {
        printf("AVISO: Mochila vazia! Nenhum item para buscar.\n\n");
        return;
    }
    
    printf("=== BUSCAR ITEM ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\n");
    
    // Realiza busca sequencial no vetor
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("=== ITEM ENCONTRADO ===\n");
            printf("Posicao: %d\n", i + 1);
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("========================\n\n");
            break;
        }
    }
    
    if(!encontrado) {
        printf("ERRO: Item '%s' nao encontrado na mochila.\n\n", nomeBusca);
    }
}

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}