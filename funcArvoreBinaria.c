#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcArvoreBinaria.h"

#define TRUE 1
#define FALSE 0

struct info { // Cria estrutura com informações sobre os nós que vão estar presentes na árvore
	
	// Informações
	
	int id;
	
};

struct arvore { // Cria estrutura dos nós da árvore

	Info info; // Informações do nó
	
	Arvore* filho_esquerda; // Filho da esquerda
	
	Arvore* filho_direita; // Filho da direita
	
};

Arvore* criaArvore ( ) {
	
	return NULL; // Ele dá um valor nulo para a árvore para que a função de adicionar saiba que ela está vazia
	
}

void adicionaArvore ( Arvore** arvore, int id ) {
	
/*	Vai receber um endereço de memoria de um nodo
* 	e vai procurar o lugar dele na arvore, indo
* 	pro lado esquerdo ou direito de acordo com o valor
*/
	
	if ( (*arvore) == NULL ) { // Verifica se o espaço de memória atual está vazio para colocar o novo nó nele
		
		(*arvore) = (Arvore*) malloc ( sizeof ( Arvore ) ); // Cria um novo nó no espaço vazio
		
		if ( (*arvore) ) { // Se a alocação de memória for bem sucedida ele executa os comandos abaixo
			
			// Vai atribuir os dados no novo nó
			
			(*arvore)->info.id = id;
			
			(*arvore)->filho_esquerda = NULL; // Deixa o filho da esquerda como nulo para quando for fazer a inserção
			
			(*arvore)->filho_direita = NULL; // Deixa o filho da direita como nulo para quando for fazer a inserção
			
			printf ("\n%d alocado com sucesso !\n");
			
		}
		
		else { // Caso a alocação não for bem sucedida ele retorna uma mensagem de erro
			
			printf ("\nNao foi possivel criar um novo nó !\n");
			
		}
		
	}
	
	else { // Caso o espaço de memória esteja ocupado
		
		if ( id < (*arvore)->info.id ) {  // Verifica se o número a ser adicionado é menor que o número que está no espaço atual
			
			adicionaArvore ( &(*arvore)->filho_esquerda, id ); // Se for menor ele manda adicionar do lado esquerdo do nó atual
			
		}
		
		else if ( id > (*arvore)->info.id ) { // Verifica se o número a ser adicionado é maior que o número que está no espaço atual
			
			adicionaArvore ( &(*arvore)->filho_direita, id ); // Se for maior ele manda adicionar do lado direito do nó atual
			
		}
		
		else {
			
			printf ("\nNumero ja existe !\n");
			
		}
		
	}
	
}

Arvore** maiorDosMenores ( Arvore** arvore ) {
	
	if ( (*arvore)->filho_direita != NULL) { // Se o nó tiver um filho direito ele chama a função novamente para o seu filho direito
	
		return maiorDosMenores ( &(*arvore)->filho_direita ); // Chama a função novamente para o filho da direita do nó atual
	
	}
	
	return arvore; // Se ele não tiver filho direito ele retorna seu próprio endereço de memória

}

Arvore** menorDosMaiores ( Arvore** arvore ) {
	
	if ( (*arvore)->filho_esquerda != NULL) { // Se o nó tiver um filho esquerdo ele chama a função novamente para o seu filho esquerdo
	
		return menorDosMaiores ( &(*arvore)->filho_esquerda ); // Chama a função novamente para o filho da esquerda do nó atual
	
	}
	
	return arvore; // Se ele não tiver filho esquerdo ele retorna seu próprio endereço de memória

}

