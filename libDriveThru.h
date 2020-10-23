#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/* Constantes  */
#define  TAMSTR  	50
#define  TAMCARTAO	16
#define  ARQUIVO_DE_PRODUTOS 		"PRODUTOS.DAT"
#define  ARQUIVO_DE_PAGAMENTOS 	    "PAGAMENTOS.DAT"
#define  ARQUIVO_DE_CARTOES 		"CARTOES.DAT"
#define  ARQUIVO_TICKET      		"TICKET.TXT"
#define  ULTIMO_PEDIDO              "ULTIMOPGTO.DAT"
#define  NOME_ESTABELECIMENTO       "DRIVE THRU DO MICKEY & DONALDS"

/* Tipos de dados pré-definidos */

/*------------------Lay-out do registro de produtos------------------
+-------------------------------------------------------------------+
|		Codprod					|	Nomeprod  	|	 Custoprod		|
+-------------------------------------------------------------------+
|	Código do produto			| 	 Nome do  	|    Valor unitário |
| chave primária (autonumérico)	|    produto  	|	   do produto	|
+-------------------------------------------------------------------+
|		inteiro 				|    string		|		float		|
+-------------------------------------------------------------------+
*/
typedef struct
{
   	int  	Codprod;
   	char 	Nomeprod[TAMSTR];
   	float	Custoprod;
}
registro_produto;

/*------------------Lay-out do registro de pedidos------------------
+-------------------------------------------------------------------+
|  Codprod	|	Nomeprod  	|  Custoprod	|  Qtd  |    Valoritem  |
+-------------------------------------------------------------------+
*/
typedef struct
{
	registro_produto	Prodped;
	int					Qtd;
	float				Valoritem;
}
registro_pedido;

/*-------Lay-out do registro de pagamentos------
+----------------------------------------------+
|     Codpgto	 |	Formapgto  	|   Valorpgto  |
+----------------------------------------------+
|    Código do   |	 Forma de  	|  Valor total |
|    pagamento   |   pagamento  |  do pedido   |
| (autonumérico) |        	    |	           |
+----------------------------------------------+
|     inteiro    |   string	    |	 float     |
+----------------------------------------------+
*/
typedef struct
{
	int		Codpgto;
	char	Formapgto[TAMSTR];
	float	Valorpgto;
}
registro_pagamento;

/* Lay-out do registro de cartões
+-------------------------------+
|     Codpgto	 |	Numcartao  	|
+-------------------------------+
|    Código do   |	 Número do 	|
|    pedido que  |   cartão     |
| foi pago com o |        	    |
|    cartão      |              |
+-------------------------------+
|     inteiro    |   string	    |	
+-------------------------------+
*/
typedef struct
{
    int		Codpgto;
    char	Numcartao[TAMCARTAO];
}
registro_cartao;

/* Protótipos de funções */
void  falha_abrir_arquivo  (void);
void  falha_gravar_arquivo (void);
void  falha_ler_arquivo    (void);
void  falha_falta_produtos (void);
void  relatorio_produtos   (void);
void  relatorio_pagamentos (void);
int   menu_produtos		   (void);
void  falha_abrir_arquivo_pedidos     (void);	   
void  falha_gravar_arquivo_pagamentos (void);
void  falha_ler_arquivo_pagamentos    (void);
void  falha_abrir_arquivo_cartoes     (void);
void  falha_gravar_arquivo_cartoes    (void);
void  falha_abrir_arquivo_cartoes     (void);
void  falha_ler_arquivo_cartoes       (void);

void  grava_produto	   	(registro_produto R);
void  sucesso_gravacao 	(registro_produto R);
char  confirmar 		(registro_produto R);
void  descartar 		(registro_produto R);
void  PesquisaProduto   (registro_produto * R);
void  PesquisaPagamento (registro_pagamento * R);

void  gravaCartao       (registro_cartao R);
void  sucesso_gravacao_cartao (registro_cartao R);

void  pagamento_bemsucedido (registro_pagamento Rpgto);

registro_produto    captura_produto (void);

void cadastra_produtos_default (void);

void geraTicket(int nroPedido, int qtd, registro_pedido rped, float total, char flag);

int CalculaRegistrosArq  (char *nomeArq);

void registraPgto (registro_pagamento Rpgto, char flag);

void resgataTemp (registro_pagamento *Rpgto);

