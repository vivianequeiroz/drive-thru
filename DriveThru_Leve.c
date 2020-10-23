/* Bibliotecas */
#include "libDriveThru.h"

/* Protótipos de funções */
int   main (void);

/* Corpo do programa */
int main (void)
{	registro_pagamento Rpgto;
    setlocale (LC_ALL, "");    
	Rpgto.Codpgto = CalculaRegistrosArq(ARQUIVO_DE_PAGAMENTOS); 
	PesquisaPagamento(&Rpgto); 
    if ( strcmp(Rpgto.Formapgto, "Dinheiro") == 0 ) 
       system ("color 02");
    else
    if ( strcmp(Rpgto.Formapgto, "Cheque") == 0 ) 
       system ("color 01");
    else
       system ("color 0d");
    system ("cls");
    printf ("\nPEDIDO [%3i] PAGO COM %s", Rpgto.Codpgto, Rpgto.Formapgto);
    getch();
	return (0);
}
