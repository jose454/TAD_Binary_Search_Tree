#include <stdio.h>
#include <stdlib.h>
#include "funcArvoreBinaria.h"

int main ( void ) {
	
	int option = 1, number;
	
	Arvore* arvore = criaArvore ( );
	
	while ( option != 5 ) { // Enquanto a opção for diferente de 0
		
		system ("cls");
		
		printf (" ----- Menu de Opcoes ----- \n\n");
		
		printf ("(1) Adicionar numero na arvore\n");
		
		printf ("(2) Remover numero da arvore\n");
		
		printf ("(3) Imprimir arvore\n");
		
		printf ("(4) Limpar arvore\n");
		
		printf ("(5) Encerrar programa\n");
		
		printf ("\nInforme a opcao: ");
		
		scanf ("%d", &option);
		
		switch ( option ) {
			
			case 1:
				
				jump ( 1 );
				
				printf ("Informe o numero: ");
				
				scanf ("%d", &number);
				
				adicionaArvore ( &arvore, number );
				
				getchPress ( );
				
				break;
				
			case 2:
				
				jump ( 1 );
				
				if ( arvore ) {
					
					imprimeArvore ( arvore );
					
					jump ( 2 );
				
					printf ("Informe o numero: ");
				
					scanf ("%d", &number);
				
					removeArvore ( &arvore, number );
				
				}
				
				else {
					
					printf ("Arvore vazia !");
					
					jump ( 1 );
					
				}
				
				getchPress ( );
				
				break;
				
			case 3:
				
				jump ( 1 );
				
				if ( arvore ) {
					
					imprimeArvore ( arvore );
					
				}
				
				else {
					
					printf ("Arvore vazia !");
					
				}
				
				jump ( 1 );
				
				getchPress ( );
				
				break;
				
			case 4:
				
				jump ( 1 );
				
				if ( arvore ) {
					
					limpaArvore (&arvore);
				
				}
				
				else {
					
					printf ("Arvore vazia !");
					
				}
				
				jump ( 1 );
				
				getchPress ( );
				
				break;
				
			case 5:
				
				jump ( 1 );
				
				printf ("Programa encerrado !");
				
				jump ( 1 );
				
				break;
				
			default:
				
				jump ( 1 );
				
				printf ("Opcao invalida !");
				
				jump ( 1 );
				
				getchPress ( );
				
		} 
		
	}
	
	if ( arvore ) {
		
		limpaArvore ( &arvore );
		
		jump ( 1 );
		
	}
	
	getchPress ( );
	
}
