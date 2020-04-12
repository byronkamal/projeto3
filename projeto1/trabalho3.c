/*
Estrutura de Dados 1.
  Turma B.
  Projeto 2.
  Alunos: Igor Guimarães Veludo         - 13/0028240
          Byron Kamal B Correa          - 15/0007281
          Gabriel Alves Soares de Souza - 15/0009917
  Professor: Matheus Mendelson
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Registro{
  char nomeCompleto[100];
  char celular[10];
  char endereco[100];
  unsigned int CEP;
  char dataNascimento[10];
  struct Registro *anterior;
  struct Registro *seguinte;
}registro;

registro *alocaNovoContato();
registro *inserirNovoRegistro();
registro *removerContato();
void visualizarRegistro();
void visualizarTodosRegistros();
registro *inicializarAgenda();
void salvarAgenda();
void freeAll();

int main(){
  FILE *ptr = NULL;
  registro *head;
  int resposta;

  head = inicializarAgenda(ptr);

  do{

    printf("Opcao 0 - Sair\n");
    printf("Opcao 1 - Inserir novo nome\n");
    printf("Opcao 2 - Remover contato\n");
    printf("Opcao 3 - Visualizar registro\n");
    printf("Opcao 4 - Visualizar todos os registros\n");

    scanf("%d", &resposta);
    switch (resposta) {
      case 0:
        salvarAgenda(head);
      break;
      case 1:
        head = inserirNovoRegistro(head);
      break;
      case 2:
        head = removerContato(head);
      break;
      case 3:
        visualizarRegistro(head);
      break;
      case 4:
        visualizarTodosRegistros(head);
      break;
      default:
        printf("Entre com um valor entre 0 e 4\n");
    }
  }while(resposta);

  fclose(ptr);
  freeAll(head);
  return 0;
}

registro *alocaNovoContado(){
  return malloc(sizeof(registro));
}

registro *inserirNovoRegistro(registro *head){
  registro *corrente;
  registro *antes;
  registro *novoRegistro = alocaNovoContado();

  scanf("%s", novoRegistro->nomeCompleto);
  scanf("%s", novoRegistro->celular);
  scanf("%s", novoRegistro->endereco);
  scanf("%s", novoRegistro->dataNascimento);
  scanf("%d", &novoRegistro->CEP);

  printf("registrado\n");

  if(head == NULL){
    head = novoRegistro;
  }
  else{
    corrente = head;
    while(corrente != NULL){
      if(strcmp(novoRegistro->nomeCompleto, corrente->nomeCompleto) > 0 && corrente->seguinte != NULL){
        corrente = corrente->seguinte;
      }
      else if(strcmp(novoRegistro->nomeCompleto, corrente->nomeCompleto) > 0 && corrente->seguinte == NULL){
        corrente->seguinte = novoRegistro;
        //antes->seguinte = novoRegistro;
        novoRegistro->anterior = corrente;
        novoRegistro->seguinte = NULL;
        break;
      }
      else if(strcmp(novoRegistro->nomeCompleto, corrente->nomeCompleto) < 0){
        if(corrente->anterior == NULL){
          head = novoRegistro;
          novoRegistro->anterior = NULL;
          novoRegistro->seguinte = corrente;
          corrente->anterior = novoRegistro;
        }
        else{
          antes = corrente->anterior;
          antes->seguinte = novoRegistro;
          novoRegistro->seguinte = corrente;
          novoRegistro->anterior = antes;
          corrente->anterior = novoRegistro;
        }
        break;
      }
    }
  }
  //printf("%s\n", head->nomeCompleto)

  return head;
}

registro *inicializarAgenda(FILE *ptr){
  registro *corrente;
  registro *head;
  registro *antes;
  char lixo[2];

  int primeiroRegistro = 1;

  if((ptr = fopen("contatos.txt", "r")) == NULL){
    return NULL;
  }

  while(!feof(ptr)){
    corrente = alocaNovoContado();
    fscanf(ptr, "%s\n%s\n%s\n%d\n%s\n%s\n", corrente->nomeCompleto, corrente->celular, corrente->endereco, &corrente->CEP, corrente->dataNascimento, lixo);
    //fscanf(ptr,"%s", &lixo);
    if(primeiroRegistro){
      head = corrente;
      antes = head;
      primeiroRegistro = 0;
    }
    else{
      antes->seguinte = corrente;
      corrente->anterior = antes;
      antes = corrente;
    }

  }
  return head;
}

void salvarAgenda(registro *head){
  registro *corrente = head;
  FILE *ptr = NULL;

  if(head == NULL)
    return;

  if((ptr = fopen("contatos.txt", "w")) == NULL){
    printf("Nao foi possivel abrir o aquivo.\n");
  }
  else{
    while(corrente != NULL){
      //printf("%15s %14p %14p %14p\n", corrente->nomeCompleto, corrente->anterior, corrente, corrente->seguinte);
      fprintf(ptr, "%s\n%s\n%s\n%d\n%s\n$\n", corrente->nomeCompleto, corrente->celular, corrente->endereco, corrente->CEP, corrente->dataNascimento);
      corrente = corrente->seguinte;
    }
  }
}

void freeAll(registro *head){
  registro *aux;
  registro *corrente = head;
  while(corrente->seguinte != NULL){
    aux = corrente;
    corrente = corrente->seguinte;
    free(aux);
  }
}

void visualizarTodosRegistros(registro *head){
registro* aux = head;
/* imprime primeiro elemento */
      printf("%s\n", aux->nomeCompleto);
      printf("%s\n", aux->celular);
      printf("%s\n", aux->endereco);
	  printf("%d\n", aux->CEP);
      printf("%s\n", aux->dataNascimento);

/* imprime sub-lista */
for (aux = head; aux != NULL; aux = aux->seguinte) {

	visualizarTodosRegistros(aux->seguinte);
	}
}

void visualizarRegistro(registro *head){
  char nome[100];
  registro *corrente = head;
  scanf("%s", nome);

  while(corrente != NULL){
    if(strcmp(corrente->nomeCompleto, nome) == 0){
      printf("%s\n", corrente->nomeCompleto);
      printf("%s\n", corrente->celular);
      printf("%s\n", corrente->endereco);
	  printf("%d\n", corrente->CEP);
      printf("%s\n", corrente->dataNascimento);
    }
    corrente = corrente->seguinte;
  }

  printf("Nome nao encontrado!\n");
}

registro *removerContato(registro *head){
  char nome[100];
  registro *corrente = head;
  registro *antes, *depois;
  scanf("%s", nome);

  while(corrente != NULL){
    antes = corrente->anterior;
    depois = corrente->seguinte;
    if(strcmp(corrente->nomeCompleto, nome) == 0){
      antes->seguinte = depois;
      depois->anterior = antes;
      return head;
    }
    corrente = corrente->seguinte;
  }

  printf("Nome nao encontrado!\n");
  return head;
}
