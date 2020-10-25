#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main(void) {

  setlocale(LC_ALL, "Portuguese");

    int codProd;
    int quantidade;
    float custoTotal_1, custoTotal_2, custoTotal_3, custoTotal_4, custoTotal_5;

    printf("Selecione o código do produto escolhido pelo cliente -- checar PRODUTOS.DAT se necessário: %i \n\n", codProd);
    scanf("%i", &codProd);

    printf("Digite a quantidade escolhida pelo cliente: %i"); 
    scanf("%i", &quantidade);

    custoTotal_1 = 6 * quantidade;
    custoTotal_2 = 9.5 * quantidade;
    custoTotal_3 = 3 * quantidade;
    custoTotal_4 = 6 * quantidade;
    custoTotal_5 = 6 * quantidade;

   
    switch (codProd)
    {
      case 1: 
        printf("O produto escolhido foi o Pão de Batata, com valor de R$6.00, e a quantidade escolhida é igual a %i. O custo total dessa compra é igual a %f", quantidade, custoTotal_1);
      break;

      case 2: 
        printf("O produto escolhido foi o Hot Dog Vegetariano, com valor de R$9.50, e a quantidade escolhida é igual a %i. O custo total dessa compra é igual a %f", quantidade, custoTotal_2);
      break;

      case 3: 
        printf("O produto escolhido foi a Coxinha de Jaca, com valor de R$3.00, e a quantidade escolhida é igual a %i.  O custo total dessa compra é igual a %f", quantidade, custoTotal_3);
      break;

      case 4: 
        printf("O produto escolhido foi a Pastel de Brócolis com queijo, com valor de R$6.00 e a quantidade escolhida é igual a %i.  O custo total dessa compra é igual a %f", quantidade, custoTotal_4);
      break;

      case 5:
        printf("O produto escolhido foi a Pizza de quatro queijos, com valor de R$12.50 e a quantidade escolhida é igual a %i.  O custo total dessa compra é igual a %f", quantidade, custoTotal_5);
      break;

      default:
      break;
    }