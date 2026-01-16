#include "library.h"

// Cabeça da lista
t_livro *cabeca = NULL;
int proximo_id = 1;

// Função para criar um novo livro
t_livro* criar_livro(char *titulo, char *autor, int ano) {
    t_livro *novo = (t_livro*)malloc(sizeof(t_livro));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }
    
    novo->id = proximo_id++;
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    novo->prox = NULL;
    novo->ant = NULL;
    
    return novo;
}

// Função para cadastrar livro
void cadastrar_livro() {
    char titulo[100], autor[100];
    int ano;
    
    printf("\n=== CADASTRAR LIVRO ===\n");
    printf("Titulo: ");
    getchar(); // Limpa buffer
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = 0; // Remove \n
    
    printf("Autor: ");
    fgets(autor, 100, stdin);
    autor[strcspn(autor, "\n")] = 0;
    
    printf("Ano: ");
    scanf("%d", &ano);
    
    t_livro *novo = criar_livro(titulo, autor, ano);
    if (novo == NULL) return;
    
    // Inserir no início da lista
    if (cabeca == NULL) {
        cabeca = novo;
    } else {
        novo->prox = cabeca;
        cabeca->ant = novo;
        cabeca = novo;
    }
    
    printf("\nLivro cadastrado com sucesso! ID: %d\n", novo->id);
}

// Função para listar todos os livros
void listar_livros() {
    if (cabeca == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE LIVROS ===\n");
    t_livro *atual = cabeca;
    while (atual != NULL) {
        printf("\nID: %d\n", atual->id);
        printf("Titulo: %s\n", atual->titulo);
        printf("Autor: %s\n", atual->autor);
        printf("Ano: %d\n", atual->ano);
        printf("------------------------\n");
        atual = atual->prox;
    }
}

// Função de busca
void buscar_livros() {
    if (cabeca == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }
    
    int opcao;
    printf("\n=== BUSCAR LIVROS ===\n");
    printf("1. Buscar por titulo\n");
    printf("2. Buscar por autor\n");
    printf("3. Buscar por ano\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    char busca[100];
    int ano_busca;
    int encontrou = 0;
    
    t_livro *atual = cabeca;
    
    switch(opcao) {
        case 1:
            printf("Digite o titulo: ");
            getchar();
            fgets(busca, 100, stdin);
            busca[strcspn(busca, "\n")] = 0;
            
            printf("\n=== RESULTADOS ===\n");
            while (atual != NULL) {
                if (strstr(atual->titulo, busca) != NULL) {
                    printf("\nID: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
                        atual->id, atual->titulo, atual->autor, atual->ano);
                    encontrou = 1;
                }
                atual = atual->prox;
            }
            break;
            
        case 2:
            printf("Digite o autor: ");
            getchar();
            fgets(busca, 100, stdin);
            busca[strcspn(busca, "\n")] = 0;
            
            printf("\n=== RESULTADOS ===\n");
            while (atual != NULL) {
                if (strstr(atual->autor, busca) != NULL) {
                    printf("\nID: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
                        atual->id, atual->titulo, atual->autor, atual->ano);
                    encontrou = 1;
                }
                atual = atual->prox;
            }
            break;
            
        case 3:
            printf("Digite o ano: ");
            scanf("%d", &ano_busca);
            
            printf("\n=== RESULTADOS ===\n");
            while (atual != NULL) {
                if (atual->ano == ano_busca) {
                    printf("\nID: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
                        atual->id, atual->titulo, atual->autor, atual->ano);
                    encontrou = 1;
                }
                atual = atual->prox;
            }
            break;
            
        default:
            printf("Opcao invalida!\n");
            return;
    }
    
    if (!encontrou) {
        printf("Nenhum livro encontrado.\n");
    }
}

// Função para remover livro
void remover_livro() {
    if (cabeca == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }
    
    int id_remover;
    printf("\n=== REMOVER LIVRO ===\n");
    printf("Digite o ID do livro a remover: ");
    scanf("%d", &id_remover);
    
    t_livro *atual = cabeca;
    
    // Procurar o livro
    while (atual != NULL && atual->id != id_remover) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("\nLivro com ID %d nao encontrado!\n", id_remover);
        return;
    }
    
    // Remover o livro da lista
    if (atual->ant == NULL) {
        // É o primeiro da lista
        cabeca = atual->prox;
        if (cabeca != NULL) {
            cabeca->ant = NULL;
        }
    } else if (atual->prox == NULL) {
        // É o último da lista
        atual->ant->prox = NULL;
    } else {
        // Está no meio
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }
    
    printf("\nLivro '%s' removido com sucesso!\n", atual->titulo);
    free(atual);
}

// Função para ordenar e exibir
void ordenar_e_exibir() {
    if (cabeca == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }
    
    int opcao;
    printf("\n=== ORDENAR LIVROS ===\n");
    printf("1. Ordenar por titulo\n");
    printf("2. Ordenar por autor\n");
    printf("3. Ordenar por ano\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    // Contar livros
    int total = 0;
    t_livro *aux = cabeca;
    while (aux != NULL) {
        total++;
        aux = aux->prox;
    }
    
    // Criar array temporário
    t_livro **array = (t_livro**)malloc(total * sizeof(t_livro*));
    aux = cabeca;
    for (int i = 0; i < total; i++) {
        array[i] = aux;
        aux = aux->prox;
    }
    
    // Bubble sort simples
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            int trocar = 0;
            
            switch(opcao) {
                case 1:
                    if (strcmp(array[j]->titulo, array[j+1]->titulo) > 0)
                        trocar = 1;
                    break;
                case 2:
                    if (strcmp(array[j]->autor, array[j+1]->autor) > 0)
                        trocar = 1;
                    break;
                case 3:
                    if (array[j]->ano > array[j+1]->ano)
                        trocar = 1;
                    break;
            }
            
            if (trocar) {
                t_livro *temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    
    // Exibir ordenado
    printf("\n=== LIVROS ORDENADOS ===\n");
    for (int i = 0; i < total; i++) {
        printf("\nID: %d\n", array[i]->id);
        printf("Titulo: %s\n", array[i]->titulo);
        printf("Autor: %s\n", array[i]->autor);
        printf("Ano: %d\n", array[i]->ano);
        printf("------------------------\n");
    }
    
    free(array);
}

// Função para liberar memória
void liberar_memoria() {
    t_livro *atual = cabeca;
    while (atual != NULL) {
        t_livro *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}