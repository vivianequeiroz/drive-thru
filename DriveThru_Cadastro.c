/* Bibliotecas */
#include "libDriveThru.h"

/* Protótipos de funções */
int   main (void);

/* Corpo do programa */
int   main (void)
{	char  esc;
    setlocale (LC_ALL, "");
    printf ("\n[D] = cadastro Default? ");
    printf ("\n[Qualquer tecla] = cadastro sequencial");
    printf ("\nSua opção: ");  fflush (stdin); esc = getche();
    if ( esc == 'D' || esc == 'd' ) 
        cadastra_produtos_default ();
    else
    {
	  do
	  {
        system ("color 70");
	    system ("cls");
		grava_produto(captura_produto());
		printf ("\nCadastra outro produto? [S=sim]");
		fflush (stdin); esc = getche();
	  }
	  while (esc == 'S' || esc == 's');
	}
	return (0);
}
