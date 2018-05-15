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



int main () {


return 0;	
}
