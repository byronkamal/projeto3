#include <stdio.h>
#include <stdlib.h>

typedef struct agenda {
char nome[100];
char celular[9];
char endereco[100];
unsigned int cep;
char dataNascimento[10]; 

struct agenda* anterior;
struct agenda* proximo;
}Agenda;

Agenda* iniciaVazio(void) {
	return NULL;
}

Agenda* insereRegistro(Agenda* atual, char *nome, char *celular, char *endereco, unsigned int cep, char *dataNasc){
	Agenda* novo = (Agenda*) malloc(sizeof(Agenda));
	

	
	novo->proximo = atual;
	novo->anterior = NULL;
	
	if(atual != NULL) {
		atual->anterior = novo;
	}
	
	return novo;
}

int main() {

	Agenda* registro = (Agenda*) malloc(sizeof(Agenda));
	registro->cep = 555;
	registro->proximo = NULL;
	registro->anterior = NULL;
		
	gets(registro->nome);
	gets( registro->celular);
	gets(registro->endereco);
	gets(registro->dataNascimento);
	
	printf("%s %s %s %s", registro->nome, registro->celular, registro->endereco, registro->dataNascimento);
return 0;	
}
