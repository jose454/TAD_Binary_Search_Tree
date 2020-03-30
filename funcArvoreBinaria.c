#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcArvoreBinaria.h"

#define TRUE 1
#define FALSE 0

struct info { // Cria estrutura com informa��es sobre os n�s que v�o estar presentes na �rvore
	
	// Informa��es
	
	int id;
	
};

struct arvore { // Cria estrutura dos n�s da �rvore

	Info info; // Informa��es do n�
	
	Arvore* filho_esquerda; // Filho da esquerda
	
	Arvore* filho_direita; // Filho da direita
	
};

Arvore* criaArvore ( ) {
	
	return NULL; // Ele d� um valor nulo para a �rvore para que a fun��o de adicionar saiba que ela est� vazia
	
}

void adicionaArvore ( Arvore** arvore, int id ) {
	
/*	Vai receber um endere�o de memoria de um nodo
* 	e vai procurar o lugar dele na arvore, indo
* 	pro lado esquerdo ou direito de acordo com o valor
*/
	
	if ( (*arvore) == NULL ) { // Verifica se o espa�o de mem�ria atual est� vazio para colocar o novo n� nele
		
		(*arvore) = (Arvore*) malloc ( sizeof ( Arvore ) ); // Cria um novo n� no espa�o vazio
		
		if ( (*arvore) ) { // Se a aloca��o de mem�ria for bem sucedida ele executa os comandos abaixo
			
			// Vai atribuir os dados no novo n�
			
			(*arvore)->info.id = id;
			
			(*arvore)->filho_esquerda = NULL; // Deixa o filho da esquerda como nulo para quando for fazer a inser��o
			
			(*arvore)->filho_direita = NULL; // Deixa o filho da direita como nulo para quando for fazer a inser��o
			
			printf ("\n%d alocado com sucesso !\n");
			
		}
		
		else { // Caso a aloca��o n�o for bem sucedida ele retorna uma mensagem de erro
			
			printf ("\nNao foi possivel criar um novo n� !\n");
			
		}
		
	}
	
	else { // Caso o espa�o de mem�ria esteja ocupado
		
		if ( id < (*arvore)->info.id ) {  // Verifica se o n�mero a ser adicionado � menor que o n�mero que est� no espa�o atual
			
			adicionaArvore ( &(*arvore)->filho_esquerda, id ); // Se for menor ele manda adicionar do lado esquerdo do n� atual
			
		}
		
		else if ( id > (*arvore)->info.id ) { // Verifica se o n�mero a ser adicionado � maior que o n�mero que est� no espa�o atual
			
			adicionaArvore ( &(*arvore)->filho_direita, id ); // Se for maior ele manda adicionar do lado direito do n� atual
			
		}
		
		else {
			
			printf ("\nNumero ja existe !\n");
			
		}
		
	}
	
}

Arvore** maiorDosMenores ( Arvore** arvore ) {
	
	if ( (*arvore)->filho_direita != NULL) { // Se o n� tiver um filho direito ele chama a fun��o novamente para o seu filho direito
	
		return maiorDosMenores ( &(*arvore)->filho_direita ); // Chama a fun��o novamente para o filho da direita do n� atual
	
	}
	
	return arvore; // Se ele n�o tiver filho direito ele retorna seu pr�prio endere�o de mem�ria

}

Arvore** menorDosMaiores ( Arvore** arvore ) {
	
	if ( (*arvore)->filho_esquerda != NULL) { // Se o n� tiver um filho esquerdo ele chama a fun��o novamente para o seu filho esquerdo
	
		return menorDosMaiores ( &(*arvore)->filho_esquerda ); // Chama a fun��o novamente para o filho da esquerda do n� atual
	
	}
	
	return arvore; // Se ele n�o tiver filho esquerdo ele retorna seu pr�prio endere�o de mem�ria

}

