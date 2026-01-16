#include "library.h"

// Menu principal
int main() {
    int opcao;
    
    do {
        printf("\n\n=== SISTEMA DE BIBLIOTECA ===\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar todos os livros\n");
        printf("3. Buscar livros\n");
        printf("4. Ordenar e exibir livros\n");
        printf("5. Remover livro\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrar_livro();
                break;
            case 2:
                listar_livros();
                break;
            case 3:
                buscar_livros();
                break;
            case 4:
                ordenar_e_exibir();
                break;
            case 5:
                remover_livro();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 0);
    
    liberar_memoria();
    return 0;
}