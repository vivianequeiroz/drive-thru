/**
 * C program to create a file and write data into file.
 */

#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 1000

int main()
{
    /* Variable to store user content */
    char data[DATA_SIZE];

    /* File pointer to hold reference to our file */
    FILE * fPtr;

    /* 
     * Open file in w (read) mode. 
     * "data/file1.txt" is complete path to create file
     */
    fPtr = fopen("produtos.txt", "r");
   

    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Erro ao acessar base de dados.\n");
        exit(EXIT_FAILURE);
    }


    struct produtos {
        int códigoProduto;
        char nomeProduto[200];
        float custoProduto;
    };

    struct produtos baseDeDados[5] = 
    {{1, "Pão de batata", 6.0}, {2, "Hot dog vegetariano", 9.5},
     {3, "Coxinha de jaca", 3.0}, {4, "Pastel de brócolis com queijo", 6.0},
     {5, "Pizza de quatro queijos", 12.5}};

    fprintf("Código do produto: %i -- Nome: %s -- custo do produto: R$ %f \n", baseDeDados[0].códigoProduto,
                                                                               baseDeDados[0].nomeProduto,
                                                                               baseDeDados[0].custoProduto);
                                                                                            

    /* Close file to save file data */
    fclose(fPtr);

    getchar();
    return 0;
}