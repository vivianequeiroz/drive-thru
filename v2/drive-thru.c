#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int mostraOpcoesDePagamento(){
    return 0;
}

int mostraOfertas(){
    return 0;
}
int selecionaMenu(number) {

 switch(number){
    case 1:
      selecionaLanche();
      break;
    case 2:
      mostraOpcoesDePagamento();
      break;
    case 3:
      mostraOfertas();
      break;
    default:
      printf("Você fechou o sistema");
      break;
  }

return 0;
}



int selecionaLanche()  {
    
    int codigoDoLanche, quantidadeDoLanche;

    printf("Os códigos das opções de lache são: \n\n");
    printf("[1] - Pão de batata \n\n");
    printf("[2] - Hot dog vegetariano \n\n");
    printf("[3] - Coxinha de jaca \n\n");
    printf("[4] - Pastel de brócolis com queijo \n\n");
    printf("[5] - Pizza de 4 queijos \n\n");
    printf("Digite um dos códigos: ");
    scanf("%i", &codigoDoLanche);
    
    printf("Digite a quantidade desejada: ");
    scanf("%i", &quantidadeDoLanche);

    return codigoDoLanche, quantidadeDoLanche;
}






int main(void) {

  setlocale(LC_ALL, "Portuguese");

  int number;


  printf("Digite uma das opções entre [ ] \n\n");
  printf("Para ver o cardapio dia digite: [1] \n\n");
  printf("Para conferir as opções de pagamento digite: [2] \n\n");
  printf("Para conferir a oferta do dia digite: [3] \n\n ");
  printf("Digite uma das opções: ");
  scanf("%i", &number);

  selecionaMenu(number);

}