/* Construção das funções */
void  falha_falta_produtos (void)
{
	system ("cls");
	printf ("FALHA: NÃO HÁ PRODUTOS CADASTRADOS EM [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);	
}

void  falha_abrir_arquivo (void)
{
	system ("cls");
	printf ("FALHA AO ABRIR [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void  falha_abrir_arquivo_pedidos(void)
{
	system ("cls");
	printf ("FALHA AO ABRIR [%s]!", ARQUIVO_DE_PAGAMENTOS);
	getch();
	exit(0);
}

void  falha_abrir_arquivo_cartoes     (void)
{
	system ("cls");
	printf ("FALHA AO ABRIR [%s]!", ARQUIVO_DE_CARTOES);
	getch();
	exit(0);
}

void  falha_gravar_arquivo (void)
{
	system ("cls");
	printf ("FALHA AO GRAVAR [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void falha_gravar_arquivo_pagamentos (void)
{
	system ("cls");
	printf ("FALHA AO GRAVAR [%s]!", ARQUIVO_DE_PAGAMENTOS);
	getch();
	exit(0);
}

void  falha_gravar_arquivo_cartoes    (void)
{
	system ("cls");
	printf ("FALHA AO GRAVAR [%s]!", ARQUIVO_DE_CARTOES);
	getch();
	exit(0);
}

void  falha_ler_arquivo (void)
{
	system ("cls");
	printf ("FALHA AO LER [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void  falha_ler_arquivo_cartoes (void)
{
	system ("cls");
	printf ("FALHA AO LER [%s]!", ARQUIVO_DE_CARTOES);
	getch();
	exit(0);
}

void falha_ler_arquivo_pagamentos (void)
{
	system ("cls");
	printf ("FALHA AO LER [%s]!", ARQUIVO_DE_PAGAMENTOS);
	getch();
	exit(0);	
}

void  relatorio_produtos	(void)
{  FILE *A;
   registro_produto R;
   A = fopen (ARQUIVO_DE_PRODUTOS, "r");
   if (A==NULL)
      falha_abrir_arquivo();	   
   else
   {    printf ("\n-------------------------------------");
        printf ("\n          PRODUTOS CADASTRADOS       ");
        printf ("\n-------------------------------------");
   	    while ( !feof(A) )
   	    { 
		    fread (&R, sizeof(R), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo();
	        if ( !feof(A) )
	           printf ("\n%3d %-20s R$%5.2f", R.Codprod, R.Nomeprod, R.Custoprod);
	   }
	   fclose(A);
   }
   printf ("\n-------------------------------------\n");
   printf ("\nPressione qualquer tecla para retornar ao menu principal.");
   getch();
}

void  relatorio_pagamentos	(void)
{  FILE *A;
   registro_pagamento R;
   A = fopen (ARQUIVO_DE_PAGAMENTOS, "r");
   if (A==NULL)
      falha_abrir_arquivo_pedidos();
   else
   {    printf ("\n---------------------------------------------");
        printf ("\n            PAGAMENTOS EFETUADOS             ");
        printf ("\n---------------------------------------------");
        printf ("\n Cod pedido    Forma Pgto          Valor pago");
        printf ("\n---------------------------------------------");
   	    while ( !feof(A) )
   	    { 
		    fread (&R, sizeof(R), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo();
	        if ( !feof(A) )
	           printf ("\n%3d\t\t%-20s R$%6.2f", R.Codpgto, R.Formapgto, R.Valorpgto);
	   }
	   fclose(A);
   }
   printf ("\n---------------------------------------------");
   _sleep(200);
}

void  relatorio_cartoes	(void)
{  FILE *A;
   registro_cartao R;
   A = fopen (ARQUIVO_DE_CARTOES, "r");
   if (A==NULL)
      falha_abrir_arquivo_cartoes();
   else
   {    printf ("\n---------------------------------------------");
        printf ("\n       PAGAMENTOS EFETUADOS COM CARTÃO       ");
        printf ("\n---------------------------------------------");
        printf ("\n Cod pedido    Número do cartão ");
        printf ("\n---------------------------------------------");
   	    while ( !feof(A) )
   	    { 
		    fread (&R, sizeof(R), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo();
	        if ( !feof(A) )
	           printf ("\n%3d\t\t%-20s ", R.Codpgto, R.Numcartao);
	   }
	   fclose(A);
   }
   printf ("\n---------------------------------------------");
   printf ("\nPressione qualquer tecla para retornar ao menu principal.");
   getch();//_sleep(200);
}

int  menu_produtos	(void)
{  FILE *A;
   registro_produto R; 
   R.Codprod=0;
   A = fopen (ARQUIVO_DE_PRODUTOS, "r");
   if (A==NULL)
      falha_abrir_arquivo();	   
   else
   {    printf ("\n--------------------------------------");
        printf ("\n          PRODUTOS CADASTRADOS        ");
        printf ("\n--------------------------------------");
   	    while ( !feof(A) )
   	    { 
		    fread (&R, sizeof(R), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo();
	        if ( !feof(A) )
	           printf ("\n%3d %-20s R$%5.2f", R.Codprod, R.Nomeprod, R.Custoprod);
	   }
	   fclose(A);
   }
   printf ("\n--------------------------------------\n");
   return (R.Codprod);
}

registro_produto    captura_produto (void)
{
   registro_produto		rprod;
   printf ("\n------------ CADASTRO DE PRODUTO -----------------");
   rprod.Codprod = system("CalculaQtdRegistrosArquivo") + 1;
   printf ("\n Código  : %i", rprod.Codprod);
   printf ("\n Nome    : "); fflush (stdin); gets(rprod.Nomeprod);
   printf ("\n Custo  R$ "); fflush (stdin); scanf ("%f", &rprod.Custoprod);
   return (rprod);
}

char  confirmar (registro_produto R)
{
   char opc;
   printf ("\n\n[%3d][%s][R$%5.2f]", R.Codprod, R.Nomeprod, R.Custoprod);
   printf ("\n\nConfirma gravação do registro? [S=sim]");
   fflush (stdin); opc = getche();
   return (opc);
}

void  descartar (registro_produto R)
{
   printf ("\n\nRegistro descartado: [%3d][%s][R$%5.2f]", R.Codprod, R.Nomeprod, R.Custoprod);
   getch();
}

void  sucesso_gravacao (registro_produto R)
{
   printf ("\n\nRegistro [%3d][%s][R$%5.2f]", R.Codprod, R.Nomeprod, R.Custoprod);
   printf ("\n gravado com sucesso!\n\n");
   _sleep(200);
}

void sucesso_gravacao_cartao (registro_cartao R)
{
   printf ("\n\nCartão [%3d][%s]", R.Codpgto, R.Numcartao);
   printf ("\n gravado com sucesso!\n\n");
   _sleep(200);	
}

void pagamento_bemsucedido (registro_pagamento Rpgto)
{
   printf ("\n\nPAGAMENTO [%3d][%s][R$%5.2f]", Rpgto.Codpgto, Rpgto.Formapgto, Rpgto.Valorpgto);
   printf ("\n gravado com sucesso!\n\n");
   _sleep(200);	
}

void  grava_produto	(registro_produto R)
{
   FILE *A;
   char esc = confirmar(R);
   if ( esc == 'S' || esc == 's')
   {
       A = fopen (ARQUIVO_DE_PRODUTOS, "a");
	   if (A==NULL)
	      falha_abrir_arquivo();	   
	   else
	   {
	      fwrite (&R, sizeof(R), 1, A);
	      if ( ferror(A) )
	         falha_gravar_arquivo();
	   }
	   fclose(A);
	   sucesso_gravacao(R);
   }
   else
      descartar (R);
}

void  gravaCartao (registro_cartao R)
{
   FILE *A;
   A = fopen (ARQUIVO_DE_CARTOES, "a");
   if (A==NULL)
      falha_abrir_arquivo_cartoes();	   
   else
   {
      fwrite (&R, sizeof(R), 1, A);
      if ( ferror(A) )
         falha_gravar_arquivo_cartoes();
   }
   fclose(A);
   sucesso_gravacao_cartao(R);
}

void cadastra_produtos_default (void)
{
   registro_produto TAB[5] = 
   {  {1, "PRODUTO UM"     , 1.0},
   	  {2, "PRODUTO DOIS"   , 2.0},
   	  {3, "PRODUTO TRÊS"   , 3.0},
   	  {4, "PRODUTO QUATRO" , 4.0},
   	  {5, "PRODUTO CINCO"  , 5.0} };
  
   FILE * A = fopen (ARQUIVO_DE_PRODUTOS, "w");
   if (A==NULL)
      falha_abrir_arquivo();	   
   else
   {
       fwrite (&TAB, sizeof(TAB), 1, A);
	   if ( ferror(A) )
	      falha_gravar_arquivo();
   }
   fclose(A);
   printf ("\nProdutos default cadastrados com sucesso!");
   getch();
}

void PesquisaProduto    (registro_produto * R)
{  FILE *A;
   registro_produto Rler; 
   A = fopen (ARQUIVO_DE_PRODUTOS, "r");
   if (A==NULL)
      falha_abrir_arquivo();	   
   else
   {    
   	    while ( !feof(A) )
   	    { 
		    fread (&Rler, sizeof(Rler), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo();
	        if ( !feof(A) )
	           if ( R->Codprod == Rler.Codprod )
	              *R = Rler;
	   }
	   fclose(A);
   }
}

void PesquisaPagamento    (registro_pagamento * R)
{  FILE *A;
   registro_pagamento Rler; 
   A = fopen (ARQUIVO_DE_PAGAMENTOS, "r");
   if (A==NULL)
      falha_abrir_arquivo_pedidos();	   
   else
   {    
   	    while ( !feof(A) )
   	    { 
		    fread (&Rler, sizeof(Rler), 1, A);
            if ( ferror(A) )
	           falha_ler_arquivo_pagamentos();
	        if ( !feof(A) )
	           if ( R->Codpgto == Rler.Codpgto )
	           {
	              *R = Rler;
	              break;
	           }
	   }
	   fclose(A);
   }
}


void geraTicket(int nroPedido, int qtd, registro_pedido rped, float total, char flag)
{   FILE * Ticket;
    if (qtd==1)
         Ticket = fopen (ARQUIVO_TICKET, "w");
    else Ticket = fopen (ARQUIVO_TICKET, "a");
    if ( Ticket == NULL )
    { 	printf ("\nErro ao gerar TICKET.TXT");
    	getch();
	}
	else
	{   if (qtd==1)
        {	fprintf (Ticket, "\n+-----------------------------------------------------------+");
		    fprintf (Ticket, "\n|                %s             |", NOME_ESTABELECIMENTO);
		    fprintf (Ticket, "\n+-----------------------------------------------------------+");
		    fprintf (Ticket, "\n| Nro do pedido: %03i                                        |", nroPedido);
		    fprintf (Ticket, "\n+-----------------------------------------------------------+");
	   		fprintf (Ticket, "\n|Cód | Produto              | Custo Unit | Qtd | Valor item |");
	   		fprintf (Ticket, "\n+-----------------------------------------------------------+");
    	}
		if ( flag == '1' )
        {   fprintf (Ticket, "\n+-----------------------------------------------------------+");
		    fprintf (Ticket, "\n TOTAL R$ %5.2f  ", total);
		    fprintf (Ticket, "\n+-----------------------------------------------------------+");
		}
		else
		   fprintf (Ticket, "\n| %2i | %-20s | %10.2f | %3i | %10.2f |", 
		   rped.Prodped.Codprod, rped.Prodped.Nomeprod, rped.Prodped.Custoprod, rped.Qtd, rped.Valoritem);
		fclose (Ticket);
	}
}

int CalculaRegistrosArq(char *nomeArq)
{
   FILE *Arq;
   registro_pagamento R;
   int numero_registros;
   
   Arq = fopen (nomeArq, "r");
   if (Arq==NULL)
   {
      numero_registros = 0; /* O arquivo não existe */
   }
   else
   {   /* Calcula o tamanho do arquivo */
		if ( fseek (Arq, 0, SEEK_END) ) /* Aqui fseek tenta se posicionar no final do arquivo...*/
		{
           printf("\nERRO ao calcular o tamanho de arquivo!\n");
           getch();
           numero_registros = -1;
        }
        else
		{   /*...para que ftell 'conte' quantos bytes o arquivo tem */
		    /* Dividindo-se o total de bytes do arquivo pelo tamanho de cada registro */
		    /* tem-se o número de registros do arquivo. */
		    numero_registros =  ftell(Arq) / sizeof (R); 
  	    }
  	    /* Fecha o arquivo */
  	    fclose (Arq);
	}
    /* Para teste: avisa quantos bytes o arquivo tem 
    printf ("\nO arquivo [%s] tem [%i] registros.", ARQUIVO_DE_PAGAMENTOS, numero_registros);
    */   
    /* 'devolve' a quantidade de registros para o programa 'chamador'*/
	return (numero_registros); 
}

void registraPgto (registro_pagamento Rpgto, char flag)
{
	FILE * A;
	if ( flag == 't')
	   A = fopen (ULTIMO_PEDIDO, "w");
	else
	   A = fopen (ARQUIVO_DE_PAGAMENTOS, "a");
	if (A == NULL)
        falha_abrir_arquivo_pedidos();
	fwrite (&Rpgto, sizeof(Rpgto), 1, A );
	if (ferror(A))	
        falha_gravar_arquivo_pagamentos();
    else
       if ( flag != 't')
           pagamento_bemsucedido(Rpgto);
    fclose (A);
}

void resgataTemp (registro_pagamento *Rpgto)
{
	FILE * A;
    A = fopen (ULTIMO_PEDIDO, "r");
	if (A == NULL)
        falha_abrir_arquivo_pedidos();
	fread (Rpgto, sizeof(registro_pagamento), 1, A );
	if (ferror(A))	
        falha_ler_arquivo_pagamentos();
    fclose (A);
}

void solicitaCartao(registro_cartao *Rcart)
{   int i;
	printf ("\nDigite o nro do cartão: "); 
	for (i=0; i<TAMCARTAO; i++)
	{   do
		{
		   fflush (stdin); Rcart->Numcartao[i] = getche();
	    }while ( Rcart->Numcartao[i] <'0' || Rcart->Numcartao[i] > '9');
	}
}

void mascaraCartao(registro_cartao *Rcart)
{   int i;
	//1234 5678 9012 3456
	for (i=0; i<TAMCARTAO; i++)
	{   if ( i>3 && i<12 )
		   Rcart->Numcartao[i] = '*';
	}
	printf ("\nCartão a gravar:  %s", Rcart->Numcartao); getch();
}
