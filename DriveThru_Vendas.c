/* Bibliotecas */
#include "libDriveThru.h"

/* Protótipos de funções */
int   main (void);

/* Corpo do programa */
int   main (void)
{	char  esc;
    registro_pedido     rped;
    float               total=0;
    int qtdItens = 0;
    int codUltimoProduto = 0;
    registro_pagamento Rpgto;
    Rpgto.Codpgto = CalculaRegistrosArq(ARQUIVO_DE_PAGAMENTOS)+1;
    
    setlocale (LC_ALL, "");
    do
    { 	do
    	{  system ("color 02");
		   system ("cls");
    	   printf ("\n--- %s ---", NOME_ESTABELECIMENTO);
	       codUltimoProduto=menu_produtos();
	       printf ("\n---------------------");
	       if (codUltimoProduto==0)
	          falha_falta_produtos();
	          
	       /* Solicita um produto cadastrado */
	       printf ("\nQual produto deseja? "); fflush(stdin); scanf("%i", &rped.Prodped.Codprod);    
	       if ( rped.Prodped.Codprod < 1 || rped.Prodped.Codprod > codUltimoProduto )
	       {
			 printf ("\nCódigo de produto inválido!");
	         getch();
	       }
	   } while ( rped.Prodped.Codprod < 1 || rped.Prodped.Codprod > codUltimoProduto );
	   /* Contabiliza quantos itens foram pedidos */
	   qtdItens++;
	   /* Busca os dados do produto selecionado */
	   PesquisaProduto(&rped.Prodped);
	   /* Solicita a quantidade de produto */
	   do
	   {   printf ("\nQuantas unidades de %s deseja? ", rped.Prodped.Nomeprod); 
		   fflush(stdin); scanf("%i", &rped.Qtd);
		   if ( rped.Qtd < 1 )    
	       {
			  printf ("\nQuantidade inválida!");
	          getch();
	       }
	   } while ( rped.Qtd < 1);
	   /* Calcula o valor do item do pedido */
	   rped.Valoritem = rped.Qtd * rped.Prodped.Custoprod;
	   /* Atualiza o total do pedido */
	   total = total + rped.Valoritem;
	   /* Mostra o que foi comprado até o momento */
	   geraTicket(Rpgto.Codpgto, qtdItens, rped, total, '0');
	   system ("TYPE TICKET.TXT");
	   printf ("\n| Total parcial R$ %6.2f |", total);
	   /* Pergunta se deseja mais algum produto */
	   printf ("\n\nDeseja mais algum produto [S=sim]");
	   fflush (stdin); esc = getche();
    }
    while ( esc == 'S' || esc == 's');
    /* Mostra o ticket completo com o total a pagar */
    geraTicket(Rpgto.Codpgto, ++qtdItens, rped, total, '1');
    system ("NOTEPAD TICKET.TXT");
    /* Prepara o arquivo de pagamentos para receber a forma de pagamento */
    Rpgto.Valorpgto = total;
    /* 't' = guarda temporariamente esse registro para preservar o nro do pedido e o total*/
    registraPgto (Rpgto, 't');
    return (0);
}
