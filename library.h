#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Struct base ** Estrutura dos livros
typedef struct s_livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    struct s_livro *prox;
    struct s_livro *ant;
} t_livro;

t_livro* criar_livro(char *titulo, char *autor, int ano);
void cadastrar_livro();
void listar_livros();
void buscar_livros();
void remover_livro();
void ordenar_e_exibir();
void liberar_memoria();

#endif