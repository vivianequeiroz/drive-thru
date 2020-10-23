/* Bibliotecas */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

/* Protótipos de funções */
char 	menu 	(void);
void 	admin 	(char escolha);
int 	main	(void);

/* Construção de funções */
char  menu (void)
{
	char  opc;
	do
	{
	   system ("color 0e");
	   system ("cls");
	   printf ("\n------------- DRIVE THRU DO MICKEY & DONALD ------------");
	   printf ("\n            c => Cadastrar produtos                     ");
	   printf ("\n            r => Relatório de produtos                  ");
	   printf ("\n            g => Relatório de pagamentos                ");
	   printf ("\n            v => Vendas                                 ");
	   printf ("\n            p => Pague                                  ");
	   printf ("\n            f => Fila de espera                         ");
	   printf ("\n            e => Entrega do pedido                      ");
	   printf ("\n            s => SAIR                                   ");
	   printf ("\n--------------------------------------------------------");
	   printf ("\n            Selecione a opção desejada: ");
	   fflush (stdin); opc = getche();
	}
	while ( opc != 'C' && opc != 'c' && opc != 'R' && opc != 'r' && opc != 'G' && opc != 'g' &&
			opc != 'V' && opc != 'v' && opc != 'P' && opc != 'p' &&
			opc != 'F' && opc != 'f' && opc != 'E' && opc != 'e' &&
			opc != 'S' && opc != 's' );
	return (opc);	
}

void admin ( char escolha )
{
    system ("color e0");
	system ("cls");
	switch ( escolha )
	{
		case 'C': case 'c': system("DriveThru_Cadastro");	break;
		case 'R': case 'r': system("DriveThru_Relatorio"); 	break;
		case 'G': case 'g': system("DriveThru_RelatPgto"); 	break;
		case 'V': case 'v': system("DriveThru_Vendas"); 	break;
		case 'P': case 'p': system("DriveThru_Pague"); 		break;
		case 'F': case 'f': printf ("FILA"); 				break;
		case 'E': case 'e': system("DriveThru_Leve"); 		break;
		case 'S': case 's': exit(0); 						break;
	}
}

/* Corpo do programa*/
int 	main	(void)
{   char  esc;
	setlocale (LC_ALL, "");
	do
	{
		esc = menu();
		admin (esc);
	}
	while (esc != 'S' && esc != 's');
	return (0);
}
