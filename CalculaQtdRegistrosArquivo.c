/* Bibliotecas */
#include "libDriveThru.h"

/* ========Corpo do programa========= */
int main()
{
   FILE *Arq;
   registro_produto R;
   int numero_registros;
   
   Arq = fopen (ARQUIVO_DE_PRODUTOS, "r");
   if (Arq==NULL)
   {
      falha_abrir_arquivo();	   
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
    printf ("\nO arquivo [%s] tem [%i] registros.", ARQUIVO_DE_PRODUTOS, numero_registros);
    */
    
    /* 'devolve' a quantidade de registros para o programa 'chamador'*/
	return (numero_registros); 
}
