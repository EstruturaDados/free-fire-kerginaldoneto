#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ==================== CONSTANTES E CORES ====================

#define MAX_COMPONENTES 20
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CIANO "\033[1;36m"
#define RESET "\033[0m"

// ==================== ESTRUTURAS DE DADOS ====================

// Struct que representa um componente da torre de fuga
typedef struct {
    char nome[30];      // Nome do componente (ex: "Chip Central")
    char tipo[20];      // Tipo (ex: "controle", "suporte", "propulsao")
    int prioridade;     // Prioridade de montagem (1 a 10)
} Componente;

// ==================== VARIÁVEIS GLOBAIS ====================

Componente torre[MAX_COMPONENTES];  // Vetor de componentes
int totalComponentes = 0;            // Contador de componentes cadastrados
long comparacoes = 0;                // Contador global de comparações

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

// Funções de entrada e exibição
void cadastrarComponente();
void mostrarComponentes(Componente arr[], int n);
void exibirMenuPrincipal();
void limparBuffer();
void pausar();

// Funções de ordenação
void bubbleSortNome(Componente arr[], int n);
void insertionSortTipo(Componente arr[], int n);
void selectionSortPrioridade(Componente arr[], int n);

// Função de busca
int buscaBinariaPorNome(Componente arr[], int n, char chave[]);

// Funções de análise
void compararAlgoritmos();
void testarBuscaBinaria();
void montarTorre();

// Funções auxiliares
void copiarArray(Componente destino[], Componente origem[], int n);
double medirTempo(void (*algoritmo)(Componente[], int), Componente arr[], int n);

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    int opcao;
    
    printf("%s", CIANO);
    printf("=======================================================\n");
    printf("          DESAFIO FINAL - TORRE DE FUGA\n");
    printf("       Sistema Avançado de Montagem Estratégica\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    printf("%sA última safe zone está se fechando!%s\n", VERMELHO, RESET);
    printf("Monte a torre de resgate com os componentes corretos.\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        printf("\n");
        
        switch(opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                mostrarComponentes(torre, totalComponentes);
                pausar();
                break;
            case 3:
                if(totalComponentes > 0) {
                    comparacoes = 0;
                    double tempo = medirTempo(bubbleSortNome, torre, totalComponentes);
                    printf("%s[BUBBLE SORT - Ordenado por NOME]%s\n", VERDE, RESET);
                    printf("Comparacoes: %ld\n", comparacoes);
                    printf("Tempo: %.6f segundos\n\n", tempo);
                    mostrarComponentes(torre, totalComponentes);
                } else {
                    printf("%sAVISO: Nenhum componente cadastrado!%s\n", AMARELO, RESET);
                }
                pausar();
                break;
            case 4:
                if(totalComponentes > 0) {
                    comparacoes = 0;
                    double tempo = medirTempo(insertionSortTipo, torre, totalComponentes);
                    printf("%s[INSERTION SORT - Ordenado por TIPO]%s\n", VERDE, RESET);
                    printf("Comparacoes: %ld\n", comparacoes);
                    printf("Tempo: %.6f segundos\n\n", tempo);
                    mostrarComponentes(torre, totalComponentes);
                } else {
                    printf("%sAVISO: Nenhum componente cadastrado!%s\n", AMARELO, RESET);
                }
                pausar();
                break;
            case 5:
                if(totalComponentes > 0) {
                    comparacoes = 0;
                    double tempo = medirTempo(selectionSortPrioridade, torre, totalComponentes);
                    printf("%s[SELECTION SORT - Ordenado por PRIORIDADE]%s\n", VERDE, RESET);
                    printf("Comparacoes: %ld\n", comparacoes);
                    printf("Tempo: %.6f segundos\n\n", tempo);
                    mostrarComponentes(torre, totalComponentes);
                } else {
                    printf("%sAVISO: Nenhum componente cadastrado!%s\n", AMARELO, RESET);
                }
                pausar();
                break;
            case 6:
                compararAlgoritmos();
                pausar();
                break;
            case 7:
                testarBuscaBinaria();
                pausar();
                break;
            case 8:
                montarTorre();
                pausar();
                break;
            case 9:
                printf("%sMissao encerrada. Boa sorte na fuga!%s\n", VERDE, RESET);
                break;
            default:
                printf("%sOpcao invalida! Tente novamente.%s\n\n", VERMELHO, RESET);
        }
        
    } while(opcao != 9);
    
    return 0;
}

