/*
 * =====================================================================================
 * PROGRAMA: Free Fire - Codigo da Ilha (Edicao Mestre)
 * AUTOR: Sistema de Gerenciamento de Mochila
 * DATA: 2024
 * DESCRICAO: Sistema avancado de gerenciamento de inventario para sobrevivencia
 *            Implementa estruturas de dados, algoritmos de busca e ordenacao
 * NIVEL: Mestre - Inclui busca binaria e ordenacao com multiplos criterios
 * =====================================================================================
 */

#include <stdio.h>      // Funcoes de entrada/saida (printf, scanf, etc.)
#include <string.h>     // Funcoes de manipulacao de strings (strcmp, strcspn, etc.)
#include <stdlib.h>     // Funcoes utilitarias (system, etc.)
#include <stdbool.h>    // Tipo booleano (true/false)

/*
 * =====================================================================================
 * CONSTANTES DO SISTEMA
 * =====================================================================================
 */
#define MAX_ITENS 10    // Capacidade maxima da mochila
#define MAX_NOME 50     // Tamanho maximo do nome do item
#define MAX_TIPO 30     // Tamanho maximo do tipo do item

/*
 * =====================================================================================
 * ESTRUTURAS DE DADOS
 * =====================================================================================
 */

/**
 * Estrutura Item: Representa um componente coletado na ilha
 * @nome: Nome identificador do item (ex: "AK-47", "Kit Medico")
 * @tipo: Categoria do item (ex: "Arma", "Medicamento", "Equipamento")
 * @quantidade: Numero de unidades do item na mochila
 * @prioridade: Nivel de importancia (1=Muito Baixa, 2=Baixa, 3=Media, 4=Alta, 5=Muito Alta)
 */
typedef struct {
    char nome[MAX_NOME];        // Nome do item
    char tipo[MAX_TIPO];        // Tipo/categoria do item
    int quantidade;             // Quantidade disponivel
    int prioridade;             // Prioridade de uso (1-5)
} Item;

/**
 * Enumeracao CriterioOrdenacao: Define os criterios disponiveis para ordenacao
 * NOME: Ordenacao alfabetica por nome (A-Z)
 * TIPO: Ordenacao alfabetica por tipo (A-Z)  
 * PRIORIDADE: Ordenacao por prioridade (Alta para Baixa)
 */
typedef enum {
    NOME = 1,           // Criterio: ordenar por nome
    TIPO,               // Criterio: ordenar por tipo
    PRIORIDADE          // Criterio: ordenar por prioridade
} CriterioOrdenacao;

/*
 * =====================================================================================
 * VARIAVEIS GLOBAIS DO SISTEMA
 * =====================================================================================
 */
Item mochila[MAX_ITENS];        // Array principal que armazena os itens da mochila
int numItens = 0;               // Contador atual de itens na mochila
int comparacoes = 0;            // Contador de comparacoes para analise de performance
bool ordenadaPorNome = false;   // Flag que indica se a mochila esta ordenada por nome

/*
 * =====================================================================================
 * DECLARACAO DE FUNCOES (PROTOTIPOS)
 * =====================================================================================
 */
void limparTela();                                          // Limpa a tela do console
void exibirMenu();                                          // Exibe o menu principal do jogo
void inserirItem();                                         // Adiciona um novo item na mochila
void removerItem();                                         // Remove um item especifico da mochila
void listarItens();                                         // Lista todos os itens com formatacao
void buscarItemPorNome();                                   // Busca sequencial por nome
void menuDeOrdenacao();                                     // Menu para escolher criterio de ordenacao
void insertionSort(CriterioOrdenacao criterio);            // Algoritmo de ordenacao por insercao
void buscaBinariaPorNome();                                 // Busca binaria otimizada por nome
int compararItens(Item a, Item b, CriterioOrdenacao criterio); // Funcao auxiliar de comparacao

/*
 * =====================================================================================
 * FUNCAO PRINCIPAL - PONTO DE ENTRADA DO PROGRAMA
 * =====================================================================================
 */