void removeArvore ( Arvore** arvore, int id ) { // Recebe um endere�o de mem�ria de uma �rvore e a identifica��o do n�mero a ser removido
	
	if ( (*arvore) ) { // Se a �rvore n�o for nula
	
		if ( (*arvore)->info.id == id ) { // Se a �rvore tiver a id do n�mero procurado, ou seja, se achar o n�mero
		
			if ( (*arvore)->filho_esquerda == NULL && (*arvore)->filho_direita == NULL ) { // Se o n� n�o tiver filhos simplesmente apaga o n�
				
				free ( (*arvore) );
				
				(*arvore) = NULL;
				
			}
		
			else { // Se o n� tiver filho direito vai procurar o menor filho do lado direito desse n� para herdar
				
				Info aux; // Registro para armazenar as informa��es do descendente
				
				if ( (*arvore)->filho_esquerda != NULL ) { // Se o n� a ser removido tiver filho esquerdo, ele vai procurar o maior do lado esquerdo
					
					Arvore** maior = maiorDosMenores ( &(*arvore)->filho_esquerda );
					
					aux.id = (*maior)->info.id; // Guarda as informa��es do descendente
					
				}
				
				else { // Caso contr�rio se o n� a ser removido tiver filho direito, ele vai procurar o menor do lado direito
					
					Arvore** menor = menorDosMaiores ( &(*arvore)->filho_direita );
					
					aux.id = (*menor)->info.id; // Guarda as informa��es do descendente
					
				}
				
				Arvore* novaArvore = ( Arvore* ) malloc ( sizeof ( Arvore ) ); // Cria um novo n� para ter as informa��es do herdeiro
				
				novaArvore->info.id = aux.id; // Guarda as informa��es do descendente no novo n�
				
				removeArvore ( &(*arvore), aux.id ); // Remove o descendente do seu antigo lugar
				
				novaArvore->filho_direita = (*arvore)->filho_direita; // O novo n� aponta para o filho da esquerda do n� a ser removido
			
				novaArvore->filho_esquerda = (*arvore)->filho_esquerda; // O novo n� aponta para o filho da direita do n� a ser removido
			
				free ( (*arvore) ); // Apaga o n�
				
				(*arvore) = NULL; // Limpa o n�
				
				(*arvore) = novaArvore; // A �rvore agora vai apontar para o novo n� ( descendente )
				
			}
			
			printf ("\nRemovido com sucesso !\n");
		
		}
	
		else { // Caso o n�mero n�o for o do n� atual
		
			if ( id < (*arvore)->info.id ) { // Se o n�mero for menor que o n�mero do n� atual
			
				removeArvore ( &(*arvore)->filho_esquerda, id ); // Chama a fun��o para inserir do lado esquerdo do n� atual
			
			}
		
			else if ( id > (*arvore)->info.id ){ // Se o n�mero for maior que o n�mero do n� atual
			
				removeArvore ( &(*arvore)->filho_direita, id ); // Chama a fun��o para inserir do lado esquerdo do n� atual
			
			}
		
		}
	
	}
	
	else { // Caso a fun��o encontre uma �rvore nula, ou seja, se ele chegar no fim da �rvore e n�o encontrar o n�mero
		
		printf ("\nNumero nao encontrado !\n");
		
	}
	
}

void imprimeArvore ( Arvore* arvore ) {
	
	if ( arvore ) { // Se o espa�o de mem�ria tiver algum n�
		
		printf ("( %d ", arvore->info.id); // Imprime o n� atual
		
		imprimeArvore ( arvore->filho_esquerda ); // Chama a fun��o para imprimir os filhos da esquerda ( os filhos menores que o n� atual )
		
		imprimeArvore ( arvore->filho_direita ); // Chama a fun��o para imprimir os filhos da direita ( os filhos maiores que o n� atual )
		
		printf (")"); // Finaliza os seus filhos
		
	}
	
}

void limpaArvore ( Arvore** arvore ) {
	
	if ( (*arvore) ) { // Se o espa�o de mem�ria tiver algum n�
		
		printf ("\n - Limpando %d - ", (*arvore)->info.id); // Imprime o n� que est� limpando
		
		limpaArvore ( &(*arvore)->filho_esquerda ); // Limpa os filhos da esquerda
		
		limpaArvore ( &(*arvore)->filho_direita ); // Limpa os filhos da direita
		
		int arvoreId = (*arvore)->info.id; // Armazena o n�mero do n� que est� sendo limpo
		
		free ( (*arvore) ); // Apaga o n�
		
		(*arvore) = NULL; // Limpa o n�
		
		printf ("\n - %d Limpo", arvoreId); // Informa que o n� e seus filhos foram limpos
		
	}
	
}

void jump ( int n ) { // Fun��o para quebrar linha
	
	if ( n > 0 ) { // Se ainda houver alguma linha para quebrar
		
		printf ("\n");
		
		jump ( n - 1 ); // Chama a fun��o novamente at� chegar em 0
		
	}

}

void getchPress ( ) { // Fun��o para fazer pausa no programa
	
	jump ( 1 ); // Chama a fun��o para quebrar linha
	
	printf ("Pressione qualquer tecla...");
	
	getch (); // Pausa o programa
	
}
