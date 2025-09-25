# 🔫🎒 Manual do Usuário - Free Fire: Código da Ilha 🎒🔫

## 📋 Índice
1. [Visão Geral](#visão-geral)
2. [Como Compilar e Executar](#como-compilar-e-executar)
3. [Funcionalidades por Nível](#funcionalidades-por-nível)
4. [Guia de Uso](#guia-de-uso)
5. [Análise de Desempenho](#análise-de-desempenho)
6. [Testes Automatizados](#testes-automatizados)
7. [Estrutura do Código](#estrutura-do-código)

---

## 🎯 Visão Geral

O **Free Fire: Código da Ilha** é um sistema de gerenciamento de inventário inspirado no popular jogo Free Fire. O programa simula o gerenciamento de uma mochila de sobrevivência durante uma fuga de uma ilha, implementando três níveis de complexidade:

- **🟢 Nível Novato**: Operações básicas (adicionar, remover, listar)
- **🟡 Nível Aventureiro**: Busca sequencial por nome
- **🔴 Nível Mestre**: Ordenação por critérios e busca binária

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
- Compilador GCC instalado
- Sistema operacional Windows, Linux ou macOS

### Compilação
```bash
gcc -o FreeFire FreeFire.c
```

### Execução
```bash
# Windows
.\FreeFire.exe

# Linux/macOS
./FreeFire
```

### Testes Automatizados
```bash
gcc -o teste_automatizado teste_automatizado.c
.\teste_automatizado.exe
```

---

## 🎮 Funcionalidades por Nível

### 🟢 Nível Novato
**Funcionalidades Básicas:**
- ➕ **Adicionar Item**: Insere novos componentes na mochila
- ➖ **Remover Item**: Remove componentes pelo nome
- 📋 **Listar Itens**: Exibe todos os componentes em formato tabular

**Características:**
- Capacidade máxima: 10 itens
- Validação de prioridade (1-5)
- Interface visual amigável

### 🟡 Nível Aventureiro
**Funcionalidade Adicional:**
- 🔍 **Busca Sequencial**: Localiza itens pelo nome usando busca linear

**Características:**
- Busca case-sensitive
- Feedback detalhado sobre itens encontrados
- Dicas para itens não encontrados

### 🔴 Nível Mestre
**Funcionalidades Avançadas:**
- 📊 **Ordenação por Critérios**:
  - Por nome (A-Z)
  - Por tipo (A-Z)
  - Por prioridade (Alta → Baixa)
- 🎯 **Busca Binária**: Busca otimizada em dados ordenados por nome
- 📈 **Análise de Desempenho**: Contagem de comparações

**Características:**
- Algoritmo Insertion Sort
- Controle de estado de ordenação
- Comparação de eficiência entre buscas

---

## 📖 Guia de Uso

### Menu Principal
```
🎮 MENU PRINCIPAL:
1️⃣  Adicionar item à mochila
2️⃣  Remover item da mochila
3️⃣  Listar todos os itens
4️⃣  Buscar item por nome (busca sequencial)
5️⃣  Ordenar itens por critério
6️⃣  Buscar item por nome (busca binária)
0️⃣  Sair do jogo
```

### 1. Adicionando Itens
1. Selecione a opção **1**
2. Digite o **nome** do item (ex: "Bandagem")
3. Digite o **tipo** do item (ex: "Cura")
4. Digite a **quantidade** (ex: 5)
5. Digite a **prioridade** de 1 a 5 (ex: 3)

### 2. Removendo Itens
1. Selecione a opção **2**
2. Digite o nome exato do item a ser removido
3. Confirme a remoção

### 3. Listando Itens
- Selecione a opção **3** para ver todos os itens em formato tabular
- Inclui estatísticas do inventário

### 4. Busca Sequencial
1. Selecione a opção **4**
2. Digite o nome do item (case-sensitive)
3. Veja os detalhes se encontrado

### 5. Ordenação
1. Selecione a opção **5**
2. Escolha o critério:
   - **1**: Por nome (A-Z)
   - **2**: Por tipo (A-Z)
   - **3**: Por prioridade (Alta → Baixa)
3. Veja o número de comparações realizadas

### 6. Busca Binária
1. **Importante**: Os itens devem estar ordenados por nome primeiro
2. Selecione a opção **6**
3. O sistema oferece ordenação automática se necessário
4. Digite o nome do item
5. Veja a eficiência da busca (número de passos)

---

## 📊 Análise de Desempenho

### Complexidade dos Algoritmos

| Operação | Complexidade | Observações |
|----------|-------------|-------------|
| Inserção | O(1) | Inserção no final do array |
| Remoção | O(n) | Reorganização do array |
| Busca Sequencial | O(n) | Busca linear |
| Busca Binária | O(log n) | Requer dados ordenados |
| Insertion Sort | O(n²) | Pior caso, O(n) melhor caso |

### Comparação de Eficiência
- **Busca Sequencial**: Até 10 comparações (mochila cheia)
- **Busca Binária**: Máximo 4 comparações (log₂ 10 ≈ 3.32)
- **Vantagem da Busca Binária**: ~60% mais eficiente

---

## 🧪 Testes Automatizados

O sistema inclui um programa de testes abrangente (`teste_automatizado.c`) que valida:

### Testes do Nível Novato
- ✅ Adição de itens
- ✅ Busca de itens existentes
- ✅ Busca de itens inexistentes
- ✅ Integridade dos dados

### Testes do Nível Aventureiro
- ✅ Busca sequencial com múltiplos itens
- ✅ Sensibilidade a maiúsculas/minúsculas
- ✅ Busca com nomes exatos

### Testes do Nível Mestre
- ✅ Ordenação por nome, tipo e prioridade
- ✅ Busca binária após ordenação
- ✅ Busca binária com itens inexistentes
- ✅ Análise de desempenho
- ✅ Controle de estado de ordenação

### Testes de Capacidade
- ✅ Limite máximo de itens
- ✅ Proteção contra overflow

---

## 🏗️ Estrutura do Código

### Estruturas de Dados
```c
typedef struct {
    char nome[MAX_NOME];      // Nome do item
    char tipo[MAX_TIPO];      // Tipo do item
    int quantidade;           // Quantidade
    int prioridade;           // Prioridade (1-5)
} Item;

typedef enum {
    NOME = 1,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;
```

### Variáveis Globais
- `Item mochila[MAX_ITENS]`: Array de itens
- `int numItens`: Contador de itens
- `int comparacoes`: Contador para análise de desempenho
- `bool ordenadaPorNome`: Flag de controle de ordenação

### Funções Principais
- `inserirItem()`: Adiciona item à mochila
- `removerItem()`: Remove item da mochila
- `listarItens()`: Lista todos os itens
- `buscarItemPorNome()`: Busca sequencial
- `insertionSort()`: Algoritmo de ordenação
- `buscaBinariaPorNome()`: Busca binária otimizada

---

## 🎯 Dicas de Uso

### Para Melhor Experiência:
1. **Sempre liste os itens** antes de fazer buscas para conhecer o inventário
2. **Use nomes descritivos** para facilitar a localização
3. **Ordene por nome** antes de usar busca binária para máxima eficiência
4. **Defina prioridades** estrategicamente (5 = muito alta, 1 = muito baixa)
5. **Monitore a capacidade** da mochila (máximo 10 itens)

### Casos de Uso Recomendados:
- **Sobrevivência**: Priorize itens de cura e proteção
- **Combate**: Mantenha armas e munições com alta prioridade
- **Exploração**: Organize por tipo para acesso rápido

---

## 🏆 Conclusão

O **Free Fire: Código da Ilha** demonstra a implementação prática de estruturas de dados e algoritmos fundamentais em C, oferecendo uma experiência interativa e educativa. O sistema é robusto, eficiente e totalmente testado, pronto para uso em cenários de aprendizado ou como base para projetos mais complexos.

**🎮 Boa sorte na ilha, sobrevivente! 🏝️**