/**
 * Funcao main: Controla o fluxo principal do programa
 * 
 * FUNCIONAMENTO:
 * 1. Exibe mensagem de boas-vindas
 * 2. Loop principal que exibe menu e processa opcoes
 * 3. Switch-case para direcionar para funcoes especificas
 * 4. Controle de pausa entre operacoes
 * 5. Encerramento gracioso do programa
 * 
 * @return: 0 se execucao bem-sucedida
 */
int main() {
    int opcao;  // Variavel para armazenar a opcao escolhida pelo usuario
    
    // Mensagem de boas-vindas ao jogador
    printf("BEM-VINDO AO DESAFIO CODIGO DA ILHA - EDICAO FREE FIRE!\n");
    printf("========================================================\n\n");
    
    // Loop principal do programa - continua ate o usuario escolher sair (opcao 0)
    do {
        exibirMenu();                           // Exibe o menu de opcoes
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);                    // Le a opcao do usuario
        
        // Processa a opcao escolhida
        switch(opcao) {
            case 1:
                inserirItem();                  // Adicionar item a mochila
                break;
            case 2:
                removerItem();                  // Remover item da mochila
                break;
            case 3:
                listarItens();                  // Listar todos os itens
                break;
            case 4:
                buscarItemPorNome();            // Busca sequencial
                break;
            case 5:
                menuDeOrdenacao();              // Menu de ordenacao
                break;
            case 6:
                buscaBinariaPorNome();          // Busca binaria
                break;
            case 0:
                printf("\nObrigado por jogar! Boa sorte na ilha!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        // Pausa para o usuario ler a saida antes de voltar ao menu
        if(opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();  // Limpa o buffer
            getchar();  // Aguarda Enter
        }
        
    } while(opcao != 0);  // Continua ate escolher sair
    
    return 0;  // Indica execucao bem-sucedida
}

/**
 * Função para simular limpeza da tela
 * Utiliza comandos específicos do sistema operacional para limpar o terminal
 * - Windows: comando "cls"
 * - Linux/Unix: comando "clear"
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");      // Comando para Windows
    #else
        system("clear");    // Comando para sistemas Unix/Linux
    #endif
}

/**
 * Função para exibir o menu principal do jogo
 * Mostra informações sobre o estado atual da mochila e as opções disponíveis
 * - Limpa a tela antes de exibir
 * - Mostra status da mochila (quantidade de itens, se está ordenada)
 * - Lista todas as opções do menu numeradas
 */
void exibirMenu() {
    limparTela();
    
    // Cabeçalho do menu com informações da mochila
    printf("MOCHILA DE SOBREVIVENCIA - FREE FIRE\n");
    printf("===============================================\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("===============================================\n\n");
    
    // Opções do menu principal
    printf("MENU PRINCIPAL:\n");
    printf("1  Adicionar item a mochila\n");
    printf("2  Remover item da mochila\n");
    printf("3  Listar todos os itens\n");
    printf("4  Buscar item por nome (busca sequencial)\n");
    printf("5  Ordenar itens por criterio\n");
    printf("6  Buscar item por nome (busca binaria)\n");
    printf("0  Sair do jogo\n");
    printf("===============================================\n");
}

/**
 * Função para comparar dois itens baseado no critério de ordenação
 * @param a Primeiro item a ser comparado
 * @param b Segundo item a ser comparado
 * @param criterio Critério de comparação (NOME, TIPO ou PRIORIDADE)
 * @return Valor negativo se a < b, positivo se a > b, zero se iguais
 * 
 * Incrementa o contador global de comparações para análise de performance
 */
int compararItens(Item a, Item b, CriterioOrdenacao criterio) {
    comparacoes++; // Incrementa contador de comparações para estatísticas
    
    switch(criterio) {
        case NOME:
            // Comparação lexicográfica dos nomes (A-Z)
            return strcmp(a.nome, b.nome);
        case TIPO:
            // Comparação lexicográfica dos tipos (A-Z)
            return strcmp(a.tipo, b.tipo);
        case PRIORIDADE:
            // Ordenação decrescente (prioridade mais alta primeiro)
            // Subtração invertida para ordem decrescente
            return b.prioridade - a.prioridade;
        default:
            return 0;   // Caso padrão: itens considerados iguais
    }
}

// Função de ordenação por inserção (Insertion Sort)
/**
 * Algoritmo de Ordenação por Inserção (Insertion Sort)
 * 
 * FUNCIONAMENTO:
 * 1. Percorre o array da segunda posição até o final
 * 2. Para cada elemento, compara com os anteriores
 * 3. Move os elementos maiores uma posição à direita
 * 4. Insere o elemento na posição correta
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(n) - array já ordenado
 * - Pior caso: O(n²) - array ordenado inversamente
 * - Caso médio: O(n²)
 * 
 * @param criterio Critério de ordenação (NOME, TIPO ou PRIORIDADE)
 */
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0; // Resetar contador para estatísticas
    
    // Percorre o array começando do segundo elemento (índice 1)
    for(int i = 1; i < numItens; i++) {
        Item chave = mochila[i];    // Elemento a ser inserido na posição correta
        int j = i - 1;              // Índice do último elemento da parte ordenada
        
        // Move elementos maiores que a chave uma posição à direita
        // Continua até encontrar a posição correta ou chegar ao início
        while(j >= 0 && compararItens(mochila[j], chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];    // Move elemento para a direita
            j--;                            // Verifica próximo elemento à esquerda
        }
        
        // Insere a chave na posição correta encontrada
        mochila[j + 1] = chave;
    }
    
    // Atualizar flag de ordenação por nome para otimizar busca binária
    if(criterio == NOME) {
        ordenadaPorNome = true;     // Habilita busca binária
    } else {
        ordenadaPorNome = false;    // Desabilita busca binária
    }
}

/**
 * Menu de Ordenação - Interface para escolha do critério de ordenação
 * 
 * FUNCIONALIDADES:
 * - Verifica se há itens para ordenar
 * - Apresenta opções de critérios de ordenação
 * - Executa a ordenação escolhida
 * - Exibe estatísticas de performance (número de comparações)
 * - Atualiza flags de controle do sistema
 */
void menuDeOrdenacao() {
    int opcao;
    
    // Validação: verifica se há itens para ordenar
    if(numItens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para ordenar.\n");
        return;
    }
    
    // Interface do menu de ordenação
    limparTela();
    printf("\nMENU DE ORDENACAO\n");
    printf("=================\n");
    printf("1  Ordenar por Nome (A-Z)\n");
    printf("2  Ordenar por Tipo (A-Z)\n");
    printf("3  Ordenar por Prioridade (Alta -> Baixa)\n");
    printf("0  Voltar ao menu principal\n");
    printf("=================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    // Processamento da opção escolhida
    switch(opcao) {
        case 1:
            // Ordenação alfabética por nome (A-Z)
            insertionSort(NOME);
            ordenadaPorNome = true;     // Habilita busca binária
            printf("Itens ordenados por nome (A-Z)!\n");
            printf("Comparacoes realizadas: %d\n", comparacoes);
            break;
        case 2:
            // Ordenação alfabética por tipo (A-Z)
            insertionSort(TIPO);
            ordenadaPorNome = false;    // Desabilita busca binária
            printf("Itens ordenados por tipo (A-Z)!\n");
            printf("Comparacoes realizadas: %d\n", comparacoes);
            break;
        case 3:
            // Ordenação por prioridade (decrescente: 5->1)
            insertionSort(PRIORIDADE);
            ordenadaPorNome = false;    // Desabilita busca binária
            printf("Itens ordenados por prioridade (Alta -> Baixa)!\n");
            printf("Comparacoes realizadas: %d\n", comparacoes);
            break;
        case 0:
            // Retorna ao menu principal
            printf("\nVoltando ao menu principal...\n");
            return;
            break;
        default:
            // Tratamento de erro para opção inválida
            printf("\nOpcao invalida!\n");
            break;
    }
    
    // Dica para visualizar resultado da ordenação
    printf("\nDica: Use a opcao 3 do menu principal para ver os itens ordenados.\n");
}

// Função de busca binária por nome
/**
 * Algoritmo de Busca Binária por Nome
 * 
 * FUNCIONAMENTO:
 * 1. Verifica se os dados estão ordenados por nome (pré-requisito)
 * 2. Divide o array pela metade a cada iteração
 * 3. Compara o elemento do meio com o valor procurado
 * 4. Elimina metade dos elementos a cada comparação
 * 5. Continua até encontrar o elemento ou esgotar possibilidades
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(1) - elemento está no meio
 * - Pior caso: O(log n) - elemento não existe ou está nas extremidades
 * - Caso médio: O(log n)
 * 
 * PRÉ-REQUISITO: Array deve estar ordenado por nome
 * VANTAGEM: Muito eficiente para grandes volumes de dados
 */
void buscaBinariaPorNome() {
    // Validação: verifica se há itens para buscar
    if(numItens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para buscar.\n");
        return;
    }
    
    // Verificação do pré-requisito: dados ordenados por nome
    if(!ordenadaPorNome) {
        printf("\nATENCAO: BUSCA BINARIA REQUER ORDENACAO!\n");
        printf("===========================================\n");
        printf("A busca binaria so funciona com dados ordenados por nome.\n");
        printf("Dica: Use a opcao 5 para ordenar os itens por nome primeiro.\n");
        printf("\nDeseja ordenar automaticamente por nome agora? (s/n): ");
        
        char resposta;
        scanf(" %c", &resposta);
        
        // Opção de ordenação automática para facilitar o uso
        if(resposta == 's' || resposta == 'S') {
            printf("\nOrdenando por nome...\n");
            insertionSort(NOME);
            printf("Itens ordenados! Prosseguindo com a busca binaria...\n");
        } else {
            printf("\nBusca cancelada. Ordene os itens primeiro.\n");
            return;
        }
    }
    
    char nomeBuscar[MAX_NOME];
    
    // Interface de entrada para o usuário
    printf("\nBUSCA BINARIA POR NOME\n");
    printf("=========================\n");
    printf("Digite o nome do item que deseja buscar: ");
    getchar(); // Limpar buffer do scanf anterior
    fgets(nomeBuscar, MAX_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = 0; // Remove quebra de linha
    
    printf("\nRealizando busca binaria...\n");
    
    // ALGORITMO DE BUSCA BINÁRIA
    int esquerda = 0;           // Índice inicial (limite esquerdo)
    int direita = numItens - 1; // Índice final (limite direito)
    int meio;                   // Índice do elemento central
    bool encontrado = false;    // Flag de controle
    int passos = 0;             // Contador para análise de performance
    
    // Loop principal: continua enquanto há elementos para verificar
    while(esquerda <= direita) {
        passos++;
        meio = (esquerda + direita) / 2;    // Calcula posição central
        int comparacao = strcmp(mochila[meio].nome, nomeBuscar);
        
        // Feedback visual do processo de busca
        printf("   Passo %d: Verificando posicao %d ('%s')\n", 
               passos, meio + 1, mochila[meio].nome);
        
        if(comparacao == 0) {
            // ENCONTRADO: nome do meio é igual ao procurado
            encontrado = true;
            break;
        } else if(comparacao < 0) {
            // Elemento procurado está na metade direita
            esquerda = meio + 1;
        } else {
            // Elemento procurado está na metade esquerda
            direita = meio - 1;
        }
    }
    
    // Processamento do resultado da busca
    if(encontrado) {
        // SUCESSO: item encontrado
        printf("\nITEM ENCONTRADO EM %d PASSOS!\n", passos);
        printf("================================\n");
        printf("Posicao na mochila: %d\n", meio + 1);
        printf("Nome: %s\n", mochila[meio].nome);
        printf("Tipo: %s\n", mochila[meio].tipo);
        printf("Quantidade: %d\n", mochila[meio].quantidade);
        printf("Prioridade: %d", mochila[meio].prioridade);
        
        // Tradução da prioridade numérica para texto
        switch(mochila[meio].prioridade) {
            case 1: printf(" (Muito Baixa)\n"); break;
            case 2: printf(" (Baixa)\n"); break;
            case 3: printf(" (Media)\n"); break;
            case 4: printf(" (Alta)\n"); break;
            case 5: printf(" (Muito Alta)\n"); break;
        }
        
        // Análise de eficiência comparativa
        printf("\nEficiencia: Busca binaria completada em apenas %d passos!\n", passos);
        printf("Comparacao: Uma busca sequencial levaria ate %d passos.\n", numItens);
    } else {
        // FALHA: item não encontrado
        printf("\nITEM NAO ENCONTRADO!\n");
        printf("========================\n");
        printf("O item '%s' nao foi encontrado na mochila.\n", nomeBuscar);
        printf("Busca completada em %d passos.\n", passos);
        printf("Dicas:\n");
        printf("   • Verifique se o nome esta escrito corretamente\n");
        printf("   • Use a opcao 3 para listar todos os itens\n");
        printf("   • Lembre-se que a busca e sensivel a maiusculas/minusculas\n");
    }
}

/**
 * Algoritmo de Busca Sequencial por Nome
 * 
 * FUNCIONAMENTO:
 * 1. Percorre o array do início ao fim
 * 2. Compara cada elemento com o valor procurado
 * 3. Para na primeira ocorrência encontrada
 * 4. Se chegar ao final sem encontrar, retorna "não encontrado"
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(1) - elemento está na primeira posição
 * - Pior caso: O(n) - elemento está na última posição ou não existe
 * - Caso médio: O(n/2)
 * 
 * VANTAGEM: Funciona com dados não ordenados
 * DESVANTAGEM: Ineficiente para grandes volumes de dados
 */
void buscarItemPorNome() {
    // Validação: verifica se há itens para buscar
    if(numItens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para buscar.\n");
        return;
    }
    
    char nomeBuscar[MAX_NOME];
    bool encontrado = false;    // Flag de controle
    int indice = -1;           // Índice do item encontrado
    
    // Interface de entrada para o usuário
    printf("\nBUSCA SEQUENCIAL POR NOME\n");
    printf("============================\n");
    printf("Digite o nome do item que deseja buscar: ");
    getchar(); // Limpar buffer do scanf anterior
    fgets(nomeBuscar, MAX_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = 0; // Remove quebra de linha
    
    printf("\nRealizando busca sequencial...\n");
    
    // ALGORITMO DE BUSCA SEQUENCIAL
    // Percorre todos os elementos do array sequencialmente
    for(int i = 0; i < numItens; i++) {
        // Compara o nome atual com o nome procurado
        if(strcmp(mochila[i].nome, nomeBuscar) == 0) {
            encontrado = true;  // Marca como encontrado
            indice = i;         // Armazena a posição
            break;              // Para a busca (primeira ocorrência)
        }
    }
    
    // Processamento do resultado da busca
    if(encontrado) {
        // SUCESSO: item encontrado
        printf("\nITEM ENCONTRADO!\n");
        printf("===================\n");
        printf("Posicao na mochila: %d\n", indice + 1);
        printf("Nome: %s\n", mochila[indice].nome);
        printf("Tipo: %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
        printf("Prioridade: %d", mochila[indice].prioridade);
        
        // Tradução da prioridade numérica para texto
        switch(mochila[indice].prioridade) {
            case 1: printf(" (Muito Baixa)\n"); break;
            case 2: printf(" (Baixa)\n"); break;
            case 3: printf(" (Media)\n"); break;
            case 4: printf(" (Alta)\n"); break;
            case 5: printf(" (Muito Alta)\n"); break;
        }
        
        printf("\nStatus: Item essencial para sobrevivencia na ilha!\n");
    } else {
        // FALHA: item não encontrado
        printf("\nITEM NAO ENCONTRADO!\n");
        printf("========================\n");
        printf("O item '%s' nao foi encontrado na mochila.\n", nomeBuscar);
        printf("Dicas:\n");
        printf("   • Verifique se o nome esta escrito corretamente\n");
        printf("   • Use a opcao 3 para listar todos os itens\n");
        printf("   • Lembre-se que a busca e sensivel a maiusculas/minusculas\n");
    }
}

// Função para inserir um novo item na mochila
/**
 * Função para inserir um novo item na mochila
 * 
 * VALIDAÇÕES IMPLEMENTADAS:
 * - Verifica se há espaço disponível na mochila (capacidade máxima)
 * - Valida entrada de prioridade (deve estar entre 1-5)
 * - Limpa buffers de entrada para evitar problemas de leitura
 * - Remove caracteres de quebra de linha das strings
 * 
 * TRATAMENTO DE ERROS:
 * - Retorna imediatamente se mochila estiver cheia
 * - Loop de validação para prioridade inválida
 * - Mensagens informativas para orientar o usuário
 * 
 * EFEITOS COLATERAIS:
 * - Incrementa contador global de itens (numItens)
 * - Desabilita flag de ordenação por nome (ordenadaPorNome = false)
 * - Modifica array global da mochila
 */
void inserirItem() {
    // VALIDAÇÃO CRÍTICA: Verificar capacidade da mochila
    if(numItens >= MAX_ITENS) {
        printf("\nMOCHILA CHEIA! Nao e possivel adicionar mais itens.\n");
        printf("Dica: Remova alguns itens antes de adicionar novos.\n");
        return;  // Saída antecipada para evitar overflow
    }
    
    Item novoItem;  // Estrutura temporária para o novo item
    
    // Interface de entrada de dados
    printf("\nADICIONANDO NOVO ITEM A MOCHILA\n");
    printf("==================================\n");
    
    // ENTRADA DE DADOS COM TRATAMENTO DE BUFFER
    printf("Nome do item: ");
    getchar(); // CRÍTICO: Limpar buffer residual do scanf anterior
    fgets(novoItem.nome, MAX_NOME, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove quebra de linha
    
    printf("Tipo do item: ");
    fgets(novoItem.tipo, MAX_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0; // Remove quebra de linha
    
    // ENTRADA NUMÉRICA: Quantidade (sem validação específica - aceita qualquer inteiro)
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    // VALIDAÇÃO RIGOROSA: Prioridade deve estar no intervalo [1,5]
    do {
        printf("Prioridade (1-5, sendo 5 a mais alta): ");
        scanf("%d", &novoItem.prioridade);
        
        // Verificação de intervalo válido
        if(novoItem.prioridade < 1 || novoItem.prioridade > 5) {
            printf("Prioridade invalida! Digite um valor entre 1 e 5.\n");
        }
    } while(novoItem.prioridade < 1 || novoItem.prioridade > 5);
    
    // INSERÇÃO SEGURA: Adicionar item na próxima posição disponível
    mochila[numItens] = novoItem;   // Copia estrutura completa
    numItens++;                     // Incrementa contador
    
    // ATUALIZAÇÃO DE ESTADO: Mochila não está mais ordenada por nome
    ordenadaPorNome = false;        // Desabilita busca binária
    
    // FEEDBACK DE SUCESSO
    printf("\nItem '%s' adicionado com sucesso!\n", novoItem.nome);
    printf("Total de itens na mochila: %d/%d\n", numItens, MAX_ITENS);
}

/**
 * Função para remover um item específico da mochila
 * 
 * VALIDAÇÕES IMPLEMENTADAS:
 * - Verifica se há itens para remover (mochila não vazia)
 * - Busca sequencial para localizar o item
 * - Confirmação visual antes da remoção
 * 
 * TRATAMENTO DE ERROS:
 * - Retorna imediatamente se mochila estiver vazia
 * - Informa se item não foi encontrado
 * - Fornece dicas para correção de problemas
 * 
 * ALGORITMO DE REMOÇÃO:
 * - Busca linear para encontrar o item
 * - Reorganização do array (shift left) para manter contiguidade
 * - Atualização do contador de itens
 */
void removerItem() {
    // VALIDAÇÃO INICIAL: Verificar se há itens para remover
    if(numItens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para remover.\n");
        return;  // Saída antecipada - operação impossível
    }
    
    char nomeRemover[MAX_NOME];     // Buffer para nome do item a remover
    bool encontrado = false;        // Flag de controle da busca
    int indice = -1;               // Índice do item encontrado (-1 = não encontrado)
    
    // Interface de entrada
    printf("\nREMOVENDO ITEM DA MOCHILA\n");
    printf("=============================\n");
    printf("Digite o nome do item a ser removido: ");
    
    // ENTRADA DE DADOS COM LIMPEZA DE BUFFER
    getchar(); // Limpar buffer residual
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0; // Remove quebra de linha
    
    // ALGORITMO DE BUSCA SEQUENCIAL
    // Percorre todo o array procurando pelo nome exato
    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = true;      // Marca como encontrado
            indice = i;            // Armazena posição
            break;                 // Para a busca (primeira ocorrência)
        }
    }
    
    // PROCESSAMENTO DO RESULTADO DA BUSCA
    if(encontrado) {
        // CONFIRMAÇÃO VISUAL: Mostra dados do item antes de remover
        printf("\nItem encontrado:\n");
        printf("   Nome: %s\n", mochila[indice].nome);
        printf("   Tipo: %s\n", mochila[indice].tipo);
        printf("   Quantidade: %d\n", mochila[indice].quantidade);
        printf("   Prioridade: %d\n", mochila[indice].prioridade);
        
        // ALGORITMO DE REORGANIZAÇÃO (SHIFT LEFT)
        // Move todos os elementos após o removido uma posição à esquerda
        // Isso mantém a contiguidade do array sem "buracos"
        for(int i = indice; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];    // Copia elemento seguinte
        }
        
        // ATUALIZAÇÃO DE ESTADO
        numItens--;     // Decrementa contador de itens
        
        // FEEDBACK DE SUCESSO
        printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
        printf("Total de itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    } else {
        // TRATAMENTO DE ERRO: Item não encontrado
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeRemover);
        printf("Dica: Verifique se o nome esta correto ou liste os itens primeiro.\n");
    }
}

/**
 * Função para listar todos os itens da mochila com formatação tabular
 * 
 * VALIDAÇÕES IMPLEMENTADAS:
 * - Verifica se há itens para exibir
 * - Calcula estatísticas em tempo real
 * 
 * FUNCIONALIDADES:
 * - Exibição tabular formatada com bordas
 * - Cálculo automático de estatísticas
 * - Informações de capacidade e utilização
 * 
 * TRATAMENTO DE CASOS ESPECIAIS:
 * - Mochila vazia: mensagem informativa
 * - Formatação consistente independente do conteúdo
 */
void listarItens() {
    // VALIDAÇÃO: Verificar se há itens para exibir
    if(numItens == 0) {
        printf("\nMOCHILA VAZIA!\n");
        printf("Adicione alguns itens para comecar sua aventura na ilha.\n");
        return;  // Saída antecipada - nada para mostrar
    }
    
    // CABEÇALHO DA LISTAGEM
    printf("\nINVENTARIO DA MOCHILA\n");
    printf("========================\n");
    printf("Total de itens: %d/%d\n\n", numItens, MAX_ITENS);
    
    // TABELA FORMATADA COM BORDAS UNICODE
    // Utiliza caracteres especiais para criar uma tabela visualmente atrativa
    printf("┌─────┬─────────────────────┬─────────────────┬──────────┬───────────┐\n");
    printf("│ No  │        Nome         │      Tipo       │ Qtd.     │ Prior.    │\n");
    printf("├─────┼─────────────────────┼─────────────────┼──────────┼───────────┤\n");
    
    // LOOP DE EXIBIÇÃO: Percorre todos os itens
    for(int i = 0; i < numItens; i++) {
        // Formatação com largura fixa para alinhamento
        printf("│ %-3d │ %-19s │ %-15s │ %-8d │ %-9d │\n", 
               i + 1,                   // Número sequencial (1-based)
               mochila[i].nome,         // Nome do item
               mochila[i].tipo,         // Tipo/categoria
               mochila[i].quantidade,   // Quantidade
               mochila[i].prioridade);  // Prioridade
    }
    
    // FECHAMENTO DA TABELA
    printf("└─────┴─────────────────────┴─────────────────┴──────────┴───────────┘\n");
    
    // CÁLCULO DE ESTATÍSTICAS EM TEMPO REAL
    int totalQuantidade = 0;    // Soma de todas as quantidades
    int prioridadeAlta = 0;     // Contador de itens de alta prioridade
    
    // Loop para calcular estatísticas
    for(int i = 0; i < numItens; i++) {
        totalQuantidade += mochila[i].quantidade;
        
        // Considera alta prioridade: valores 4 e 5
        if(mochila[i].prioridade >= 4) {
            prioridadeAlta++;
        }
    }
    
    // EXIBIÇÃO DE ESTATÍSTICAS CALCULADAS
    printf("\nESTATISTICAS:\n");
    printf("   • Total de unidades: %d\n", totalQuantidade);
    printf("   • Itens de alta prioridade (4-5): %d\n", prioridadeAlta);
    printf("   • Espaco disponivel: %d slots\n", MAX_ITENS - numItens);
}