// ==================== FUNÇÕES DE MENU E ENTRADA ====================

void exibirMenuPrincipal() {
    printf("-------------------------------------------------------\n");
    printf("%sMENU DE OPERAÇÕES%s\n", AMARELO, RESET);
    printf("-------------------------------------------------------\n");
    printf("1. Cadastrar componente\n");
    printf("2. Listar todos os componentes\n");
    printf("3. Ordenar por NOME (Bubble Sort)\n");
    printf("4. Ordenar por TIPO (Insertion Sort)\n");
    printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("6. Comparar desempenho dos algoritmos\n");
    printf("7. Buscar componente-chave (Busca Binaria)\n");
    printf("8. Montar Torre de Fuga (Missao Final)\n");
    printf("9. Sair\n");
    printf("-------------------------------------------------------\n");
}

void cadastrarComponente() {
    if(totalComponentes >= MAX_COMPONENTES) {
        printf("%sERRO: Limite de %d componentes atingido!%s\n\n", VERMELHO, MAX_COMPONENTES, RESET);
        return;
    }
    
    printf("%s=== CADASTRAR NOVO COMPONENTE ===%s\n", AZUL, RESET);
    
    // Lê o nome do componente
    printf("Nome do componente: ");
    fgets(torre[totalComponentes].nome, 30, stdin);
    torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = '\0';
    
    // Lê o tipo
    printf("Tipo (controle/suporte/propulsao/energia): ");
    fgets(torre[totalComponentes].tipo, 20, stdin);
    torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = '\0';
    
    // Lê a prioridade
    printf("Prioridade (1-10): ");
    scanf("%d", &torre[totalComponentes].prioridade);
    limparBuffer();
    
    // Valida prioridade
    if(torre[totalComponentes].prioridade < 1 || torre[totalComponentes].prioridade > 10) {
        printf("%sERRO: Prioridade deve estar entre 1 e 10!%s\n\n", VERMELHO, RESET);
        return;
    }
    
    totalComponentes++;
    printf("%sSUCESSO: Componente cadastrado! Total: %d/%d%s\n\n", VERDE, totalComponentes, MAX_COMPONENTES, RESET);
}