void removeArvore ( Arvore** arvore, int id ) { // Recebe um endereço de memória de uma árvore e a identificação do número a ser removido
	
	if ( (*arvore) ) { // Se a árvore não for nula
	
		if ( (*arvore)->info.id == id ) { // Se a árvore tiver a id do número procurado, ou seja, se achar o número
		
			if ( (*arvore)->filho_esquerda == NULL && (*arvore)->filho_direita == NULL ) { // Se o nó não tiver filhos simplesmente apaga o nó
				
				free ( (*arvore) );
				
				(*arvore) = NULL;
				
			}
		
			else { // Se o nó tiver filho direito vai procurar o menor filho do lado direito desse nó para herdar
				
				Info aux; // Registro para armazenar as informações do descendente
				
				if ( (*arvore)->filho_esquerda != NULL ) { // Se o nó a ser removido tiver filho esquerdo, ele vai procurar o maior do lado esquerdo
					
					Arvore** maior = maiorDosMenores ( &(*arvore)->filho_esquerda );
					
					aux.id = (*maior)->info.id; // Guarda as informações do descendente
					
				}
				
				else { // Caso contrário se o nó a ser removido tiver filho direito, ele vai procurar o menor do lado direito
					
					Arvore** menor = menorDosMaiores ( &(*arvore)->filho_direita );
					
					aux.id = (*menor)->info.id; // Guarda as informações do descendente
					
				}
				
				Arvore* novaArvore = ( Arvore* ) malloc ( sizeof ( Arvore ) ); // Cria um novo nó para ter as informações do herdeiro
				
				novaArvore->info.id = aux.id; // Guarda as informações do descendente no novo nó
				
				removeArvore ( &(*arvore), aux.id ); // Remove o descendente do seu antigo lugar
				
				novaArvore->filho_direita = (*arvore)->filho_direita; // O novo nó aponta para o filho da esquerda do nó a ser removido
			
				novaArvore->filho_esquerda = (*arvore)->filho_esquerda; // O novo nó aponta para o filho da direita do nó a ser removido
			
				free ( (*arvore) ); // Apaga o nó
				
				(*arvore) = NULL; // Limpa o nó
				
				(*arvore) = novaArvore; // A árvore agora vai apontar para o novo nó ( descendente )
				
			}
			
			printf ("\nRemovido com sucesso !\n");
		
		}
	
		else { // Caso o número não for o do nó atual
		
			if ( id < (*arvore)->info.id ) { // Se o número for menor que o número do nó atual
			
				removeArvore ( &(*arvore)->filho_esquerda, id ); // Chama a função para inserir do lado esquerdo do nó atual
			
			}
		
			else if ( id > (*arvore)->info.id ){ // Se o número for maior que o número do nó atual
			
				removeArvore ( &(*arvore)->filho_direita, id ); // Chama a função para inserir do lado esquerdo do nó atual
			
			}
		
		}
	
	}
	
	else { // Caso a função encontre uma árvore nula, ou seja, se ele chegar no fim da árvore e não encontrar o número
		
		printf ("\nNumero nao encontrado !\n");
		
	}
	
}

void imprimeArvore ( Arvore* arvore ) {
	
	if ( arvore ) { // Se o espaço de memória tiver algum nó
		
		printf ("( %d ", arvore->info.id); // Imprime o nó atual
		
		imprimeArvore ( arvore->filho_esquerda ); // Chama a função para imprimir os filhos da esquerda ( os filhos menores que o nó atual )
		
		imprimeArvore ( arvore->filho_direita ); // Chama a função para imprimir os filhos da direita ( os filhos maiores que o nó atual )
		
		printf (")"); // Finaliza os seus filhos
		
	}
	
}

void limpaArvore ( Arvore** arvore ) {
	
	if ( (*arvore) ) { // Se o espaço de memória tiver algum nó
		
		printf ("\n - Limpando %d - ", (*arvore)->info.id); // Imprime o nó que está limpando
		
		limpaArvore ( &(*arvore)->filho_esquerda ); // Limpa os filhos da esquerda
		
		limpaArvore ( &(*arvore)->filho_direita ); // Limpa os filhos da direita
		
		int arvoreId = (*arvore)->info.id; // Armazena o número do nó que está sendo limpo
		
		free ( (*arvore) ); // Apaga o nó
		
		(*arvore) = NULL; // Limpa o nó
		
		printf ("\n - %d Limpo", arvoreId); // Informa que o nó e seus filhos foram limpos
		
	}
	
}

void jump ( int n ) { // Função para quebrar linha
	
	if ( n > 0 ) { // Se ainda houver alguma linha para quebrar
		
		printf ("\n");
		
		jump ( n - 1 ); // Chama a função novamente até chegar em 0
		
	}

}

void getchPress ( ) { // Função para fazer pausa no programa
	
	jump ( 1 ); // Chama a função para quebrar linha
	
	printf ("Pressione qualquer tecla...");
	
	getch (); // Pausa o programa
	
}