void mostrarComponentes(Componente arr[], int n) {
    printf("%s=== COMPONENTES DA TORRE ===%s\n", AZUL, RESET);
    printf("Total: %d/%d componentes\n\n", n, MAX_COMPONENTES);
    
    if(n == 0) {
        printf("Nenhum componente cadastrado.\n\n");
        return;
    }
    
    printf("%-4s %-25s %-15s %s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < n; i++) {
        printf("%-4d %-25s %-15s %d\n", 
               i + 1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("\n");
}

// ==================== ALGORITMOS DE ORDENAÇÃO ====================

// Bubble Sort - Ordena por NOME (ordem alfabética)
void bubbleSortNome(Componente arr[], int n) {
    Componente temp;
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            // Compara strings e troca se necessário
            if(strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort - Ordena por TIPO (ordem alfabética)
void insertionSortTipo(Componente arr[], int n) {
    Componente chave;
    
    for(int i = 1; i < n; i++) {
        chave = arr[i];
        int j = i - 1;
        
        // Move elementos maiores para frente
        while(j >= 0) {
            comparacoes++;
            if(strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

// Selection Sort - Ordena por PRIORIDADE (ordem crescente)
void selectionSortPrioridade(Componente arr[], int n) {
    int minIdx;
    Componente temp;
    
    for(int i = 0; i < n - 1; i++) {
        minIdx = i;
        
        // Encontra o elemento com menor prioridade
        for(int j = i + 1; j < n; j++) {
            comparacoes++;
            if(arr[j].prioridade < arr[minIdx].prioridade) {
                minIdx = j;
            }
        }
        
        // Troca elementos
        if(minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

// ==================== BUSCA BINÁRIA ====================

// Busca binária por NOME (array deve estar ordenado por nome)
int buscaBinariaPorNome(Componente arr[], int n, char chave[]) {
    int esquerda = 0;
    int direita = n - 1;
    
    comparacoes = 0;
    
    while(esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(arr[meio].nome, chave);
        
        if(cmp == 0) {
            return meio;  // Encontrado
        } else if(cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;  // Não encontrado
}

// ==================== FUNÇÕES DE ANÁLISE ====================

void compararAlgoritmos() {
    if(totalComponentes < 2) {
        printf("%sAVISO: Cadastre pelo menos 2 componentes para comparar!%s\n\n", AMARELO, RESET);
        return;
    }
    
    printf("%s", MAGENTA);
    printf("=======================================================\n");
    printf("     ANÁLISE COMPARATIVA DE ALGORITMOS\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    // Cria cópias do array para testar cada algoritmo
    Componente copia1[MAX_COMPONENTES];
    Componente copia2[MAX_COMPONENTES];
    Componente copia3[MAX_COMPONENTES];
    
    copiarArray(copia1, torre, totalComponentes);
    copiarArray(copia2, torre, totalComponentes);
    copiarArray(copia3, torre, totalComponentes);
    
    // Testa Bubble Sort
    comparacoes = 0;
    double tempo1 = medirTempo(bubbleSortNome, copia1, totalComponentes);
    long comp1 = comparacoes;
    
    // Testa Insertion Sort
    comparacoes = 0;
    double tempo2 = medirTempo(insertionSortTipo, copia2, totalComponentes);
    long comp2 = comparacoes;
    
    // Testa Selection Sort
    comparacoes = 0;
    double tempo3 = medirTempo(selectionSortPrioridade, copia3, totalComponentes);
    long comp3 = comparacoes;
    
    // Exibe resultados
    printf("%s[BUBBLE SORT - Por Nome]%s\n", VERDE, RESET);
    printf("Comparacoes: %ld\n", comp1);
    printf("Tempo: %.6f segundos\n", tempo1);
    printf("Complexidade: O(n²) - Pior caso\n\n");
    
    printf("%s[INSERTION SORT - Por Tipo]%s\n", VERDE, RESET);
    printf("Comparacoes: %ld\n", comp2);
    printf("Tempo: %.6f segundos\n", tempo2);
    printf("Complexidade: O(n²) - Eficiente para dados quase ordenados\n\n");
    
    printf("%s[SELECTION SORT - Por Prioridade]%s\n", VERDE, RESET);
    printf("Comparacoes: %ld\n", comp3);
    printf("Tempo: %.6f segundos\n", tempo3);
    printf("Complexidade: O(n²) - Número fixo de trocas\n\n");
    
    // Determina o mais rápido
    printf("%s[ANÁLISE]%s\n", AMARELO, RESET);
    if(tempo1 <= tempo2 && tempo1 <= tempo3) {
        printf("Mais rapido: BUBBLE SORT\n");
    } else if(tempo2 <= tempo1 && tempo2 <= tempo3) {
        printf("Mais rapido: INSERTION SORT\n");
    } else {
        printf("Mais rapido: SELECTION SORT\n");
    }
    
    if(comp1 <= comp2 && comp1 <= comp3) {
        printf("Menos comparacoes: BUBBLE SORT (%ld)\n", comp1);
    } else if(comp2 <= comp1 && comp2 <= comp3) {
        printf("Menos comparacoes: INSERTION SORT (%ld)\n", comp2);
    } else {
        printf("Menos comparacoes: SELECTION SORT (%ld)\n", comp3);
    }
    printf("\n");
}

void testarBuscaBinaria() {
    if(totalComponentes == 0) {
        printf("%sAVISO: Nenhum componente cadastrado!%s\n\n", AMARELO, RESET);
        return;
    }
    
    printf("%s=== BUSCA BINÁRIA - COMPONENTE-CHAVE ===%s\n", AZUL, RESET);
    printf("%sATENCAO: O array sera ordenado por nome primeiro!%s\n\n", AMARELO, RESET);
    
    // Ordena por nome primeiro
    bubbleSortNome(torre, totalComponentes);
    printf("%sArray ordenado por nome:%s\n", VERDE, RESET);
    mostrarComponentes(torre, totalComponentes);
    
    // Solicita nome do componente-chave
    char chave[30];
    printf("Digite o nome do componente-chave: ");
    fgets(chave, 30, stdin);
    chave[strcspn(chave, "\n")] = '\0';
    
    // Realiza busca binária
    clock_t inicio = clock();
    int resultado = buscaBinariaPorNome(torre, totalComponentes, chave);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n");
    
    if(resultado != -1) {
        printf("%s[COMPONENTE-CHAVE ENCONTRADO]%s\n", VERDE, RESET);
        printf("Posicao: %d\n", resultado + 1);
        printf("Nome: %s\n", torre[resultado].nome);
        printf("Tipo: %s\n", torre[resultado].tipo);
        printf("Prioridade: %d\n", torre[resultado].prioridade);
        printf("\n%s[ESTATÍSTICAS DA BUSCA]%s\n", AMARELO, RESET);
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Tempo: %.6f segundos\n", tempo);
        printf("Complexidade: O(log n)\n");
        printf("\n%sTorre pronta para montagem!%s\n", VERDE, RESET);
    } else {
        printf("%sERRO: Componente-chave nao encontrado!%s\n", VERMELHO, RESET);
        printf("Comparacoes realizadas: %ld\n", comparacoes);
        printf("Tempo: %.6f segundos\n", tempo);
        printf("\n%sA torre nao pode ser montada sem este componente!%s\n", VERMELHO, RESET);
    }
    printf("\n");
}

void montarTorre() {
    if(totalComponentes == 0) {
        printf("%sERRO: Nenhum componente cadastrado!%s\n\n", VERMELHO, RESET);
        return;
    }
    
    printf("%s", CIANO);
    printf("=======================================================\n");
    printf("           MONTAGEM DA TORRE DE FUGA\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    printf("%sEtapa 1: Ordenando componentes por PRIORIDADE...%s\n", AMARELO, RESET);
    selectionSortPrioridade(torre, totalComponentes);
    printf("%sConcluido!%s\n\n", VERDE, RESET);
    
    printf("%s[SEQUÊNCIA DE MONTAGEM]%s\n", AZUL, RESET);
    printf("%-4s %-25s %-15s %s\n", "ORD", "COMPONENTE", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < totalComponentes; i++) {
        printf("%-4d %-25s %-15s %d", 
               i + 1, torre[i].nome, torre[i].tipo, torre[i].prioridade);
        
        // Destaca componentes críticos
        if(torre[i].prioridade >= 8) {
            printf(" %s[CRÍTICO]%s", VERMELHO, RESET);
        } else if(torre[i].prioridade >= 5) {
            printf(" %s[IMPORTANTE]%s", AMARELO, RESET);
        }
        printf("\n");
    }
    
    printf("\n%s", VERDE);
    printf("=======================================================\n");
    printf("  TORRE MONTADA COM SUCESSO!\n");
    printf("  Voce escapou da zona de perigo!\n");
    printf("=======================================================\n");
    printf("%s\n", RESET);
    
    printf("%sEstatisticas da missao:%s\n", AMARELO, RESET);
    printf("- Total de componentes: %d\n", totalComponentes);
    printf("- Componentes criticos: ");
    int criticos = 0;
    for(int i = 0; i < totalComponentes; i++) {
        if(torre[i].prioridade >= 8) criticos++;
    }
    printf("%d\n", criticos);
    printf("- Estrategia: Ordenacao por prioridade\n");
    printf("- Algoritmo: Selection Sort\n\n");
}

// ==================== FUNÇÕES AUXILIARES ====================

void copiarArray(Componente destino[], Componente origem[], int n) {
    for(int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

double medirTempo(void (*algoritmo)(Componente[], int), Componente arr[], int n) {
    clock_t inicio = clock();
    algoritmo(arr, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("Pressione ENTER para continuar...");
    getchar();
    printf("\n");
}